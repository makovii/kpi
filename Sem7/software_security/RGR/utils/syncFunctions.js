const crypto = require('crypto');

function encryptSync(sessionKey, message) {
  const iv = crypto.randomBytes(16);
  const cipher = crypto.createCipheriv('aes-256-cbc', sessionKey, iv);
  let encrypted = cipher.update(message);
  encrypted = Buffer.concat([encrypted, cipher.final()]);
  return { iv, encrypted };
}

function decryptSync(sessionKey, encrypted, iv) {
  const decipher = crypto.createDecipheriv('aes-256-cbc', sessionKey, iv);
  let decrypted = decipher.update(encrypted);
  decrypted = Buffer.concat([decrypted, decipher.final()]);
  return decrypted.toString();
}

exports.decryptSync = decryptSync;
exports.encryptSync = encryptSync;
