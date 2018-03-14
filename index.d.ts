
export declare interface add_torrent_params {
    save_path: string;
    ti: torrent_info;
}

export declare interface alert {
    message: string;
    type: number;
    what: string;
}

export declare interface torrent_alert extends alert {
    handle: torrent_handle;
}

export declare class torrent_info {
    constructor(fileName: string);
}

export declare class torrent_handle {
    status(): torrent_status;
}

export declare class torrent_status {
    download_rate(): number;
    info_hash(): string;
    name(): string;
    progress(): number;
    state(): number;
}

export declare class session {
    add_torrent(params: add_torrent_params): torrent_handle;
    pop_alerts(): Array<alert>;
    wait_for_alert(timeout: number, callback: (err: Error, result: boolean) => void): void;
}
