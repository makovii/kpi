const express = require('express');
const router = express.Router();
const personModel = require("../schemas/person");
var validator = require('validator');


router.post('/person', async (req, res) => {
  const person = new personModel(req.body);
    try {
      const validation = validator.isEmail(person.email);
      if (!validation) {
        res.status(400).send({ error: "not valid email address" });
      }
      await person.save();
      res.render("person.hbs", { person });
    } catch (e) {
      res.status(400).send({ error: e });
    }
})

router.get('/person', async (req, res) => {
  try {
    const persons = await personModel.find();
    res.render("person.hbs", { persons });
  } catch (e) {
    res.status(500).send(e);
  }
})

router.get('/person/:id', async (req, res) => {
  try {
    const id = req.params.id;
    const person = await personModel.find({ _id: id });
    res.render("person.hbs", { person });
  } catch (e) {
    res.status(500).send(e);
  }
})

router.put('/person/:id', async (req, res) => {
  try {
    const id = req.params.id;
    const body = req.body;
    const result = await personModel.updateOne({ _id: id }, { ...body });
    if (result.modifiedCount === 1) res.send({ message: "update was success" });
    else res.send({ message: "smth was wrong" });
  } catch (e) {
    res.status(500).send(e);
  }
})

router.delete('/person/:id', async (req, res) => {
  try {
    const id = req.params.id;
    const result = await personModel.deleteOne({ _id: id });
    if (result.deletedCount === 1) res.send({ message: "delete was success" });
    else res.send({ message: "smth was wrong" });
  } catch (e) {
    res.status(500).send(e);
  }
})


module.exports = router