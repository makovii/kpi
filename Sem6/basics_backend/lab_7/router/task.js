const express = require('express');
const router = express.Router();
const taskModel = require("../schemas/task");


router.post('/task', async (req, res) => {
  const task = new taskModel(req.body);
    try {
      await task.save();
      res.render("task.hbs", { task });
    } catch (e) {
      res.send({ message: e.message });
    }
})

router.get('/task', async (req, res) => {
  try {
    const tasks = await taskModel.find();
    res.render("task.hbs", { tasks });
  } catch (e) {
    res.status(500).send(e);
  }
})

router.get('/task/:id', async (req, res) => {
  try {
    const id = req.params.id;
    const task = await taskModel.find({ _id: id });
    res.render("task.hbs", { task });
  } catch (e) {
    res.status(500).send(e);
  }
})

router.put('/task/:id', async (req, res) => {
  try {
    const id = req.params.id;
    const body = req.body;
    const result = await taskModel.updateOne({ _id: id }, { ...body });
    if (result.modifiedCount === 1) res.send({ message: "update was success" });
    else res.send({ message: "smth was wrong 2" });
  } catch (e) {
    console.log(e)
    res.status(500).send(e);
  }
})

router.delete('/task/:id', async (req, res) => {
  try {
    const id = req.params.id;
    const result = await taskModel.deleteOne({ _id: id });
    if (result.deletedCount === 1) res.send({ message: "delete was success" });
    else res.status(200).send({ message: "smth was wrong" });
  } catch (e) {
    res.status(500).send(e);
  }
})


module.exports = router