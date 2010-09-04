#ifndef N2O_CLASS_INCLUDED
#define N2O_CLASS_INCLUDED

namespace n2o {

template <typename T>
struct class_ {
    class_(const char * classname) {}

    template <typename F>
    class_ &
    function(const char * name, F f) {
        return *this;
    }
};

} // end of namespace n2o

#endif // N2O_CLASS_INCLUDED
