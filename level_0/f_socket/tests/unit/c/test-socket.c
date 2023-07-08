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

    cmocka_unit_test(test__f_socket_bind_inet4__fails),
    cmocka_unit_test(test__f_socket_bind_inet4__works),

    cmocka_unit_test(test__f_socket_bind_inet6__fails),
    cmocka_unit_test(test__f_socket_bind_inet6__works),

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

    cmocka_unit_test(test__f_socket_read_stream__fails),
    cmocka_unit_test(test__f_socket_read_stream__works),

    cmocka_unit_test(test__f_socket_write__fails),
    cmocka_unit_test(test__f_socket_write__works),

    cmocka_unit_test(test__f_socket_write_message__fails),
    cmocka_unit_test(test__f_socket_write_message__works),

    cmocka_unit_test(test__f_socket_write_stream__fails),
    cmocka_unit_test(test__f_socket_write_stream__works),

    cmocka_unit_test(test__f_socket_sockets_append_all__returns_data_not),
    cmocka_unit_test(test__f_socket_sockets_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_socket_sockets_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_socket_sockets_increase__returns_data_not),
    cmocka_unit_test(test__f_socket_sockets_increase_by__returns_data_not),

    cmocka_unit_test(test__f_socket_sockets_adjust__works),
    cmocka_unit_test(test__f_socket_sockets_append__works),
    cmocka_unit_test(test__f_socket_sockets_append_all__works),
    cmocka_unit_test(test__f_socket_sockets_decimate_by__works),
    cmocka_unit_test(test__f_socket_sockets_decrease_by__works),
    cmocka_unit_test(test__f_socket_sockets_increase__works),
    cmocka_unit_test(test__f_socket_sockets_increase_by__works),
    cmocka_unit_test(test__f_socket_sockets_resize__works),

    cmocka_unit_test(test__f_socket_socketss_append__returns_data_not),
    cmocka_unit_test(test__f_socket_socketss_append_all__returns_data_not),
    cmocka_unit_test(test__f_socket_socketss_decimate_by__returns_data_not),
    cmocka_unit_test(test__f_socket_socketss_decrease_by__returns_data_not),
    cmocka_unit_test(test__f_socket_socketss_increase__returns_data_not),
    cmocka_unit_test(test__f_socket_socketss_increase_by__returns_data_not),

    cmocka_unit_test(test__f_socket_socketss_adjust__works),
    cmocka_unit_test(test__f_socket_socketss_append__works),
    cmocka_unit_test(test__f_socket_socketss_append_all__works),
    cmocka_unit_test(test__f_socket_socketss_decimate_by__works),
    cmocka_unit_test(test__f_socket_socketss_decrease_by__works),
    cmocka_unit_test(test__f_socket_socketss_increase__works),
    cmocka_unit_test(test__f_socket_socketss_increase_by__works),
    cmocka_unit_test(test__f_socket_socketss_resize__works),

    #ifndef _di_level_0_parameter_checking_
      cmocka_unit_test(test__f_socket_accept__parameter_checking),
      cmocka_unit_test(test__f_socket_bind__parameter_checking),
      cmocka_unit_test(test__f_socket_bind_inet4__parameter_checking),
      cmocka_unit_test(test__f_socket_bind_inet6__parameter_checking),
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
      cmocka_unit_test(test__f_socket_read_stream__parameter_checking),
      cmocka_unit_test(test__f_socket_write__parameter_checking),
      cmocka_unit_test(test__f_socket_write_message__parameter_checking),
      cmocka_unit_test(test__f_socket_write_stream__parameter_checking),

      cmocka_unit_test(test__f_socket_sockets_adjust__parameter_checking),
      cmocka_unit_test(test__f_socket_sockets_append__parameter_checking),
      cmocka_unit_test(test__f_socket_sockets_append_all__parameter_checking),
      cmocka_unit_test(test__f_socket_sockets_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_socket_sockets_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_socket_sockets_increase__parameter_checking),
      cmocka_unit_test(test__f_socket_sockets_increase_by__parameter_checking),
      cmocka_unit_test(test__f_socket_sockets_resize__parameter_checking),

      cmocka_unit_test(test__f_socket_socketss_adjust__parameter_checking),
      cmocka_unit_test(test__f_socket_socketss_append__parameter_checking),
      cmocka_unit_test(test__f_socket_socketss_append_all__parameter_checking),
      cmocka_unit_test(test__f_socket_socketss_decimate_by__parameter_checking),
      cmocka_unit_test(test__f_socket_socketss_decrease_by__parameter_checking),
      cmocka_unit_test(test__f_socket_socketss_increase__parameter_checking),
      cmocka_unit_test(test__f_socket_socketss_increase_by__parameter_checking),
      cmocka_unit_test(test__f_socket_socketss_resize__parameter_checking),
    #endif // _di_level_0_parameter_checking_
  };

  return cmocka_run_group_tests(tests, setup, setdown);
}

#ifdef __cplusplus
} // extern "C"
#endif
