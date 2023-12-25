import platform from '../img/platform.png';
import hills from '../img/hills.png';
import background from '../img/background.png';
import platformSmallTall from '../img/platformSmallTall.png';
import spriteRunLeft from '../img/spriteRunLeft.png';
import spriteRunRight from '../img/spriteRunRight.png';
import spriteStandLeft from '../img/spriteStandLeft.png';
import spriteStandRight from '../img/spriteStandRight.png';

const canvas = document.querySelector('canvas');
const c = canvas.getContext('2d');

canvas.width = 1024
canvas.height = 576

const gravity = 1;

class Player {
  constructor() {
    this.position = {x: 100, y: 100 };
    this.velocity = { x: 0, y: 0 };
    this.width = 66;
    this.height = 150;
    this.speed = 10;

    this.image = createImage(spriteStandRight);
    this.frames = 0;
    this.sprites = {
      stand: {
        right: createImage(spriteStandRight),
        left: createImage(spriteStandLeft),
        cropWidth: 177,
        width: 66,
      },
      run: {
        right: createImage(spriteRunRight),
        left: createImage(spriteRunLeft),
        cropWidth: 341,
        width: 127.875,
      }
    }

    this.currentSprite = this.sprites.stand.right;
    this.currentCropWidth = this.sprites.stand.cropWidth;
  }
  

  draw() {
    c.drawImage(
      this.currentSprite,
      this.currentCropWidth * this.frames,
      0,
      this.currentCropWidth,
      400,
      this.position.x,
      this.position.y,
      this.width,
      this.height);
  }

  update() {
    this.frames += 1;
    if (this.frames > 59 && (this.currentSprite === this.sprites.stand.right || this.currentSprite === this.sprites.stand.left)) {
      this.frames = 0;
    } else if (this.frames > 29 && (this.currentSprite === this.sprites.run.right
    || this.currentSprite === this.sprites.run.left)) {
      this.frames = 0;
    }
    this.draw();
    this.position.y += this.velocity.y;
    this.position.x += this.velocity.x;

    if (this.position.y + this.height + this.velocity.y <= canvas.height) {
      this.velocity.y += gravity;
    } else {
      // this.velocity.y = 0;
    }
  }
}

class Platform {
  constructor({ x, y, image }) {
    this.position = {
      x,
      y,
    };
    this.image = image;
    // this.image.width = 520;
    // this.image.height = 70;
    this.width = this.image.width; //image.weight;
    this.height = this.image.height //image.height;
    
  }

  draw() {
    c.drawImage(this.image, this.position.x, this.position.y);
  }
}

class GenericObject {
  constructor({ x, y, image }) {
    this.position = {
      x,
      y,
    };
    this.image = image;
    // this.image.width = 520;
    // this.image.height = 70;
    this.width = this.image.width; //image.weight;
    this.height = this.image.height //image.height;
    
  }

  draw() {
    c.drawImage(this.image, this.position.x, this.position.y);
  }
}

function createImage(path) {
  const image = new Image();
  image.src = path;
  image.width = 580;
  image.height = 70;

  console.log(image.width, image.height);  

  return image
}

function init() {
  platformImg = createImage(platform);
  platformSmallTallImg = createImage(platformSmallTall);

  player = new Player();
  platforms = [
    new Platform({ x: platformImg.width * 5 + 300 - 2 - platformSmallTallImg.width, y: 270, image: platformSmallTallImg }),
    new Platform({ x: -1, y: 470, image: platformImg }),
    new Platform({ x: platformImg.width - 3, y: 470, image: platformImg }),
    new Platform({ x: platformImg.width * 2 + 100, y: 470, image: platformImg }),
    new Platform({ x: platformImg.width * 3 + 300, y: 470, image: platformImg }),
    new Platform({ x: platformImg.width * 4 + 300 - 2, y: 470, image: platformImg }),
    new Platform({ x: platformImg.width * 5 + 700 - 2, y: 470, image: platformImg }),
  ];


  genericObjects = [
    new GenericObject({ x: -1, y: -1, image: createImage(background) }),
    new GenericObject({ x: -1, y: -1, image: createImage(hills) }),
  ]    

  scrollOffset = 0;
}

let platformImg = createImage(platform);
let platformSmallTallImg = createImage(platformSmallTall);

let player = new Player();
let platforms = [];
let genericObjects = []    

let lastKey;
const keys = {
  right: {
    pressed: false,
  },
  left: {
    pressed: false,
  }
}

let scrollOffset = 0;


function animate() {
  requestAnimationFrame(animate);
  c.fillStyle = "white";
  c.fillRect(0, 0, canvas.width, canvas.height);

  genericObjects.forEach(genericObject => {
    genericObject.draw();
  })

  platforms.forEach(platform => {
    platform.draw();  
  })
  
  player.update();

  if (keys.right.pressed && player.position.x < 400) {
    player.velocity.x = player.speed;
  } else if(keys.left.pressed && player.position.x > 100
    || keys.left.pressed && scrollOffset === 0 && player.position.x > 0) {
    player.velocity.x = -player.speed;
  } else {
    player.velocity.x = 0;

    if (keys.right.pressed) {
      scrollOffset += player.speed;
      platforms.forEach(platform => {
        platform.position.x -= player.speed;  
      })
      genericObjects.forEach(genericObject => {
        genericObject.position.x -= player.speed * 0.66;
      })
    } else if(keys.left.pressed &&  scrollOffset > 0) {
      scrollOffset -= player.speed;
      platforms.forEach(platform => {
        platform.position.x += player.speed;  
      })

      genericObjects.forEach(genericObject => {
        genericObject.position.x += player.speed * 0.66;
      })
    }
  }

  // platform collision detection
  platforms.forEach(platform => {
    if (player.position.y + player.height <= platform.position.y 
      && player.position.y + player.height + player.velocity.y >= platform.position.y
      && player.position.x + player.width >= platform.position.x
      && player.position.x <= platform.position.x + platform.width) {
      player.velocity.y = 0;
    }  
  })

  //sprite switching condition;
  if (keys.right.pressed && lastKey === 'right' && player.currentSprite !== player.sprites.run.right) {
    player.frames = 1;
    player.currentSprite = player.sprites.run.right;
    player.currentCropWidth = player.sprites.run.cropWidth;
    player.width = player.sprites.run.width;
  } else if (keys.left.pressed && lastKey === 'left' && player.currentSprite !== player.sprites.run.left) {
    player.currentSprite = player.sprites.run.left;
    player.currentCropWidth = player.sprites.run.cropWidth;
    player.width = player.sprites.run.width;
  }

  // win condition
  if (scrollOffset > 2000) {
    console.log("You win");
  }

  //lose condition
  if (player.position.y > canvas.height) {
    init()
  }
}

init();
animate();

window.addEventListener('keydown', ({ keyCode, key }) => {
  // console.log(keyCode, key)
  switch(true) {
    case (key === "a" || key === "ArrowLeft"):
      keys.left.pressed = true;
      lastKey = 'left'
      break

    case (key === "w" || key === "ArrowUp"):
      player.velocity.y -= 20
      break

    case (key === "d" || key === "ArrowRight"):
      keys.right.pressed = true;
      lastKey = 'right';
      break

    case (key ===  "s" || key === "ArrowDown"):
      break
  }
})

window.addEventListener('keyup', ({ keyCode, key }) => {
  // console.log(keyCode, key)
  switch(true) {
    case (key === "a" || key === "ArrowLeft"):
      keys.left.pressed = false;
      player.currentSprite = player.sprites.stand.left;
      player.currentCropWidth = player.sprites.stand.cropWidth;
      player.width = player.sprites.stand.width;
      break

    case (key === "w" || key === "ArrowUp"):
      // player.velocity.y -= 20
      break

    case (key === "d" || key === "ArrowRight"):
      keys.right.pressed = false;

      player.currentSprite = player.sprites.stand.right;
      player.currentCropWidth = player.sprites.stand.cropWidth;
      player.width = player.sprites.stand.width;
      break

    case (key ===  "s" || key === "ArrowDown"):
      break
  }
})
