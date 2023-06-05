const express = require('express')
const app = express();
const hbs = require("hbs");
app.set('view engine', 'hbs');
require('dotenv').config();
const axios = require('axios');
const fs = require('fs');
hbs.registerPartials(__dirname + '/views/partials');

app.get('/', function (req, res) {
  res.render('home.hbs');
})


app.get('/whether', function (req, res) {
  const cities = JSON.parse(fs.readFileSync("cities.json"));
  const ip = req.ip === '::1' ? '77.75.149.62' : req.ip;
  axios.get(`http://api.weatherapi.com/v1/current.json?key=${process.env.API_KEY}&q=${ip}&aqi=no`)
  .then((response) => {
    res.render('whether.hbs', { cities, response });
  });
})

app.get('/whether/:city', (req, res) => {
  const cities = JSON.parse(fs.readFileSync("cities.json"));
  const city = req.params.city;

  axios.get(`http://api.weatherapi.com/v1/current.json?key=${process.env.API_KEY}&q=${city}&aqi=no`)
  .then((response) => {
    res.render('whether.hbs', { cities, response });
  });

})

app.listen(3000, () => {
  console.log('http://localhost:3000');
})