const express = require('express');
const app = express();
require('dotenv').config();
const router = require('./router');
const mongoose = require("mongoose");
app.use(express.json());

app.use('', router);

mongoose.connect(
  process.env.MONGODB_URI, 
  {useNewUrlParser: true, useUnifiedTopology: true}
)


const db = mongoose.connection;
db.on("error", console.error.bind(console, "connection error: "));
db.once("open", function () {
  console.log("Connected successfully");
});


app.listen(3000, () => {
  console.log('http://localhost:3000');
})