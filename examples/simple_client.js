const lt = require('../');
const fs = require('fs');

let torrents = {};

// Construct a session. Hold on to this.
const session = new lt.session({
    alert_mask: 4294967295,
    enable_dht: true
});

function alertHandler(err, result) {
    if (result) {
        const alerts = session.pop_alerts();

        for (const alert of alerts) {
            switch (alert.what) {
                case "add_torrent":
                    torrents[alert.handle.info_hash()] = alert.handle;
                    break;
            }
        }
    }

    session.wait_for_alert(500, alertHandler);
}

session.wait_for_alert(500, alertHandler);

fs.readFile(process.argv[2], (err, buf) => {
    session.async_add_torrent({
        save_path: __dirname,
        ti: new lt.torrent_info(buf)
    });
});

function update() {
    for (const hash in torrents) {
        const torrent = torrents[hash];
        const status = torrent.status();

        console.log(status.info_hash, status.progress);
    }
}

setInterval(update, 1000);
