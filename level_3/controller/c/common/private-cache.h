/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 */
#ifndef _PRIVATE_common_cache_h
#define _PRIVATE_common_cache_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Action related cache.
 *
 * line_action: The line in some file representing an Action.
 * line_item:   The line in some file representing an Item.
 * name_action: A NULL terminated name of some Action.
 * name_file:   A NULL terminated name of some File.
 * name_item:   A NULL terminated name of some Item.
 * generic:     A NULL terminated string for general use.
 */
#ifndef _di_controller_cache_action_t_
  typedef struct {
    f_number_unsigned_t line_action;
    f_number_unsigned_t line_item;

    f_string_dynamic_t name_action;
    f_string_dynamic_t name_file;
    f_string_dynamic_t name_item;

    f_string_dynamic_t generic;
  } controller_cache_action_t;

  #define controller_cache_action_t_initialize { \
    0, \
    0, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
  }

  #define macro_controller_cache_action_t_clear(cache) \
    cache.line_action = 0; \
    cache.line_item = 0; \
    macro_f_string_dynamic_t_clear(cache.name_action) \
    macro_f_string_dynamic_t_clear(cache.name_file) \
    macro_f_string_dynamic_t_clear(cache.name_item) \
    macro_f_string_dynamic_t_clear(cache.generic)
#endif // _di_controller_cache_action_t_

/**
 * A cache intended for re-using memory while loading and processing rules whenever possible.
 *
 * timestamp:       The timestamp.
 * range_action:    The Range for some Action.
 * ats:             Locations.
 * stack:           Locations within a items history used as a history stack for circular recursion prevention.
 * comments:        Comments associated with a buffer string.
 * delimits:        Delimits associated with a buffer string.
 * content_action:  The specific Content for some Action.
 * content_actions: Content for some Action.
 * content_items:   Content for some Item.
 * object_actions:  Objects for some Action.
 * object_items:    Objects for some Item.
 * buffer_file:     A generic file related buffer.
 * buffer_item:     A generic item related buffer.
 * buffer_path:     A generic path related buffer.
 * expanded:        An array of expanded strings, generally used by the execute functions.
 * action:          A cache for some Action, often used by error printing for reporting where an error happened.
 */
#ifndef _di_controller_cache_t_
  typedef struct {
    f_time_spec_t timestamp;

    f_string_range_t range_action;

    f_number_unsigneds_t ats;
    f_number_unsigneds_t stack;

    f_string_ranges_t comments;
    f_number_unsigneds_t delimits;

    f_string_ranges_t content_action;
    f_string_rangess_t content_actions;
    f_string_rangess_t content_items;
    f_string_ranges_t object_actions;
    f_string_ranges_t object_items;

    f_string_dynamic_t buffer_file;
    f_string_dynamic_t buffer_item;
    f_string_dynamic_t buffer_path;

    f_string_dynamics_t expanded;

    controller_cache_action_t action;
  } controller_cache_t;

  #define controller_cache_t_initialize { \
    f_time_spec_t_initialize, \
    f_string_range_t_initialize, \
    f_number_unsigneds_t_initialize, \
    f_number_unsigneds_t_initialize, \
    f_string_ranges_t_initialize, \
    f_number_unsigneds_t_initialize, \
    f_string_ranges_t_initialize, \
    f_string_rangess_t_initialize, \
    f_string_rangess_t_initialize, \
    f_string_ranges_t_initialize, \
    f_string_ranges_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamic_t_initialize, \
    f_string_dynamics_t_initialize, \
    controller_cache_action_t_initialize, \
  }
#endif // _di_controller_cache_t_

/**
 * Fully deallocate all memory for the given cache without caring about return status.
 *
 * @param cache
 *   The cache to deallocate.
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_controller_cache_action_delete_simple_
  extern void controller_cache_action_delete_simple(controller_cache_action_t * const cache) F_attribute_visibility_internal_d;
#endif // _di_controller_cache_action_delete_simple_

/**
 * Fully deallocate all memory for the given cache without caring about return status.
 *
 * @param cache
 *   The cache to deallocate.
 *
 * @see controller_cache_action_delete_simple()
 *
 * @see f_memory_array_resize()
 * @see f_memory_arrays_resize()
 */
#ifndef _di_controller_cache_delete_simple_
  extern void controller_cache_delete_simple(controller_cache_t * const cache) F_attribute_visibility_internal_d;
#endif // _di_controller_cache_delete_simple_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_common_cache_h
