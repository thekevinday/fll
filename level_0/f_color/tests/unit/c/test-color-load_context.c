#include "test-color.h"
#include "test-color-load_context.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_level_0_parameter_checking_
  void test__f_color_load_context__parameter_checking(void **state) {

    {
      const f_status_t status = f_color_load_context(F_true, 0);

      assert_int_equal(status, F_status_set_error(F_parameter));
    }
  }
#endif // _di_level_0_parameter_checking_

void test__f_color_load_context__works(void **state) {

  f_color_context_t context = f_color_context_t_initialize;

  f_string_t terms[3] = {
    "linux",
    "xterm-256color",
    0,
  };

  {
    f_status_t status = F_none;

    macro_f_color_context_t_new(status, context);
  }

  for (uint8_t i = 0; i < 2; ++i) {

    for (uint8_t j = 0; j < 3; ++j) {

      will_return(__wrap_getenv, i);
      will_return(__wrap_getenv, terms[j]);

      const f_status_t status = f_color_load_context(F_true, &context);

      assert_int_equal(status, F_none);

      assert_ptr_equal(context.set.reset.before, &context.reset);
      assert_ptr_equal(context.set.reset.after, &context.reset);

      assert_ptr_equal(context.set.warning.before, &context.warning);
      assert_ptr_equal(context.set.warning.after, &context.reset);

      assert_ptr_equal(context.set.error.before, &context.error);
      assert_ptr_equal(context.set.error.after, &context.reset);

      assert_ptr_equal(context.set.title.before, &context.title);
      assert_ptr_equal(context.set.title.after, &context.reset);

      assert_ptr_equal(context.set.notable.before, &context.notable);
      assert_ptr_equal(context.set.notable.after, &context.reset);

      assert_ptr_equal(context.set.important.before, &context.important);
      assert_ptr_equal(context.set.important.after, &context.reset);

      assert_ptr_equal(context.set.standout.before, &context.standout);
      assert_ptr_equal(context.set.standout.after, &context.reset);

      assert_ptr_equal(context.set.success.before, &context.success);
      assert_ptr_equal(context.set.success.after, &context.reset);

      assert_ptr_equal(context.set.normal.before, &context.normal);
      assert_ptr_equal(context.set.normal.after, &context.reset);

      assert_ptr_equal(context.set.normal_reset.before, &context.normal_reset);
      assert_ptr_equal(context.set.normal_reset.after, &context.reset);
    } // for
  } // for

  macro_f_color_context_t_delete_simple(context);
}

#ifdef __cplusplus
} // extern "C"
#endif
