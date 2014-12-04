//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#include <iostream>
#include <n2o.hpp>

namespace {

using namespace n2o;

//=== Basic Functions ==========================================================

void void_void(void) {}
void void_int(int)   {}
int  int_void(void)  { return 5; }
int  int_int(int v)  { return v; }

void basic_functions(object exports) {
  exports["void_void"] = function(void_void);
  exports["void_int"]  = function(void_int);
  exports["int_void"]  = function(int_void);
  exports["int_int"]   = function(int_int);
}

//=== Rvalue Arguments =========================================================

bool bool_bool(bool b) { return b; }

int signed_char_short_int_long(
          signed char  a
        , signed short b
        , signed int   c
        , signed long  d)
{
    return a + b + c + d;
}
int unsigned_char_short_int_long(
          unsigned char  a
        , unsigned short b
        , unsigned int   c
        , unsigned long  d)
{
    return a + b + c + d;
}

double double_float_double(float a, double b) { return a + b; }

std::string string_string(std::string s) { return s; }
std::string string_string_constref(std::string const& s) { return s; }

void rvalue_arguments(object exports) {
    exports["bool_bool"]                    = function(bool_bool);
    exports["signed_char_short_int_long"]   = function(signed_char_short_int_long);
    exports["unsigned_char_short_int_long"] = function(unsigned_char_short_int_long);
    exports["double_float_double"]          = function(double_float_double);
    exports["string_string"]                = function(string_string);
    exports["string_string_constref"]       = function(string_string_constref);
}

//=== Function Names ===========================================================

void named_function() {}
void anonymous_function() {}

void function_names(object exports) {
    exports["named_function"] = function("function_with_a_name", named_function);
    exports["anonymous_function"] = function(anonymous_function);
}


} // end of anonymous namespace

//=== Init =====================================================================

N2O_ADD_ON(object exports) {
    basic_functions(exports);
    rvalue_arguments(exports);
    function_names(exports);
}
