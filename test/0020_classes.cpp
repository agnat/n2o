#include <n2o.hpp>

using namespace n2o;

class world {
public:
    world() : greeting_("Hello") {}
    std::string greet() const { return greeting_ + " world."; }
private:
    std::string greeting_;
};

N2O_MODULE(object exports) {
    exports["World"] =
        class_<world>("World")
            . function("greet", &world::greet)
            ;
}
