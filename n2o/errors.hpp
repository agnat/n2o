#ifndef N2O_ERRORS_INCLUDED
#define N2O_ERRORS_INCLUDED

#include <boost/function/function0.hpp>

namespace n2o  {

struct error_already_set {
    virtual ~error_already_set();
};

bool handle_exception_impl(boost::function0<void>);

template <typename T>
bool
handle_exception(T f) {
    return handle_exception_impl(boost::function0<void>(boost::ref(f)));
}

namespace detail { inline void rethrow() { throw; } }

inline
void
handle_exception() {
    handle_exception(detail::rethrow);
}

void throw_error_already_set();

void js_type_error(const char * msg);
void js_range_error(const char * msg);

void js_error(const char * msg);

} // end of namespace n2o

#endif // N2O_ERRORS_INCLUDED
