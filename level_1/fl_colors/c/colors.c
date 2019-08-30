#include <level_1/colors.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_color_set_
  f_return_status fl_color_set(FILE *file, const f_colors_format format, const char *color1, const char *color2, const char *color3, const char *color4, const char *color5) {
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
  f_return_status fl_color_save(f_dynamic_string *buffer, const f_colors_format format, const char *color1, const char *color2, const char *color3, const char *color4, const char *color5) {
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

      f_resize_dynamic_string(status, (*buffer), buffer->used + string_size + 1); // the additional 1 is the EOS

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
    buffer->string[buffer->used] = f_eos;

    return f_none;
  }
#endif // _di_fl_color_save_

#ifndef _di_fl_color_print_
  f_return_status fl_color_print(FILE *file, const f_dynamic_string start_color, const f_dynamic_string end_color, const char *string, ...) {
    #ifndef _di_level_1_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (string == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (start_color.used != 0) {
      f_status status = f_print_dynamic_string(file, start_color);

      if (f_status_is_error(status)) return status;
    }

    va_list ap;

    va_start(ap, string);

    vfprintf(file, string, ap);

    va_end(ap);

    if (end_color.used != 0) {
      f_status status = f_print_dynamic_string(file, end_color);

      if (f_status_is_error(status)) return status;
    }

    return f_none;
  }
#endif // _di_fl_color_print_

#ifndef _di_fl_color_print_line_
  f_return_status fl_color_print_line(FILE *file, const f_dynamic_string start_color, const f_dynamic_string end_color, const char *string, ...) {
    #ifndef _di_level_1_parameter_checking_
      if (file == 0) return f_status_set_error(f_invalid_parameter);
      if (string == 0) return f_status_set_error(f_invalid_parameter);
    #endif // _di_level_1_parameter_checking_

    if (start_color.used != 0) {
      f_status status = f_print_dynamic_string(file, start_color);

      if (f_status_is_error(status)) return status;
    }

    va_list ap;

    va_start(ap, string);

    vfprintf(file, string, ap);

    va_end(ap);

    if (end_color.used != 0) {
      f_status status = f_print_dynamic_string(file, end_color);

      if (f_status_is_error(status)) return status;
    }

    // now print the trailing newline, this is done _after_ ending the colors to avoid color wrapping issues that can happen when a color code follows a newline
    fprintf(file, "\n");

    return f_none;
  }
#endif // _di_fl_color_print_line_

#ifndef _di_fl_color_print_code_
  f_return_status fl_color_print_code(FILE *file, const f_dynamic_string color) {
    if (color.used != 0) {
      f_status status = f_print_dynamic_string(file, color);

      if (f_status_is_error(status)) return status;
    }

    return f_none;
  }
#endif // _di_fl_color_print_code_

#ifdef __cplusplus
} // extern "C"
#endif
