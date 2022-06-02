#include "test-fss.h"
#include "test-fss-sets_adjust.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_set_adjust__parameter_checking(void **state) {

  const int length = 5;
  f_fss_set_t data = f_fss_set_t_initialize;

  {
    const f_status_t status = f_fss_set_adjust(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.objects.used, 0);
    assert_int_equal(data.contents.size, 0);
  }

  assert_null(data.objects.array);
  assert_null(data.contents.array);
}

void test__f_fss_set_adjust__works(void **state) {

  const int length = 5;
  f_fss_set_t data = f_fss_set_t_initialize;

  {
    const f_status_t status = f_fss_set_adjust(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.objects.used, 0);
    assert_int_equal(data.contents.size, length);
  }

  free((void *) data.objects.array);
  free((void *) data.contents.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
