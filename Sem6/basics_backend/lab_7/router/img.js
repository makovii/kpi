const express = require("express");
const router = express.Router();
const homeController = require("../controller/home");
const uploadController = require("../controller/upload");

let routes = app => {
  router.get("/img", homeController.getHome);

  router.post("/img/upload", uploadController.uploadFiles);
  router.get("/img/files", uploadController.getListFiles);
  router.get("/img/files/:name", uploadController.download);

  return app.use("/", router);
};

module.exports = routes;