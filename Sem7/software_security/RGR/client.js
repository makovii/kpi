const net = require('net');
const crypto = require('crypto');
const fs = require('fs');
const path = require('path');
const forge = require('node-forge');
const generateMasterSecret = require('./utils/generateMasterSecret');
const { decryptSync, encryptSync } = require('./utils/syncFunctions');

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

    // Крок 1: Ініціювання клієнтом
    const clientHello = {
      message: 'hello',
      code: crypto.randomBytes(48),
    };
    client.write(JSON.stringify(clientHello));
});

client.on('data', (data) => {
    const serverMessage = JSON.parse(data);

    if (serverMessage.message === "hello") {
      console.log("Hello from server: ", serverMessage);
      
      // const publicKey = forge.pki.publicKeyFromPem(String(serverMessage.publicKey));
      preMasterSecret = generatePremasterSecret();
      // const encrypted = publicKey.encrypt(preMasterSecret);
      console.log("premaster in client:", preMasterSecret);
      const encrypted = crypto.publicEncrypt(serverMessage.publicKey, preMasterSecret);

      client.write(JSON.stringify({ message: "premaster", preMasterSecret: encrypted }));

      const label = 'master secret';
      const seed = Buffer.from('master secret', 'ascii');
      const length = 32; // Довжина master secret у байтах (зазвичай 48 байтів)
      masterSecret = generateMasterSecret(preMasterSecret, label, seed, length);

      console.log("master secret in client:", masterSecret);

      client.write(JSON.stringify({ message: 'ready' }));
    } else if (serverMessage.message === 'ready') {
      const { iv: encIv, encrypted: encryptedMessage } = encryptSync(masterSecret, 'handshake is completed: said client');
      // send text
      client.write(JSON.stringify({ message: 'complete', encryptedMessage, encIv }));

      // send file
      const fileReadStream = fs.createReadStream('message.txt');
      fileReadStream.on('readable', function() {
        let data;
        while (data = this.read()) {
          client.write(JSON.stringify({ message: 'file', chunk: data.toString() }));
        }
      });

      // Handle the end of the file stream
      fileReadStream.on('end', () => {
        console.log('File sent successfully.');
        client.write(JSON.stringify({ message: 'endFile' }));
      });
      fileReadStream.on('error', (error) => console.log(error))

    } else if (serverMessage.message === 'complete') {
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
