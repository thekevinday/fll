#include "test-abstruse.h"
#include "test-abstruse-s_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_abstruse_s_delete_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_string_t a_string = "example";
  f_string_range_t a_range = macro_f_string_range_t_initialize_1(1, 2);
  f_string_static_t a_static = macro_f_string_static_t_initialize_1(a_string, 0, 7);
  f_string_dynamic_t a_dynamic = f_string_dynamic_t_initialize;

  f_abstruse_t data_0 = { .type = f_abstruse_range_e, .is.a_range = a_range };
  f_abstruse_t data_1 = { .type = f_abstruse_string_e, .is.a_string = a_string };
  f_abstruse_t data_2 = { .type = f_abstruse_dynamic_e, .is.a_dynamic = a_static };
  f_abstruse_t data_3 = { .type = f_abstruse_dynamic_e, .is.a_dynamic = a_dynamic };
  f_abstruse_t data_array[] = { data_0, data_1, data_2, data_3 };

  const f_number_unsigned_t length = 4;

  {
    const f_status_t status = f_string_append("a", 1, &data_array[3].is.a_dynamic);
    assert_int_equal(status, F_okay);
  }

  {
    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_abstruses_delete_callback(0, length, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  free((void *) data_array[3].is.a_dynamic.string);
}

void test__f_abstruse_s_delete_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  f_string_t a_string = "example";
  f_string_range_t a_range = macro_f_string_range_t_initialize_1(1, 2);
  f_string_static_t a_static = macro_f_string_static_t_initialize_1(a_string, 0, 7);
  f_string_dynamic_t a_dynamic = f_string_dynamic_t_initialize;

  f_abstruse_t data_0 = { .type = f_abstruse_range_e, .is.a_range = a_range };
  f_abstruse_t data_1 = { .type = f_abstruse_string_e, .is.a_string = a_string };
  f_abstruse_t data_2 = { .type = f_abstruse_dynamic_e, .is.a_dynamic = a_static };
  f_abstruse_t data_3 = { .type = f_abstruse_dynamic_e, .is.a_dynamic = a_dynamic };
  f_abstruse_t data_array[] = { data_0, data_1, data_2, data_3 };

  const f_number_unsigned_t length = 4;

  f_abstruses_t datas = macro_f_abstruses_t_initialize_2(data_array, length);

  {
    const f_status_t status = f_string_append("a", 1, &datas.array[3].is.a_dynamic);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_abstruses_delete_callback(0, length, (void *) datas.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datas.array[3].is.a_dynamic.size, 0);
  }

  free((void *) datas.array[3].is.a_dynamic.string);
}

#ifdef __cplusplus
} // extern "C"
#endif
