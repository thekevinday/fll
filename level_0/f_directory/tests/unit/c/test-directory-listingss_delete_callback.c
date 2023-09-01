#include "test-directory.h"
#include "test-directory-listingss_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_directory_listingss_delete_callback__fails(void **state) {

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
  f_directory_listings_t datas = { .array = data_array, .used = 0, .size = 1 };
  f_directory_listings_t datas_array[] = { datas };

  {
    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listingss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0] = datas;
  datas_array[0].array[0].block = bases;
  datas_array[0].array[0].character = bases;
  datas_array[0].array[0].directory = bases;
  datas_array[0].array[0].regular = bases;
  datas_array[0].array[0].link = bases;
  datas_array[0].array[0].fifo = bases;
  datas_array[0].array[0].socket = bases;
  datas_array[0].array[0].unknown = bases;

  {
    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listingss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0] = datas;
  datas_array[0].array[0].block = bases;
  datas_array[0].array[0].character = bases;
  datas_array[0].array[0].directory = bases;
  datas_array[0].array[0].regular = bases;
  datas_array[0].array[0].link = bases;
  datas_array[0].array[0].fifo = bases;
  datas_array[0].array[0].socket = bases;
  datas_array[0].array[0].unknown = bases;

  {
    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listingss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0] = datas;
  datas_array[0].array[0].block = bases;
  datas_array[0].array[0].character = bases;
  datas_array[0].array[0].directory = bases;
  datas_array[0].array[0].regular = bases;
  datas_array[0].array[0].link = bases;
  datas_array[0].array[0].fifo = bases;
  datas_array[0].array[0].socket = bases;
  datas_array[0].array[0].unknown = bases;

  {
    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_arrays_resize, true);
    will_return(__wrap_f_memory_arrays_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listingss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0] = datas;
  datas_array[0].array[0].block = bases;
  datas_array[0].array[0].character = bases;
  datas_array[0].array[0].directory = bases;
  datas_array[0].array[0].regular = bases;
  datas_array[0].array[0].link = bases;
  datas_array[0].array[0].fifo = bases;
  datas_array[0].array[0].socket = bases;
  datas_array[0].array[0].unknown = bases;

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

    const f_status_t status = f_directory_listingss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0].array[0].block = bases;
  datas_array[0].array[0].character = bases;
  datas_array[0].array[0].directory = bases;
  datas_array[0].array[0].regular = bases;
  datas_array[0].array[0].link = bases;
  datas_array[0].array[0].fifo = bases;
  datas_array[0].array[0].socket = bases;
  datas_array[0].array[0].unknown = bases;

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

    const f_status_t status = f_directory_listingss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0].array[0].block = bases;
  datas_array[0].array[0].character = bases;
  datas_array[0].array[0].directory = bases;
  datas_array[0].array[0].regular = bases;
  datas_array[0].array[0].link = bases;
  datas_array[0].array[0].fifo = bases;
  datas_array[0].array[0].socket = bases;
  datas_array[0].array[0].unknown = bases;

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

    const f_status_t status = f_directory_listingss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0].array[0].block = bases;
  datas_array[0].array[0].character = bases;
  datas_array[0].array[0].directory = bases;
  datas_array[0].array[0].regular = bases;
  datas_array[0].array[0].link = bases;
  datas_array[0].array[0].fifo = bases;
  datas_array[0].array[0].socket = bases;
  datas_array[0].array[0].unknown = bases;

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

    const f_status_t status = f_directory_listingss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  datas_array[0].array[0].block = bases;
  datas_array[0].array[0].character = bases;
  datas_array[0].array[0].directory = bases;
  datas_array[0].array[0].regular = bases;
  datas_array[0].array[0].link = bases;
  datas_array[0].array[0].fifo = bases;
  datas_array[0].array[0].socket = bases;
  datas_array[0].array[0].unknown = bases;

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

    will_return(__wrap_f_memory_arrays_resize, false);
    will_return(__wrap_f_memory_arrays_resize, F_okay);

    will_return(__wrap_f_memory_array_resize, true);
    will_return(__wrap_f_memory_array_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listingss_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_directory_listingss_delete_callback__works(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 1;

  const f_number_unsigned_t length = 1;

  f_directory_listingss_t datass = f_directory_listingss_t_initialize;

  {
    f_status_t status = f_memory_array_resize(length, sizeof(f_directory_listings_t), (void **) &datass.array, &datass.used, &datass.size);
    assert_int_equal(status, F_okay);

    status = f_memory_array_resize(1, sizeof(f_directory_listing_t), (void **) &datass.array[0].array, &datass.array[0].used, &datass.array[0].size);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datass.array[0].array[0].block.array, &datass.array[0].array[0].block.used, &datass.array[0].array[0].block.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datass.array[0].array[0].character.array, &datass.array[0].array[0].character.used, &datass.array[0].array[0].character.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datass.array[0].array[0].directory.array, &datass.array[0].array[0].directory.used, &datass.array[0].array[0].directory.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datass.array[0].array[0].regular.array, &datass.array[0].array[0].regular.used, &datass.array[0].array[0].regular.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datass.array[0].array[0].link.array, &datass.array[0].array[0].link.used, &datass.array[0].array[0].link.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datass.array[0].array[0].fifo.array, &datass.array[0].array[0].fifo.used, &datass.array[0].array[0].fifo.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datass.array[0].array[0].socket.array, &datass.array[0].array[0].socket.used, &datass.array[0].array[0].socket.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);

    status = f_memory_arrays_resize(1, sizeof(f_string_dynamic_t), (void **) &datass.array[0].array[0].unknown.array, &datass.array[0].array[0].unknown.used, &datass.array[0].array[0].unknown.size, &f_string_dynamics_delete_callback);
    assert_int_equal(status, F_okay);
  }

  {
    const f_status_t status = f_directory_listingss_delete_callback(0, length, (void *) datass.array);

    assert_int_equal(status, F_okay);
    assert_int_equal(datass.array[0].size, 0);
  }

  free((void *) datass.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
