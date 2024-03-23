#include "test-fss.h"
#include "test-fss-set_delete.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_set_delete__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_range_t base = f_range_t_initialize;
  f_range_t base_array[] = { base };
  f_ranges_t objects = { .array = base_array, .used = 0, .size = 1 };
  f_ranges_t objects_array[] = { objects };
  f_rangess_t contents = { .array = objects_array, .used = 0, .size = 1 };

  f_fss_set_t data = { .objects = objects, .contents = contents };

  {
    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_fss_set_delete(&data);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_fss_set_delete__parameter_checking(void **state) {

  {
    const f_status_t status = f_fss_set_delete(0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_fss_set_delete__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_fss_set_t data = f_fss_set_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_range_t), (void **) &data.objects.array, &data.objects.used, &data.objects.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_ranges_t), (void **) &data.contents.array, &data.contents.used, &data.contents.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_range_t), (void **) &data.contents.array[0].array, &data.contents.array[0].used, &data.contents.array[0].size);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_fss_set_delete(&data);

    assert_int_equal(status, F_okay);
    assert_int_equal(data.objects.size, 0);
    assert_int_equal(data.contents.size, 0);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif