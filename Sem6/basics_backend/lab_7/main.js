const express = require('express');
const app = express();
require('dotenv').config();
const hbs = require("hbs");
app.set('view engine', 'hbs');
const person = require('./router/person');
const task = require('./router/task');
const personApi = require('./router/personApi');
const taskApi = require('./router/taskApi');
const mongoose = require("mongoose");
hbs.registerPartials(__dirname + '/views/partials');
app.use(express.json());

const initRoutes = require("./router/img");
app.use(express.urlencoded({ extended: true }));
initRoutes(app);

app.use('', person);
app.use('', task);
app.use('', personApi);
app.use('', taskApi);

app.get('', async (req, res) => {
  res.render("home.hbs");
})

mongoose.connect(
  process.env.MONGODB_URI, 
  {
    useNewUrlParser: true,
    useUnifiedTopology: true,
    autoIndex: true, 
}
)


const db = mongoose.connection // .syncIndexes() ;
db.on("error", console.error.bind(console, "connection error: "));
db.once("open", function () {
  console.log("Connected successfully");
});


app.listen(3000, () => {
  console.log('http://localhost:3000');
})