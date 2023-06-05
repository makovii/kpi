'use strict';

const btn = this.document.getElementById('copyText');
const btnForKey = this.document.getElementById('copyKey');
const textInput = this.document.getElementById('text_input');
const textInput1 = this.document.getElementById('text_input1');
const keyInput = this.document.getElementById('key_input');
const textOut = this.document.getElementById('text_out');
const textOutKey = this.document.getElementById('text_out1');
const textUnencrypt = this.document.getElementById('unencrypt');
const rad = this.document.getElementsByName('dzen');
textOut.innerHTML = '';
const characterSpan = this.document.createElement('span');
const characterSpan3 = this.document.createElement('span');
const allsymbols = '1234567890-=+[];/.<>~@#$^&()_!L:HAGWYIMNBCVXZSJ*"?№×÷|';
const string = allsymbols.split('');
textUnencrypt.innerHTML = '';
const characterSpan2 = this.document.createElement('span');

const checking = (expression) => {
  const english = /^[a-zA-Z0-9]+$/;
  const afterCheck = expression.split('');
  for (let i = 0; i < afterCheck.length; i += 1) {
    if (english.test(afterCheck[i])) {
      alert('Ангийский не подходит');
      throw new Error('Уупс!');
    }
  }
  if (!expression) {
    alert('Вы ничего не ввели');
    throw new Error('Уупс!');
  }
};

function randomInteger(min, max) {
  // получить случайное число от (min-0.5) до (max+0.5)
  const rand = min - 0.5 + Math.random() * (max - min + 1);
  return Math.round(rand);
}

const randomSymbol = () => { // функция генерации символа
  const rand = randomInteger(1, string.length - 1);
  const symbol = string[rand];
  string.splice(rand, 1);
  return symbol;
};

const generateKey = () => { // функия генерирования ключа
  const key = [];
  let randomNum = 0;
  const maxRandNum = 99;
  const maxSide = 10;
  const side = randomInteger(1, maxSide);
  for (let c = 0; c < side; c += 1) {
    randomNum = randomInteger(0, maxRandNum);
    key.push(randomNum);
  }
  const result1 = key.join('');
  return result1;
};

const result = {
  key: {
    name: '',
    code: 0,
  },
  coddingResult: 0,
};

const codding = () => { // функция кодировки
  checking(textInput.value);
  const alphabet = {
  };
  let res = textInput.value.split('');
  const lenght = res.length;
  const newAlphabet = alphabet;
  if (rad[1].checked) {
    const generatedKey = generateKey();// генерируем ключ
    for (let j = 0; j < lenght; j += 1) { // создаём алфавит символов в тексте
      alphabet[res[j]] = res[j];
    }

    Object.keys(newAlphabet).forEach((keys1) => { // генерируем рандомный символы для каждой буквы
      newAlphabet[keys1] = randomSymbol();
    });

    for (let i = 0; i < lenght; i += 1) { // кодируем наш текст
      // eslint-disable-next-line no-restricted-syntax
      for (const keys of Object.keys(alphabet)) {
        if (res[i] === keys) {
          res[i] = newAlphabet[keys];
        }
      }
    }

    res = res.join('');
    result.key.name = generatedKey;
    result.key.code = newAlphabet;
    result.coddingResult = res;
    characterSpan3.innerText = result.key.name;
    textOutKey.appendChild(characterSpan3);
    characterSpan.innerText = result.coddingResult;
    textOut.appendChild(characterSpan);
  }
  
  // вывод зашифрован текста
  if (rad[0].checked) {
    if (keyInput.value === result.key.name) {
      let resOfUncoding = textInput1.value.split('');
      for (let i = 0; i < resOfUncoding.length; i += 1) {
        for (const keys of Object.keys(result.key.code)) {
          if (resOfUncoding[i] === result.key.code[keys]) {
            resOfUncoding[i] = keys;
          }
        }
      }
      resOfUncoding = resOfUncoding.join('');
      characterSpan2.innerText = resOfUncoding;
      textUnencrypt.appendChild(characterSpan2);
    } else alert('Wrong key');
  }
};

btn.onclick = function copytext() {
  navigator.clipboard.writeText(result.coddingResult);
};

btnForKey.onclick = function copykey() {
  navigator.clipboard.writeText(result.key.name);
};

this.document.querySelector('button').onclick = codding;
