const {EventEmitter} = require("events");

const binding = require("pkg-prebuilds")(
  __dirname,
  require("./binding-options")
);

Object.setPrototypeOf(binding.Session.prototype, EventEmitter.prototype);

module.exports = binding;
