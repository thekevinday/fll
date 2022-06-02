#include "test-fss.h"
#include "test-fss-nests_resize.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_nest_resize__parameter_checking(void **state) {

  const int length = 5;
  f_fss_nest_t data = f_fss_nest_t_initialize;

  {
    const f_status_t status = f_fss_nest_resize(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.depth);
}

void test__f_fss_nest_resize__works(void **state) {

  const int length = 5;
  f_fss_nest_t data = f_fss_nest_t_initialize;

  {
    const f_status_t status = f_fss_nest_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, length);
  }

  free((void *) data.depth);
}

#ifdef __cplusplus
} // extern "C"
#endif
