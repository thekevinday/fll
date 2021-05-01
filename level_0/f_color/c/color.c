#include "color.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_color_set_
  f_status_t f_color_set(FILE *stream, const f_color_format_t format, const char *color1, const char *color2, const char *color3, const char *color4, const char *color5) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
      if (!color1) return F_status_set_error(F_parameter);

      // make sure all data is in the proper order
      if (!color2 && (color3 != 0 || color4 != 0 || color5 != 0)) return F_status_set_error(F_parameter);
      if (!color3 && (color4 != 0 || color5 != 0))                return F_status_set_error(F_parameter);
      if (!color4 && color5 != 0)                                 return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if      (!color2) fprintf(stream, "%s%s%s",                 format.begin, color1, format.end);
    else if (!color3) fprintf(stream, "%s%s%s%s%s",             format.begin, color1, format.medium, color2, format.end);
    else if (!color4) fprintf(stream, "%s%s%s%s%s%s%s",         format.begin, color1, format.medium, color2, format.medium, color3, format.end);
    else if (!color5) fprintf(stream, "%s%s%s%s%s%s%s%s%s",     format.begin, color1, format.medium, color2, format.medium, color3, format.medium, color4, format.end);
    else              fprintf(stream, "%s%s%s%s%s%s%s%s%s%s%s", format.begin, color1, format.medium, color2, format.medium, color3, format.medium, color4, format.medium, color5, format.end);

    return F_none;
  }
#endif // _di_f_color_set_

#ifndef _di_f_color_set_to_
  f_status_t f_color_set_to(const int id, const f_color_format_t format, const char *color1, const char *color2, const char *color3, const char *color4, const char *color5) {
    #ifndef _di_level_1_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
      if (!color1) return F_status_set_error(F_parameter);

      // make sure all data is in the proper order
      if (!color2 && (color3 != 0 || color4 != 0 || color5 != 0)) return F_status_set_error(F_parameter);
      if (!color3 && (color4 != 0 || color5 != 0))                return F_status_set_error(F_parameter);
      if (!color4 && color5 != 0)                                 return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if      (!color2) dprintf(id, "%s%s%s",                 format.begin, color1, format.end);
    else if (!color3) dprintf(id, "%s%s%s%s%s",             format.begin, color1, format.medium, color2, format.end);
    else if (!color4) dprintf(id, "%s%s%s%s%s%s%s",         format.begin, color1, format.medium, color2, format.medium, color3, format.end);
    else if (!color5) dprintf(id, "%s%s%s%s%s%s%s%s%s",     format.begin, color1, format.medium, color2, format.medium, color3, format.medium, color4, format.end);
    else              dprintf(id, "%s%s%s%s%s%s%s%s%s%s%s", format.begin, color1, format.medium, color2, format.medium, color3, format.medium, color4, format.medium, color5, format.end);

    return F_none;
  }
#endif // _di_f_color_set_to_

#ifndef _di_f_color_save_
  f_status_t f_color_save(f_string_dynamic_t *buffer, const f_color_format_t format, const char *color1, const char *color2, const char *color3, const char *color4, const char *color5) {
    #ifndef _di_level_1_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!color1) return F_status_set_error(F_parameter);

      // make sure all data is in the proper order
      if (!color2 && (color3 != 0 || color4 != 0 || color5 != 0)) return F_status_set_error(F_parameter);
      if (!color3 && (color4 != 0 || color5 != 0))                return F_status_set_error(F_parameter);
      if (!color4 && color5 != 0)                                 return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_array_length_t string_size = strnlen(format.begin, f_color_max_size) + strnlen(format.end, f_color_max_size) + 1;

    if      (!color2) string_size += strnlen(color1, f_color_max_size);
    else if (!color3) string_size += strnlen(color1, f_color_max_size) + strnlen(color2, f_color_max_size);
    else if (!color4) string_size += strnlen(color1, f_color_max_size) + strnlen(color2, f_color_max_size) + strnlen(color3, f_color_max_size);
    else if (!color5) string_size += strnlen(color1, f_color_max_size) + strnlen(color2, f_color_max_size) + strnlen(color3, f_color_max_size) + strnlen(color4, f_color_max_size);
    else              string_size += strnlen(color1, f_color_max_size) + strnlen(color2, f_color_max_size) + strnlen(color3, f_color_max_size) + strnlen(color4, f_color_max_size) + strnlen(color5, f_color_max_size);

    // make sure there is enough allocated space, if not, then allocate some more
    if (buffer->size - buffer->used - 1 < string_size) {
      f_status_t status = F_none;

      macro_f_string_dynamic_t_resize(status, (*buffer), buffer->used + string_size + 1); // the additional 1 is the EOS

      if (F_status_is_error(status)) {
        return status;
      }
    }

    if (!color2) {
      strncat(buffer->string, format.begin, f_color_max_size);
      strncat(buffer->string, color1, f_color_max_size);
      strncat(buffer->string, format.end, f_color_max_size);
    }
    else if (!color3) {
      strncat(buffer->string, format.begin, f_color_max_size);
      strncat(buffer->string, color1, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color2, f_color_max_size);
      strncat(buffer->string, format.end, f_color_max_size);
    }
    else if (!color4) {
      strncat(buffer->string, format.begin, f_color_max_size);
      strncat(buffer->string, color1, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color2, f_color_max_size);
      strncat(buffer->string, format.medium, f_color_max_size);
      strncat(buffer->string, color3, f_color_max_size);
      strncat(buffer->string, format.end, f_color_max_size);
    }
    else if (!color5) {
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
    buffer->string[buffer->used] = 0;

    return F_none;
  }
#endif // _di_f_color_save_

#ifndef _di_f_color_print_
  f_status_t f_color_print(FILE *stream, const f_color_set_t set, const f_string_t string, ...) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (set.before) {
      fprintf(stream, "%s", set.before->string);
    }

    va_list ap;

    va_start(ap, string);

    vfprintf(stream, string, ap);

    va_end(ap);

    if (set.after) {
      fprintf(stream, "%s", set.after->string);
    }

    return F_none;
  }
#endif // _di_f_color_print_

#ifndef _di_f_color_print2_
  f_status_t f_color_print2(FILE *stream, const f_color_set_t set, const f_color_set_t extra, const f_string_t string, ...) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    if (set.before) {
      fprintf(stream, "%s", set.before->string);
    }

    if (extra.before) {
      fprintf(stream, "%s", extra.before->string);
    }

    va_list ap;

    va_start(ap, string);

    vfprintf(stream, string, ap);

    va_end(ap);

    if (set.after) {
      fprintf(stream, "%s", set.after->string);
    }

    if (extra.after) {
      fprintf(stream, "%s", extra.after->string);
    }

    return F_none;
  }
#endif // _di_f_color_print2_

#ifndef _di_f_color_print_code_
  f_status_t f_color_print_code(FILE *stream, const f_string_static_t color) {
    #ifndef _di_level_1_parameter_checking_
      if (!stream) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (color.used) {
      fprintf(stream, "%s", color.string);
    }

    return F_none;
  }
#endif // _di_f_color_print_code_

#ifndef _di_f_color_print_code_to_
  f_status_t f_color_print_code_to(const int id, const f_string_static_t color) {
    #ifndef _di_level_1_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (color.used) {
      dprintf(id, "%s", color.string);
    }

    return F_none;
  }
#endif // _di_f_color_print_code_to_

#ifndef _di_f_color_print_to_
  f_status_t f_color_print_to(const int id, const f_color_set_t set, const f_string_t string, ...) {
    #ifndef _di_level_1_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    if (set.before) {
      dprintf(id, "%s", set.before->string);
    }

    va_list ap;

    va_start(ap, string);

    vdprintf(id, string, ap);

    va_end(ap);

    if (set.after) {
      dprintf(id, "%s", set.after->string);
    }

    return F_none;
  }
#endif // _di_f_color_print_to_

#ifndef _di_f_color_print2_to_
  f_status_t f_color_print2_to(const int id, const f_color_set_t set, const f_color_set_t extra, const f_string_t string, ...) {
    #ifndef _di_level_1_parameter_checking_
      if (id == -1) return F_status_set_error(F_parameter);
      if (!string) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    if (set.before) {
      dprintf(id, "%s", set.before->string);
    }

    if (extra.before) {
      dprintf(id, "%s", extra.before->string);
    }

    va_list ap;

    va_start(ap, string);

    vdprintf(id, string, ap);

    va_end(ap);

    if (set.after) {
      dprintf(id, "%s", set.after->string);
    }

    if (extra.after) {
      dprintf(id, "%s", extra.after->string);
    }

    return F_none;
  }
#endif // _di_f_color_print2_to_

#ifndef _di_f_color_load_context_
  f_status_t f_color_load_context(f_color_context_t *context, const bool use_light_colors) {
    #ifndef _di_level_1_parameter_checking_
      if (!context) return F_status_set_error(F_parameter);
    #endif // _di_level_1_parameter_checking_

    f_status_t status = F_none;

    // switch to the appropriate terminal color mode
    {
      char *environment = getenv("TERM");

      if (!environment || strncmp(environment, "linux", 6) == 0) {
        macro_f_color_t_set_linux(context->list);
      }
      else {
        macro_f_color_t_set_xterminal(context->list);
      }
    }

    status = macro_fl_color_save_1(&context->reset, context->format, context->list.reset);

    if (F_status_is_error_not(status)) {
      status = macro_fl_color_save_1(&context->warning, context->format, context->list.yellow);
    }

    if (F_status_is_error_not(status)) {
      status = macro_fl_color_save_2(&context->error, context->format, context->list.bold, context->list.red);
    }

    if (F_status_is_error_not(status)) {
      status = macro_fl_color_save_1(&context->notable, context->format, context->list.bold);
    }

    if (F_status_is_error_not(status)) {
      status = macro_fl_color_save_1(&context->standout,  context->format, context->list.purple);
    }

    if (use_light_colors) {
      if (F_status_is_error_not(status)) {
        status = macro_fl_color_save_2(&context->title, context->format, context->list.bold, context->list.blue);
      }

      if (F_status_is_error_not(status)) {
        status = macro_fl_color_save_1(&context->important, context->format, context->list.blue);
      }

      if (F_status_is_error_not(status)) {
        context->mode = f_color_mode_light;
      }

      if (F_status_is_error_not(status)) {
        status = macro_fl_color_save_1(&context->standout,  context->format, context->list.purple);
      }
    }
    else {
      if (F_status_is_error_not(status)) {
        status = macro_fl_color_save_2(&context->title, context->format, context->list.bold, context->list.yellow);
      }

      if (F_status_is_error_not(status)) {
        status = macro_fl_color_save_2(&context->important, context->format, context->list.bold, context->list.green);
      }

      if (F_status_is_error_not(status)) {
        context->mode = f_color_mode_dark;
      }

      if (F_status_is_error_not(status)) {
        status = macro_fl_color_save_1(&context->standout,  context->format, context->list.green);
      }
    }

    if (F_status_is_error_not(status)) {
      context->set.warning.before = &context->warning;
      context->set.warning.after = &context->reset;

      context->set.error.before = &context->error;
      context->set.error.after = &context->reset;

      context->set.title.before = &context->title;
      context->set.title.after = &context->reset;

      context->set.notable.before = &context->notable;
      context->set.notable.after = &context->reset;

      context->set.important.before = &context->important;
      context->set.important.after = &context->reset;

      context->set.standout.before = &context->standout;
      context->set.standout.after = &context->reset;

      context->set.normal.before = &context->normal;
      context->set.normal.after = &context->reset;

      context->set.warning.before = &context->warning;
      context->set.warning.after = &context->reset;

      context->set.normal_reset.before = &context->normal_reset;
      context->set.normal_reset.after = &context->reset;
    }

    return status;
  }
#endif // _di_f_color_load_context_

#ifdef __cplusplus
} // extern "C"
#endif
