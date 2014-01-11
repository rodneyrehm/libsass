#include <cstdlib>
#include <cstring>
#include "sass_interface.h"
#include "empscripten_wrapper.hpp"

char *sass_compile_unrolled(
  char *source_string,
  int output_style,
  char **error_message
) {
  char *output_string;
  struct sass_options options;
  struct sass_context *ctx = sass_new_context();

  options.output_style = output_style;
  options.image_path = NULL;
  options.include_paths = NULL;

  ctx->options = options;
  ctx->source_string = source_string;

  sass_compile(ctx);

  if (ctx->output_string) {
    output_string = strdup(ctx->output_string);
  } else {
    output_string = NULL;
  }

  if (ctx->error_status) {
    *error_message = strdup(ctx->error_message);
  } else {
    *error_message = NULL;
  }
  // I'm too dumb to understand how to access error_message pointer form JS
  // just return the error message and have JS figure things out
  if (ctx->error_status) {
    output_string = strdup(ctx->error_message);
  }

  sass_free_context(ctx);
  return output_string;
}

