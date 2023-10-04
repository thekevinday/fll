#include "test-abstruse.h"
#include "test-abstruse-ss_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_abstruse_ss_delete_callback__fails(void **state) {

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

  f_abstruses_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_abstruses_t datas_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_abstrusess_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_abstruse_ss_delete_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_abstrusess_t datass = f_abstrusess_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_abstruse_t), (void **) &datass.array, &datass.used, &datass.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_abstruse_t), (void **) &datass.array[0].array, &datass.array[0].used, &datass.array[0].size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_string_t), (void **) &datass.array[0].array[0].is.a_dynamic, &datass.array[0].array[0].is.a_dynamic.used, &datass.array[0].array[0].is.a_dynamic.size);
    assert_int_equal(status, F_okay);

    datass.array[0].array[0].type = f_abstruse_dynamic_e;
  }

  {
    const f_status_t status = f_abstrusess_delete_callback(0, length, (void *) datass.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datass.array[0].size, 0);
  }

  free((void *) datass.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
