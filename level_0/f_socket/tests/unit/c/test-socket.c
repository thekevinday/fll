#include "test-socket.h"

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
    cmocka_unit_test(test__f_socket_accept__fails),
    cmocka_unit_test(test__f_socket_accept__works),

    cmocka_unit_test(test__f_socket_bind__fails),
    cmocka_unit_test(test__f_socket_bind__works),

    cmocka_unit_test(test__f_socket_bind_local__fails),
    cmocka_unit_test(test__f_socket_bind_local__works),

    cmocka_unit_test(test__f_socket_connect__fails),
    cmocka_unit_test(test__f_socket_connect__works),

    cmocka_unit_test(test__f_socket_create__fails),
    cmocka_unit_test(test__f_socket_create__works),

    cmocka_unit_test(test__f_socket_create_pair__fails),
    cmocka_unit_test(test__f_socket_create_pair__works),

    cmocka_unit_test(test__f_socket_disconnect__fails_for_close_fast),
    cmocka_unit_test(test__f_socket_disconnect__fails_for_close_read),
    cmocka_unit_test(test__f_socket_disconnect__fails_for_close_unknown),
    cmocka_unit_test(test__f_socket_disconnect__fails_for_close_write),
    cmocka_unit_test(test__f_socket_disconnect__works_for_close_fast),
    cmocka_unit_test(test__f_socket_disconnect__works_for_close_read),
    cmocka_unit_test(test__f_socket_disconnect__works_for_close_write),

    cmocka_unit_test(test__f_socket_listen__fails),
    cmocka_unit_test(test__f_socket_listen__works),

    cmocka_unit_test(test__f_socket_name_host__allocates_default),
    cmocka_unit_test(test__f_socket_name_host__fails),
    cmocka_unit_test(test__f_socket_name_host__works),

    cmocka_unit_test(test__f_socket_name_peer__fails),
    cmocka_unit_test(test__f_socket_name_peer__works),

    cmocka_unit_test(test__f_socket_option_get__fails),
    cmocka_unit_test(test__f_socket_option_get__works),

    cmocka_unit_test(test__f_socket_option_set__fails),
    cmocka_unit_test(test__f_socket_option_set__works),

    cmocka_unit_test(test__f_socket_read__fails),
    cmocka_unit_test(test__f_socket_read__works),

    cmocka_unit_test(test__f_socket_read_message__fails),
    cmocka_unit_test(test__f_socket_read_message__works),

    cmocka_unit_test(test__f_socket_write__fails),
    cmocka_unit_test(test__f_socket_write__works),

    cmocka_unit_test(test__f_socket_write_message__fails),
    cmocka_unit_test(test__f_socket_write_message__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_socket_accept__parameter_checking),
      cmocka_unit_test(test__f_socket_bind__parameter_checking),
      cmocka_unit_test(test__f_socket_bind_local__parameter_checking),
      cmocka_unit_test(test__f_socket_create__parameter_checking),
      cmocka_unit_test(test__f_socket_create_pair__parameter_checking),
      cmocka_unit_test(test__f_socket_disconnect__parameter_checking),
      cmocka_unit_test(test__f_socket_listen__parameter_checking),
      cmocka_unit_test(test__f_socket_name_host__parameter_checking),
      cmocka_unit_test(test__f_socket_name_peer__parameter_checking),
      cmocka_unit_test(test__f_socket_option_get__parameter_checking),
      cmocka_unit_test(test__f_socket_option_set__parameter_checking),
      cmocka_unit_test(test__f_socket_read__parameter_checking),
      cmocka_unit_test(test__f_socket_read_message__parameter_checking),
      cmocka_unit_test(test__f_socket_write__parameter_checking),
      cmocka_unit_test(test__f_socket_write_message__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
