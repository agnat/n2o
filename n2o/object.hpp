#ifndef N2O_OBJECT_INCLUDED
#define N2O_OBJECT_INCLUDED

namespace n2o {

namespace detail {

struct property_value {
  property_value(v8::Handle<v8::Object> o, const char * name) : obj_(o), name_(name) {}

  v8::Local<v8::Object> obj_;
  const char *          name_;

  property_value operator=(v8::Handle<v8::FunctionTemplate> v) {
    obj_->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), name_), v->GetFunction());
    return *this;
  }
};

} // end of namespace detail

class object {
  public:
    explicit object(v8::Handle<v8::Object> o) : obj_(o) {}

    detail::property_value operator[](const char * name) {
      return detail::property_value(obj_, name);
    }

    v8::Local<v8::Object> obj_;
};

}

#endif // N2O_OBJECT_INCLUDED
