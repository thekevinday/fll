#include "test-directory.h"
#include "test-directory-listings_delete_callback.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_directory_listings_delete_callback__fails(void **state) {

  mock_unwrap = 0;

  f_directory_listing_t data = f_directory_listing_t_initialize;
  f_directory_listing_t data_array[] = { data };
  f_directory_listings_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_directory_listings_t datas_array[] = { datas };

  {
    will_return(__wrap_f_string_dynamics_resize, true);
    will_return(__wrap_f_string_dynamics_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, true);
    will_return(__wrap_f_string_dynamics_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, true);
    will_return(__wrap_f_string_dynamics_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, true);
    will_return(__wrap_f_string_dynamics_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, true);
    will_return(__wrap_f_string_dynamics_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, true);
    will_return(__wrap_f_string_dynamics_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, true);
    will_return(__wrap_f_string_dynamics_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }

  {
    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, true);
    will_return(__wrap_f_string_dynamics_resize, F_status_set_error(F_failure));

    const f_status_t status = f_directory_listings_delete_callback(0, 1, (void *) datas_array);

    assert_int_equal(status, F_status_set_error(F_failure));
  }
}

void test__f_directory_listings_delete_callback__works(void **state) {

  mock_unwrap = 0;

  f_directory_listing_t data = f_directory_listing_t_initialize;
  f_directory_listing_t data_array[] = { data };
  f_directory_listings_t datas = { .array = data_array, .used = 1, .size = 1 };
  f_directory_listings_t datas_array[] = { datas };
  const f_number_unsigned_t length = 1;

  {
    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    will_return(__wrap_f_string_dynamics_resize, false);
    will_return(__wrap_f_string_dynamics_resize, F_okay);

    const f_status_t status = f_directory_listings_delete_callback(0, length, (void *) datas_array);

    assert_int_equal(status, F_okay);
  }
}

#ifdef __cplusplus
} // extern "C"
#endif
