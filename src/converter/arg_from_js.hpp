#ifndef N2O_CONVERTER_ARG_FROM_JS_INCLUDED
#define N2O_CONVERTER_ARG_FROM_JS_INCLUDED

#include "rvalue_from_js_data.hpp"
#include "from_js.hpp"
#include "../detail/void_ptr.hpp"

#include "registered.hpp"

namespace n2o {
    
template <typename T> struct arg_from_js;


namespace converter {

struct dummy_converter {};

//=== rvalue ==================================================================

template <typename T>
struct arg_rvalue_from_js {
    // we can't add_const here, or it would be impossible to pass
    // auto_ptr<U> args from JS to C++
    typedef typename boost::add_reference<T>::type result_type;

    arg_rvalue_from_js(v8::Handle<v8::Value>);
    bool convertible() const;

    result_type operator()();
  private:
    rvalue_from_js_data<result_type> data_;
    v8::Handle<v8::Value> source_;
};

template <typename T>
struct select_arg_from_js {
    typedef arg_rvalue_from_js<T> type;
};

template <typename T>
inline
arg_rvalue_from_js<T>::arg_rvalue_from_js(v8::Handle<v8::Value> v) :
    data_(converter::rvalue_from_js_stage1(v, registered<T>::converters)), source_(v)
{}

template <typename T>
inline
bool
arg_rvalue_from_js<T>::convertible() const {
    return data_.stage1.convertible != 0;
}

template <typename T>
inline
typename arg_rvalue_from_js<T>::result_type
arg_rvalue_from_js<T>::operator()() {
    if (data_.stage1.construct != 0) 
        data_.stage1.construct(source_, &data_.stage1);

    return n2o::detail::void_ptr_to_reference(data_.stage1.convertible, (result_type(*)())0);
}

} // end of namespace converter

} // end of namespace n2o

#endif // N2O_CONVERTER_ARG_FROM_JS_INCLUDED
