/* ------------------------------------------------------------
 * Primitive Types
 * ------------------------------------------------------------ */

/* boolean */

%fragment(SWIG_From_frag(bool),"header") {
}

%fragment(SWIG_AsVal_frag(bool),"header") {
}

/* int */

%fragment(SWIG_From_frag(int),"header") {
}

%fragment(SWIG_AsVal_frag(int),"header") {
}

/* long */

%fragment(SWIG_From_frag(long),"header") {
}

%fragment(SWIG_AsVal_frag(long),"header") {
}

/* unsigned long */

%fragment(SWIG_From_frag(unsigned long),"header") {
}

%fragment(SWIG_AsVal_frag(unsigned long),"header") {
}

/* long long */
// Note: these are copied from 'long' and probably need fixing

%fragment(SWIG_From_frag(long long),"header") {
%#ifdef SWIG_LONG_LONG_AVAILABLE
%#endif
}

%fragment(SWIG_AsVal_frag(long long),"header") {
%#ifdef SWIG_LONG_LONG_AVAILABLE
%#endif
}

/* unsigned long long */
// Note: these are copied from 'unsigned long' and probably need fixing

%fragment(SWIG_From_frag(unsigned long long),"header") {
%#ifdef SWIG_LONG_LONG_AVAILABLE
%#endif
}

%fragment(SWIG_AsVal_frag(unsigned long long),"header") {
%#ifdef SWIG_LONG_LONG_AVAILABLE
%#endif
}

/* double */

%fragment(SWIG_From_frag(double),"header") {
}

%fragment(SWIG_AsVal_frag(double),"header") {
}
