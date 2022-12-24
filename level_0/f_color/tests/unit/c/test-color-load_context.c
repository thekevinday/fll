#include "test-color.h"
#include "test-color-load_context.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_color_load_context__parameter_checking(void **state) {

  {
    const f_status_t status = f_color_load_context(F_true, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_color_load_context__works(void **state) {

  f_color_context_t context = f_color_context_t_initialize;

  f_string_t terms[4] = {
    "linux",
    "xterm-256color",
    "unknown",
    0,
  };

  uint8_t modes[4] = {
    f_color_mode_none_e,
    f_color_mode_not_e,
    f_color_mode_dark_e,
    f_color_mode_light_e,
  };

  f_status_t statuss[4] = {
    F_data_not,
    F_none,
    F_none,
    F_none,
  };

  {
    f_status_t status = F_none;

    macro_f_color_context_t_new(status, context);
  }

  for (uint8_t i = 0; i < 4; ++i) {

    for (uint8_t j = 0; j < 4; ++j) {

      if (modes[j] == f_color_mode_dark_e || modes[j] == f_color_mode_light_e) {
        will_return(__wrap_getenv, 0);
        will_return(__wrap_getenv, terms[i]);
      }

      const f_status_t status = f_color_load_context(modes[j], &context);

      assert_int_equal(status, statuss[j]);

      if (modes[j] == f_color_mode_not_e) {
        assert_ptr_equal(context.set.reset.before, &f_string_empty_s);
        assert_ptr_equal(context.set.reset.after, &f_string_empty_s);

        assert_ptr_equal(context.set.warning.before, &f_string_empty_s);
        assert_ptr_equal(context.set.warning.after, &f_string_empty_s);

        assert_ptr_equal(context.set.error.before, &f_string_empty_s);
        assert_ptr_equal(context.set.error.after, &f_string_empty_s);

        assert_ptr_equal(context.set.title.before, &f_string_empty_s);
        assert_ptr_equal(context.set.title.after, &f_string_empty_s);

        assert_ptr_equal(context.set.notable.before, &f_string_empty_s);
        assert_ptr_equal(context.set.notable.after, &f_string_empty_s);

        assert_ptr_equal(context.set.important.before, &f_string_empty_s);
        assert_ptr_equal(context.set.important.after, &f_string_empty_s);

        assert_ptr_equal(context.set.standout.before, &f_string_empty_s);
        assert_ptr_equal(context.set.standout.after, &f_string_empty_s);

        assert_ptr_equal(context.set.success.before, &f_string_empty_s);
        assert_ptr_equal(context.set.success.after, &f_string_empty_s);

        assert_ptr_equal(context.set.normal.before, &f_string_empty_s);
        assert_ptr_equal(context.set.normal.after, &f_string_empty_s);

        assert_ptr_equal(context.set.normal_reset.before, &f_string_empty_s);
        assert_ptr_equal(context.set.normal_reset.after, &f_string_empty_s);
      }
      else if (statuss[j] == F_data_not) {
        // In this case, the data is not touched.
      }
      else {
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
      }
    } // for
  } // for

  macro_f_color_context_t_delete_simple(context);
}

#ifdef __cplusplus
} // extern "C"
#endif
