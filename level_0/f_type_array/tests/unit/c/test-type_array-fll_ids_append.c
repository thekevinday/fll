#include "test-type_array.h"
#include "test-type_array-fll_ids_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_fll_ids_append__works(void **state) {

  const f_fll_id_t source = { .name = "test", .type = 1, .used = 4 };
  f_fll_ids_t destination = f_fll_ids_t_initialize;

  {
    const f_status_t status = f_fll_ids_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_string_equal(destination.array[0].name, source.name);
    assert_int_equal(destination.array[0].type, source.type);
    assert_int_equal(destination.array[0].used, source.used);
  }

  free((void *) destination.array);
}

void test__f_type_array_fll_ids_append__parameter_checking(void **state) {

  const f_fll_id_t data = f_fll_id_t_initialize;

  {
    const f_status_t status = f_fll_ids_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
