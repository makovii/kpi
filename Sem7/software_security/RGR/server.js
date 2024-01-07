const fs = require('fs');
const forge = require('node-forge');
const net = require('net');
const path = require('path');
const crypto = require('crypto');
const generateMasterSecret = require('./utils/generateMasterSecret');
const { decryptSync, encryptSync } = require('./utils/syncFunctions');

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
  const filePath = path.join(__dirname, 'received_message.txt');
  const fileWriteStream = fs.createWriteStream(filePath);

  clientSocket.on('data', (data) => {
      const clientMessage = JSON.parse(data);
  
      if (clientMessage.message === "hello") {
        console.log("Hello from client: ", data.toString());

        const serverHello = {
          message: 'hello',
          certificate: fs.readFileSync(path.join(__dirname, 'keys', 'server-certificate.pem')),
          publicKey: publicKey,
        };
        clientSocket.write(JSON.stringify(serverHello));

      } else if (clientMessage.message === 'premaster') {
        const premaster = crypto.privateDecrypt(privateKey, Buffer.from(clientMessage.preMasterSecret));
        console.log("get premaster from client:", premaster);

        const label = 'master secret';
        const seed = Buffer.from('master secret', 'ascii');
        const length = 32; // Довжина master secret у байтах
        masterSecret = generateMasterSecret(premaster, label, seed, length);

        console.log("master secret in server:", masterSecret);

        clientSocket.write(JSON.stringify({ message: 'ready' }));
    
      } else if (clientMessage.message === 'ready') {
        const { iv: encIv, encrypted: encryptedMessage } = encryptSync(masterSecret, 'handshake is completed: said server');
        clientSocket.write(JSON.stringify({ message: 'complete', encryptedMessage, encIv }));

      } else if (clientMessage.message === 'complete') {
        const message = decryptSync(masterSecret, Buffer.from(clientMessage.encryptedMessage.data), Buffer.from(clientMessage.encIv.data));
        console.log("message from client:", message);
      } else if (clientMessage.message === 'file') {
        fileWriteStream.write(clientMessage.chunk);
      } else if (clientMessage.message === 'endFile') {
        fileWriteStream.end();
        console.log("file received");
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
