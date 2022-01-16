#include "color.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_color_load_context_
  f_status_t f_color_load_context(f_color_context_t *context, const bool use_light_colors) {
    #ifndef _di_level_0_parameter_checking_
      if (!context) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    // Switch to the appropriate terminal color mode.
    {
      char *environment = getenv("TERM");

      if (!environment || strncmp(environment, "linux", 6) == 0) {
        macro_f_color_t_set_linux(context->list);
      }
      else {
        macro_f_color_t_set_xterminal(context->list);
      }
    }

    f_status_t status = macro_fl_color_save_1(&context->reset, context->format, context->list.reset);

    if (F_status_is_error_not(status)) {
      status = macro_fl_color_save_1(&context->warning, context->format, context->list.yellow);
    }

    if (F_status_is_error_not(status)) {
      status = macro_fl_color_save_2(&context->error, context->format, context->list.bold, context->list.red);
    }

    if (F_status_is_error_not(status)) {
      status = macro_fl_color_save_2(&context->success, context->format, context->list.bold, context->list.green);
    }

    if (F_status_is_error_not(status)) {
      status = macro_fl_color_save_1(&context->notable, context->format, context->list.bold);
    }

    if (use_light_colors) {
      if (F_status_is_error_not(status)) {
        status = macro_fl_color_save_2(&context->title, context->format, context->list.bold, context->list.blue);
      }

      if (F_status_is_error_not(status)) {
        status = macro_fl_color_save_1(&context->important, context->format, context->list.blue);
      }

      if (F_status_is_error_not(status)) {
        status = macro_fl_color_save_1(&context->standout,  context->format, context->list.purple);
      }

      if (F_status_is_error_not(status)) {
        context->mode = F_color_mode_light_d;
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
        status = macro_fl_color_save_1(&context->standout, context->format, context->list.green);
      }

      if (F_status_is_error_not(status)) {
        context->mode = F_color_mode_dark_d;
      }
    }

    if (F_status_is_error_not(status)) {
      context->set.reset.before = &context->reset;
      context->set.reset.after = &context->reset;

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

      context->set.success.before = &context->success;
      context->set.success.after = &context->reset;

      context->set.normal.before = &context->normal;
      context->set.normal.after = &context->reset;

      context->set.normal_reset.before = &context->normal_reset;
      context->set.normal_reset.after = &context->reset;
    }

    return status;
  }
#endif // _di_f_color_load_context_

#ifndef _di_f_color_save_
  f_status_t f_color_save(f_string_dynamic_t * const buffer, const f_color_format_t format, const char *color1, const char *color2, const char *color3, const char *color4, const char *color5) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!color1) return F_status_set_error(F_parameter);

      // Require all data to be in the proper order.
      if (!color2 && (color3 || color4 || color5)) return F_status_set_error(F_parameter);
      if (!color3 && (color4 || color5))           return F_status_set_error(F_parameter);
      if (!color4 && color5)                       return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_array_length_t size_string = 0;
    uint8_t size_begin = 0;
    uint8_t size_medium = 0;
    uint8_t size_end = 0;
    uint8_t size_color1 = 0;
    uint8_t size_color2 = 0;
    uint8_t size_color3 = 0;
    uint8_t size_color4 = 0;
    uint8_t size_color5 = 0;

    if (format.begin) {
      size_begin = strnlen(format.begin, F_color_max_size_d);
      size_string += size_begin;
    }

    if (format.medium) {
      size_medium += strnlen(format.medium, F_color_max_size_d);
    }

    if (format.end) {
      size_end = strnlen(format.end, F_color_max_size_d);
      size_string += size_end;
    }

    size_color1 = strnlen(color1, F_color_max_size_d);
    size_string += size_color1;

    if (color2) {
      size_color2 = strnlen(color2, F_color_max_size_d);
      size_string += size_color2;
    }

    if (color3) {
      size_color3 = strnlen(color3, F_color_max_size_d);
      size_string += size_color3;
    }

    if (color4) {
      size_color4 = strnlen(color4, F_color_max_size_d);
      size_string += size_color4;
    }

    if (color5) {
      size_color5 = strnlen(color5, F_color_max_size_d);
      size_string += size_color5;
    }

    {
      const f_status_t status = f_string_dynamic_increase_by(size_string + 1, buffer);
      if (F_status_is_error(status)) return status;
    }

    if (!color2) {
      if (size_begin) {
        memcpy(buffer->string + buffer->used, format.begin, size_begin);
        buffer->used += size_begin;
      }

      memcpy(buffer->string + buffer->used, color1, size_color1);
      buffer->used += size_color1;

      if (size_end) {
        memcpy(buffer->string + buffer->used, format.end, size_end);
        buffer->used += size_end;
      }
    }
    else if (!color3) {
      if (size_begin) {
        memcpy(buffer->string + buffer->used, format.begin, size_begin);
        buffer->used += size_begin;
      }

      memcpy(buffer->string + buffer->used, color1, size_color1);
      buffer->used += size_color1;

      if (size_medium) {
        memcpy(buffer->string + buffer->used, format.medium, size_medium);
        buffer->used += size_medium;
      }

      memcpy(buffer->string + buffer->used, color2, size_color2);
      buffer->used += size_color2;

      if (size_end) {
        memcpy(buffer->string + buffer->used, format.end, size_end);
        buffer->used += size_end;
      }
    }
    else if (!color4) {
      if (size_begin) {
        memcpy(buffer->string + buffer->used, format.begin, size_begin);
        buffer->used += size_begin;
      }

      memcpy(buffer->string + buffer->used, color1, size_color1);
      buffer->used += size_color1;

      if (size_medium) {
        memcpy(buffer->string + buffer->used, format.medium, size_medium);
        buffer->used += size_medium;
      }

      memcpy(buffer->string + buffer->used, color2, size_color2);
      buffer->used += size_color2;

      if (size_medium) {
        memcpy(buffer->string + buffer->used, format.medium, size_medium);
        buffer->used += size_medium;
      }

      memcpy(buffer->string + buffer->used, color3, size_color3);
      buffer->used += size_color3;

      if (size_end) {
        memcpy(buffer->string + buffer->used, format.end, size_end);
        buffer->used += size_end;
      }
    }
    else if (!color5) {
      if (size_begin) {
        memcpy(buffer->string + buffer->used, format.begin, size_begin);
        buffer->used += size_begin;
      }

      memcpy(buffer->string + buffer->used, color1, size_color1);
      buffer->used += size_color1;

      if (size_medium) {
        memcpy(buffer->string + buffer->used, format.medium, size_medium);
        buffer->used += size_medium;
      }

      memcpy(buffer->string + buffer->used, color2, size_color2);
      buffer->used += size_color2;

      if (size_medium) {
        memcpy(buffer->string + buffer->used, format.medium, size_medium);
        buffer->used += size_medium;
      }

      memcpy(buffer->string + buffer->used, color3, size_color3);
      buffer->used += size_color3;

      if (size_medium) {
        memcpy(buffer->string + buffer->used, format.medium, size_medium);
        buffer->used += size_medium;
      }

      memcpy(buffer->string + buffer->used, color4, size_color4);
      buffer->used += size_color4;

      if (size_end) {
        memcpy(buffer->string + buffer->used, format.end, size_end);
        buffer->used += size_end;
      }
    }
    else {
      if (size_begin) {
        memcpy(buffer->string + buffer->used, format.begin, size_begin);
        buffer->used += size_begin;
      }

      memcpy(buffer->string + buffer->used, color1, size_color1);
      buffer->used += size_color1;

      if (size_medium) {
        memcpy(buffer->string + buffer->used, format.medium, size_medium);
        buffer->used += size_medium;
      }

      memcpy(buffer->string + buffer->used, color2, size_color2);
      buffer->used += size_color2;

      if (size_medium) {
        memcpy(buffer->string + buffer->used, format.medium, size_medium);
        buffer->used += size_medium;
      }

      memcpy(buffer->string + buffer->used, color3, size_color3);
      buffer->used += size_color3;

      if (size_medium) {
        memcpy(buffer->string + buffer->used, format.medium, size_medium);
        buffer->used += size_medium;
      }

      memcpy(buffer->string + buffer->used, color4, size_color4);
      buffer->used += size_color4;

      if (size_medium) {
        memcpy(buffer->string + buffer->used, format.medium, size_medium);
        buffer->used += size_medium;
      }

      memcpy(buffer->string + buffer->used, color5, size_color5);
      buffer->used += size_color5;

      if (size_end) {
        memcpy(buffer->string + buffer->used, format.end, size_end);
        buffer->used += size_end;
      }
    }

    buffer->string[buffer->used] = 0;

    return F_none;
  }
#endif // _di_f_color_save_

#ifdef __cplusplus
} // extern "C"
#endif
