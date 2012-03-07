/* FLL - Level 1
 * Project:       Colors
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 */
#include <level_1/colors.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fl_set_color_
  f_return_status fl_set_color(f_file_type file, const f_colors_format format, const f_autochar *color1, const f_autochar *color2, const f_autochar *color3, const f_autochar *color4, const f_autochar *color5){
    #ifndef _di_level_1_parameter_checking_
      if (file   == f_null) return f_invalid_parameter;
      if (color1 == f_null) return f_invalid_parameter;

      // make sure all data is in the proper order
      if (color2 == f_null && (color3 != f_null || color4 != f_null || color5 != f_null)) return f_invalid_parameter;
      if (color3 == f_null && (color4 != f_null || color5 != f_null))                     return f_invalid_parameter;
      if (color4 == f_null && color5 != f_null)                                           return f_invalid_parameter;
    #endif // _di_level_1_parameter_checking_

    if      (color2 == f_null) fprintf(file, "%s%s%s",                 format.begin, color1, format.end);
    else if (color3 == f_null) fprintf(file, "%s%s%s%s%s",             format.begin, color1, format.medium, color2, format.end);
    else if (color4 == f_null) fprintf(file, "%s%s%s%s%s%s%s",         format.begin, color1, format.medium, color2, format.medium, color3, format.end);
    else if (color5 == f_null) fprintf(file, "%s%s%s%s%s%s%s%s%s",     format.begin, color1, format.medium, color2, format.medium, color3, format.medium, color4, format.end);
    else                       fprintf(file, "%s%s%s%s%s%s%s%s%s%s%s", format.begin, color1, format.medium, color2, format.medium, color3, format.medium, color4, format.medium, color5, format.end);

    return f_none;
  }
#endif // _di_fl_set_color_

#ifndef _di_fl_save_color_
  f_return_status fl_save_color(f_dynamic_string *buffer, const f_colors_format format, const f_autochar *color1, const f_autochar *color2, const f_autochar *color3, const f_autochar *color4, const f_autochar *color5){
    #ifndef _di_level_1_parameter_checking_
      if (buffer == f_null) return f_invalid_parameter;
      if (color1 == f_null) return f_invalid_parameter;

      // make sure all data is in the proper order
      if (color2 == f_null && (color3 != f_null || color4 != f_null || color5 != f_null)) return f_invalid_parameter;
      if (color3 == f_null && (color4 != f_null || color5 != f_null))                     return f_invalid_parameter;
      if (color4 == f_null && color5 != f_null)                                           return f_invalid_parameter;
    #endif // _di_level_1_parameter_checking_

    f_string_length string_size = strnlen(format.begin, f_color_max_size) + strnlen(format.end, f_color_max_size) + 1;

    if      (color2 == f_null) string_size += strnlen(color1, f_color_max_size);
    else if (color3 == f_null) string_size += strnlen(color1, f_color_max_size) + strnlen(color2, f_color_max_size);
    else if (color4 == f_null) string_size += strnlen(color1, f_color_max_size) + strnlen(color2, f_color_max_size) + strnlen(color3, f_color_max_size);
    else if (color5 == f_null) string_size += strnlen(color1, f_color_max_size) + strnlen(color2, f_color_max_size) + strnlen(color3, f_color_max_size) + strnlen(color4, f_color_max_size);
    else                       string_size += strnlen(color1, f_color_max_size) + strnlen(color2, f_color_max_size) + strnlen(color3, f_color_max_size) + strnlen(color4, f_color_max_size) + strnlen(color5, f_color_max_size);

    // make sure there is enough allocated space, if not, then allocate some more
    if (buffer->size - buffer->used - 1 < string_size){
      f_status status = f_status_initialize;

      f_resize_dynamic_string(status, (*buffer), buffer->used + string_size + 1); // the additional 1 is the EOS

      if (f_macro_test_for_allocation_errors(status)){
        return status;
      }
    }

    if (color2 == f_null){
      strncat(buffer->string, format.begin, f_color_max_size);
      strncat(buffer->string, color1, f_color_max_size);
      strncat(buffer->string, format.end, f_color_max_size);
    } else if (color3 == f_null){
      strncat(buffer->string, format.begin, f_color_max_size);
      strncat(buffer->string, color1, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color2, f_color_max_size);
      strncat(buffer->string, format.end, f_color_max_size);
    } else if (color4 == f_null){
      strncat(buffer->string, format.begin, f_color_max_size);
      strncat(buffer->string, color1, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color2, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color3, f_color_max_size);
      strncat(buffer->string, format.end, f_color_max_size);
    } else if (color5 == f_null){
      strncat(buffer->string, format.begin, f_color_max_size);
      strncat(buffer->string, color1, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color2, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color3, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color4, f_color_max_size);
      strncat(buffer->string, format.end, f_color_max_size);
    } else {
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
#endif // _di_fl_save_color_

#ifndef _di_fl_print_color_
  f_return_status fl_print_color(f_file_type file, const f_dynamic_string start_color, const f_dynamic_string end_color, const f_autochar *string, ...){
    #ifndef _di_level_1_parameter_checking_
      if (file   == f_null) return f_invalid_parameter;
      if (string == f_null) return f_invalid_parameter;
    #endif // _di_level_1_parameter_checking_

    if (start_color.used != 0){
      fprintf(file, "%s", start_color.string);
    }

    va_list ap;

    va_start(ap, string);

    vfprintf(file, string, ap);

    va_end(ap);

    if (end_color.used != 0){
      fprintf(file, "%s", end_color.string);
    }

    return f_none;
  }
#endif // _di_fl_print_color_

#ifndef _di_fl_print_color_line_
  f_return_status fl_print_color_line(f_file_type file, const f_dynamic_string start_color, const f_dynamic_string end_color, const f_autochar *string, ...){
    #ifndef _di_level_1_parameter_checking_
      if (file   == f_null) return f_invalid_parameter;
      if (string == f_null) return f_invalid_parameter;
    #endif // _di_level_1_parameter_checking_

    if (start_color.used != 0){
      fprintf(file, "%s", start_color.string);
    }

    va_list ap;

    va_start(ap, string);

    vfprintf(file, string, ap);

    va_end(ap);

    if (end_color.used != 0){
      fprintf(file, "%s", end_color.string);
    }

    // now print the trailing newline, this is done _after_ ending the colors to avoid color wrapping issues that can happen when a color code follows a newline
    fprintf(file, "\n");

    return f_none;
  }
#endif // _di_fl_print_color_line_

#ifndef _di_fl_print_color_code_
  f_return_status fl_print_color_code(f_file_type file, const f_dynamic_string color){
    if (color.used != 0){
      fprintf(file, "%s", color.string);
    }

    return f_none;
  }
#endif // _di_fl_print_color_code_

#ifdef __cplusplus
} // extern "C"
#endif
