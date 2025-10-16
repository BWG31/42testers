const assert = require('assert');
const makeRequest = require('../lib/makeRequest');

module.exports = function testHome(done) {
  makeRequest({ path: '/' }, (err, res) => {
    if (err)
		return done(err);
    assert.strictEqual(res.status, 200);
    console.log('✓ GET / returns 200');
    done();
  });
};
