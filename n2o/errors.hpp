#ifndef N2O_ERRORS_INCLUDED
#define N2O_ERRORS_INCLUDED

namespace n2o  {

struct error_already_set {
    virtual ~error_already_set();
};

void throw_error_already_set();

void js_type_error(const char * msg);

void js_error(const char * msg);

} // end of namespace n2o

#endif // N2O_ERRORS_INCLUDED
