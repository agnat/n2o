#include "n2o.hpp"

#include <iostream>

void greet() {std::cout << "greetingz" << std::endl;}

int int_f_void() { return -5; }
int int_f_int(int x) { return x; }

struct flux_compensator {
    void compensate() {}
    float current_flux;
};


using namespace n2o;

void init() {

    function("greet", greet);

    function("int_f_void", int_f_void);
    function("int_f_int", int_f_int);

    class_<flux_compensator>("FluxCompensator")
        . function("compensate", & flux_compensator::compensate)
        ;

    detail::get_signature(int_f_void);
}

N2O_NODE_MODULE(init);
