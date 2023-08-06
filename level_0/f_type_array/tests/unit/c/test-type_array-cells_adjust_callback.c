#include "test-type_array.h"
#include "test-type_array-cells_adjust_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_cells_adjust_callback__fails(void **state) {

  f_cell_t data = f_cell_t_initialize;
  f_cell_t data_array[] = { data };
  f_cells_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_cells_t datass_array[] = { datas };

  {
    will_return(__wrap_f_memory_array_adjust, true);
    will_return(__wrap_f_memory_array_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_cells_adjust_callback(0, 1, (void *) datass_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_type_array_cells_adjust_callback__works(void **state) {

  f_cell_t data = f_cell_t_initialize;
  f_cell_t data_array[] = { data };
  f_cells_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_cells_t datass_array[] = { datas };
  const f_number_unsigned_t length = 1;

  {
    will_return(__wrap_f_memory_array_adjust, false);
    will_return(__wrap_f_memory_array_adjust, F_none);

    const f_status_t status = f_cells_adjust_callback(0, length, (void *) datass_array);

    assert_int_equal(status, F_none);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
