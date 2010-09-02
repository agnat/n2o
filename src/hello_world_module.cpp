#include "n2o.hpp"

#include "hello_world.hpp"

using namespace n2o;

N2O_MODULE(helloWorld) {

    function("greet", greet);

    class_<hello_world>("hello_world")
        . function("greet", & hello_world::greet)
        . function("bye",   & hello_world::bye)
        ;
}
