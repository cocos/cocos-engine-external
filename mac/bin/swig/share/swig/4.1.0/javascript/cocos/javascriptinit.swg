//cjh %insert(init) "swiginit.swg"

// Open the initializer function
%insert(init)
// Im init block
%{%}

/* -----------------------------------------------------------------------------
 * js_initializer:  template for the module initializer function
 *   - $jsname:                   module name
 *   - $jscreatenamespaces:       part with code for creating namespace objects
 *   - $jsregisternamespaces:     part with code for registration of namespaces
 * ----------------------------------------------------------------------------- */
%fragment ("js_initializer", "templates") %{
bool register_all_$js_module_name(se::Object* obj) {
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("$js_namespace", &nsVal, true))
    {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("$js_namespace", nsVal);
    }
    se::Object* ns = nsVal.toObject();
    /* Register classes */
    $jsregisterclasses
    /* Register global variables & global functions */
    $jsregisternamespaces
    return true;
}
%}

%fragment ("se_global_variables", "templates") %{
    JSB_REGISTER_OBJECT_TYPE($jsclassname);
    extern se::Object *__jsb_$jsmangledname_proto; // NOLINT
    extern se::Class * __jsb_$jsmangledname_class; // NOLINT
%}

%fragment ("js_register_module_declare", "templates") %{
bool register_all_$jsmodulename(se::Object* obj);
%}