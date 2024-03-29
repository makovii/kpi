const canvas = document.getElementById("game");
const ctx = canvas.getContext("2d");
const again = document.getElementById("again");

const againBtn = document.getElementById("againBtn");
const overlay = document.getElementById("overlay");
const popup = document.getElementById("popup");


againBtn.addEventListener("click", function () {
	window.location = "https://snake-d069d.web.app/";
});

const ground = new Image();
ground.src = "image/canvas.png";

const foodImg = new Image();
foodImg.src = "image/mango.png";

let box = 32;

let score = 0;

let food = {
	x: Math.floor((Math.random() * 17 + 1)) * box,
	y: Math.floor((Math.random() * 15 + 3)) * box,
};

let snake = [];
snake[0] = {
	x: 9 * box,
	y: 10 * box
};

document.addEventListener("keydown", direction);

let dir;

function direction(event) {
	if((event.keyCode == 37 || event.keyCode == 65 ) && dir != "right")
		dir = "left";
	else if((event.keyCode == 38 || event.keyCode == 87 ) && dir != "down")
		dir = "up";
	else if((event.keyCode == 39 || event.keyCode == 68 ) && dir != "left")
		dir = "right";
	else if((event.keyCode == 40 || event.keyCode == 83 ) && dir != "up")
		dir = "down";
}

function eatTail(head, arr) {
	for(let i = 0; i < arr.length; i++) {
		if(head.x == arr[i].x && head.y == arr[i].y) {
			clearInterval(game);
			popup.style.display = "block";
			overlay.style.display = "block"
		}
			
	}
}

function drawGame() {
	ctx.drawImage(ground, 0, 0);

	ctx.drawImage(foodImg, food.x, food.y);

	for(let i = 0; i < snake.length; i++) {
		ctx.fillStyle = i == 0 ? "green" : "red";
		ctx.fillRect(snake[i].x, snake[i].y, box, box);
	}

	ctx.fillStyle = "white";
	ctx.font = "50px Arial";
	ctx.fillText(`Score ${score}`, box * 1, box * 1.7);

	let snakeX = snake[0].x;
	let snakeY = snake[0].y;

	if(snakeX == food.x && snakeY == food.y) {
		score++;
		food = {
			x: Math.floor((Math.random() * 17 + 1)) * box,
			y: Math.floor((Math.random() * 15 + 3)) * box,
		};
	} else
		snake.pop();

	if(snakeX < box || snakeX > box * 17 || snakeY < 3 * box || snakeY > box * 17) {
		clearInterval(game);
		popup.style.display = "block";
		overlay.style.display = "block";
	}

	if(dir == "left") snakeX -= box;
	if(dir == "right") snakeX += box;
	if(dir == "up") snakeY -= box;
	if(dir == "down") snakeY += box;

	let newHead = {
		x: snakeX,
		y: snakeY
	};

	eatTail(newHead, snake);

	snake.unshift(newHead);
}

let game = setInterval(drawGame, 100);
