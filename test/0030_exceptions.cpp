//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#include <n2o.hpp>

#include <exception>
#include <stdexcept>
#include <boost/cast.hpp>

using namespace n2o;

//==============================================================================
void throw_bad_alloc() { throw std::bad_alloc(); }
void throw_bad_numeric_cast() { boost::numeric_cast<unsigned>(-1); }
void throw_out_of_range() { throw std::out_of_range("kaputt"); }


//==============================================================================
struct out_of_cheese : std::exception {
  char const* what() const throw() { return "out of cheese"; }
};
void translate(out_of_cheese const& ex) { js_error(ex.what()); }
void throw_out_of_cheese() { throw out_of_cheese(); }
void register_translator() {
    register_exception_translator<out_of_cheese>(translate);
}

//==============================================================================
N2O_ADD_ON(object exports) {
    exports["throw_bad_alloc"]        = function(throw_bad_alloc);
    exports["throw_bad_numeric_cast"] = function(throw_bad_numeric_cast);
    exports["throw_out_of_range"]     = function(throw_out_of_range);

    exports["throw_out_of_cheese"]    = function(throw_out_of_cheese);
    exports["register_translator"]    = function(register_translator);
}
