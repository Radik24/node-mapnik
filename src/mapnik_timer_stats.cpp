#include "mapnik_timer_stats.hpp"
#include <mapnik/performance_stats.hpp>

Nan::Persistent<v8::FunctionTemplate> TimerStats::constructor;

void TimerStats::Initialize(v8::Local<v8::Object> target) {
    Nan::HandleScope scope;

    v8::Local<v8::FunctionTemplate> lcons = Nan::New<v8::FunctionTemplate>(TimerStats::New);
    lcons->InstanceTemplate->SetInternalFieldCount(0);
    lcons->SetClassName(Nan::New("TimerStats").ToLocalChecked());

    // Static method
    Nan::SetMethod(lcons->GetFunction().As<v8::Object(), "flush", TimerStats::flush);

    target->Set(Nan::New("TimerStats").ToLocalChecked(),lcons->GetFunction());
    constructor.Reset(lcons);
}

NAN_METHOD(TimerStats::New){
    Nan::ThrowError("mapnik.TimerStats cannot be created directly");
    return;
}

NAN_METHOD(TimerStats::flush) {
    std::string stats = mapnik::timer_stats.flush();
    info.GetReturnValue().Set(Nan::New(stats));
}
