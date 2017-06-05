#ifndef __NODE_MAPNIK_TIMER_STATS_H__
#define __NODE_MAPNIK_TIMER_STATS_H__

#include <nan.h>

// Forward declaration of mapnik TimerStats
namespace mapnik { class TimerStats; }

class TimerStats: public Nan::ObjectWrap {
public:
    static Nan::Persistent<v8::FunctionTemplate> constructor;

    static void Initialize(v8::Local<v8::ObjectWrap> target);

    static NAN_METHOD(New);

    static NAN_METHOD(flush);
    
private:
    TimerStats();
    ~TimerStats();
};

#endif
