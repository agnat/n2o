#include <n2o.hpp>

#include <stdexcept>
#include <boost/cast.hpp>

using namespace n2o;

void throw_bad_alloc() { throw std::bad_alloc(); }
void throw_bad_numeric_cast() { boost::numeric_cast<unsigned>(-1); }
void throw_out_of_range() { throw std::out_of_range("kaputt"); }

N2O_MODULE(object exports) {
    exports["throw_bad_alloc"]        = function(throw_bad_alloc);
    exports["throw_bad_numeric_cast"] = function(throw_bad_numeric_cast);
    exports["throw_out_of_range"]     = function(throw_out_of_range);
}
