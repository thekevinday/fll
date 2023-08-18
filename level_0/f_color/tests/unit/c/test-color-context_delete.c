#include "test-color.h"
#include "test-color-context_delete.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_color_context_delete__frees_memory(void **state) {

  const f_number_unsigned_t size = 3;

  f_color_context_t context = f_color_context_t_initialize;

  {
    const f_status_t status = f_string_dynamic_resize(size, &context.reset);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.reset.size, 0);
    assert_non_null(context.reset.string);
  }

  {
    const f_status_t status = f_string_dynamic_resize(size, &context.warning);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.warning.size, 0);
    assert_non_null(context.warning.string);
  }

  {
    const f_status_t status = f_string_dynamic_resize(size, &context.error);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.error.size, 0);
    assert_non_null(context.error.string);
  }

  {
    const f_status_t status = f_string_dynamic_resize(size, &context.title);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.title.size, 0);
    assert_non_null(context.title.string);
  }

  {
    const f_status_t status = f_string_dynamic_resize(size, &context.notable);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.notable.size, 0);
    assert_non_null(context.notable.string);
  }

  {
    const f_status_t status = f_string_dynamic_resize(size, &context.important);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.important.size, 0);
    assert_non_null(context.important.string);
  }

  {
    const f_status_t status = f_string_dynamic_resize(size, &context.standout);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.standout.size, 0);
    assert_non_null(context.standout.string);
  }

  {
    const f_status_t status = f_string_dynamic_resize(size, &context.success);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.success.size, 0);
    assert_non_null(context.success.string);
  }

  {
    const f_status_t status = f_string_dynamic_resize(size, &context.normal);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.normal.size, 0);
    assert_non_null(context.normal.string);
  }

  {
    const f_status_t status = f_string_dynamic_resize(size, &context.normal_reset);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.normal_reset.size, 0);
    assert_non_null(context.normal_reset.string);
  }

  {
    const f_status_t status = f_color_context_delete(&context);

    assert_int_equal(status, F_okay);
    assert_int_equal(context.reset.size, 0);
    assert_int_equal(context.warning.size, 0);
    assert_int_equal(context.error.size, 0);
    assert_int_equal(context.title.size, 0);
    assert_int_equal(context.notable.size, 0);
    assert_int_equal(context.important.size, 0);
    assert_int_equal(context.standout.size, 0);
    assert_int_equal(context.success.size, 0);
    assert_int_equal(context.normal.size, 0);
    assert_int_equal(context.normal_reset.size, 0);
  }
}

void test__f_color_context_delete__parameter_checking(void **state) {

  {
    const f_status_t status = f_color_context_delete(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
