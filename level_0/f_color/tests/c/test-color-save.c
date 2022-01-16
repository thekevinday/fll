#include "test-color.h"
#include "test-color-save.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_level_0_parameter_checking_
  void test__f_color_save__parameter_checking(void **state) {

    f_string_static_t buffer = f_string_static_t_initialize;
    const f_color_format_t format = f_color_format_t_initialize;
    const char *color = "color";

    {
      const f_status_t status = f_color_save(0, format, 0, 0, 0, 0, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }

    {
      const f_status_t status = f_color_save(&buffer, format, 0, 0, 0, 0, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }

    {
      const f_status_t status = f_color_save(&buffer, format, color, 0, color, 0, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }

    {
      const f_status_t status = f_color_save(&buffer, format, color, 0, color, color, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }

    {
      const f_status_t status = f_color_save(&buffer, format, color, 0, color, 0, color);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }

    {
      const f_status_t status = f_color_save(&buffer, format, color, 0, color, color, color);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }

    {
      const f_status_t status = f_color_save(&buffer, format, color, 0, 0, color, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }

    {
      const f_status_t status = f_color_save(&buffer, format, color, 0, 0, 0, color);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }

    {
      const f_status_t status = f_color_save(&buffer, format, color, color, 0, color, 0);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }

    {
      const f_status_t status = f_color_save(&buffer, format, color, color, 0, 0, color);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }

    {
      const f_status_t status = f_color_save(&buffer, format, color, color, color, 0, color);

      assert_int_equal(F_status_set_fine(status), F_parameter);
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_color_save__works(void **state) {

  f_color_context_t context = f_color_context_t_initialize;
  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
  const f_color_format_t format = f_color_format_t_initialize;
  const f_string_t color1 = "color1";
  const f_string_t color2 = "color2";
  const f_string_t color3 = "color3";
  const f_string_t color4 = "color4";
  const f_string_t color5 = "color5";

  {
    f_status_t status = F_none;

    macro_f_color_context_t_new(status, context);
  }

  {
    const f_status_t status = f_color_save(&buffer, format, color1, 0, 0, 0, 0);

    assert_int_equal(status, F_none);
    assert_string_equal(buffer.string, "color1");
  }

  {
    buffer.used = 0;

    const f_status_t status = f_color_save(&buffer, format, color1, color2, 0, 0, 0);

    assert_int_equal(status, F_none);
    assert_string_equal(buffer.string, "color1color2");
  }

  {
    buffer.used = 0;

    const f_status_t status = f_color_save(&buffer, format, color1, color2, color3, 0, 0);

    assert_int_equal(status, F_none);
    assert_string_equal(buffer.string, "color1color2color3");
  }

  {
    buffer.used = 0;

    const f_status_t status = f_color_save(&buffer, format, color1, color2, color3, color4, 0);

    assert_int_equal(status, F_none);
    assert_string_equal(buffer.string, "color1color2color3color4");
  }

  {
    buffer.used = 0;

    const f_status_t status = f_color_save(&buffer, format, color1, color2, color3, color4, color5);

    assert_int_equal(status, F_none);
    assert_string_equal(buffer.string, "color1color2color3color4color5");
  }

  macro_f_color_context_t_delete_simple(context);

  f_string_dynamic_resize(0, &buffer);
}

#ifdef __cplusplus
} // extern "C"
#endif
