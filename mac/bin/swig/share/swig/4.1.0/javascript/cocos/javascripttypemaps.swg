/* ------------------------------------------------------------
 *  Typemap specializations for Javascript
 * ------------------------------------------------------------ */

/* ------------------------------------------------------------
 *  Fragment section
 * ------------------------------------------------------------ */


/* These macros are necessary to provide an extra parameter
   to SWIG_AsVal_dec functions (JSContextRef context).
   They must be defined before including `typemaps/fragments.swg`
*/
#define SWIG_FROM_DECL_ARGS SWIG_JSC_FROM_DECL_ARGS
#define SWIG_FROM_CALL_ARGS SWIG_JSC_FROM_CALL_ARGS
#define SWIG_AS_DECL_ARGS SWIG_JSC_AS_DECL_ARGS
#define SWIG_AS_CALL_ARGS SWIG_JSC_AS_CALL_ARGS

/* Include fundamental fragemt definitions */
%include <typemaps/fragments.swg>

/* Look for user fragments file. */
%include <javascriptfragments.swg>

/* Javascript fragments for fundamental types */
//cjh %include <javascriptprimtypes.swg>

/* Javascript fragments for char* strings */
//cjh %include <javascriptstrings.swg>


/* -----------------------------------------------------------------------------
 * javascripttypemaps.swg
 *
 * basic typemaps for Javascript.
 * ----------------------------------------------------------------------------- */

/* -----------------------------------------------------------------------------
 *                          standard typemaps
 * ----------------------------------------------------------------------------- */
// number
%typemap(in) char, int, short, long, signed char, float, double, int8_t, int16_t, int32_t, int64_t, size_t, ssize_t
%{
  ok &= sevalue_to_native($input, &$1, s.thisObject());
  SE_PRECONDITION2(ok, false, "Error processing arguments"); %}
 
// additional check for unsigned numbers, to not permit negative input
%typemap(in) unsigned char, unsigned int, unsigned short, unsigned long, unsigned char, uint8_t, uint16_t, uint32_t, uint64_t, size_t, ssize_t
%{
  ok &= sevalue_to_native($input, &$1, s.thisObject());
  SE_PRECONDITION2(ok, false, "Error processing arguments");
%}

%typemap(out) char, int,short,long,
             unsigned char, unsigned int,unsigned short,unsigned long,
             signed char,unsigned char,
             float,double,
             int8_t, int16_t, int32_t, int64_t,
             uint8_t, uint16_t, uint32_t, uint64_t,
             size_t, ssize_t
%{
   ok &= nativevalue_to_se($1, s.rval(), s.thisObject()); %}

%apply long {long long, signed long long, unsigned long long};
// size_t (which is just a unsigned long)
%apply unsigned long { size_t };

// we must also provide typemaps for primitives by const reference:
// given a function:
// int intbyref(const int& i);
// SWIG assumes that this code will need a pointer to int to be passed in
// (this might be ok for objects by const ref, but not for numeric primitives)
// therefore we add a set of typemaps to fix this (for both in & out)
%typemap(in) const int& ($*1_ltype temp), const unsigned int& ($*1_ltype temp)
%{ 
  ok &= sevalue_to_native($input, &temp, s.thisObject());
  SE_PRECONDITION2(ok, false, "Error processing arguments"); 
  $1 = &temp;
%}

%typemap(out) const int&, const unsigned int&
%{
  ok &= nativevalue_to_se(*$1, s.rval(), s.thisObject());
  SE_PRECONDITION2(ok, false, "Error processing arguments"); 
%}

// for the other numbers we can just use an apply statement to cover them
%apply const int & {const short&,const long&,const signed char&,
             const float&,const double&};

%apply const unsigned int & {const unsigned short&,const unsigned long&,
             const unsigned char&};

%apply const long& {const long long&, const signed long long&, const unsigned long long&};
%apply const unsigned long & { const size_t & };

%typemap(in) bool
%{
  ok &= sevalue_to_native($input, &$1);
  SE_PRECONDITION2(ok, false, "Error processing arguments"); %}

%typemap(out) bool
%{
  ok &= nativevalue_to_se($1, s.rval(), s.thisObject());%}

%typemap(out) bool &
%{
  ok &= nativevalue_to_se(*$1, s.rval(), s.thisObject());%}

%typemap(in) const char * (ccstd::string temp)
%{
   ok &= sevalue_to_native($input, &temp);
   SE_PRECONDITION2(ok, false, "Error processing arguments");
   $1 = ($ltype) temp.c_str(); %}

%typemap(out) const char *, char *
%{
  ok &= nativevalue_to_se($1, s.rval(), nullptr /*ctx*/);
  SE_PRECONDITION2(ok, false, "Error processing arguments");
%}

%apply const char* {char*, const char[ANY], char[ANY]}

// pointers and references
// under SWIG rules, it is ok, to have a pass in a javascript null,
// it should be converted to a SWIG NULL.
// This will only be allowed for pointers & arrays, not refs or by value
%typemap(in) SWIGTYPE*
%{
  ok &= sevalue_to_native($input, &$1, s.thisObject());
  SE_PRECONDITION2(ok, false, "Error processing arguments"); %}

%typemap(in) SWIGTYPE[]
%{
  ok &= sevalue_to_native($input, &$1, s.thisObject());
  SE_PRECONDITION2(ok, false, "Error processing arguments"); %}

%typemap(in) SWIGTYPE& ($*ltype temp)
%{
  ok &= sevalue_to_native($input, &temp, s.thisObject());
  SE_PRECONDITION2(ok, false, "Error processing arguments");
  $1 = &temp;
%}

%typemap(in) SWIGTYPE&& ($*ltype temp)
%{
  ok &= sevalue_to_native($input, &temp, s.thisObject());
  SE_PRECONDITION2(ok, false, "Error processing arguments");
  $1 = &temp;
%}

// out is simple
%typemap(out) SWIGTYPE&
%{
  ok &= nativevalue_to_se(*$1, s.rval(), s.thisObject());
    SE_PRECONDITION2(ok, false, "Error processing arguments");
    SE_HOLD_RETURN_VALUE(*$1, s.thisObject(), s.rval()); %}

%typemap(out) SWIGTYPE*
%{
  ok &= nativevalue_to_se($1, s.rval(), s.thisObject());
   SE_PRECONDITION2(ok, false, "Error processing arguments");
   SE_HOLD_RETURN_VALUE($1, s.thisObject(), s.rval()); %}

%typemap(out) SWIGTYPE&&
%{
  ok &= nativevalue_to_se($1, s.rval(), s.thisObject());
   SE_PRECONDITION2(ok, false, "Error processing arguments");
   SE_HOLD_RETURN_VALUE($1, s.thisObject(), s.rval()); %}

// passing objects by value
// SWIG_ConvertPtr wants an object pointer (the $&ltype argp)
// then dereferences it to get the object
%typemap(in) SWIGTYPE //($&ltype argp)
%{
  ok &= sevalue_to_native($input, &$1, s.thisObject());
  SE_PRECONDITION2(ok, false, "Error processing arguments"); 
%}

// Primitive types--return by value
// must make a new object, copy the data & return the new object
// Note: the brackets are {...} and not %{..%}, because we want them to be included in the wrapper
// this is because typemap(out) does not support local variables, like in typemap(in) does
// and we need the $&1_ltype resultptr; to be declared
%typemap(out) SWIGTYPE 
%{
    ok &= nativevalue_to_se($1, s.rval(), s.thisObject() /*ctx*/);
    SE_PRECONDITION2(ok, false, "Error processing arguments");
    SE_HOLD_RETURN_VALUE($1, s.thisObject(), s.rval());
%}

// member function pointer
// a member fn ptr is not 4 bytes like a normal pointer, but 8 bytes (at least on mingw)
// so the standard wrapping cannot be done
// nor can you cast a member function pointer to a void* (obviously)
// therefore a special wrapping functions SWIG_ConvertMember() & SWIG_NewMemberObj() were written
%typemap(in) SWIGTYPE (CLASS::*)
%{
  static_assert(false, "Binding member function pointer is not supported!");
%}

%typemap(out) SWIGTYPE (CLASS::*)
%{
  static_assert(false, "Returning member function pointer is not supported!");
%}


// void (must be empty without the SWIG_arg++)
%typemap(out) void "";

/* void* is a special case
A function void fn(void*) should take any kind of pointer as a parameter (just like C/C++ does)
but if it's an output, then it should be wrapped like any other SWIG object (using default typemap)
*/
%typemap(in) void*
%{  ok &= sevalue_to_native($input, &$1);
    SE_PRECONDITION2(ok, false, "Error processing arguments");%}

/* -----------------------------------------------------------------------------
 *                          typecheck rules
 * ----------------------------------------------------------------------------- */
/* These are needed for the overloaded functions
These define the detection routines which will spot what
parameters match which function
*/

%typemap(in) SWIGTYPE *self 
%{ $1 = SE_THIS_OBJECT<$*ltype>(s);
   if (nullptr == $1) return true;%}


/* -----------------------------------------------------------------------------
 *                          Others
 * ----------------------------------------------------------------------------- */

// Array reference typemaps
%apply SWIGTYPE & { SWIGTYPE ((&)[ANY]) }
%apply SWIGTYPE && { SWIGTYPE ((&&)[ANY]) }

/* const pointers */
%apply SWIGTYPE * { SWIGTYPE *const }
%apply SWIGTYPE (CLASS::*) { SWIGTYPE (CLASS::*const) }
%apply SWIGTYPE & { SWIGTYPE (CLASS::*const&) }




/* -----------------------------------------------------------------------------
 *                          Specials
 * ----------------------------------------------------------------------------- */
// swig::LANGUAGE_OBJ was added to allow containers of native objects
// however it's rather difficult to do this in javascript, as you cannot hold pointers
// to native objects (they are held in the interpreter)
// therefore for now: just ignoring this feature
#ifdef __cplusplus
%ignore swig::LANGUAGE_OBJ;

//%inline %{
// %{
// namespace swig {
// typedef struct{} LANGUAGE_OBJ;
// }
// %}

#endif // __cplusplus

// Cocos custom type

%typemap(in) cc::Mat4* (cc::Mat4 temp) %{
  ok &= sevalue_to_native($input, &temp);
  SE_PRECONDITION2(ok, false, "Error processing arguments");
  $1 = ($ltype) &temp;
%}

%typemap(out) cc::Float32Array %{
    ok &= nativevalue_to_se($1, s.rval(), s.thisObject());
    SE_PRECONDITION2(ok, false, "Error processing arguments");
    SE_HOLD_RETURN_VALUE($1, s.thisObject(), s.rval());
%}

%typemap(out, func_only=1) cc::Vec4 ($ltype* temp), cc::Vec3 ($ltype* temp), cc::Vec2 ($ltype* temp), cc::Mat4 ($ltype* temp), cc::Mat3 ($ltype* temp), cc::Quaternion ($ltype* temp), cc::Color ($ltype* temp) %{
  temp = ccnew $ltype($1);
  ok &= nativevalue_to_se(temp, s.rval(), s.thisObject());
  SE_PRECONDITION2(ok, false, "Error processing arguments");
  s.rval().toObject()->getPrivateObject()->tryAllowDestroyInGC();
%}