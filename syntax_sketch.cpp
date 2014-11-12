
void foo() {};

struct Bar {
    void baz() {}
};

void
init(Exports exports) {
    exports["foo"] = function(foo);

    exports["Bar"] = function(ctor<Bar>());
    exports["Bar"].prototype["baz"] = function(Bar::baz);

}

