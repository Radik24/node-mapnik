"use strict";

var mapnik = require('../');
var assert = require('assert');

// register fonts and datasource plugins
mapnik.register_default_fonts();
mapnik.register_default_input_plugins();

describe('TimerStats', function() {

    it('test that you cannot initialize a TimerStats', function() {
        assert.throws(function() { var l = new mapnik.TimerStats(); });
    });

    describe('flush()', function() {
        before(function(done) {
            mapnik.TimerStats.flush();
            done();
        });

        after(function(done) {
            mapnik.TimerStats.flush();
            done();
        });


        it('should return an empty string if no map rendered', function(done) {
            assert.equal(mapnik.TimerStats.flush(), "");
            done();
        });

        it('returns some timing stats after rendering a map', function(done) {
            var map = new mapnik.Map(256, 256);
            map.load('./test/stylesheet.xml', function(err,map) {
                if (err) throw err;
                map.zoomAll();
                var im = new mapnik.Image(256, 256);
                map.render(im, function(err,im) {
                    if (err) throw err;
                    assert.ok(/^total_map_rendering/.test(mapnik.TimerStats.flush()));
                    done();
                });
            });
        });
    });
});
