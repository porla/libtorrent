#include <node_api.h>

#include "common.h"
#include "session.h"

#ifdef WIN32
// TODO: Ugly hack
FILE _iob[] = { *stdin, *stdout, *stderr }; 
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
#endif

napi_value Init(napi_env env, napi_value exports) {
    porla::Session::Init(env, exports);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
