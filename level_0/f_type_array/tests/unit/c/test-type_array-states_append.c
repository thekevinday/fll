#include "test-type_array.h"
#include "test-type_array-states_append.h"

#ifdef __cplusplus
extern "C" {
#endif

void test__f_type_array_states_append__parameter_checking(void **state) {

  const f_state_t data = f_state_t_initialize;

  {
    const f_status_t status = f_states_append(data, 0);

    assert_int_equal(status, F_status_set_error(F_parameter));
  }
}

void test__f_type_array_states_append__works(void **state) {

  int fake_1 = 1;
  int fake_2 = 2;
  int fake_3 = 3;

  const f_state_t source = macro_f_state_t_initialize_1(12, 6, 0, 0, 0, 0, 0, (void *) &fake_1, (void *) &fake_2, (void *) &fake_3);
  f_states_t destination = f_states_t_initialize;

  {
    const f_status_t status = f_states_append(source, &destination);

    assert_int_equal(status, F_none);
    assert_int_equal(destination.used, 1);
    assert_int_equal(destination.array[0].step_large, source.step_large);
    assert_int_equal(destination.array[0].step_small, source.step_small);
    assert_int_equal(destination.array[0].handle, source.handle);
    assert_int_equal(destination.array[0].interrupt, source.interrupt);
    assert_int_equal(destination.array[0].callbacks, source.callbacks);
    assert_int_equal(destination.array[0].custom, source.custom);
    assert_int_equal(destination.array[0].data, source.data);
  }

  free((void *) destination.array);
}

#ifdef __cplusplus
} // extern "C"
#endif
