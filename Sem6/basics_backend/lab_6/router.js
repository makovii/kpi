const express = require('express');
const router = express.Router();
const personModel = require("./schemas/person");


router.post('/person', async (req, res) => {
  const perosn = new personModel(req.body);
    try {
      await perosn.save();
      res.send(perosn);
    } catch (e) {
      res.status(500).send(e);
    }
})

router.get('/person', async (req, res) => {
  try {
    const persons = await personModel.find();
    res.send(persons);
  } catch (e) {
    res.status(500).send(e);
  }
})

router.get('/person/:id', async (req, res) => {
  try {
    const id = req.params.id;
    const persons = await personModel.find({ _id: id });
    res.send(persons);
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