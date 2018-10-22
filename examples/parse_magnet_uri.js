const lt = require('../');
const params = lt.parse_magnet_uri(process.argv[2]);

console.log('info hash', params.info_hash);
console.log('name', params.name);
console.log('trackers', params.trackers);
