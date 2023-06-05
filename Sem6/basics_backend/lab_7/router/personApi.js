const express = require('express');
const router = express.Router();
const personModel = require("../schemas/person");
var validator = require('validator');



router.post('/api/person', async (req, res) => {
  const perosn = new personModel(req.body);
    try {
      const validation = validator.isEmail(perosn.email);
      if (!validation) {
        throw new Error("not valid email address");
      }

      await perosn.save();
      res.send(perosn);
    } catch (e) {
      res.send({ message: e.message });
    }
})

router.get('/api/person', async (req, res) => {
  try {
    const persons = await personModel.find();
    res.send(persons);
  } catch (e) {
    res.status(500).send(e);
  }
})

router.get('/api/person/:id', async (req, res) => {
  try {
    const id = req.params.id;
    const persons = await personModel.find({ _id: id });
    res.send(persons);
  } catch (e) {
    res.status(500).send(e);
  }
})

router.put('/api/person/:id', async (req, res) => {
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

router.delete('/api/person/:id', async (req, res) => {
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