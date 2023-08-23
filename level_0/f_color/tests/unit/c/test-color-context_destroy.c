#include "test-color.h"
#include "test-color-context_destroy.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_color_context_destroy__frees_memory(void **state) {

  const f_number_unsigned_t size = 3;

  f_color_context_t context = f_color_context_t_initialize;

  {
    const f_status_t status = f_memory_array_resize(size, sizeof(f_char_t), (void **) &context.reset.string, &context.reset.used, &context.reset.size);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.reset.size, 0);
    assert_non_null(context.reset.string);
  }

  {
    const f_status_t status = f_memory_array_resize(size, sizeof(f_char_t), (void **) &context.warning.string, &context.warning.used, &context.warning.size);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.warning.size, 0);
    assert_non_null(context.warning.string);
  }

  {
    const f_status_t status = f_memory_array_resize(size, sizeof(f_char_t), (void **) &context.error.string, &context.error.used, &context.error.size);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.error.size, 0);
    assert_non_null(context.error.string);
  }

  {
    const f_status_t status = f_memory_array_resize(size, sizeof(f_char_t), (void **) &context.title.string, &context.title.used, &context.title.size);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.title.size, 0);
    assert_non_null(context.title.string);
  }

  {
    const f_status_t status = f_memory_array_resize(size, sizeof(f_char_t), (void **) &context.notable.string, &context.notable.used, &context.notable.size);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.notable.size, 0);
    assert_non_null(context.notable.string);
  }

  {
    const f_status_t status = f_memory_array_resize(size, sizeof(f_char_t), (void **) &context.important.string, &context.important.used, &context.important.size);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.important.size, 0);
    assert_non_null(context.important.string);
  }

  {
    const f_status_t status = f_memory_array_resize(size, sizeof(f_char_t), (void **) &context.standout.string, &context.standout.used, &context.standout.size);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.standout.size, 0);
    assert_non_null(context.standout.string);
  }

  {
    const f_status_t status = f_memory_array_resize(size, sizeof(f_char_t), (void **) &context.success.string, &context.success.used, &context.success.size);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.success.size, 0);
    assert_non_null(context.success.string);
  }

  {
    const f_status_t status = f_memory_array_resize(size, sizeof(f_char_t), (void **) &context.normal.string, &context.normal.used, &context.normal.size);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.normal.size, 0);
    assert_non_null(context.normal.string);
  }

  {
    const f_status_t status = f_memory_array_resize(size, sizeof(f_char_t), (void **) &context.normal_reset.string, &context.normal_reset.used, &context.normal_reset.size);

    assert_int_equal(status, F_okay);
    assert_int_not_equal(context.normal_reset.size, 0);
    assert_non_null(context.normal_reset.string);
  }

  {
    const f_status_t status = f_color_context_destroy(&context);

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

void test__f_color_context_destroy__parameter_checking(void **state) {

  {
    const f_status_t status = f_color_context_destroy(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
