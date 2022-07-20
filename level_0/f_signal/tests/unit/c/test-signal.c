#include "test-signal.h"

#ifdef __cplusplus
extern "C" {
#endif

int setup(void **state) {

  return 0;
}

int setdown(void **state) {

  errno = 0;

  return 0;
}

int main(void) {

  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test__f_signal_action__fails),
    cmocka_unit_test(test__f_signal_action__works),

    cmocka_unit_test(test__f_signal_close__fails),
    cmocka_unit_test(test__f_signal_close__works),

    cmocka_unit_test(test__f_signal_mask__fails),
    cmocka_unit_test(test__f_signal_mask__works),

    cmocka_unit_test(test__f_signal_open__fails),
    cmocka_unit_test(test__f_signal_open__works),

    cmocka_unit_test(test__f_signal_pause__works),

    cmocka_unit_test(test__f_signal_queue__fails),
    cmocka_unit_test(test__f_signal_queue__works),

    cmocka_unit_test(test__f_signal_read__fails),
    cmocka_unit_test(test__f_signal_read__works),

    cmocka_unit_test(test__f_signal_send__fails),
    cmocka_unit_test(test__f_signal_send__works),

    cmocka_unit_test(test__f_signal_set_add__fails),
    cmocka_unit_test(test__f_signal_set_add__works),

    cmocka_unit_test(test__f_signal_set_delete__fails),
    cmocka_unit_test(test__f_signal_set_delete__works),

    cmocka_unit_test(test__f_signal_set_empty__fails),
    cmocka_unit_test(test__f_signal_set_empty__works),

    cmocka_unit_test(test__f_signal_set_fill__fails),
    cmocka_unit_test(test__f_signal_set_fill__works),

    cmocka_unit_test(test__f_signal_set_has__fails),
    cmocka_unit_test(test__f_signal_set_has__works),

    cmocka_unit_test(test__f_signal_suspend__fails),
    cmocka_unit_test(test__f_signal_suspend__works),

    cmocka_unit_test(test__f_signal_wait__fails),
    cmocka_unit_test(test__f_signal_wait__works),

    cmocka_unit_test(test__f_signal_wait_until__fails),
    cmocka_unit_test(test__f_signal_wait_until__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_signal_action__parameter_checking),
      cmocka_unit_test(test__f_signal_close__parameter_checking),
      cmocka_unit_test(test__f_signal_mask__parameter_checking),
      cmocka_unit_test(test__f_signal_open__parameter_checking),
      // f_signal_pause() doesn't use parameter checking.
      // f_signal_queue() doesn't use parameter checking.
      cmocka_unit_test(test__f_signal_read__parameter_checking),
      // f_signal_send() doesn't use parameter checking.
      cmocka_unit_test(test__f_signal_set_add__parameter_checking),
      cmocka_unit_test(test__f_signal_set_delete__parameter_checking),
      cmocka_unit_test(test__f_signal_set_empty__parameter_checking),
      cmocka_unit_test(test__f_signal_set_fill__parameter_checking),
      cmocka_unit_test(test__f_signal_set_has__parameter_checking),
      cmocka_unit_test(test__f_signal_suspend__parameter_checking),
      // f_signal_wait() doesn't use parameter checking.
      // f_signal_wait_until() doesn't use parameter checking.
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
