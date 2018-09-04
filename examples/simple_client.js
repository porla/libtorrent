const lt = require('../');
const fs = require('fs');

// Construct a session. Hold on to this.
const session = new lt.session({
    alert_mask: 4294967295,
    enable_dht: true
});

function alertHandler(err, result) {
    if (result) {
        const alerts = session.pop_alerts();

        for (const alert of alerts) {
            console.log(alert.message);
        }
    }

    session.wait_for_alert(500, alertHandler);
}

session.wait_for_alert(500, alertHandler);

const handle = session.add_torrent({
    save_path: __dirname,
    ti: new lt.torrent_info(process.argv[2])
});

function update() {
    console.log(handle.status().progress);
    setTimeout(update, 1000);
}

update();
