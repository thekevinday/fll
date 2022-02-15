#include "test-type_array.h"
#include "test-type_array-fll_idss_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_fll_idss_append__works(void **state) {

  const int length = 5;
  const int length_inner = 2;
  f_fll_idss_t source = f_fll_ids_t_initialize;
  f_fll_idss_t destination = f_fll_ids_t_initialize;

  const f_fll_id_t fll_id_0 = { name: "test", type: 1, used: 4 };
  const f_fll_id_t fll_id_1 = { name: "other", type: 2, used: 5 };

  {
    const f_status_t status = f_fll_idss_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    for (; source.used < length; ++source.used) {

      const f_status_t status = f_fll_ids_resize(length_inner, &source.array[source.used]);

      assert_int_equal(status, F_none);

      memcpy(&source.array[source.used].array[source.array[source.used].used++], (void *) &fll_id_0, sizeof(f_fll_id_t));
      memcpy(&source.array[source.used].array[source.array[source.used].used++], (void *) &fll_id_1, sizeof(f_fll_id_t));
    } // for
  }

  {
    const f_status_t status = f_fll_idss_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    for (f_array_length_t i = 0; i < destination.used; ++i) {

      assert_int_equal(destination.array[i].used, length_inner);
      assert_int_equal(destination.array[i].size, length_inner);

      assert_string_equal(destination.array[i].array[0].name, fll_id_0.name);
      assert_int_equal(destination.array[i].array[0].type, fll_id_0.type);
      assert_int_equal(destination.array[i].array[0].used, fll_id_0.used);

      assert_string_equal(destination.array[i].array[1].name, fll_id_1.name);
      assert_int_equal(destination.array[i].array[1].type, fll_id_1.type);
      assert_int_equal(destination.array[i].array[1].used, fll_id_1.used);
    } // for
  }

  for (f_array_length_t i = 0; i < source.used; ++i) {
    free((void *) source.array[i].array);
  } // for

  for (f_array_length_t i = 0; i < destination.used; ++i) {
    free((void *) destination.array[i].array);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

void test__f_type_array_fll_idss_append__returns_data_not(void **state) {

  const int length = 5;
  f_fll_idss_t source = f_fll_ids_t_initialize;
  f_fll_idss_t destination = f_fll_ids_t_initialize;

  {
    const f_status_t status = f_fll_idss_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_fll_idss_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
  }

  free((void *) source.array);
  assert_null(destination.array);
}

void test__f_type_array_fll_idss_append__fails_on_invalid_parameter(void **state) {

  const int length = 5;
  f_fll_idss_t data = f_fll_ids_t_initialize;

  {
    const f_status_t status = f_fll_idss_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
