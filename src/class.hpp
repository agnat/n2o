#ifndef N2O_CLASS_INCLUDED
#define N2O_CLASS_INCLUDED

#include "ctor.hpp"

namespace n2o {

enum no_ctor_t { no_ctor };

template <typename T>
class class_ {
    public:
        class_(const char * classname) :
            t_(v8::FunctionTemplate::New()),
            classname_(v8::String::NewSymbol(classname))
        {
            this->initialize(ctor<>());
        }
        ~class_() {
            detail::get_context()->Set( classname_, t_->GetFunction());
        }

        template <typename F>
        class_ &
        function(const char * name, F f) {
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
};

} // end of namespace n2o

#endif // N2O_CLASS_INCLUDED
