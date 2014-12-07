# Notes

## The Object API

* provides objects that feel like JavaScript:
  * named and indexed property access
  * truth value
  * operators (Number + Number, String + Number, &c)
  * expose JavaScript core methods


## Bound Functions

* The user level object `Function` holds a `v8::Function`
* The `v8::Function` is created with a `data` value that hold the calling infrastructure
* To keep the `data` value accessible it is installed in the `v8::Functions`s prototype chain


