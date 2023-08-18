#include "color.h"
#include "private-color.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_color_load_context_) || !defined(_di_f_color_save_1_)
  f_status_t private_f_color_save_1(const f_color_format_t format, const f_string_static_t color1, f_string_dynamic_t * const buffer) {

    {
      const f_status_t status = f_string_dynamic_increase_by(format.begin.used + format.end.used + color1.used + 1, buffer);
      if (F_status_is_error(status)) return status;
    }

    if (format.begin.used) {
      memcpy(buffer->string + buffer->used, format.begin.string, sizeof(f_char_t) * format.begin.used);

      buffer->used += format.begin.used;
    }

    if (color1.used) {
      memcpy(buffer->string + buffer->used, color1.string, sizeof(f_char_t) * color1.used);

      buffer->used += color1.used;
    }

    if (format.end.used) {
      memcpy(buffer->string + buffer->used, format.end.string, sizeof(f_char_t) * format.end.used);

      buffer->used += format.end.used;
    }

    buffer->string[buffer->used] = 0;

    return F_okay;
  }
#endif // !defined(_di_f_color_load_context_) || !defined(_di_f_color_save_2_)

#if !defined(_di_f_color_load_context_) || !defined(_di_f_color_save_2_)
  f_status_t private_f_color_save_2(const f_color_format_t format, const f_string_static_t color1, const f_string_static_t color2, f_string_dynamic_t * const buffer) {

    {
      const f_status_t status = f_string_dynamic_increase_by(format.begin.used + format.medium.used + format.end.used + color1.used + color2.used + 1, buffer);
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
      }
    }

    if (format.end.used) {
      memcpy(buffer->string + buffer->used, format.end.string, sizeof(f_char_t) * format.end.used);

      buffer->used += format.end.used;
    }

    buffer->string[buffer->used] = 0;

    return F_okay;
  }
#endif // !defined(_di_f_color_load_context_) || !defined(_di_f_color_save_2_)

#ifdef __cplusplus
} // extern "C"
#endif
