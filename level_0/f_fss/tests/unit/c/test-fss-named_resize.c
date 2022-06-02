#include "test-fss.h"
#include "test-fss-nameds_resize.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_named_resize__parameter_checking(void **state) {

  const int length = 5;
  f_fss_named_t data = f_fss_named_t_initialize;

  {
    const f_status_t status = f_fss_named_resize(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.objects.used, 0);
    assert_int_equal(data.objects.size, 0);
    assert_int_equal(data.contents.used, 0);
    assert_int_equal(data.contents.size, 0);
    assert_int_equal(data.quotess.used, 0);
    assert_int_equal(data.quotess.size, 0);
  }

  assert_null(data.objects.array);
  assert_null(data.contents.array);
  assert_null(data.quotess.array);
}

void test__f_fss_named_resize__works(void **state) {

  const int length = 5;
  f_fss_named_t data = f_fss_named_t_initialize;

  {
    const f_status_t status = f_fss_named_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.objects.used, 0);
    assert_int_equal(data.objects.size, length);
    assert_int_equal(data.contents.used, 0);
    assert_int_equal(data.contents.size, length);
    assert_int_equal(data.quotess.used, 0);
    assert_int_equal(data.quotess.size, length);
  }

  free((void *) data.objects.array);
  free((void *) data.contents.array);
  free((void *) data.quotess.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
