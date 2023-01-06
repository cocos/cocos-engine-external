%fragment ("js_check_arg_count", "templates") %{
    if (argc != $jsargcount) {
        SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, $jsargcount);
        return false;
    }%}

/* -----------------------------------------------------------------------------
 * js_ctor:  template for wrapping a ctor.
 *   - $jswrapper:        wrapper of called ctor
 *   - $jslocals:         locals part of wrapper
 *   - $jscode:           code part of wrapper
 *   - $jsargcount:       number of arguments
 *   - $jsmangledtype:    mangled type of class
 * ----------------------------------------------------------------------------- */
%fragment ("js_ctor", "templates")
%{
static bool $jswrapper(se::State& s) // NOLINT(readability-identifier-naming)
{
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();
    $js_check_arg_count
    $jslocals
    $jscode
    auto *ptr = JSB_MAKE_PRIVATE_OBJECT_WITH_INSTANCE(result);
    s.thisObject()->setPrivateObject(ptr);
    return true;
}
SE_BIND_CTOR($jswrapper, __jsb_$jsmangledname_class, js_delete_$jsdtor)%}

/* -----------------------------------------------------------------------------
 * js_ctor_dispatcher:  dispatcher for overloaded constructors
 *   - $jswrapper:        name of wrapper
 *   - $jsname:           class name
 *   - $jsdispatchcases:  part containing code for dispatching
 * ----------------------------------------------------------------------------- */
%fragment ("js_ctor_dispatcher", "templates")
%{
static bool $jswrapper(se::State& s) // NOLINT(readability-identifier-naming)
{
    size_t argc = s.args().size();
    bool ret = false;
    $jsdispatchcases
    SE_REPORT_ERROR("Illegal arguments for construction of $jsname");
    return false;
}
SE_BIND_CTOR($jswrapper, __jsb_$jsmangledname_class, js_delete_$jsdtor)%}

/* -----------------------------------------------------------------------------
 * js_overloaded_ctor:  template for wrapping a ctor.
 *   - $jswrapper:        wrapper of called ctor
 *   - $jslocals:         locals part of wrapper
 *   - $jscode:           code part of wrapper
 *   - $jsargcount:       number of arguments
 *   - $jsmangledtype:    mangled type of class
 * ----------------------------------------------------------------------------- */
%fragment ("js_overloaded_ctor", "templates")
%{
static bool $jswrapper(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    CC_UNUSED bool ok = true;
    $jslocals
    $jscode
    auto *ptr = JSB_MAKE_PRIVATE_OBJECT_WITH_INSTANCE(result);
    s.thisObject()->setPrivateObject(ptr);
    return true;
}
%}

/* -----------------------------------------------------------------------------
 * js_ctor_dispatch_case:  template for a dispatch case for calling an overloaded ctor.
 *   - $jsargcount:       number of arguments of called ctor
 *   - $jswrapper:        wrapper of called ctor
 *
 *  Note: a try-catch-like mechanism is used to switch cases
 * ----------------------------------------------------------------------------- */
%fragment ("js_ctor_dispatch_case", "templates")
%{
  if(argc == $jsargcount) {
    ret = $jswrapper(s);
    if (ret) { return ret; } /* reset exception and return */
  }
%}


/* -----------------------------------------------------------------------------
 * js_dtor:  template for a destructor wrapper
 *   - $jsmangledname:  mangled class name
 *   - $jstype:         class type
 * ----------------------------------------------------------------------------- */
%fragment ("js_dtor", "templates")
%{
static bool $jswrapper(se::State& s) {
  return true;
}
SE_BIND_FINALIZE_FUNC($jswrapper) %}

/* -----------------------------------------------------------------------------
 * js_dtor:  template for a destructor wrapper
 *   - $jsmangledname:  mangled class name
 *   - $jstype:         class type
 *   - ${destructor_action}: The custom destructor action to invoke.
 * ----------------------------------------------------------------------------- */
%fragment ("js_dtoroverride", "templates")
%{
static bool $jswrapper(se::State& s)
{
  return true;
}
SE_BIND_FINALIZE_FUNC($jswrapper) %}

/* -----------------------------------------------------------------------------
 * js_getter:  template for getter function wrappers
 *   - $jswrapper:  wrapper function name
 *   - $jslocals:   locals part of wrapper
 *   - $jscode:     code part of wrapper
 * ----------------------------------------------------------------------------- */
%fragment ("js_getter", "templates")
%{
static bool $jswrapper(se::State& s)
{
    $js_getter_begin
    CC_UNUSED bool ok = true;
    $jslocals
    $jscode
    $js_getter_end
    return true;
}
SE_BIND_PROP_GET($jswrapper) %}

/* -----------------------------------------------------------------------------
 * js_setter:  template for setter function wrappers
 *   - $jswrapper:  wrapper function name
 *   - $jslocals:   locals part of wrapper
 *   - $jscode:     code part of wrapper
 * ----------------------------------------------------------------------------- */
%fragment ("js_setter", "templates")
%{
static bool $jswrapper(se::State& s)
{
    $js_setter_begin
    CC_UNUSED bool ok = true;
    const auto& args = s.args();
    size_t argc = args.size();
    $jslocals
    $jscode
    $js_setter_end
    return true;
}
SE_BIND_PROP_SET($jswrapper) %}

/* -----------------------------------------------------------------------------
 * js_function:  template for function wrappers
 *   - $jswrapper:  wrapper function name
 *   - $jslocals:   locals part of wrapper
 *   - $jscode:     code part of wrapper
 * ----------------------------------------------------------------------------- */
%fragment ("js_function", "templates")
%{
static bool $jswrapper(se::State& s)
{
  $js_func_begin
  CC_UNUSED bool ok = true;
  const auto& args = s.args();
  size_t argc = args.size();
  $jslocals
  if(argc != $jsargcount) {
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, $jsargcount);
    return false;
  }
  $jscode
  $js_func_end
  return true;
}
SE_BIND_FUNC($jswrapper) %}

/* -----------------------------------------------------------------------------
 * js_function_dispatcher:  template for a function dispatcher for overloaded functions
 *   - $jswrapper:  wrapper function name
 *   - $jsname:     name of the wrapped function
 *   - $jslocals:   locals part of wrapper
 *   - $jscode:     code part of wrapper
 * ----------------------------------------------------------------------------- */
%fragment ("js_function_dispatcher", "templates")
%{
static bool $jswrapper(se::State& s)
{
  CC_UNUSED bool ok = true;
  const auto& args = s.args();
  size_t argc = args.size();
  $jslocals
  $jscode
  SE_REPORT_ERROR("wrong number of arguments: %d", (int)argc);
  return false;
}
SE_BIND_FUNC($jswrapper) %}

/* -----------------------------------------------------------------------------
 * js_overloaded_function:  template for a overloaded function
 *   - $jswrapper:  wrapper function name
 *   - $jslocals:   locals part of wrapper
 *   - $jscode:     code part of wrapper
 * ----------------------------------------------------------------------------- */
%fragment ("js_overloaded_function", "templates")
%{
static bool $jswrapper(se::State& s)
{
  $js_func_begin
  CC_UNUSED bool ok = true;
  const auto& args = s.args();
  $jslocals
  $jscode
  $js_func_end
  return true;
}%}

/* -----------------------------------------------------------------------------
 * js_function_dispatch_case:  template for a case used in the function dispatcher
 *   - $jswrapper:  wrapper function name
 *   - $jsargcount: number of arguments of overloaded function
 *   - $jscode:     code part of wrapper
 * ----------------------------------------------------------------------------- */
%fragment ("js_function_dispatch_case", "templates")
%{
  if (argc == $jsargcount) {
     ok = $jswrapper(s);
     if (ok) { return true; }
  } %}

/* -----------------------------------------------------------------------------
 * jsc_variable_declaration:  template for a variable table entry
 *   - $jsname:       name of the variable
 *   - $jsgetter:     wrapper of getter function
 *   - $jssetter:     wrapper of setter function
 * ----------------------------------------------------------------------------- */
%fragment ("jsc_variable_declaration", "templates")
%{ cls->defineProperty("$jsname", $jsgetter, $jssetter); %}

%fragment ("jsc_static_variable_declaration", "templates")
%{ cls->defineStaticProperty("$jsname", $jsgetter, $jssetter); %}

%fragment ("jsc_global_variable_declaration", "templates")
%{ ns->defineProperty("$jsname", $jsgetter, $jssetter); %}

/* -----------------------------------------------------------------------------
 * jsc_function_declaration:  template for a function table entry
 *   - $jsname:       name of the variable
 *   - $jswrapper:    wrapper function
 * ----------------------------------------------------------------------------- */
%fragment ("jsc_function_declaration", "templates")
%{ cls->defineFunction("$jsname", _SE($jswrapper)); %}

%fragment ("jsc_static_function_declaration", "templates")
%{ cls->defineStaticFunction("$jsname", _SE($jswrapper)); %}

%fragment ("jsc_global_function_declaration", "templates")
%{ ns->defineFunction("$jsname", _SE($jswrapper)); %}

/* -----------------------------------------------------------------------------
 * jsc_classtemplate_declaration:  template for a namespace declaration
 *   - $jsmangledname:      mangled class name
 * ----------------------------------------------------------------------------- */
%fragment ("jsc_class_declaration", "templates")
%{
se::Class* __jsb_$jsmangledname_class = nullptr;
se::Object* __jsb_$jsmangledname_proto = nullptr;
SE_DECLARE_FINALIZE_FUNC(js_delete_$jsdtor) %}

/* -----------------------------------------------------------------------------
 * jsc_define_class_template:  template for defining a class template
 *   - $jsmangledname:            mangled class name
 *   - $jsmangledtype:            mangled class type
 *   - $jsctor:                   wrapper of ctor
 *   - $jsbaseclass:              mangled name of base class
 * ----------------------------------------------------------------------------- */
%fragment ("jsc_class_definition", "templates")
%{
bool js_register_$jsmangledname(se::Object* obj) {
    $jsclass_inheritance
    cls->defineStaticProperty("__isJSB", se::Value(true), se::PropertyAttribute::READ_ONLY | se::PropertyAttribute::DONT_ENUM | se::PropertyAttribute::DONT_DELETE);
    $jsclassvariables
    $jsclassfunctions
    $jsstaticclassvariables
    $jsstaticclassfunctions
    $jsfinalizefunction
    cls->install();
    JSBClassType::registerClass<$jsclassname>(cls);

    __jsb_$jsmangledname_proto = cls->getProto();
    __jsb_$jsmangledname_class = cls;
    se::ScriptEngine::getInstance()->clearException();
    return true;
}
%}

%fragment ("jsc_finalize_function", "templates") %{
    cls->defineFinalizeFunction(_SE($jsdtor));
%}

%fragment ("jsc_class_inherit", "templates")
%{ auto* cls = se::Class::create($jsname, obj, __jsb_$jsbaseclassmangled_proto, $jsctor); %}

%fragment ("jsc_class_noinherit", "templates")
%{ auto* cls = se::Class::create($jsname, obj, nullptr, $jsctor); %}

/* -----------------------------------------------------------------------------
 * jsc_register_class:  template for registration of a class
 *   - $jsname:                   class name
 *   - $jsmangledname:            mangled class name
 *   - $jsnspace:                 mangled name of namespace
 * ----------------------------------------------------------------------------- */
%fragment ("jsc_class_registration", "templates")
%{ js_register_$jsmangledname(ns); %}


/* -----------------------------------------------------------------------------
 * jsc_nspace_definition:  template for definition of a namespace object
 *   - $jsmangledname:            mangled name of namespace
 * ----------------------------------------------------------------------------- */
%fragment ("jsc_global_registration", "templates")
%{$jsglobalvariables
  $jsglobalfunctions %}

%fragment ("jsc_struct_prop_snippet", "templates") %{
    json->getProperty("$field_symname", &field, true);
    if (!field.isNullOrUndefined()) {
        ok &= sevalue_to_native(field, &(to->$field_name), ctx);
    }
%}


%fragment ("jsc_struct_prop_conversion_declare", "templates") %{
template<>
bool sevalue_to_native(const se::Value &from, $jsclassname * to, se::Object *ctx);
%}

%fragment ("jsc_struct_prop_conversion", "templates") %{
template<>
bool sevalue_to_native(const se::Value &from, $jsclassname * to, se::Object *ctx)
{
    assert(from.isObject());
    se::Object *json = from.toObject();
    auto* data = reinterpret_cast<$jsclassname*>(json->getPrivateData());
    if (data) {
        *to = *data;
        return true;
    }
    se::Value field;
    bool ok = true;
    $jscode
    return ok;
}
%}