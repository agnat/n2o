//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#include <n2o.hpp>

using namespace n2o;

class world {
public:
    world() : greeting_("Hello") {}
    std::string greet() const { return greeting_ + " world."; }
private:
    std::string greeting_;
};

N2O_ADD_ON(object exports) {
    exports["World"] = constructor<world>("World")
            . function("greet", &world::greet)
            ;
}
