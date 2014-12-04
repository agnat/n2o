//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#include <n2o/errors.hpp>

#include <boost/cast.hpp>
#include <v8.h>

#include <n2o/detail/exception_handler.hpp>

namespace n2o {

error_already_set::~error_already_set() {}

bool
handle_exception_impl(boost::function0<void> f) {
    try {
        if (detail::exception_handler::chain) {
            return detail::exception_handler::chain->handle(f);
        }
        f();
        return false;
    } catch (error_already_set const& ex) {
        // javascript error already set.
    } catch (const std::bad_alloc&) {
        js_error("memory allocation failed");
    } catch (const boost::bad_numeric_cast& x) {
        js_range_error(x.what());
    } catch (const std::out_of_range& x) {
        js_range_error(x.what());
    } catch (...) {
        js_error("unknown c++ exception");
    }
    return true;
}

void throw_error_already_set() {
    throw error_already_set();
}

void js_type_error(const char * msg) {
    v8::Isolate::GetCurrent()->ThrowException(
            v8::Exception::TypeError(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), msg)));
}

void js_error(const char * msg) {
    v8::Isolate::GetCurrent()->ThrowException(
            v8::Exception::Error(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), msg)));
}

void js_range_error(const char * msg) {
    v8::Isolate::GetCurrent()->ThrowException(
            v8::Exception::RangeError(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), msg)));
}

namespace detail {

bool exception_handler::operator()(boost::function0<void> const& f) const {
    if (next_) {
        return next_->handle(f);
    } else {
        f();
        return false;
    }
}

exception_handler::exception_handler(handler_function const& impl) :
      impl_(impl)
    , next_(0)
{
    if (chain != 0) {
        tail->next_ = this;
    } else {
        chain = this;
    }
    tail = this;
}

exception_handler * exception_handler::chain;
exception_handler * exception_handler::tail;

void
register_exception_handler(handler_function const& f) {
    // not actually leaked, as the object is hooked into a handler chain
    // by the constructor.
    new exception_handler(f);
}

} // end of namespace detail

} // end of namespace n2o
