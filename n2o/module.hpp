#ifndef N2O_MODULE_HPP_INCLUDED_
#define N2O_MODULE_HPP_INCLUDED_

#include <node.h>

#include <n2o/object.hpp>

namespace n2o { namespace detail {


struct module_init {
    typedef void (*init_func)(n2o::object);
    module_init(init_func init, v8::Handle<v8::Object> exports) :
          init_(init)
        , exports_(exports)
    {}

    void operator()() const { init_(exports_); }
private:
    init_func init_;
    object    exports_;
};

}} // end of namespace n2o::detail

#define N2O_MODULE(args) N2O_NAMED_MODULE( N2O_MODULE_NAME, args )

#define N2O_NAMED_MODULE(name, args)                                        \
    void n2o_init_ ## name(args);                                           \
    void n2o_node_init_ ## name(v8::Handle<v8::Object> exports) {           \
        n2o::detail::module_init init_function(n2o_init_ ## name, exports); \
        n2o::handle_exception(init_function);                               \
    }                                                                       \
    NODE_MODULE(name, n2o_node_init_ ## name);                              \
    void n2o_init_ ## name( args )

#endif // N2O_MODULE_HPP_INCLUDED_
