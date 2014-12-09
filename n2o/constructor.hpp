//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#ifndef N2O_CONSTRUCTOR_INCLUDED
# define N2O_CONSTRUCTOR_INCLUDED

# include <n2o/init.hpp>
# include <n2o/signature.hpp>
# include <n2o/detail/make_function.hpp>

namespace n2o {

enum no_init_t { no_init };

template <typename T>
class constructor {
public:
    constructor(const char * classname) :
        t_(v8::FunctionTemplate::New(v8::Isolate::GetCurrent())),
        classname_(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), classname))
    {
        this->initialize(init<>());
    }
    ~constructor() {
    }

    template <typename F>
    constructor &
    function(const char * name, F f) {
        v8::Local<v8::Function> function = detail::make_function(
                f, default_call_policies(), detail::get_signature(f, (T*)NULL));
        v8::Local<v8::String> symbol = v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), name);
        t_->PrototypeTemplate()->Set(symbol, function);
        return *this;
    }

    v8::Handle<v8::FunctionTemplate> function_template() const {
        return t_;
    }
private:
    v8::Local<v8::FunctionTemplate> t_;
    v8::Local<v8::String> classname_;

    template <typename Init>
    void
    initialize(Init const& init) {
        t_->SetClassName(classname_);
        t_->InstanceTemplate()->SetInternalFieldCount(1);
        t_->SetCallHandler(Init::call);
    }
    void
    initialize(no_init_t) {
        t_->SetClassName(classname_);
    }

    //detail::context_frame * ctx;
};

} // end of namespace n2o

#endif // N2O_CONSTRUCTOR_INCLUDED
