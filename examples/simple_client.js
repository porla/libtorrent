const lt = require('../');
const fs = require('fs');

let torrents = {};

const sp = new lt.session_params();
sp.settings.set_int('alert_mask', lt.alert.all_categories);
sp.settings.set_bool('enable_dht', true);
sp.settings.set_str('peer_fingerprint', lt.generate_fingerprint('XX', 1, 1));

// Construct a session. Hold on to this.
const session = new lt.session(sp);

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
    const params = new lt.add_torrent_params();
    params.save_path = './';
    params.ti = new lt.torrent_info(buf);

    session.async_add_torrent(params);
});

function update() {
    for (const hash in torrents) {
        const torrent = torrents[hash];
        const status = torrent.status();

        console.log(status.info_hash, status.progress);
    }
}

setInterval(update, 1000);
