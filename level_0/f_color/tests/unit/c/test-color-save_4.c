#include "test-color.h"
#include "test-color-save_4.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_color_save_4_parameter_checking(void **state) {

  const f_color_format_t format = f_color_format_t_initialize;
  const f_string_static_t color = macro_f_string_static_t_initialize2("color", 5);

  {
    const f_status_t status = f_color_save_4(format, color, color, color, color, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_color_save_4_works(void **state) {

  f_color_context_t context = f_color_context_t_initialize;
  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
  const f_color_format_t format = f_color_format_t_initialize;
  const f_string_static_t color1 = macro_f_string_static_t_initialize2("color1", 6);
  const f_string_static_t color2 = macro_f_string_static_t_initialize2("color2", 6);
  const f_string_static_t color3 = macro_f_string_static_t_initialize2("color3", 6);
  const f_string_static_t color4 = macro_f_string_static_t_initialize2("color4", 6);

  {
    f_status_t status = F_none;

    macro_f_color_context_t_new(status, context);
  }

  {
    const f_status_t status = f_color_save_4(format, color1, color2, color3, color4, &buffer);

    assert_int_equal(status, F_none);
    assert_string_equal(buffer.string, "color1color2color3color4");
  }

  macro_f_color_context_t_delete_simple(context);

  f_string_dynamic_resize(0, &buffer);
}

#ifdef __cplusplus
} // extern "C"
#endif
