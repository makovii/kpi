const mongoose = require("mongoose");

const personSchema = new mongoose.Schema({
  name: { type: String, required: true },
  surname: String,
  degreeId: { type: String, required: true },
  jobId: { type: String, required: true },
  audience: Number,
});

const Person = mongoose.model("person", personSchema);
module.exports = Person;