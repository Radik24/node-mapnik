"use strict";

var mapnik = require('../');
var assert = require('assert');

describe('timer_stats', function() {

    it('flush should return an empty string', function(done) {
        assert.equal(mapnik.TimerStats.flush(), "");
        done();
    });
    
    it('test that you cant initialize a TimerStats', function() {
        assert.throws(function() { var l = new mapnik.TimerStats(); });
    });

});
