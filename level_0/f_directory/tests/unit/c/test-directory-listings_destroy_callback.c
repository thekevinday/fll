#include "test-directory.h"
#include "test-directory-listings_destroy_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_directory_listings_destroy_callback__fails(void **state) {

  mock_unwrap = 0;
  mock_unwrap_f_memory = 0;

  f_directory_listing_t data = f_directory_listing_t_initialize;
  f_directory_listing_t data_array[] = { data };
  f_directory_listings_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_directory_listings_t datas_array[] = { datas };

  {
    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, false);
    will_return(__wrap_f_memory_arrays_adjust, F_okay);

    will_return(__wrap_f_memory_arrays_adjust, true);
    will_return(__wrap_f_memory_arrays_adjust, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_destroy_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_directory_listings_destroy_callback__works(void **state) {

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
    const f_status_t status = f_directory_listings_destroy_callback(0, length, (void *) datas.array);

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
