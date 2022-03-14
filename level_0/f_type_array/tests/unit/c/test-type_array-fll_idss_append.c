#include "test-type_array.h"
#include "test-type_array-fll_idss_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_fll_idss_append__works(void **state) {

  const int length = 5;
  f_fll_ids_t source = f_fll_ids_t_initialize;
  f_fll_idss_t destination = f_fll_idss_t_initialize;

  const f_fll_id_t fll_id = { .name = "test", .type = 1, .used = 4 };

  {
    const f_status_t status = f_fll_ids_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  while (source.used < length) {
    memcpy(&source.array[source.used++], (void *) &fll_id, sizeof(f_fll_id_t));
  } // while

  {
    const f_status_t status = f_fll_idss_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].used, source.used);
    assert_int_equal(destination.array[0].size, source.used);

    for (f_array_length_t i = 0; i < destination.array[0].used; ++i) {

      assert_string_equal(destination.array[0].array[i].name, fll_id.name);
      assert_int_equal(destination.array[0].array[i].type, fll_id.type);
      assert_int_equal(destination.array[0].array[i].used, fll_id.used);
    } // for
  }

  for (f_array_length_t i = 0; i < destination.used; ++i) {
    free((void *) destination.array[i].array);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

void test__f_type_array_fll_idss_append__returns_data_not(void **state) {

  const int length = 5;
  f_fll_ids_t source = f_fll_idss_t_initialize;
  f_fll_idss_t destination = f_fll_idss_t_initialize;

  {
    const f_status_t status = f_fll_ids_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_fll_idss_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_type_array_fll_idss_append__parameter_checking(void **state) {

  f_fll_ids_t data = f_fll_ids_t_initialize;

  {
    const f_status_t status = f_fll_idss_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
