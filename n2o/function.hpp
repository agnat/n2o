#ifndef N2O_FUNCTION_INCLUDED
#define N2O_FUNCTION_INCLUDED

#include <n2o/config.h>

#include <n2o/default_call_policies.hpp>
#include <n2o/detail/caller.hpp>
#include <n2o/detail/make_function.hpp>
//#include <n2o/object.hpp>

namespace n2o {

class function /*: public object */ {
public:
    template <typename F>
    explicit
    function(F f) : template_(detail::make_function(f, default_call_policies(), detail::get_signature(f))) {} 

    v8::Handle<v8::FunctionTemplate>
    function_template() const {
        return template_;
    }
private:
    v8::Local<v8::FunctionTemplate> template_;
};

/*
template <typename F>
v8::Local<v8::FunctionTemplate>
function(F f) {
    return detail::make_function(
            f, default_call_policies(), detail::get_signature(f));
}
*/
} // end of namespace n2o

#endif // N2O_FUNCTION_INCLUDED
