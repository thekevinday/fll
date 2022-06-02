#include "test-fss.h"
#include "test-fss-sets_decimate_by.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_set_decimate_by__parameter_checking(void **state) {

  const int length = 5;
  f_fss_set_t data = f_fss_set_t_initialize;

  {
    const f_status_t status = f_fss_set_decimate_by(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.objects.used, 0);
    assert_int_equal(data.contents.size, 0);
  }

  assert_null(data.objects.array);
  assert_null(data.contents.array);
}

void test__f_fss_set_decimate_by__returns_data_not(void **state) {

  const int length = 5;
  f_fss_set_t data = f_fss_set_t_initialize;

  {
    const f_status_t status = f_fss_set_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.objects.used, 0);
    assert_int_equal(data.contents.size, length);
  }

  {
    const f_status_t status = f_fss_set_decimate_by(0, &data);

    assert_int_equal(status, F_data_not);
    assert_int_equal(data.objects.used, 0);
    assert_int_equal(data.contents.size, length);
  }

  free((void *) data.objects.array);
  free((void *) data.contents.array);
}

void test__f_fss_set_decimate_by__works(void **state) {

  const int length = 5;
  f_fss_set_t data = f_fss_set_t_initialize;

  {
    const f_status_t status = f_fss_set_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.objects.used, 0);
    assert_int_equal(data.contents.size, length);
  }

  {
    const f_status_t status = f_fss_set_decimate_by(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.objects.used, 0);
    assert_int_equal(data.contents.size, 0);
  }

  assert_null(data.objects.array);
  assert_null(data.contents.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
