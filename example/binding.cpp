#include "n2o.hpp"

#include <iostream>

void greet() {std::cout << "greetingz" << std::endl;}

int int_f_void() { return 5; }

struct flux_compensator {
    void compensate() {}
    float current_flux;
};


using namespace n2o;

N2O_MODULE(bttf) {

    function("greet", greet);

    function("int_f_void", int_f_void);

    class_<flux_compensator>("fluxCompensator")
        . function("compensate", & flux_compensator::compensate)
        ;

    detail::get_signature(int_f_void);
}
