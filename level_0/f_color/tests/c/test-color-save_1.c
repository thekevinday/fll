#include "test-color.h"
#include "test-color-save_1.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_level_0_parameter_checking_
  void test__f_color_save_1_parameter_checking(void **state) {

    f_string_static_t buffer = f_string_static_t_initialize;
    const f_color_format_t format = f_color_format_t_initialize;
    const f_string_static_t color = macro_f_string_static_t_initialize("color", 5);

    {
      const f_status_t status = f_color_save_1(format, color, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_color_save_1_works(void **state) {

  f_color_context_t context = f_color_context_t_initialize;
  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
  const f_color_format_t format = f_color_format_t_initialize;
  const f_string_static_t color1 = macro_f_string_static_t_initialize("color1", 6);

  {
    f_status_t status = F_none;

    macro_f_color_context_t_new(status, context);
  }

  {
    const f_status_t status = f_color_save_1(format, color1, &buffer);

    assert_int_equal(status, F_none);
    assert_string_equal(buffer.string, "color1");
  }

  macro_f_color_context_t_delete_simple(context);

  f_string_dynamic_resize(0, &buffer);
}

#ifdef __cplusplus
} // extern "C"
#endif
