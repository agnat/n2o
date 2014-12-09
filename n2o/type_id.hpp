//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_TYPE_ID_INCLUDED
# define N2O_TYPE_ID_INCLUDED

# include <n2o/settings.hpp>

# include <typeinfo>

# include <boost/operators.hpp>

namespace n2o {

struct type_info : private boost::totally_ordered<type_info> {
    inline type_info(std::type_info const& = typeid(void));

    inline bool operator<(type_info const& rhs) const;
    inline bool operator==(type_info const& rhs) const;

    char const* name() const;

    friend std::ostream & operator<<(std::ostream&, type_info const&);
private:
    typedef std::type_info const* base_id_t;

    base_id_t base_type_;
};

template <typename T>
inline
type_info
type_id() {
    return type_info(typeid(T));
}

inline
type_info::type_info(std::type_info const& id) : base_type_(&id) {}

inline
bool
type_info::operator<(type_info const& rhs) const {
    return base_type_->before(*rhs.base_type_);
}

inline
bool
type_info::operator==(type_info const& rhs) const {
    return *base_type_ == *rhs.base_type_;
}

namespace detail { char const* gcc_demangle(char const*); }

inline
char const* type_info::name() const {
    char const* mangled_name = base_type_->name();
    return detail::gcc_demangle(mangled_name);
}

std::ostream& operator<<(std::ostream&, type_info const&);

} // end of namespace n2o

#endif // N2O_TYPE_ID_INCLUDED
