#ifndef N2O_CLASS_INCLUDED
#define N2O_CLASS_INCLUDED

#include "ctor.hpp"

namespace n2o {

// XXX duplicate
template <typename F, typename CallPolicies, typename Sig>
v8::Local<v8::FunctionTemplate>
make_function(F f, CallPolicies const& p, Sig signature) {
    return v8::FunctionTemplate::New(
              v8::Isolate::GetCurrent()
            , detail::caller<F, CallPolicies, Sig>::call
            , detail::caller<F, CallPolicies, Sig>::create(f)
            );
}

enum no_ctor_t { no_ctor };

template <typename T>
class class_ {
    public:
        class_(const char * classname) :
            t_(v8::FunctionTemplate::New(v8::Isolate::GetCurrent())),
            classname_(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), classname))
        {
            this->initialize(ctor<>());
            // XXX detail::get_context()->Set( classname_, t_->GetFunction());
        }
        ~class_() {
        }

        template <typename F>
        class_ &
        function(const char * name, F f) {
            /*
            v8::Local<v8::FunctionTemplate> t = detail::make_function(
                    f, default_call_policies(), detail::get_signature(f, (T*)NULL));
            t_->PrototypeTemplate()->Set(v8::String::NewSymbol(name), t);
            */
            return *this;
        }

    private:
        v8::Local<v8::FunctionTemplate> t_;
        v8::Local<v8::String> classname_;

        template <typename Ctor>
        inline
        void
        initialize(Ctor const& ctor) {
            t_->SetClassName(classname_);
            t_->InstanceTemplate()->SetInternalFieldCount(1);
            t_->SetCallHandler(Ctor::call);
        }
        inline
        void
        initialize(no_ctor_t) {
            t_->SetClassName(classname_);
        }

        //detail::context_frame * ctx;
};

} // end of namespace n2o

#endif // N2O_CLASS_INCLUDED
