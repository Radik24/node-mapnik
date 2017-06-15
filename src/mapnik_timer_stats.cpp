#include <string>
#include "mapnik_timer_stats.hpp"
#include <mapnik/performance_stats.hpp>

Nan::Persistent<v8::FunctionTemplate> TimerStats::constructor;

void TimerStats::Initialize(v8::Local<v8::Object> target) {
    Nan::HandleScope scope;

    v8::Local<v8::FunctionTemplate> lcons = Nan::New<v8::FunctionTemplate>(TimerStats::New);
    lcons->SetClassName(Nan::New("TimerStats").ToLocalChecked());

    // Static method
    Nan::SetMethod(lcons->GetFunction().As<v8::Object>(), "flush", TimerStats::flush);

    target->Set(Nan::New("TimerStats").ToLocalChecked(),lcons->GetFunction());
    constructor.Reset(lcons);
}

NAN_METHOD(TimerStats::New){
    Nan::ThrowError("mapnik.TimerStats cannot be created directly");
    return;
}

NAN_METHOD(TimerStats::flush) {
    auto stats = mapnik::timer_stats::instance().flush();
    v8::Local<v8::Object> stats_obj = Nan::New<v8::Object>();
    auto cpu_time_key = Nan::New<v8::String>("cpu_time").ToLocalChecked();
    auto wall_time_key = Nan::New<v8::String>("wall_time").ToLocalChecked();

    for (auto metric : stats) {
        auto key = metric.first;
        auto values = metric.second;
        v8::Local<v8::Object> metric_obj = Nan::New<v8::Object>();

        metric_obj->Set(cpu_time_key, Nan::New<v8::Number>(values.cpu_elapsed));
        metric_obj->Set(wall_time_key, Nan::New<v8::Number>(values.wall_clock_elapsed));

        stats_obj->Set(Nan::New<v8::String>(key).ToLocalChecked(), metric_obj);
    }

    info.GetReturnValue().Set(stats_obj);
}
