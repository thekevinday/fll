#include "test-type_array.h"
#include "test-type_array-statess_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_statess_append__parameter_checking(void **state) {

  f_states_t data = f_states_t_initialize;

  {
    const f_status_t status = f_statess_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_type_array_statess_append__returns_data_not(void **state) {

  const int length = 5;
  f_states_t source = f_states_t_initialize;
  f_statess_t destination = f_statess_t_initialize;

  {
    const f_status_t status = f_states_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_statess_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
    assert_null(destination.array);
  }

  free((void *) source.array);
}

void test__f_type_array_statess_append__works(void **state) {

  const int length = 5;
  f_states_t source = f_states_t_initialize;
  f_statess_t destination = f_statess_t_initialize;

  int fake_1 = 1;
  int fake_2 = 2;
  int fake_3 = 3;

  const f_state_t state_data = macro_f_state_t_initialize_1(12, 6, 0, 0, 0, 0, 0, (void *) &fake_1, (void *) &fake_2, (void *) &fake_3);

  {
    const f_status_t status = f_states_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  while (source.used < length) {
    memcpy(&source.array[source.used++], (void *) &state_data, sizeof(f_state_t));
  } // while

  {
    const f_status_t status = f_statess_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].used, source.used);
    assert_int_equal(destination.array[0].size, source.used);

    for (f_array_length_t i = 0; i < destination.array[0].used; ++i) {

      assert_int_equal(destination.array[0].array[i].step_large, state_data.step_large);
      assert_int_equal(destination.array[0].array[i].step_small, state_data.step_small);
      assert_int_equal(destination.array[0].array[i].handle, state_data.handle);
      assert_int_equal(destination.array[0].array[i].interrupt, state_data.interrupt);
      assert_int_equal(destination.array[0].array[i].callbacks, state_data.callbacks);
      assert_int_equal(destination.array[0].array[i].custom, state_data.custom);
      assert_int_equal(destination.array[0].array[i].data, state_data.data);
    } // for
  }

  for (f_array_length_t i = 0; i < destination.used; ++i) {
    free((void *) destination.array[i].array);
  } // for

  free((void *) source.array);
  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
