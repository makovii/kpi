let history = {};

// encryption with Unicode
const encryptByUnicode = () => {
  const textinput = this.document.getElementById('text_input').value.split('');
  const textout = this.document.getElementById('text_out');
  const textunencrypt = this.document.getElementById('unencrypt');
  textout.innerHTML = '';
  const areacipher = this.document.createElement('span');
  textunencrypt.innerHTML = '';
  const areadecryption = this.document.createElement('span');
  const date = new Date().toLocaleString();

  const key = [];
  const text = textinput;

  const output = [];
  let unencrypt = [];
  const range = 1001;
  for (let i = 0; i < text.length; i += 1) {
    const random = Math.round(Math.random() * range);
    text[i] = String.fromCharCode(text[i].charCodeAt() + random);
    key[i] = random;
    output.push(text[i]);
  }
  history[date] = output;
  areacipher.innerText = output.join('');
  textout.appendChild(areacipher);

  // unencypt
  for (let i = 0; i < text.length; i += 1) {
    text[i] = String.fromCharCode(output[i].charCodeAt() - key[i]);
    unencrypt += text[i];
  }
  history[date] = unencrypt;
  areadecryption.innerText = unencrypt;
  textunencrypt.appendChild(areadecryption);
};

// asymmetric encryption
const asymmetricalCipher = () => {
  // get message, keys, create output element
  const input = this.document.getElementById('text_input').value.split('');
  const openkey = this.document.getElementById('open_key_field').value.split(' ');
  const output = this.document.getElementById('asymmetrical_cipher');
  output.innerHTML = '';
  const areacipher = this.document.createElement('span');

  const outputasymciphet = [];
  const date = new Date().toLocaleString();
  // create the first element to obfuscate the message
  const shift = BigInt(33);
  const time = BigInt(new Date().getDate());
  outputasymciphet[0] = time + shift;

  // I assign public key to variables
  const FirstKey = BigInt(openkey[0]);
  let SecondKey;
  // key verification
  try {
    SecondKey = BigInt(openkey[1]);
  } catch (e) {
    alert('Wrong Open Key');
    throw new Error('Wrong Open Key');
  }

  for (let i = 0; i < input.length; i += 1) {
    input[i] = input[i].charCodeAt();

    // asymmetric encryption
    outputasymciphet[i + 1] = ((BigInt(input[i]) ** FirstKey) % SecondKey) + time + shift;

    // entanglement
    outputasymciphet[i + 1] = (outputasymciphet[i + 1] + outputasymciphet[i]);
  }
  for (let i = 0; i < input.length + 1; i += 1) {
    outputasymciphet[i] = String.fromCharCode(Number(outputasymciphet[i]));
  }
  outputasymciphet.join('');
  history[date] = outputasymciphet;
  areacipher.innerText = outputasymciphet.join('');
  output.appendChild(areacipher);
};

// asymmetric decryption
const asymmetricalDecryption = () => {
  // get message, keys, create output element
  const input = this.document.getElementById('text_input').value.split('');
  const privatekey = this.document.getElementById('private_key_field').value.split(' ');
  const output = this.document.getElementById('asymmetrical_decryption');
  output.innerHTML = '';
  const areadecryption = this.document.createElement('span');
  const outputasymdecryption = [];
  const date = new Date().toLocaleString();

  // I assign private key to variables
  const FirstKey = BigInt(privatekey[0]);
  let SecondKey;
  // key verification
  try {
    SecondKey = BigInt(privatekey[1]);
  } catch (e) {
    alert('Wrong Private Key');
    throw new Error('Wrong Private Key');
  }

  for (let i = 0; i < input.length; i += 1) {
    input[i] = input[i].charCodeAt();
  }

  for (let i = 1; i < input.length; i += 1) {
    // untangling
    outputasymdecryption[i - 1] = input[i] - input[i - 1];
  }
  const shift = 33;
  // create the first element to obfuscate the message
  const time = new Date().getDate();

  for (let i = 0; i < input.length - 1; i += 1) {
    outputasymdecryption[i] -= time + shift;
    outputasymdecryption[i] = (BigInt(outputasymdecryption[i]) ** FirstKey) % SecondKey;
    outputasymdecryption[i] = String.fromCharCode(Number(outputasymdecryption[i]));
  }
  // outputasymdecryption.join(''); may be delete
  history[date] = outputasymdecryption.join('');
  areadecryption.innerText = outputasymdecryption.join('');
  output.appendChild(areadecryption);
};

// function for delete all elements of history
const deleteAll = () => {
  history = {};
};

// call functions by button
this.document.querySelector('button').onclick = encryptByUnicode;
this.document.getElementById('asym_cipher').onclick = asymmetricalCipher;
this.document.getElementById('asym_decryption').onclick = asymmetricalDecryption;

// check message for deletion
const chekOnDelete = () => {
  const text = this.document.getElementById('text_input').value;
  const checkLength = (text.length === 'delete n'.length) ? 1 : 0;
  const lastSymbol = parseInt(text[text.length - 1], 10);
  const checkNumber = !Number.isNaN(lastSymbol) ? 1 : 0;

  // исправить случай для одного удаления
  if (checkLength && checkNumber) {
    const ke = Object.keys(history);
    delete history[ke[lastSymbol - 1]];
  } else if (text === 'delete all') deleteAll();
};

// 500 change
setInterval(chekOnDelete, 500);

// encryption history by button
const historyText = this.document.getElementById('get_history');

// history is shown or not
let selector = 0;

historyText.addEventListener('click', () => {
  const out = this.document.getElementById('text_history');
  out.innerHTML = '';
  const span = this.document.createElement('span');
  const output = [];
  // let output = '';
  let count = 0;
  Object.keys(history).forEach((i) => {
    count += 1;
    output.push(`${count}) ${i} --- ${history[i]}\n`);
  });
  span.innerText = output.join('');
  out.appendChild(span);
  if (selector === 0) {
    // show history
    out.style.display = 'block';
    selector = 1;
  } else {
    // hide history
    out.style.display = 'none';
    selector = 0;
  }
});
