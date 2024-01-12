const net = require('net');
const crypto = require('crypto');
const fs = require('fs');
const path = require('path');
const forge = require('node-forge');
const generateMasterSecret = require('./utils/generateMasterSecret');
const { decryptSync, encryptSync } = require('./utils/syncFunctions');
const ChunkQueue = require('./utils/queue');

const options = {
  host: 'localhost',
  port: 3000,
  rejectUnauthorized: true,
  ca: fs.readFileSync(path.join(__dirname, 'keys', 'server-certificate.pem')),
};

let preMasterSecret;
let masterSecret;

const client = net.createConnection(options, () => {
    console.log('Connected to server.');

    // Step 1: Customer initiation
    const clientHello = {
      type: 'hello',
      code: crypto.randomBytes(48),
    };
    client.write(JSON.stringify(clientHello));
});

client.on('data', (data) => {
    const serverMessage = JSON.parse(data);

    if (serverMessage.type === "hello") {
      console.log("Hello from server: ", serverMessage);
      
      // const publicKey = forge.pki.publicKeyFromPem(String(serverMessage.publicKey));
      preMasterSecret = generatePremasterSecret();
      console.log("premaster in client:", preMasterSecret);
      const encrypted = crypto.publicEncrypt(serverMessage.publicKey, preMasterSecret);

      client.write(JSON.stringify({ type: "premaster", preMasterSecret: encrypted }));

      const label = 'master secret';
      const seed = Buffer.from('master secret', 'ascii');
      const length = 32; // Length master secret in bytes
      masterSecret = generateMasterSecret(preMasterSecret, label, seed, length);

      console.log("master secret in client:", masterSecret);

      client.write(JSON.stringify({ type: 'ready' }));
    } else if (serverMessage.type === 'ready') {
      const { iv: encIv, encrypted: encryptedMessage } = encryptSync(masterSecret, 'handshake is completed: said client');
      // send text
      client.write(JSON.stringify({ type: 'complete', encryptedMessage, encIv }));

      // send files
      const filePaths = [
        { 
          filePath: './sendFiles/1.txt',
          fileName: "1.txt"
        },
        { 
          filePath: './sendFiles/2.txt',
          fileName: "2.txt"
        },
        { 
          filePath: './sendFiles/3.txt',
          fileName: "3.txt"
        }];
      const chunkQueue = new ChunkQueue();
      chunkQueue.setMaxSend(filePaths.length);

      filePaths.forEach((filePathInfo) => {
        const fileStream = fs.createReadStream(filePathInfo.filePath);
        let chunkNumber = 1;

        fileStream.on('data', (chunk) => {
          const { iv: encIv, encrypted: encryptedMessage } = encryptSync(masterSecret, chunk);
            chunkQueue.enqueue({ filePath: filePathInfo.fileName, chunkNumber, encryptedMessage, endOfFile: false, type: 'file', encIv });
            chunkNumber++;
        });

        fileStream.on('end', () => {
            // Signal the end of file transmission
            chunkQueue.enqueue({ filePath: filePathInfo.fileName, chunkNumber, endOfFile: true, type: 'file' });
            chunkQueue.addSendCompleted(() => sendChunks(client, chunkQueue))
            
        });
    });

    } else if (serverMessage.type === 'complete') {
      const message = decryptSync(masterSecret, Buffer.from(serverMessage.encryptedMessage.data), Buffer.from(serverMessage.encIv.data));
      console.log("message from server:", message);
    }
    
});

client.on('end', () => {
  console.log('Connection closed.');
});

function generatePremasterSecret() {
  return crypto.randomBytes(32);
}

async function sendChunks(client, chunkQueue) {
  if (!chunkQueue.isEmpty()) {
    const { filePath, chunkNumber, chunk, endOfFile, type, encIv, encryptedMessage  } = chunkQueue.dequeue();
    const message = JSON.stringify({ filePath, chunkNumber, chunk, endOfFile, type, encIv, encryptedMessage  });
    console.log("message:", message);
    client.write(message)
    setTimeout( () => sendChunks(client, chunkQueue), 500)
  }
}
