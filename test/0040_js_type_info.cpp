//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================

#include <string>

#include <n2o.hpp>
#include <n2o/tap.hpp>

using namespace n2o;

void test_js_type_info(v8::FunctionCallbackInfo<v8::Value> const& args) {
    tap t(args[0]);
    t.plan(7);

    t.ok(std::string(js_typeof(v8::Undefined(args.GetIsolate())).name()) == "undefined");
    t.ok(std::string(js_typeof(v8::Null(args.GetIsolate())).name()) == "object");
    t.ok(std::string(js_typeof(v8::Boolean::New(args.GetIsolate(),true)).name()) == "boolean");
    t.ok(std::string(js_typeof(v8::Number::New(args.GetIsolate(),0)).name()) == "number");
    t.ok(std::string(js_typeof(v8::String::NewFromUtf8(args.GetIsolate(),"")).name()) == "string");
    t.ok(std::string(js_typeof(v8::Symbol::New(args.GetIsolate())).name()) == "symbol");
    t.ok(std::string(js_typeof(v8::Object::New(args.GetIsolate())).name()) == "object");

    t.end();
}

N2O_ADD_ON(object exports) {
    exports["test_js_type_info"] = v8::Function::New(v8::Isolate::GetCurrent(), test_js_type_info);
}
