/**
 * Private include file for firewall.c.
 */

#ifndef _PRIVATE_firewall_h
#define _PRIVATE_firewall_h

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_firewall_local_data_
  typedef struct {
    f_bool is_global;
    f_bool is_main;
    f_bool is_stop;
    f_bool is_lock;

    f_file_position file_position;

    f_array_length device;

    f_dynamic_string buffer;
    f_array_length   chain;
    f_array_lengths  chain_ids;
    f_fss_objects    chain_objects;
    f_fss_contents   chain_contents;
    f_fss_objects    rule_objects;
    f_fss_contents   rule_contents;
  } firewall_local_data;

  #define firewall_local_data_initialize \
    { \
      f_true, \
      f_false, \
      f_false, \
      f_false, \
      f_file_position_initialize, \
      0, \
      f_dynamic_string_initialize, \
      0, \
      f_array_lengths_initialize, \
      f_fss_objects_initialize, \
      f_fss_contents_initialize, \
      f_fss_objects_initialize, \
      f_fss_contents_initialize, \
    }
#endif // _di_firewall_local_data_

#ifndef _di_firewall_reserved_chains_
  typedef struct {
    f_bool has_main;
    f_bool has_stop;
    f_bool has_lock;

    f_array_length main_at;
    f_array_length stop_at;
    f_array_length lock_at;
  } firewall_reserved_chains;

  #define firewall_reserved_chains_initialize \
    { \
      f_false, \
      f_false, \
      f_false, \
      0, \
      0, \
      0, \
    }
#endif // _di_firewall_reserved_chains_

#ifndef _di_firewall_macro_private_
  #define firewall_macro_delete_fss_buffers(status, buffer, objects, contents) \
    f_delete_dynamic_string(status, buffer); \
    f_delete_fss_objects(status, objects); \
    f_delete_fss_contents(status, contents);
#endif // _di_firewall_macro_private_

#ifndef _di_firewall_perform_commands_
  f_return_status firewall_perform_commands(const firewall_local_data local, const firewall_data data) __attribute__((visibility("internal")));
#endif // _di_firewall_perform_commands_

#ifndef _di_firewall_create_custom_chains_
  f_return_status firewall_create_custom_chains(firewall_reserved_chains *reserved, firewall_local_data *local, firewall_data *data) __attribute__((visibility("internal")));
#endif // _di_firewall_create_custom_chains_

#ifndef _di_firewall_buffer_rules_
  f_return_status firewall_buffer_rules(const f_string filename, const f_bool optional, firewall_local_data *local, firewall_data *data) __attribute__((visibility("internal")));
#endif // _di_firewall_buffer_rules_

#ifndef _di_firewall_process_rules_
  f_return_status firewall_process_rules(f_string_location *input, firewall_local_data *local, firewall_data *data) __attribute__((visibility("internal")));
#endif // _di_firewall_process_rules_

#ifndef _di_firewall_delete_local_data_
  f_return_status firewall_delete_local_data(firewall_local_data *local) __attribute__((visibility("internal")));
#endif // _di_firewall_delete_local_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_firewall_h
