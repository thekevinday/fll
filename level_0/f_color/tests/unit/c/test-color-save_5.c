#include "test-color.h"
#include "test-color-save_5.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_color_save_5_parameter_checking(void **state) {

  const f_color_format_t format = f_color_format_t_initialize;
  const f_string_static_t color = macro_f_string_static_t_initialize_2("color", 5);

  {
    const f_status_t status = f_color_save_5(format, color, color, color, color, color, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_color_save_5_works(void **state) {

  f_color_context_t context = f_color_context_t_initialize;
  f_string_dynamic_t buffer = f_string_dynamic_t_initialize;
  const f_color_format_t format = f_color_format_t_initialize;
  const f_string_static_t color1 = macro_f_string_static_t_initialize_2("color1", 6);
  const f_string_static_t color2 = macro_f_string_static_t_initialize_2("color2", 6);
  const f_string_static_t color3 = macro_f_string_static_t_initialize_2("color3", 6);
  const f_string_static_t color4 = macro_f_string_static_t_initialize_2("color4", 6);
  const f_string_static_t color5 = macro_f_string_static_t_initialize_2("color5", 6);

  {
    f_status_t status = f_memory_array_resize(F_color_max_size_terminated_d, sizeof(f_char_t), (void **) &context.reset.string, &context.reset.used, &context.reset.size);

    if (F_status_is_error_not(status)) status = f_memory_array_resize(F_color_max_size_terminated_d, sizeof(f_char_t), (void **) &context.reset.string, &context.reset.used, &context.reset.size);
    if (F_status_is_error_not(status)) status = f_memory_array_resize(F_color_max_size_terminated_d, sizeof(f_char_t), (void **) &context.error.string, &context.error.used, &context.error.size);
    if (F_status_is_error_not(status)) status = f_memory_array_resize(F_color_max_size_terminated_d, sizeof(f_char_t), (void **) &context.important.string, &context.important.used, &context.important.size);
    if (F_status_is_error_not(status)) status = f_memory_array_resize(F_color_max_size_terminated_d, sizeof(f_char_t), (void **) &context.normal.string, &context.normal.used, &context.normal.size);
    if (F_status_is_error_not(status)) status = f_memory_array_resize(F_color_max_size_terminated_d, sizeof(f_char_t), (void **) &context.normal_reset.string, &context.normal_reset.used, &context.normal_reset.size);
    if (F_status_is_error_not(status)) status = f_memory_array_resize(F_color_max_size_terminated_d, sizeof(f_char_t), (void **) &context.notable.string, &context.notable.used, &context.notable.size);
    if (F_status_is_error_not(status)) status = f_memory_array_resize(F_color_max_size_terminated_d, sizeof(f_char_t), (void **) &context.standout.string, &context.standout.used, &context.standout.size);
    if (F_status_is_error_not(status)) status = f_memory_array_resize(F_color_max_size_terminated_d, sizeof(f_char_t), (void **) &context.success.string, &context.success.used, &context.success.size);
    if (F_status_is_error_not(status)) status = f_memory_array_resize(F_color_max_size_terminated_d, sizeof(f_char_t), (void **) &context.title.string, &context.title.used, &context.title.size);
    if (F_status_is_error_not(status)) status = f_memory_array_resize(F_color_max_size_terminated_d, sizeof(f_char_t), (void **) &context.warning.string, &context.warning.used, &context.warning.size);
  }

  {
    const f_status_t status = f_color_save_5(format, color1, color2, color3, color4, color5, &buffer);

    assert_int_equal(status, F_okay);
    assert_string_equal(buffer.string, "color1color2color3color4color5");
  }

  f_memory_array_resize(0, sizeof(f_char_t), (void **) &context.reset.string, &context.reset.used, &context.reset.size);
  f_memory_array_resize(0, sizeof(f_char_t), (void **) &context.error.string, &context.error.used, &context.error.size);
  f_memory_array_resize(0, sizeof(f_char_t), (void **) &context.important.string, &context.important.used, &context.important.size);
  f_memory_array_resize(0, sizeof(f_char_t), (void **) &context.normal.string, &context.normal.used, &context.normal.size);
  f_memory_array_resize(0, sizeof(f_char_t), (void **) &context.normal_reset.string, &context.normal_reset.used, &context.normal_reset.size);
  f_memory_array_resize(0, sizeof(f_char_t), (void **) &context.notable.string, &context.notable.used, &context.notable.size);
  f_memory_array_resize(0, sizeof(f_char_t), (void **) &context.standout.string, &context.standout.used, &context.standout.size);
  f_memory_array_resize(0, sizeof(f_char_t), (void **) &context.success.string, &context.success.used, &context.success.size);
  f_memory_array_resize(0, sizeof(f_char_t), (void **) &context.title.string, &context.title.used, &context.title.size);
  f_memory_array_resize(0, sizeof(f_char_t), (void **) &context.warning.string, &context.warning.used, &context.warning.size);

  free((void *) buffer.string);
}

#ifdef __cplusplus
} // extern "C"
#endif
