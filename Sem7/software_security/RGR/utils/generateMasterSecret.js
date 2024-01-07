const crypto = require('crypto');

function generateMasterSecret(preMasterSecret, label, seed, length) {
  const prfOutput = prf(preMasterSecret, label, seed, length);
  return prfOutput;
}

function prf(secret, label, seed, length) {
  const seedBuffer = Buffer.concat([Buffer.from(label, 'ascii'), seed]);
  let result = Buffer.alloc(0);
  let a = seedBuffer;

  while (result.length < length) {
    a = hmac(secret, a);
    result = Buffer.concat([result, hmac(secret, Buffer.concat([a, seedBuffer]))]);
  }

  return result.slice(0, length);
}

function hmac(key, data) {
  const hmac = crypto.createHmac('sha256', key);
  hmac.update(data);
  return hmac.digest();
}

module.exports = generateMasterSecret;
