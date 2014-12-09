//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_JS_TYPE_INFO_INCLUDED
# define N2O_JS_TYPE_INFO_INCLUDED

# include <n2o/settings.hpp>

# include <v8.h>

namespace n2o {

struct js_type_info {
    explicit js_type_info(char const* name) : name_(name) {}
    char const* name() const;
private:
    char const* name_;
};

js_type_info const&
js_typeof(v8::Handle<v8::Value> v);

} // end of namespace n2o

#endif // N2O_JS_TYPE_INFO_INCLUDED
