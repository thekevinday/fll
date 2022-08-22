#include "color.h"
#include "private-color.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_color_load_context_
  f_status_t f_color_load_context(const uint8_t mode, f_color_context_t * const context) {
    #ifndef _di_level_0_parameter_checking_
      if (!context) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    context->mode = mode;

    if (mode == f_color_mode_color_not_e) {
      macro_f_color_t_set_none(context->list);

      context->format.begin = f_string_empty_s;
      context->format.end = f_string_empty_s;
      context->format.medium = f_string_empty_s;

      context->set.error = f_color_set_empty_s;
      context->set.important = f_color_set_empty_s;
      context->set.normal = f_color_set_empty_s;
      context->set.normal_reset = f_color_set_empty_s;
      context->set.notable = f_color_set_empty_s;
      context->set.reset = f_color_set_empty_s;
      context->set.standout = f_color_set_empty_s;
      context->set.success = f_color_set_empty_s;
      context->set.title = f_color_set_empty_s;
      context->set.warning = f_color_set_empty_s;

      f_status_t status = F_none;

      if (context->error.size) {
        status = f_string_dynamic_resize(0, &context->error);
        if (F_status_is_error(status)) return status;
      }
      else {
        context->error.used = 0;
      }

      if (context->important.size) {
        status = f_string_dynamic_resize(0, &context->important);
        if (F_status_is_error(status)) return status;
      }
      else {
        context->important.used = 0;
      }

      if (context->normal.size) {
        status = f_string_dynamic_resize(0, &context->normal);
        if (F_status_is_error(status)) return status;
      }
      else {
        context->normal.used = 0;
      }

      if (context->normal_reset.size) {
        status = f_string_dynamic_resize(0, &context->normal_reset);
        if (F_status_is_error(status)) return status;
      }
      else {
        context->normal_reset.used = 0;
      }

      if (context->notable.size) {
        status = f_string_dynamic_resize(0, &context->notable);
        if (F_status_is_error(status)) return status;
      }
      else {
        context->notable.used = 0;
      }

      if (context->reset.size) {
        status = f_string_dynamic_resize(0, &context->reset);
        if (F_status_is_error(status)) return status;
      }
      else {
        context->reset.used = 0;
      }

      if (context->standout.size) {
        status = f_string_dynamic_resize(0, &context->standout);
        if (F_status_is_error(status)) return status;
      }
      else {
        context->standout.used = 0;
      }

      if (context->success.size) {
        status = f_string_dynamic_resize(0, &context->success);
        if (F_status_is_error(status)) return status;
      }
      else {
        context->success.used = 0;
      }

      if (context->title.size) {
        status = f_string_dynamic_resize(0, &context->title);
        if (F_status_is_error(status)) return status;
      }
      else {
        context->title.used = 0;
      }

      if (context->warning.size) {
        status = f_string_dynamic_resize(0, &context->warning);
        if (F_status_is_error(status)) return status;
      }
      else {
        context->warning.used = 0;
      }

      return F_none;
    }

    if (mode != f_color_mode_dark_e && mode != f_color_mode_light_e) return F_data_not;

    // Switch to the appropriate terminal color mode.
    {
      char *environment = getenv(f_color_terminal_name_s.string);

      if (!environment || strncmp(environment, f_color_terminal_value_linux_s.string, f_color_terminal_value_linux_s.used) == 0) {
        macro_f_color_t_set_linux(context->list);
      }
      else {
        macro_f_color_t_set_xterminal(context->list);
      }
    }

    f_status_t status = private_f_color_save_1(context->format, context->list.reset, &context->reset);

    if (F_status_is_error_not(status)) {
      status = private_f_color_save_1(context->format, context->list.yellow, &context->warning);
    }

    if (F_status_is_error_not(status)) {
      status = private_f_color_save_2(context->format, context->list.bold, context->list.red, &context->error);
    }

    if (F_status_is_error_not(status)) {
      status = private_f_color_save_2(context->format, context->list.bold, context->list.green, &context->success);
    }

    if (F_status_is_error_not(status)) {
      status = private_f_color_save_1(context->format, context->list.bold, &context->notable);
    }

    if (mode == f_color_mode_light_e) {
      if (F_status_is_error_not(status)) {
        status = private_f_color_save_2(context->format, context->list.bold, context->list.blue, &context->title);
      }

      if (F_status_is_error_not(status)) {
        status = private_f_color_save_1(context->format, context->list.blue, &context->important);
      }

      if (F_status_is_error_not(status)) {
        status = private_f_color_save_1(context->format, context->list.purple, &context->standout);
      }
    }
    else {
      if (F_status_is_error_not(status)) {
        status = private_f_color_save_2(context->format, context->list.bold, context->list.yellow, &context->title);
      }

      if (F_status_is_error_not(status)) {
        status = private_f_color_save_2(context->format, context->list.bold, context->list.green, &context->important);
      }

      if (F_status_is_error_not(status)) {
        status = private_f_color_save_1(context->format, context->list.green, &context->standout);
      }
    }

    if (F_status_is_error_not(status)) {
      context->set.error.before = &context->error;
      context->set.error.after = &context->reset;

      context->set.important.before = &context->important;
      context->set.important.after = &context->reset;

      context->set.normal.before = &context->normal;
      context->set.normal.after = &context->reset;

      context->set.normal_reset.before = &context->normal_reset;
      context->set.normal_reset.after = &context->reset;

      context->set.notable.before = &context->notable;
      context->set.notable.after = &context->reset;

      context->set.reset.before = &context->reset;
      context->set.reset.after = &context->reset;

      context->set.standout.before = &context->standout;
      context->set.standout.after = &context->reset;

      context->set.success.before = &context->success;
      context->set.success.after = &context->reset;

      context->set.title.before = &context->title;
      context->set.title.after = &context->reset;

      context->set.warning.before = &context->warning;
      context->set.warning.after = &context->reset;

      status = F_none;
    }

    return status;
  }
#endif // _di_f_color_load_context_

#ifndef _di_f_color_save_1_
  f_status_t f_color_save_1(const f_color_format_t format, const f_string_static_t color1, f_string_dynamic_t * const buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_color_save_1(format, color1, buffer);
  }
#endif // _di_f_color_save_1_

#ifndef _di_f_color_save_2_
  f_status_t f_color_save_2(const f_color_format_t format, const f_string_static_t color1, const f_string_static_t color2, f_string_dynamic_t * const buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_color_save_2(format, color1, color2, buffer);
  }
#endif // _di_f_color_save_2_

#ifndef _di_f_color_save_3_
  f_status_t f_color_save_3(const f_color_format_t format, const f_string_static_t color1, const f_string_static_t color2, const f_string_static_t color3, f_string_dynamic_t * const buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      const f_status_t status = f_string_dynamic_increase_by(format.begin.used + (format.medium.used * 2) + format.end.used + color1.used + color2.used + color3.used + 1, buffer);
      if (F_status_is_error(status)) return status;
    }

    if (color1.used) {
      memcpy(buffer->string + buffer->used, color1.string, sizeof(f_char_t) * color1.used);

      buffer->used += color1.used;

      if (color2.used) {
        if (format.medium.used) {
          memcpy(buffer->string + buffer->used, format.medium.string, sizeof(f_char_t) * format.medium.used);

          buffer->used += format.medium.used;
        }

        memcpy(buffer->string + buffer->used, color2.string, sizeof(f_char_t) * color2.used);

        buffer->used += color2.used;

        if (color3.used) {
          if (format.medium.used) {
            memcpy(buffer->string + buffer->used, format.medium.string, sizeof(f_char_t) * format.medium.used);

            buffer->used += format.medium.used;
          }

          memcpy(buffer->string + buffer->used, color3.string, sizeof(f_char_t) * color3.used);

          buffer->used += color3.used;
        }
      }
    }

    if (format.end.used) {
      memcpy(buffer->string + buffer->used, format.end.string, sizeof(f_char_t) * format.end.used);

      buffer->used += format.end.used;
    }

    buffer->string[buffer->used] = 0;

    return F_none;
  }
#endif // _di_f_color_save_3_

#ifndef _di_f_color_save_4_
  f_status_t f_color_save_4(const f_color_format_t format, const f_string_static_t color1, const f_string_static_t color2, const f_string_static_t color3, const f_string_static_t color4, f_string_dynamic_t * const buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      const f_status_t status = f_string_dynamic_increase_by(format.begin.used + (format.medium.used * 3) + format.end.used + color1.used + color2.used + color3.used + color4.used + 1, buffer);
      if (F_status_is_error(status)) return status;
    }

    if (color1.used) {
      memcpy(buffer->string + buffer->used, color1.string, sizeof(f_char_t) * color1.used);

      buffer->used += color1.used;

      if (color2.used) {
        if (format.medium.used) {
          memcpy(buffer->string + buffer->used, format.medium.string, sizeof(f_char_t) * format.medium.used);

          buffer->used += format.medium.used;
        }

        memcpy(buffer->string + buffer->used, color2.string, sizeof(f_char_t) * color2.used);

        buffer->used += color2.used;

        if (color3.used) {
          if (format.medium.used) {
            memcpy(buffer->string + buffer->used, format.medium.string, sizeof(f_char_t) * format.medium.used);

            buffer->used += format.medium.used;
          }

          memcpy(buffer->string + buffer->used, color3.string, sizeof(f_char_t) * color3.used);

          buffer->used += color3.used;

          if (color4.used) {
            if (format.medium.used) {
              memcpy(buffer->string + buffer->used, format.medium.string, sizeof(f_char_t) * format.medium.used);

              buffer->used += format.medium.used;
            }

            memcpy(buffer->string + buffer->used, color4.string, sizeof(f_char_t) * color4.used);

            buffer->used += color4.used;
          }
        }
      }
    }

    if (format.end.used) {
      memcpy(buffer->string + buffer->used, format.end.string, sizeof(f_char_t) * format.end.used);

      buffer->used += format.end.used;
    }

    buffer->string[buffer->used] = 0;

    return F_none;
  }
#endif // _di_f_color_save_4_

#ifndef _di_f_color_save_5_
  f_status_t f_color_save_5(const f_color_format_t format, const f_string_static_t color1, const f_string_static_t color2, const f_string_static_t color3, const f_string_static_t color4, const f_string_static_t color5, f_string_dynamic_t * const buffer) {
    #ifndef _di_level_0_parameter_checking_
      if (!buffer) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      const f_status_t status = f_string_dynamic_increase_by(format.begin.used + (format.medium.used * 4) + format.end.used + color1.used + color2.used + color3.used + color4.used + color5.used + 1, buffer);
      if (F_status_is_error(status)) return status;
    }

    if (format.begin.used) {
      memcpy(buffer->string + buffer->used, format.begin.string, sizeof(f_char_t) * format.begin.used);

      buffer->used += format.begin.used;
    }

    if (color1.used) {
      memcpy(buffer->string + buffer->used, color1.string, sizeof(f_char_t) * color1.used);

      buffer->used += color1.used;

      if (color2.used) {
        if (format.medium.used) {
          memcpy(buffer->string + buffer->used, format.medium.string, sizeof(f_char_t) * format.medium.used);

          buffer->used += format.medium.used;
        }

        memcpy(buffer->string + buffer->used, color2.string, sizeof(f_char_t) * color2.used);

        buffer->used += color2.used;

        if (color3.used) {
          if (format.medium.used) {
            memcpy(buffer->string + buffer->used, format.medium.string, sizeof(f_char_t) * format.medium.used);

            buffer->used += format.medium.used;
          }

          memcpy(buffer->string + buffer->used, color3.string, sizeof(f_char_t) * color3.used);

          buffer->used += color3.used;

          if (color4.used) {
            if (format.medium.used) {
              memcpy(buffer->string + buffer->used, format.medium.string, sizeof(f_char_t) * format.medium.used);

              buffer->used += format.medium.used;
            }

            memcpy(buffer->string + buffer->used, color4.string, sizeof(f_char_t) * color4.used);

            buffer->used += color4.used;

            if (color5.used) {
              if (format.medium.used) {
                memcpy(buffer->string + buffer->used, format.medium.string, sizeof(f_char_t) * format.medium.used);

                buffer->used += format.medium.used;
              }

              memcpy(buffer->string + buffer->used, color5.string, sizeof(f_char_t) * color5.used);

              buffer->used += color5.used;
            }
          }
        }
      }
    }

    if (format.end.used) {
      memcpy(buffer->string + buffer->used, format.end.string, sizeof(f_char_t) * format.end.used);

      buffer->used += format.end.used;
    }

    buffer->string[buffer->used] = 0;

    return F_none;
  }
#endif // _di_f_color_save_5_

#ifdef __cplusplus
} // extern "C"
#endif
