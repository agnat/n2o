#ifndef N2O_OBJECTS_JS_FUNCTION_INCLUDED
# define N2O_OBJECTS_JS_FUNCTION_INCLUDED

# include <memory>
# include <boost/mpl/size.hpp>

# include <n2o/detail/signature.hpp>

namespace n2o { namespace objects {

struct js_function_impl_base {
    virtual ~js_function_impl_base();
    virtual v8::Handle<v8::Value> operator()(v8::FunctionCallbackInfo<v8::Value> const& args) = 0;
    virtual unsigned min_arity() const = 0;
    virtual unsigned max_arity() const;
    virtual detail::js_function_signature_info signature() const = 0;
};

template <typename Caller>
struct caller_js_function_impl : js_function_impl_base {
    caller_js_function_impl(Caller const& caller) : caller_(caller) {}

    v8::Handle<v8::Value> operator()(v8::FunctionCallbackInfo<v8::Value> const& args) {
        return caller_(args);
    }

    virtual unsigned min_arity() const {
        return caller_.min_arity();
    }

    virtual detail::js_function_signature_info signature() const {
        return caller_.signature();
    }
private:
    Caller caller_;
};

template <typename Caller, typename Sig>
struct signature_js_function_impl : js_function_impl_base {
    signature_js_function_impl(Caller const& caller) : caller_(caller) {}

    v8::Handle<v8::Value> operator()(v8::FunctionCallbackInfo<v8::Value> const& args) {
        return caller_(args);
    }

    virtual unsigned min_arity() const {
        return boost::mpl::size<Sig>::value - 1;
    }

    virtual detail::js_function_signature_info signature() const {
        detail::signature_element const* sig = detail::signature<Sig>::elements();
        detail::js_function_signature_info result = {sig, sig};
        return result;
    }
private:
    Caller caller_;
};

template <typename Caller, typename Sig>
struct full_js_function_impl: js_function_impl_base {
    full_js_function_impl(Caller const& caller, unsigned min_arity, unsigned max_arity)
        : caller_(caller)
        , min_arity_(min_arity)
        , max_arity_(max_arity)
    {}

    v8::Handle<v8::Value> operator()(v8::FunctionCallbackInfo<v8::Value> const& args) {
        return caller_(args);
    }

    virtual unsigned min_arity() const { return min_arity_; }
    virtual unsigned max_arity() const { return max_arity_; }
    
    virtual detail::js_function_signature_info signature() const {
        detail::signature_element const* sig = detail::signature<Sig>::elements();
        detail::js_function_signature_info result = {sig, sig};
        return result;
    }
private:
    Caller   caller_;
    unsigned min_arity_;
    unsigned max_arity_;
};

struct js_function {
    template <typename Caller>
    js_function(Caller const& caller)
        : impl_(new caller_js_function_impl<Caller>(caller))
    {}

    template <typename Caller, typename Sig>
    js_function(Caller const& caller, Sig)
        : impl_(new signature_js_function_impl<Caller, Sig>(caller))
    {}

    template <typename Caller, typename Sig>
    js_function(Caller const& caller, Sig, int min_arity, int max_arity = 0)
        : impl_(new full_js_function_impl<Caller, Sig>(caller, min_arity, max_arity))
    {}

    js_function(js_function const& rhs) : impl_(rhs.impl_) {}

    v8::Handle<v8::Value> operator()(v8::FunctionCallbackInfo<v8::Value> const& args) const {
        return (*impl_)(args);
    }

    unsigned min_arity() const { return impl_->min_arity(); }
    unsigned max_arity() const { return impl_->max_arity(); }

    virtual detail::signature_element const* signature() const {
        return impl_->signature().signature;
    }

    virtual detail::signature_element const* get_return_type() const {
        return impl_->signature().ret;
    }
private:
    mutable std::auto_ptr<js_function_impl_base> impl_;
};

}} // end of namespace n2o::objects

#endif // N2O_OBJECTS_JS_FUNCTION_INCLUDED
