#include "test-type_array.h"
#include "test-type_array-fll_ids_append_all.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_fll_ids_append_all__works(void **state) {

  const int length = 5;
  f_fll_ids_t source = f_fll_ids_t_initialize;
  f_fll_ids_t destination = f_fll_ids_t_initialize;

  const f_fll_id_t fll_id_0 = { .name = "test", .type = 1, .used = 4 };
  const f_fll_id_t fll_id_1 = { .name = "other", .type = 2, .used = 5 };

  {
    const f_status_t status = f_fll_ids_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  memcpy(&source.array[source.used++], (void *) &fll_id_0, sizeof(f_fll_id_t));
  memcpy(&source.array[source.used++], (void *) &fll_id_1, sizeof(f_fll_id_t));

  {
    const f_status_t status = f_fll_ids_append_all(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    assert_string_equal(destination.array[0].name, fll_id_0.name);
    assert_int_equal(destination.array[0].type, fll_id_0.type);
    assert_int_equal(destination.array[0].used, fll_id_0.used);

    assert_string_equal(destination.array[1].name, fll_id_1.name);
    assert_int_equal(destination.array[1].type, fll_id_1.type);
    assert_int_equal(destination.array[1].used, fll_id_1.used);
  }

  free((void *) source.array);
  free((void *) destination.array);
}

void test__f_type_array_fll_ids_append_all__returns_data_not(void **state) {

  const int length = 5;
  f_fll_ids_t source = f_fll_ids_t_initialize;
  f_fll_ids_t destination = f_fll_ids_t_initialize;

  {
    const f_status_t status = f_fll_ids_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_fll_ids_append_all(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_type_array_fll_ids_append_all__parameter_checking(void **state) {

  const f_fll_ids_t data = f_fll_ids_t_initialize;

  {
    const f_status_t status = f_fll_ids_append_all(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
