//==============================================================================
// Copyright David Siegel 2014. Distributed under the MIT license. See LICENSE.
//==============================================================================
#include <n2o/type_id.hpp>

#include <ostream>
#include <vector>
#include <cassert>

#include <cxxabi.h>

namespace n2o {

namespace {

  struct compare_first_cstring {
      template <class T>
      bool
      operator()(T const& x, T const& y) {
          return std::strcmp(x.first,y.first) < 0;
      }
  };
  struct free_mem {
      free_mem(char*p) : p(p) {}
      ~free_mem() { std::free(p); }
      char* p;
  };
} // end of anonymous namespace

namespace detail {

bool cxxabi_cxa_demangle_is_broken() {
    static bool was_tested = false;
    static bool is_broken = false;
    if (not was_tested) {
        int status;
        free_mem keeper(abi::__cxa_demangle("b", 0, 0, &status));
        was_tested = true;
        if (status == -2 || strcmp(keeper.p, "bool") != 0) {
            is_broken = true;
        }
    }
    return is_broken;
}

char const* gcc_demangle(char const* mangled) {
    typedef std::vector<std::pair<char const*, char const*> > mangling_map;

    static mangling_map demangler;
    mangling_map::iterator p = std::lower_bound(demangler.begin(), demangler.end(),
            std::make_pair(mangled, (char const*)0), compare_first_cstring());

    if (p == demangler.end() || strcmp(p->first, mangled)) {
        int status;
        free_mem keeper(abi::__cxa_demangle(mangled, 0, 0, &status));

        assert(status != -3);

        if (status == -1) {
            throw std::bad_alloc();
        } else {
            char const* demangled = status == -2 ? mangled : keeper.p;

            if (cxxabi_cxa_demangle_is_broken() && status == -2 && strlen(mangled) == 1) {
                // list from
                // http://www.codesourcery.com/cxx-abi/abi.html
                switch (mangled[0]) {
                    case 'v': demangled = "void"; break;
                    case 'w': demangled = "wchar_t"; break;
                    case 'b': demangled = "bool"; break;
                    case 'c': demangled = "char"; break;
                    case 'a': demangled = "signed char"; break;
                    case 'h': demangled = "unsigned char"; break;
                    case 's': demangled = "short"; break;
                    case 't': demangled = "unsigned short"; break;
                    case 'i': demangled = "int"; break;
                    case 'j': demangled = "unsigned int"; break;
                    case 'l': demangled = "long"; break;
                    case 'm': demangled = "unsigned long"; break;
                    case 'x': demangled = "long long"; break;
                    case 'y': demangled = "unsigned long long"; break;
                    case 'n': demangled = "__int128"; break;
                    case 'o': demangled = "unsigned __int128"; break;
                    case 'f': demangled = "float"; break;
                    case 'd': demangled = "double"; break;
                    case 'e': demangled = "long double"; break;
                    case 'g': demangled = "__float128"; break;
                    case 'z': demangled = "..."; break;
                }
            }

            p = demangler.insert(p, std::make_pair(mangled, demangled));
            keeper.p = 0;
        }

    }
    return p->second;
}


} // end of namespace detail

std::ostream& operator<<(std::ostream& os, type_info const& x) {
    return os << x.name();
}

} // end of namespace n2o
