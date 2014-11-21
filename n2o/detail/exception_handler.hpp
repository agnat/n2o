#ifndef N2O_DETAIL_EXCEPTION_HANDLER_INCLUDED
#define N2O_DETAIL_EXCEPTION_HANDLER_INCLUDED

#include <boost/function/function0.hpp>
#include <boost/function/function2.hpp>

namespace n2o { namespace detail {

struct exception_handler;

typedef boost::function2< bool
                        , exception_handler const&
                        , boost::function0<void> const&> handler_function;

struct exception_handler {
    explicit exception_handler(handler_function const& impl);
    inline bool handle(boost::function0<void> const& f) const;
    bool operator()(boost::function0<void> const& f) const;

    static exception_handler * chain;
private:
    static exception_handler * tail;

    handler_function impl_;
    exception_handler * next_;
};

inline
bool
exception_handler::handle(boost::function0<void> const& f) const {
    return this->impl_(*this, f);
}

void
register_exception_handler(handler_function const& f);

}} // end of namespace n2o::detail

#endif // N2O_DETAIL_EXCEPTION_HANDLER_INCLUDED
