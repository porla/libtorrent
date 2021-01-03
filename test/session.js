const assert = require('assert');
const lt = require('../');

describe('Session', function () {
    describe('is_paused', function () {
        it('should return false when session is not paused', function () {
            const session = new lt.session();
            assert.strictEqual(false, session.is_paused());
        });

        it('should return true when session is paused', function () {
            const session = new lt.session();
            session.pause();
            assert.strictEqual(true, session.is_paused());
        });
    });
});
