const fs = require('fs');
const forge = require('node-forge');
const net = require('net');
const path = require('path');
const crypto = require('crypto');
const generateMasterSecret = require('./utils/generateMasterSecret');
const { decryptSync, encryptSync } = require('./utils/syncFunctions');
const ChunkQueue = require('./utils/queue');

// Example for generate keys and certificate
// function generateKeys() {
//   const keys = forge.pki.rsa.generateKeyPair({ bits: 2048, e: 0x10001 });

  // generate certificate
  // const cert = forge.pki.createCertificate();

  // cert.publicKey = keys.publicKey;
  // cert.serialNumber = '01';
  // cert.validity.notBefore = new Date();
  // cert.validity.notAfter = new Date();
  // cert.validity.notAfter.setFullYear(cert.validity.notBefore.getFullYear() + 1);

  // const attrs = [
  //   { name: 'commonName', value: 'localhost' },
  //   { name: 'countryName', value: 'UA' },
  //   { shortName: 'ST', value: '' },
  //   { name: 'localityName', value: 'Kyiv' },
  //   { name: 'organizationName', value: 'RGR' },
  //   { shortName: 'OU', value: 'R' },
  // ];
  // cert.setSubject(attrs);
  // cert.setIssuer(attrs);
  // cert.sign(keys.privateKey);


  // Save certificate, public and private key
  // fs.writeFileSync('keys/server-certificate.pem', forge.pki.certificateToPem(cert));
//   fs.writeFileSync('keys/server-private-key.pem', forge.pki.privateKeyToPem(keys.privateKey));
//   fs.writeFileSync('keys/server-public-key.pem', forge.pki.publicKeyToPem(keys.publicKey));

//   console.log('Keys generated successfully!');

//   return keys;
// }

const server = net.createServer((clientSocket) => {
  console.log('Client connected.');

  // Example for generate key
  // const keys = generateKeys();
  // const publicKeyInPem = forge.pki.publicKeyToPem(keys.publicKey);

  const { publicKey, privateKey } = crypto.generateKeyPairSync('rsa', {
    modulusLength: 2048, // Adjust the modulus length as needed
    publicKeyEncoding: { type: 'spki', format: 'pem' },
    privateKeyEncoding: { type: 'pkcs8', format: 'pem' }
  });

  let masterSecret;
  
  // prepare for get file
  const fileChunks = {};
  const chunkQueue = new ChunkQueue();
  const maxConcurrency = 3;  // Maximum number of files transmitted simultaneously

  clientSocket.on('data', (data) => {
      console.log("new message: ")
      const messages = data.toString().split('\n').filter((message) => message.trim() !== '');
      console.log(messages);
      const clientMessage = JSON.parse(data);
  
      if (clientMessage.type === "hello") {
        console.log("Hello from client: ", data.toString());

        const serverHello = {
          type: 'hello',
          certificate: fs.readFileSync(path.join(__dirname, 'keys', 'server-certificate.pem')),
          publicKey: publicKey,
        };
        clientSocket.write(JSON.stringify(serverHello));

      } else if (clientMessage.type === 'premaster') {
        const premaster = crypto.privateDecrypt(privateKey, Buffer.from(clientMessage.preMasterSecret));
        console.log("get premaster from client:", premaster);

        const label = 'master secret';
        const seed = Buffer.from('master secret', 'ascii');
        const length = 32; // Length master secret in bytes
        masterSecret = generateMasterSecret(premaster, label, seed, length);

        console.log("master secret in server:", masterSecret);

        clientSocket.write(JSON.stringify({ type: 'ready' }));
    
      } else if (clientMessage.type === 'ready') {
        const { iv: encIv, encrypted: encryptedMessage } = encryptSync(masterSecret, 'handshake is completed: said server');
        clientSocket.write(JSON.stringify({ type: 'complete', encryptedMessage, encIv }));

      } else if (clientMessage.type === 'complete') {
        const message = decryptSync(masterSecret, Buffer.from(clientMessage.encryptedMessage.data), Buffer.from(clientMessage.encIv.data));
        console.log("message from client:", message);
      } else if (clientMessage.type === 'file') {
        const { filePath, chunkNumber, chunk, endOfFile, encryptedMessage, encIv } = JSON.parse(data);

        chunkQueue.enqueue({ filePath, chunkNumber, chunk, endOfFile, encryptedMessage, encIv });

        // Start processing chunks
        processNextChunk(clientSocket, fileChunks, chunkQueue, maxConcurrency, masterSecret);
      } 
  });

  clientSocket.on('end', () => {
      console.log('Client disconnected.');
  });
});

const serverPort = 3000;
server.listen(serverPort, () => {
  console.log(`Server listening on port ${serverPort}`);
});


function processNextChunk(clientSocket, fileChunks, chunkQueue, maxConcurrency, masterSecret) {
  let currentConcurrency = 0;

  if (currentConcurrency < maxConcurrency && !chunkQueue.isEmpty()) {
      currentConcurrency++;

      const { filePath, chunkNumber, endOfFile, encryptedMessage, encIv } = chunkQueue.dequeue();
      // Check if the chunk indicates the end of file
      if (endOfFile) {
          // Write the accumulated chunks to the file
          if (filePath in fileChunks) {
              const accumulatedChunks = fileChunks[filePath][chunkNumber - 1] || [];
              const message = decryptSync(masterSecret, Buffer.from(accumulatedChunks[0].encryptedMessage), Buffer.from(accumulatedChunks[0].encIv));

              const filePathOnServer = path.join(__dirname, 'receiveFiles', filePath);
              fs.writeFileSync(filePathOnServer, message);

              // Signal the end of file transmission
              delete fileChunks[filePath];
          }

          currentConcurrency--;
          // Process the next chunk
          processNextChunk(clientSocket, fileChunks, chunkQueue, maxConcurrency);
      } else {
          // Accumulate the chunks
          if (!(filePath in fileChunks)) {
              fileChunks[filePath] = {};
          }
          if (!(chunkNumber in fileChunks[filePath])) {
              fileChunks[filePath][chunkNumber] = [];
          }
          fileChunks[filePath][chunkNumber].push({ encryptedMessage, encIv });

          // Process the next chunk
          processNextChunk(clientSocket, fileChunks, chunkQueue, maxConcurrency, masterSecret);
      }
  }
}
