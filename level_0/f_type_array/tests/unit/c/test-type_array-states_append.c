#include "test-type_array.h"
#include "test-type_array-states_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_states_append__works(void **state) {

  const int length = 5;
  f_states_t source = f_states_t_initialize;
  f_states_t destination = f_states_t_initialize;

  const f_state_t state_0 = { step_large: 10, step_small: 1, handle: 0, interrupt: 0, callbacks: 0, custom: 0, data: 0 };
  const f_state_t state_1 = { step_large: 20, step_small: 2, handle: 0, interrupt: 0, callbacks: 0, custom: 0, data: 0 };

  {
    const f_status_t status = f_type_states_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  memcpy(&source.array[source.used++], (void *) &state_0, sizeof(f_state_t));
  memcpy(&source.array[source.used++], (void *) &state_1, sizeof(f_state_t));

  {
    const f_status_t status = f_type_states_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, source.used);
    assert_int_equal(destination.size, source.used);

    assert_int_equal(destination.array[0].step_large, state_0.step_large);
    assert_int_equal(destination.array[0].step_small, state_0.step_small);
    assert_null(destination.array[0].handle);
    assert_null(destination.array[0].interrupt);
    assert_null(destination.array[0].callbacks);
    assert_null(destination.array[0].custom);
    assert_null(destination.array[0].data);

    assert_int_equal(destination.array[1].step_large, state_1.step_large);
    assert_int_equal(destination.array[1].step_small, state_1.step_small);
    assert_null(destination.array[1].handle);
    assert_null(destination.array[1].interrupt);
    assert_null(destination.array[1].callbacks);
    assert_null(destination.array[1].custom);
    assert_null(destination.array[1].data);
  }

  free((void *) source.array);
  free((void *) destination.array);
}

void test__f_type_array_states_append__returns_data_not(void **state) {

  const int length = 5;
  f_states_t source = f_states_t_initialize;
  f_states_t destination = f_states_t_initialize;

  {
    const f_status_t status = f_type_states_resize(length, &source);

    assert_int_equal(status, F_none);
    assert_int_equal(source.used, 0);
    assert_int_equal(source.size, length);
  }

  {
    const f_status_t status = f_type_states_append(source, &destination);

    assert_int_equal(status, F_data_not);
    assert_int_equal(destination.used, 0);
    assert_int_equal(destination.size, 0);
  }

  free((void *) source.array);
  assert_null(destination.array);
}

void test__f_type_array_states_append__fails_on_invalid_parameter(void **state) {

  const int length = 5;
  f_states_t data = f_states_t_initialize;

  {
    const f_status_t status = f_type_states_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
    assert_int_equal(data.used, 0);
    assert_int_equal(data.size, 0);
  }

  assert_null(data.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
