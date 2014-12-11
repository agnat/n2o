//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_PROXY_INCLUDED
# define N2O_PROXY_INCLUDED

# include <n2o/settings.hpp>

# include <n2o/value_core.hpp>
# include <n2o/value_operators.hpp>

namespace n2o { namespace api {

template <typename Policies>
class proxy : public value_operators<proxy<Policies> > {
    typedef typename Policies::key_type key_type;

public:
    proxy(value const& target, key_type const& key);
    operator value() const;

    proxy const&
    operator=(proxy const&) const;

    template <typename T>
    inline
    proxy const&
    operator=(T const& rhs) const {
        Policies::set(target_, key_, value(rhs));
        return *this;
    }

public: // implementation detail
    void del() const;
private:
    value    target_;
    key_type key_;
};

template <typename T>
inline
void
delete_(proxy<T> const& x) {
    x.del();
}

//=== Implementation ===========================================================

template <typename Policies>
inline
proxy<Policies>::proxy(value const& target, key_type const& key)
    : target_(target), key_(key)
{}

template <typename Policies>
inline
proxy<Policies>::operator value() const {
    return Policies::get(target_, key_);
}

template <typename Policies>
inline
proxy<Policies> const&
proxy<Policies>::operator=(proxy<Policies> const& rhs) const {
    return *this = n2o::value(rhs);
}

# define N2O_PROXY_INPLACE(op)                          \
template <typename Policies, typename R>                \
proxy<Policies> const&                                  \
operator op(proxy<Policies> const& lhs, R const& rhs) { \
    value old(lhs);                                     \
    return lhs = (old op rhs);                          \
}

N2O_PROXY_INPLACE(+=)
N2O_PROXY_INPLACE(-=)
N2O_PROXY_INPLACE(*=)
N2O_PROXY_INPLACE(/=)
N2O_PROXY_INPLACE(%=)
N2O_PROXY_INPLACE(<<=)
N2O_PROXY_INPLACE(>>=)
N2O_PROXY_INPLACE(&=)
N2O_PROXY_INPLACE(^=)
N2O_PROXY_INPLACE(|=)

# undef N2O_PROXY_INPLACE

template <typename Policies>
inline
void
proxy<Policies>::del() const {
    Policies::del(target_, key_);
}

}} // end of namespace n2o::api

#endif // N2O_PROXY_INCLUDED
