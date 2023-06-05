'use strict';

const input = this.document.getElementById('input');
const label = this.document.getElementById('label');
const biba = this.document.getElementById('biba');
const buttonPassword = this.document.getElementById('button');
const massPassword = this.document.getElementById('mass-password');
const biba2 = this.document.getElementById('biba2');
const input2 = this.document.getElementById('input2');
const buttonCopy = this.document.getElementById('button2');

const generator = (len, settings) => {
  let str = '';
  if (settings.BigChungus) {
    str += 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
  }
  if (settings.SmallChungus) {
    str += 'abcdefghijklmnopqrstuvwxyz';
  }
  if (settings.Numbers) {
    str += '0123456789';
  }
  if (settings.Symbols) {
    str += 'a!@✝#$%^&*()_+№;:?-=卐';
  }
  let string = '';
  for (let i = 0; i < len; i += 1) {
    string += str[Math.round(Math.random() * (str.length - 1))];
    if (string === 'undefined') {
      alert('Choose at least one option');
      break;
    }
  }
  return string;
};

const checker = () => {
  const uppercase = this.document.getElementById('A-Z');
  const lowercase = this.document.getElementById('a-z');
  const number = this.document.getElementById('0-9');
  const symbs = this.document.getElementById('symbols');
  const objects = {
    BigChungus: uppercase.checked,
    SmallChungus: lowercase.checked,
    Numbers: number.checked,
    Symbols: symbs.checked,
  };
  label.value = generator(input.value, objects);
  function amountgenerator(len) {
    let res = '';
    if (len <= 1) {
      massPassword.style.display = 'none';
      buttonCopy.style.display = 'none';
    }
    if (len > 1) {
      buttonCopy.style.display = '';
      massPassword.style.display = '';
      for (let i = 0; i < len; i += 1) {
        res += generator(input.value, objects) + "\n" ;
      }
    }
    return res;
  }
  massPassword.textContent = amountgenerator(input2.value);
  biba.textContent = input.value;
  biba2.textContent = input2.value;
};

const copying = () => {
  const copyText = this.document.getElementById('label');
  copyText.select();
  this.document.execCommand('copy');
  alert('Copied password: ' + copyText.value);
};

const copying2 = () => {
  const copyText = this.document.getElementById('mass-password');
  copyText.select();
  this.document.execCommand('copy');
  alert('Copied the text: ' + copyText.value);
};

input.addEventListener('input', checker);
buttonPassword.addEventListener('click', checker);
label.addEventListener('click', copying);
checker();
input2.addEventListener('input', checker);
buttonCopy.addEventListener('click', copying2);
