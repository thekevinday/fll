#include "test-type_array.h"
#include "test-type_array-cells_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_cells_append__works(void **state) {

  const int length = 5;
  f_cells_t source = f_cells_t_initialize;
  f_cells_t destination = f_cells_t_initialize;

  const f_cell_t cell_0 = { row: 1, column: 2 };
  const f_cell_t cell_1 = { row: 3, column: 4 };

  {
    const f_status_t status = f_type_cells_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  memcpy(&source.array[source.used++], (void *) &cell_0, sizeof(f_cell_t));
  memcpy(&source.array[source.used++], (void *) &cell_1, sizeof(f_cell_t));

  {
    const f_status_t status = f_type_cells_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    assert_int_equal(destination.array[0].row, cell_0.row);
    assert_int_equal(destination.array[0].column, cell_0.column);

    assert_int_equal(destination.array[1].row, cell_1.row);
    assert_int_equal(destination.array[1].column, cell_1.column);
  }

  free((void *) source.array);
  free((void *) destination.array);
}

void test__f_type_array_cells_append__returns_data_not(void **state) {

  const int length = 5;
  f_cells_t source = f_cells_t_initialize;
  f_cells_t destination = f_cells_t_initialize;

  {
    const f_status_t status = f_type_cells_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_type_cells_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
  }

  free((void *) source.array);
  assert_null(destination.array);
}

void test__f_type_array_cells_append__fails_on_invalid_parameter(void **state) {

  const int length = 5;
  f_cells_t data = f_cells_t_initialize;

  {
    const f_status_t status = f_type_cells_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
