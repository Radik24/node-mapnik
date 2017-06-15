"use strict";

var mapnik = require('../');
var assert = require('assert');

// register fonts and datasource plugins
mapnik.register_default_fonts();
mapnik.register_default_input_plugins();

describe('mapnik.TimerStats', function() {

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


        it('should return an empty object if no work is done', function(done) {
            assert.deepEqual(mapnik.TimerStats.flush(), {});
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
                    var stats = mapnik.TimerStats.flush();
                    assert.ok(stats.total_map_rendering !== undefined);
                    assert.ok(stats.total_map_rendering.cpu_time > 0);
                    assert.ok(stats.total_map_rendering.wall_time > 0);
                    done();
                });
            });
        });
    });
});
