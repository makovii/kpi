class ChunkQueue {
  constructor() {
    this.queue = [];
    this.completedSend = 0;
    this.portion = 0;
  }

  enqueue(chunk) {
    this.queue.push(chunk);
  }

  dequeue() {
    return this.queue.shift();
  }

  isEmpty() {
    return this.queue.length === 0;
  }

  addSendCompleted(callback) {
    this.completedSend += 1;
    if (this.completedSend >= this.maxSend) callback();
  }

  setMaxSend(maxSend) {
    this.maxSend = maxSend;
  }

  setPortionSend(portion) {
    this.portion = portion;
  }
}

module.exports = ChunkQueue;
