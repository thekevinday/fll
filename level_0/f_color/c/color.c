#include "color.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_color_load_context_
  f_status_t f_color_load_context(f_color_context_t *context, const bool use_light_colors) {
    #ifndef _di_level_0_parameter_checking_
      if (!context) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

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
        context->mode = F_color_mode_light_d;
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
        context->mode = F_color_mode_dark_d;
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

#ifndef _di_f_color_save_
  f_status_t f_color_save(f_string_dynamic_t *buffer, const f_color_format_t format, const char *color1, const char *color2, const char *color3, const char *color4, const char *color5) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
      if (!color1) return F_status_set_error(F_parameter);

      // make sure all data is in the proper order.
      if (!color2 && (color3 != 0 || color4 != 0 || color5 != 0)) return F_status_set_error(F_parameter);
      if (!color3 && (color4 != 0 || color5 != 0))                return F_status_set_error(F_parameter);
      if (!color4 && color5 != 0)                                 return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_array_length_t string_size = strnlen(format.begin, F_color_max_size_d) + strnlen(format.end, F_color_max_size_d) + 1;

    if      (!color2) string_size += strnlen(color1, F_color_max_size_d);
    else if (!color3) string_size += strnlen(color1, F_color_max_size_d) + strnlen(color2, F_color_max_size_d);
    else if (!color4) string_size += strnlen(color1, F_color_max_size_d) + strnlen(color2, F_color_max_size_d) + strnlen(color3, F_color_max_size_d);
    else if (!color5) string_size += strnlen(color1, F_color_max_size_d) + strnlen(color2, F_color_max_size_d) + strnlen(color3, F_color_max_size_d) + strnlen(color4, F_color_max_size_d);
    else              string_size += strnlen(color1, F_color_max_size_d) + strnlen(color2, F_color_max_size_d) + strnlen(color3, F_color_max_size_d) + strnlen(color4, F_color_max_size_d) + strnlen(color5, F_color_max_size_d);

    if (buffer->size - buffer->used - 1 < string_size) {
      f_status_t status = F_none;

      macro_f_string_dynamic_t_resize(status, (*buffer), buffer->used + string_size + 1);

      if (F_status_is_error(status)) {
        return status;
      }
    }

    if (!color2) {
      strncat(buffer->string, format.begin, F_color_max_size_d);
      strncat(buffer->string, color1, F_color_max_size_d);
      strncat(buffer->string, format.end, F_color_max_size_d);
    }
    else if (!color3) {
      strncat(buffer->string, format.begin, F_color_max_size_d);
      strncat(buffer->string, color1, F_color_max_size_d);
      strncat(buffer->string, format.medium, F_color_max_size_d);
      strncat(buffer->string, color2, F_color_max_size_d);
      strncat(buffer->string, format.end, F_color_max_size_d);
    }
    else if (!color4) {
      strncat(buffer->string, format.begin, F_color_max_size_d);
      strncat(buffer->string, color1, F_color_max_size_d);
      strncat(buffer->string, format.medium, F_color_max_size_d);
      strncat(buffer->string, color2, F_color_max_size_d);
      strncat(buffer->string, format.medium, F_color_max_size_d);
      strncat(buffer->string, color3, F_color_max_size_d);
      strncat(buffer->string, format.end, F_color_max_size_d);
    }
    else if (!color5) {
      strncat(buffer->string, format.begin, F_color_max_size_d);
      strncat(buffer->string, color1, F_color_max_size_d);
      strncat(buffer->string, format.medium, F_color_max_size_d);
      strncat(buffer->string, color2, F_color_max_size_d);
      strncat(buffer->string, format.medium, F_color_max_size_d);
      strncat(buffer->string, color3, F_color_max_size_d);
      strncat(buffer->string, format.medium, F_color_max_size_d);
      strncat(buffer->string, color4, F_color_max_size_d);
      strncat(buffer->string, format.end, F_color_max_size_d);
    }
    else {
      strncat(buffer->string, format.begin, F_color_max_size_d);
      strncat(buffer->string, color1, F_color_max_size_d);
      strncat(buffer->string, format.medium, F_color_max_size_d);
      strncat(buffer->string, color2, F_color_max_size_d);
      strncat(buffer->string, format.medium, F_color_max_size_d);
      strncat(buffer->string, color3, F_color_max_size_d);
      strncat(buffer->string, format.medium, F_color_max_size_d);
      strncat(buffer->string, color4, F_color_max_size_d);
      strncat(buffer->string, format.medium, F_color_max_size_d);
      strncat(buffer->string, color5, F_color_max_size_d);
      strncat(buffer->string, format.end, F_color_max_size_d);
    }

    buffer->used += string_size;
    buffer->string[buffer->used] = 0;

    return F_none;
  }
#endif // _di_f_color_save_

#ifdef __cplusplus
} // extern "C"
#endif
