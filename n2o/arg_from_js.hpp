#ifndef N2O_ARG_FROM_JS_INCLUDED
#define N2O_ARG_FROM_JS_INCLUDED

#include <n2o/converter/arg_from_js.hpp>

namespace n2o {

template <typename T>
struct arg_from_js : converter::select_arg_from_js<T>::type {
    typedef typename converter::select_arg_from_js<T>::type base;
    arg_from_js(v8::Handle<v8::Value>);
};

template <>
struct arg_from_js<v8::Handle<v8::Value> > {
    typedef v8::Handle<v8::Value> result_type;

    arg_from_js(v8::Handle<v8::Value> v) : source_(v) {}
    bool convertible() const { return true; }
    v8::Handle<v8::Value> operator()() const { return source_; }
  private:
    v8::Handle<v8::Value> source_;
};

template <class T>
inline
arg_from_js<T>::arg_from_js(v8::Handle<v8::Value> source) : base(source) {}

} // end of namespace n2o
#endif // N2O_ARG_FROM_JS_INCLUDED
