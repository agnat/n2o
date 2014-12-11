//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_VALUE_PROTOCOL_CORE_INCLUDED
# define N2O_VALUE_PROTOCOL_CORE_INCLUDED

# include <n2o/settings.hpp>

namespace n2o {
    
namespace api {

class value;

value getproperty(value const& target, value const& key);
void setproperty(value const& target, value const& key, value const& v);
void delproperty(value const& target, value const& key);

value getproperty(value const& target, char const* key);
void setproperty(value const& target, char const* key, value const& v);
void delproperty(value const& target, char const* key);

} // end of namespace api


using api::getproperty;
using api::setproperty;
using api::delproperty;

} // end of namespace n2o

#endif // N2O_VALUE_PROTOCOL_CORE_INCLUDED
