/* -----------------------------------------------------------------------------
 * javascript.swg
 *
 * Javascript typemaps
 * ----------------------------------------------------------------------------- */

%include <typemaps/swigmacros.swg>

%include <attribute.i>

%include <javascripttypemaps.swg>

%include <javascriptruntime.swg>

%include <javascripthelpers.swg>

%include <javascriptkw.swg>

%include <javascriptcode.swg>

%include <javascriptinit.swg>

#define %module_macro(m) %feature("module_macro","m")
#define %release_returned_cpp_object_in_gc(method)  %feature("release_returned_cpp_object_in_gc", "1") method