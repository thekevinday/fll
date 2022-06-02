#include "test-fss.h"
#include "test-fss-set_quote_resize.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_fss_set_quote_resize__parameter_checking(void **state) {

  const int length = 5;
  f_fss_set_quote_t data = f_fss_set_quote_t_initialize;

  {
    const f_status_t status = f_fss_set_quote_resize(length, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.objects.used, 0);
    assert_int_equal(data.objects.size, 0);
    assert_int_equal(data.contents.used, 0);
    assert_int_equal(data.contents.size, 0);
    assert_int_equal(data.objects_quote.used, 0);
    assert_int_equal(data.objects_quote.size, 0);
    assert_int_equal(data.contents_quote.used, 0);
    assert_int_equal(data.contents_quote.size, 0);
  }

  assert_null(data.objects.array);
  assert_null(data.contents.array);
  assert_null(data.objects_quote.array);
  assert_null(data.contents_quote.array);
}

void test__f_fss_set_quote_resize__works(void **state) {

  const int length = 5;
  f_fss_set_quote_t data = f_fss_set_quote_t_initialize;

  {
    const f_status_t status = f_fss_set_quote_resize(length, &data);

    assert_int_equal(status, F_none);
    assert_int_equal(data.objects.used, 0);
    assert_int_equal(data.objects.size, length);
    assert_int_equal(data.contents.used, 0);
    assert_int_equal(data.contents.size, length);
    assert_int_equal(data.objects_quote.used, 0);
    assert_int_equal(data.objects_quote.size, length);
    assert_int_equal(data.contents_quote.used, 0);
    assert_int_equal(data.contents_quote.size, length);
  }

  free((void *) data.objects.array);
  free((void *) data.contents.array);
  free((void *) data.objects_quote.array);
  free((void *) data.contents_quote.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
