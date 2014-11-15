#include <n2o/errors.hpp>

#include <v8.h>

namespace n2o {

error_already_set::~error_already_set() {}

void throw_error_already_set() {
    throw error_already_set();
}

void js_type_error(const char * msg) {
    v8::Isolate::GetCurrent()->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), msg)));
}

void js_error(const char * msg) {
    v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), msg)));
}

}