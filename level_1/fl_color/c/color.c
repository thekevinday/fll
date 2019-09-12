#include <level_1/color.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_color_set_
  f_return_status fl_color_set(FILE *file, const f_color_format format, const int8_t *color1, const int8_t *color2, const int8_t *color3, const int8_t *color4, const int8_t *color5) {
    #ifndef _di_level_1_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (color1 == 0) return f_status_set_error(f_invalid_parameter);

      // make sure all data is in the proper order
      if (color2 == 0 && (color3 != 0 || color4 != 0 || color5 != 0)) return f_status_set_error(f_invalid_parameter);
      if (color3 == 0 && (color4 != 0 || color5 != 0))                return f_status_set_error(f_invalid_parameter);
      if (color4 == 0 && color5 != 0)                                 return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if      (color2 == 0) fprintf(file, "%s%s%s",                 format.begin, color1, format.end);
    else if (color3 == 0) fprintf(file, "%s%s%s%s%s",             format.begin, color1, format.medium, color2, format.end);
    else if (color4 == 0) fprintf(file, "%s%s%s%s%s%s%s",         format.begin, color1, format.medium, color2, format.medium, color3, format.end);
    else if (color5 == 0) fprintf(file, "%s%s%s%s%s%s%s%s%s",     format.begin, color1, format.medium, color2, format.medium, color3, format.medium, color4, format.end);
    else                  fprintf(file, "%s%s%s%s%s%s%s%s%s%s%s", format.begin, color1, format.medium, color2, format.medium, color3, format.medium, color4, format.medium, color5, format.end);

    return f_none;
  }
#endif // _di_fl_color_set_

#ifndef _di_fl_color_save_
  f_return_status fl_color_save(f_string_dynamic *buffer, const f_color_format format, const int8_t *color1, const int8_t *color2, const int8_t *color3, const int8_t *color4, const int8_t *color5) {
    #ifndef _di_level_1_parameter_checking_
      if (buffer == 0) return f_status_set_error(f_invalid_parameter);
      if (color1 == 0) return f_status_set_error(f_invalid_parameter);

      // make sure all data is in the proper order
      if (color2 == 0 && (color3 != 0 || color4 != 0 || color5 != 0)) return f_status_set_error(f_invalid_parameter);
      if (color3 == 0 && (color4 != 0 || color5 != 0))                return f_status_set_error(f_invalid_parameter);
      if (color4 == 0 && color5 != 0)                                 return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_string_length string_size = strnlen(format.begin, f_color_max_size) + strnlen(format.end, f_color_max_size) + 1;

    if      (color2 == 0) string_size += strnlen(color1, f_color_max_size);
    else if (color3 == 0) string_size += strnlen(color1, f_color_max_size) + strnlen(color2, f_color_max_size);
    else if (color4 == 0) string_size += strnlen(color1, f_color_max_size) + strnlen(color2, f_color_max_size) + strnlen(color3, f_color_max_size);
    else if (color5 == 0) string_size += strnlen(color1, f_color_max_size) + strnlen(color2, f_color_max_size) + strnlen(color3, f_color_max_size) + strnlen(color4, f_color_max_size);
    else                  string_size += strnlen(color1, f_color_max_size) + strnlen(color2, f_color_max_size) + strnlen(color3, f_color_max_size) + strnlen(color4, f_color_max_size) + strnlen(color5, f_color_max_size);

    // make sure there is enough allocated space, if not, then allocate some more
    if (buffer->size - buffer->used - 1 < string_size) {
      f_status status = f_none;

      f_macro_string_dynamic_resize(status, (*buffer), buffer->used + string_size + 1); // the additional 1 is the EOS

      if (f_status_is_error(status)) {
        return status;
      }
    }

    if (color2 == 0) {
      strncat(buffer->string, format.begin, f_color_max_size);
      strncat(buffer->string, color1, f_color_max_size);
      strncat(buffer->string, format.end, f_color_max_size);
    }
    else if (color3 == 0) {
      strncat(buffer->string, format.begin, f_color_max_size);
      strncat(buffer->string, color1, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color2, f_color_max_size);
      strncat(buffer->string, format.end, f_color_max_size);
    }
    else if (color4 == 0) {
      strncat(buffer->string, format.begin, f_color_max_size);
      strncat(buffer->string, color1, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color2, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color3, f_color_max_size);
      strncat(buffer->string, format.end, f_color_max_size);
    }
    else if (color5 == 0) {
      strncat(buffer->string, format.begin, f_color_max_size);
      strncat(buffer->string, color1, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color2, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color3, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color4, f_color_max_size);
      strncat(buffer->string, format.end, f_color_max_size);
    }
    else {
      strncat(buffer->string, format.begin, f_color_max_size);
      strncat(buffer->string, color1, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color2, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color3, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color4, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color5, f_color_max_size);
      strncat(buffer->string, format.end, f_color_max_size);
    }

    // update the amount of space that is to be used
    buffer->used += string_size;

    // do not forget the EOS
    buffer->string[buffer->used] = f_string_eos;

    return f_none;
  }
#endif // _di_fl_color_save_

#ifndef _di_fl_color_print_
  f_return_status fl_color_print(FILE *file, const f_string_dynamic start_color, const f_string_dynamic end_color, const int8_t *string, ...) {
    #ifndef _di_level_1_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (string == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (start_color.used != 0) {
      f_status status = f_print_string_dynamic(file, start_color);

      if (f_status_is_error(status)) return status;
    }

    va_list ap;

    va_start(ap, string);

    vfprintf(file, string, ap);

    va_end(ap);

    if (end_color.used != 0) {
      f_status status = f_print_string_dynamic(file, end_color);

      if (f_status_is_error(status)) return status;
    }

    return f_none;
  }
#endif // _di_fl_color_print_

#ifndef _di_fl_color_print_line_
  f_return_status fl_color_print_line(FILE *file, const f_string_dynamic start_color, const f_string_dynamic end_color, const int8_t *string, ...) {
    #ifndef _di_level_1_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (string == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (start_color.used != 0) {
      f_status status = f_print_string_dynamic(file, start_color);

      if (f_status_is_error(status)) return status;
    }

    va_list ap;

    va_start(ap, string);

    vfprintf(file, string, ap);

    va_end(ap);

    if (end_color.used != 0) {
      f_status status = f_print_string_dynamic(file, end_color);

      if (f_status_is_error(status)) return status;
    }

    // now print the trailing newline, this is done _after_ ending the colors to avoid color wrapping issues that can happen when a color code follows a newline
    fprintf(file, "%c", f_string_eol);

    return f_none;
  }
#endif // _di_fl_color_print_line_

#ifndef _di_fl_color_print_code_
  f_return_status fl_color_print_code(FILE *file, const f_string_dynamic color) {
    if (color.used != 0) {
      f_status status = f_print_string_dynamic(file, color);

      if (f_status_is_error(status)) return status;
    }

    return f_none;
  }
#endif // _di_fl_color_print_code_

#ifndef _di_fl_color_load_context_
  f_return_status fl_color_load_context(fl_color_context *context, const f_bool use_light_colors) {
    #ifndef _di_level_1_parameter_checking_
      if (context == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status status = f_none;

    // switch to the appropriate terminal color mode
    {
      int8_t *environment = getenv("TERM");

      if (!environment || strncmp(environment, "linux", 6) == 0) {
        context->color_list = f_color_linux;
      }
      else {
        context->color_list = f_color_xterminal;
      }
    }

    // load the colors
    if (use_light_colors) {
      status = fl_macro_color_save_1(&context->reset, context->color_format, context->color_list.reset);

      if (f_status_is_not_error(status)) status = fl_macro_color_save_1(&context->warning,   context->color_format, context->color_list.yellow);
      if (f_status_is_not_error(status)) status = fl_macro_color_save_2(&context->error,     context->color_format, context->color_list.bold, context->color_list.red);
      if (f_status_is_not_error(status)) status = fl_macro_color_save_2(&context->title,     context->color_format, context->color_list.bold, context->color_list.blue);
      if (f_status_is_not_error(status)) status = fl_macro_color_save_1(&context->notable,   context->color_format, context->color_list.bold);
      if (f_status_is_not_error(status)) status = fl_macro_color_save_1(&context->important, context->color_format, context->color_list.blue);
      if (f_status_is_not_error(status)) status = fl_macro_color_save_1(&context->standout,  context->color_format, context->color_list.purple);
    }
    else {
      status = fl_macro_color_save_1(&context->reset, context->color_format, context->color_list.reset);

      if (f_status_is_not_error(status)) status = fl_macro_color_save_1(&context->warning,   context->color_format, context->color_list.yellow);
      if (f_status_is_not_error(status)) status = fl_macro_color_save_2(&context->error,     context->color_format, context->color_list.bold, context->color_list.red);
      if (f_status_is_not_error(status)) status = fl_macro_color_save_2(&context->title,     context->color_format, context->color_list.bold, context->color_list.yellow);
      if (f_status_is_not_error(status)) status = fl_macro_color_save_1(&context->notable,   context->color_format, context->color_list.bold);
      if (f_status_is_not_error(status)) status = fl_macro_color_save_2(&context->important, context->color_format, context->color_list.bold, context->color_list.green);
      if (f_status_is_not_error(status)) status = fl_macro_color_save_1(&context->standout,  context->color_format, context->color_list.green);
    }

    return status;
  }
#endif // _di_fl_color_load_context_

#ifdef __cplusplus
} // extern "C"
#endif
