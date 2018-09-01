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
            // console.log(alert.message);
        }
    }

    session.wait_for_alert(500, alertHandler);
}

fs.readFile(process.argv[2], (err, buf) => {
    const meta = lt.bdecode(buf);
    console.log(meta);
});

session.wait_for_alert(500, alertHandler);

// The torrent_handle representing our
// added torrent.
const handle = session.add_torrent({
    save_path: "./",
    ti: new lt.torrent_info(process.argv[2])
});

function update() {
    const status = handle.status();

    if (status.errc) {
        console.error(status.errc.message);
        return;
    }

    console.log(session.listen_port());

    if (status.progress >= 1) {
        console.log('finished');
    } else {
        setTimeout(update, 1000);
    }
}

update();
