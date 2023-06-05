const mongoose = require("mongoose");

const personSchema = new mongoose.Schema({
  name: { type: String, required: true, trim: true },
  surname: { type: String, trim: true },
  degreeId: { type: String, required: true },
  jobId: { type: String, required: true },
  audience: { 
    type: Number,
    default: 0,
    validate(value) {
      if (value <= 0) throw new Error('audience number must be positive')
    }
  },
  email: { type: String, lowercase: true, unique: true },
  password: { type: String, required: true, trim: true, minLength: 7,
    validate(value) {
      if(value === 'password' || value === 'PASSWORD') {
        throw new Error('password must not contain "password"')
      }
    }
  },
});

const Person = mongoose.model("person", personSchema);
module.exports = Person;

