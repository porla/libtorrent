const {arch, platform} = require('os');
const path = require('path');
const prebuild = path.join(__dirname, 'prebuilds', `${platform()}-${arch()}`, 'node-napi.node');

module.exports = require(prebuild);
