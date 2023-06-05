const mongoose = require("mongoose");

const taskSchema = new mongoose.Schema({
  description: { type: String, require: true },
  completed: { type: Boolean, default: false },
  user_id: { type: mongoose.Schema.ObjectId, ref: 'person' },
});

const Task = mongoose.model("task", taskSchema);
module.exports = Task;