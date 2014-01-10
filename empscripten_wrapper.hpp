
#ifndef _EMSCRIPTEN_WRAPPER_H
#define _EMSCRIPTEN_WRAPPER_H

#ifdef __cplusplus
extern "C" {
using namespace std;
#endif

char *sass_compile_unrolled(
  char *source_string,
  int output_style,
  char **error_message
);

#ifdef __cplusplus
}
#endif


#endif
