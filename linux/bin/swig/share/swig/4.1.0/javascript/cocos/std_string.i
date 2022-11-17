// %include <typemaps/std_string.swg>

/* -----------------------------------------------------------------------------
 * std_string.i
 *
 * std::string typemaps for LUA
 * ----------------------------------------------------------------------------- */

%{
#include <string>
%}

/*
Only std::string and const std::string& are typemapped
they are converted to the Lua strings automatically

std::string& and std::string* are not
they must be explicitly managed (see below)

eg.

std::string test_value(std::string x) {
   return x;
}

can be used as

s="hello world"
s2=test_value(s)
assert(s==s2)
*/

namespace std {

// %naturalvar string;

// %typemap(in) string
// %{// string
//      ok &= sevalue_to_native($input, &$1);
//    SE_PRECONDITION2(ok, false, "Error processing arguments"); %}

// %typemap(out) string
// %{ lua_pushlstring(L,$1.data(),$1.size()); SWIG_arg++;%}

// %typemap(in) string *self 
// %{ $1 = SE_THIS_OBJECT<$*ltype>(s);
//    SE_PRECONDITION2($1, false, "Invalid Native Object"); %}

// %typemap(in,checkfn="lua_isstring") string*
// %{// string*
//     std::string
//     ok &= sevalue_to_native($input, &$1);
//     SE_PRECONDITION2(ok, false, "Error processing arguments");
//     $1.assign(lua_tostringxxx(L,$input),lua_rawlen(L,$input));%}

// %typemap(out) string*
// %{// out string*
//      lua_pushlstringxxx(L,$1.data(),$1.size()); SWIG_arg++;%}

// %typemap(in,checkfn="lua_isstring") const string& ($*1_ltype temp)
// %{ // const std::string&
//     temp.assign(lua_tostring(L,$input),lua_rawlen(L,$input)); $1=&temp;%}

// %typemap(out) const string&
// %{ // out const string&
//     lua_pushlstring(L,$1->data(),$1->size()); SWIG_arg++;%}

// // %typecheck(SWIG_TYPECHECK_STRING) string, const string& {
// //   $1 = lua_isstring(L,$input);
// // }

// /*
// std::string& can be wrapped, but you must inform SWIG if it is in or out

// eg:
// void fn(std::string& str);
// Is this an in/out/inout value?

// Therefore you need the usual
// %apply (std::string& INOUT) {std::string& str};
// or
// %apply std::string& INOUT {std::string& str};
// typemaps to tell SWIG what to do.
// */

// %typemap(in) string &INPUT=const string &;

// %typemap(in, numinputs=0) string &OUTPUT ($*1_ltype temp)
// %{ $1 = &temp; %}

// %typemap(argout) string &OUTPUT
// %{ lua_pushlstring(L,$1->data(),$1->size()); SWIG_arg++;%}

// %typemap(in) string &INOUT =const string &;
// %typemap(in) string *INOUT %{
//     // inout ... string*
// %};

// %typemap(argout) string &INOUT = string &OUTPUT;

/*
A really cut down version of the string class

This provides basic mapping of lua strings <-> std::string
and little else
(the std::string has a lot of unneeded functions anyway)

note: no fn's taking the const string&
as this is overloaded by the const char* version
*/

  class string {
    public:
      string();
      string(const char*);
      unsigned int size() const;
      unsigned int length() const;
      bool empty() const;
      // no support for operator[]
      const char* c_str()const;
      const char* data()const;
      // assign does not return a copy of this object
      // (no point in a scripting language)
      void assign(const char*);
      // no support for all the other features
      // it's probably better to do it in lua
  };
}


