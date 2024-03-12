#include "test-random.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_random_array_shuffle__fails(void **state) {

  mock_unwrap = 0;

  int errnos[] = {
    EAGAIN,
    EFAULT,
    EINTR,
    EINVAL,
    ENOSYS,
    mock_errno_generic,
  };

  f_status_t statuss[] = {
    F_again,
    F_buffer,
    F_interrupt,
    F_parameter,
    F_support_not,
    F_failure,
  };

  f_string_dynamic_t cache = f_string_dynamic_t_initialize;
  f_number_unsigneds_t indexes = f_number_unsigneds_t_initialize;

  f_number_unsigned_t indexes_array[5] = { 0, 1, 2, 3, 4 };
  indexes.array = indexes_array;
  indexes.used = 5;

  for (uint8_t i = 0; i < 6; ++i) {

    will_return(__wrap_getrandom, true);
    will_return(__wrap_getrandom, errnos[i]);
    will_return(__wrap_getrandom, -1);

    const f_status_t status = f_random_array_shuffle(0, indexes.used, sizeof(f_number_unsigned_t), &cache, (void *) indexes.array);

    if (status != F_status_set_error(statuss[i])) {
      printf("[  ERROR   ] --- At index %d, first loop.\n", i);
    }

    assert_int_equal(status, F_status_set_error(statuss[i]));
  } // for

  if (cache.string) free(cache.string);
}

void test__f_random_array_shuffle__parameter_checking(void **state) {

  mock_unwrap = 0;

  {
    const f_status_t status = f_random_array_shuffle(0, 0, 0, 0, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    f_string_dynamic_t cache = f_string_dynamic_t_initialize;

    const f_status_t status = f_random_array_shuffle(0, 0, 0, &cache, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }

  {
    f_number_unsigneds_t indexes = f_number_unsigneds_t_initialize;

    const f_status_t status = f_random_array_shuffle(0, 0, 0, 0, (void *) indexes.array);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_random_array_shuffle__returns_data_not(void **state) {

  mock_unwrap = 0;

  f_string_dynamic_t cache = f_string_dynamic_t_initialize;
  f_number_unsigneds_t indexes = f_number_unsigneds_t_initialize;

  f_number_unsigned_t indexes_array[5] = { 0, 1, 2, 3, 4 };
  indexes.array = indexes_array;
  indexes.used = 5;

  {
    const f_status_t status = f_random_array_shuffle(0, 0, sizeof(f_number_unsigned_t), &cache, (void *) indexes.array);
    assert_int_equal(status, F_data_not);
  }

  if (cache.string) free(cache.string);
}

void test__f_random_array_shuffle__returns_too_small(void **state) {

  mock_unwrap = 0;

  f_string_dynamic_t cache = f_string_dynamic_t_initialize;
  f_number_unsigneds_t indexes = f_number_unsigneds_t_initialize;

  f_number_unsigned_t indexes_array[5] = { 0, 1, 2, 3, 4 };
  indexes.array = indexes_array;
  indexes.used = 5;

  {
    const f_status_t status = f_random_array_shuffle(0, indexes.used, 0, &cache, (void *) indexes.array);
    assert_int_equal(status, F_status_set_error(F_too_small));
  }

  if (cache.string) free(cache.string);
}

void test__f_random_array_shuffle__works(void **state) {

  mock_unwrap = 1;

  f_string_dynamic_t cache = f_string_dynamic_t_initialize;
  f_number_unsigneds_t indexes = f_number_unsigneds_t_initialize;

  f_number_unsigned_t indexes_array[5] = { 0, 1, 2, 3, 4 };
  indexes.array = indexes_array;
  indexes.used = 5;

  uint8_t unchanged = F_true;
  const uint8_t tries = 20;

  for (uint8_t i = 0; i < tries; ++i) {

    const f_status_t status = f_random_array_shuffle(0, indexes.used, sizeof(f_number_unsigned_t), &cache, (void *) indexes.array);
    assert_int_equal(status, F_okay);

    uint8_t founds[] = { F_false, F_false, F_false, F_false, F_false };

    for (uint8_t j = 0; j < indexes.used; ++j) {
      founds[indexes.array[j]] = F_true;

      if (indexes.array[j] > indexes.used) {
        printf("[  ERROR   ] --- value (%lu) at index %d is too large.\n", indexes.array[j], j);
      }

      assert_true(indexes.array[j] <= indexes.used);
    } // for

    for (uint8_t j = 0; j < indexes.used; ++j) {

      if (!founds[j]) {
        printf("[  ERROR   ] --- Did not find index %d, value=%lu.\n", j, indexes.array[j]);
      }

      assert_int_equal(founds[j], F_true);
    } // for

    // Because things are random, the values could randomly be the same { 0, 1, 2, 3, 4 }.
    // Try multiple times to get a different value and if a different order is found, then break.
    for (uint8_t j = 0; j < indexes.used; ++j) {

      if (indexes.array[j] != j) {
        unchanged = F_false;

        break;
      }
    } // for
  } // for

  if (unchanged) {
    printf("[  ERROR   ] --- Failed to shuffle to a different result at least once in %d tries.\n", tries);
  }

  assert_false(unchanged);

  if (cache.string) free(cache.string);
}

#ifdef __cplusplus
} // extern "C"
#endif
