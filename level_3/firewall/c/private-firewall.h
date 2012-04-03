/**
 * Private include file for firewall.c.
 */

#ifndef _di_firewall_main_
  f_return_status firewall_perform_commands(const f_fss_objects objects, const f_fss_contents contents, const f_bool is_global, const f_string_length this_device, const f_dynamic_string buffer, const firewall_data data, const f_dynamic_string *custom_chain) __attribute__((visibility("internal")));
#endif // _di_firewall_main_
