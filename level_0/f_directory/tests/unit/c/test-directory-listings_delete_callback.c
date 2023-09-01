#include "test-directory.h"
#include "test-directory-listings_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_directory_listings_delete_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_string_static_t base = macro_f_string_static_t_initialize_1(F_string_empty_s, 1, 0);
  f_string_static_t base_array[] = { base };
  f_string_statics_t bases = macro_f_string_statics_t_initialize_1(base_array, 1, 0);

  f_directory_listing_t data = {
    .block = bases,
    .character = bases,
    .directory = bases,
    .regular = bases,
    .link = bases,
    .fifo = bases,
    .socket = bases,
    .unknown = bases,
  };

  f_directory_listing_t data_array[] = { data };

  {
    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_delete_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  data_array[0].block = bases;
  data_array[0].character = bases;
  data_array[0].directory = bases;
  data_array[0].regular = bases;
  data_array[0].link = bases;
  data_array[0].fifo = bases;
  data_array[0].socket = bases;
  data_array[0].unknown = bases;

  {
    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_delete_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  data_array[0].block = bases;
  data_array[0].character = bases;
  data_array[0].directory = bases;
  data_array[0].regular = bases;
  data_array[0].link = bases;
  data_array[0].fifo = bases;
  data_array[0].socket = bases;
  data_array[0].unknown = bases;

  {
    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_delete_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  data_array[0].block = bases;
  data_array[0].character = bases;
  data_array[0].directory = bases;
  data_array[0].regular = bases;
  data_array[0].link = bases;
  data_array[0].fifo = bases;
  data_array[0].socket = bases;
  data_array[0].unknown = bases;

  {
    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_delete_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  data_array[0].block = bases;
  data_array[0].character = bases;
  data_array[0].directory = bases;
  data_array[0].regular = bases;
  data_array[0].link = bases;
  data_array[0].fifo = bases;
  data_array[0].socket = bases;
  data_array[0].unknown = bases;

  {
    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_delete_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  data_array[0].block = bases;
  data_array[0].character = bases;
  data_array[0].directory = bases;
  data_array[0].regular = bases;
  data_array[0].link = bases;
  data_array[0].fifo = bases;
  data_array[0].socket = bases;
  data_array[0].unknown = bases;

  {
    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_delete_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  data_array[0].block = bases;
  data_array[0].character = bases;
  data_array[0].directory = bases;
  data_array[0].regular = bases;
  data_array[0].link = bases;
  data_array[0].fifo = bases;
  data_array[0].socket = bases;
  data_array[0].unknown = bases;

  {
    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_delete_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  data_array[0].block = bases;
  data_array[0].character = bases;
  data_array[0].directory = bases;
  data_array[0].regular = bases;
  data_array[0].link = bases;
  data_array[0].fifo = bases;
  data_array[0].socket = bases;
  data_array[0].unknown = bases;

  {
    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_delete_callback(0, 1, (void *) data_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_directory_listings_delete_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_directory_listings_t datas = f_directory_listings_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_directory_listing_t), (void **) &datas.array, &datas.used, &datas.size);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datas.array[0].block.array, &datas.array[0].block.used, &datas.array[0].block.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datas.array[0].character.array, &datas.array[0].character.used, &datas.array[0].character.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datas.array[0].directory.array, &datas.array[0].directory.used, &datas.array[0].directory.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datas.array[0].regular.array, &datas.array[0].regular.used, &datas.array[0].regular.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datas.array[0].link.array, &datas.array[0].link.used, &datas.array[0].link.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datas.array[0].fifo.array, &datas.array[0].fifo.used, &datas.array[0].fifo.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datas.array[0].socket.array, &datas.array[0].socket.used, &datas.array[0].socket.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datas.array[0].unknown.array, &datas.array[0].unknown.used, &datas.array[0].unknown.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_directory_listings_delete_callback(0, length, (void *) datas.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datas.array[0].block.size, 0);
    assert_int_equal(datas.array[0].character.size, 0);
    assert_int_equal(datas.array[0].directory.size, 0);
    assert_int_equal(datas.array[0].regular.size, 0);
    assert_int_equal(datas.array[0].link.size, 0);
    assert_int_equal(datas.array[0].fifo.size, 0);
    assert_int_equal(datas.array[0].socket.size, 0);
    assert_int_equal(datas.array[0].unknown.size, 0);
  }

  free((void *) datas.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
