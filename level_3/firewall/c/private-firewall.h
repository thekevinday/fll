/**
 * FLL - Level 3
 *
 * Project: Firewall
 * API Version: 0.5
 * Licenses: lgplv2.1
 */
#ifndef _PRIVATE_firewall_h
#define _PRIVATE_firewall_h

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  bool is_global;
  bool is_main;
  bool is_stop;
  bool is_lock;

  f_array_length_t device;

  f_string_dynamic_t buffer;
  f_array_length_t chain;
  f_array_lengths_t chain_ids;
  f_fss_objects_t chain_objects;
  f_fss_contents_t chain_contents;
  f_fss_objects_t rule_objects;
  f_fss_contents_t rule_contents;
} firewall_local_data_t;

#define firewall_local_data_t_initialize \
  { \
    F_true, \
    F_false, \
    F_false, \
    F_false, \
    0, \
    f_string_dynamic_t_initialize, \
    0, \
    f_array_lengths_t_initialize, \
    f_fss_objects_t_initialize, \
    f_fss_contents_t_initialize, \
    f_fss_objects_t_initialize, \
    f_fss_contents_t_initialize, \
  }

typedef struct {
  bool has_main;
  bool has_stop;
  bool has_lock;

  f_array_length_t main_at;
  f_array_length_t stop_at;
  f_array_length_t lock_at;
} firewall_reserved_chains_t;

#define firewall_reserved_chains_t_initialize \
  { \
    F_false, \
    F_false, \
    F_false, \
    0, \
    0, \
    0, \
  }

#define firewall_macro_delete_fss_buffers(status, buffer, objects, contents) \
  f_macro_string_dynamic_t_delete_simple(buffer); \
  f_macro_fss_objects_t_delete_simple(objects); \
  f_macro_fss_contents_t_delete_simple(contents);

#define firewall_macro_concat_string(destination, source, length) \
  memcpy((void *)(destination), source, length);

#define firewall_macro_rule_contents_has_incorrect_items(index, total_items) \
  local.rule_contents.array[index].used <= 0 || local.rule_contents.array[index].used > total_items

// the buffer start to stop points are inclusive such that the size is ((stop - start) + 1).
#define firewall_macro_string_dynamic_size(structure, index) \
  (structure.string[index].stop - structure.string[index].start) + 1

// the buffer start to stop points are inclusive such that the size is ((stop - start) + 1).
#define firewall_macro_structure_size(structure, index) \
  (structure.array[index].stop - structure.array[index].start) + 1

// TODO: temporarily added, convert this to a function below.
// TODO: also report: fl_color_print(data.error.to.stream, data.context.set.error, "CRITICAL ERROR: Unable to allocate memory.%c", f_string_eol_s[0]);
#define firewall_macro_append_argument_to_arguments(status, arguments, argument) \
  if (arguments.used == arguments.size) { \
    f_macro_string_dynamics_t_resize(status, arguments, arguments.used + firewall_default_allocation_step); \
    \
    if (F_status_is_error(status)) break; \
  } \
  \
  arguments.array[arguments.used].string = argument.string; \
  arguments.array[arguments.used].size   = argument.size; \
  arguments.array[arguments.used].used   = argument.used; \
  arguments.used++; \
  \
  f_macro_string_dynamic_t_clear(argument);

/**
 * Perform commands.
 *
 * @param local
 *   Local firewall settings.
 * @param data
 *   Firewall data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
f_status_t firewall_perform_commands(const firewall_local_data_t local, const firewall_data_t data) f_gcc_attribute_visibility_internal;

/**
 * Create custom chains.
 *
 * @param reserved
 *   firewall chains.
 * @param local
 *   Local firewall settings.
 * @param data
 *   Firewall data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
f_status_t firewall_create_custom_chains(firewall_reserved_chains_t *reserved, firewall_local_data_t *local, firewall_data_t *data) f_gcc_attribute_visibility_internal;

/**
 * Deallocate chains.
 *
 * @param data
 *   Firewall data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
f_status_t firewall_delete_chains(const firewall_data_t data) f_gcc_attribute_visibility_internal;

/**
 * Lock the firewall.
 *
 * @param data
 *   Firewall data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
f_status_t firewall_default_lock(const firewall_data_t data) f_gcc_attribute_visibility_internal;

/**
 * Buffer firewall rules.
 *
 * @param filename
 *   File name to read the rules from.
 * @param optional
 *   TRUE if this files is optional.
 *   FALSE otherwise (more are errors returned when not optional).
 * @param local
 *   Local firewall settings.
 * @param data
 *   Firewall data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
f_status_t firewall_buffer_rules(const f_string_t filename, const bool optional, firewall_local_data_t *local, firewall_data_t *data) f_gcc_attribute_visibility_internal;

/**
 * Process buffered rules.
 *
 * @param range
 *   The current position within the buffer and the stop point.
 * @param local
 *   Local firewall settings.
 * @param data
 *   Firewall data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
f_status_t firewall_process_rules(f_string_range_t *range, firewall_local_data_t *local, firewall_data_t *data) f_gcc_attribute_visibility_internal;

/**
 * Delete allocated data.
 *
 * @param local
 *   Local firewall settings.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 */
f_status_t firewall_delete_local_data(firewall_local_data_t *local) f_gcc_attribute_visibility_internal;

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_firewall_h
