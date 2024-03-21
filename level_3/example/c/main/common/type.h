/**
 * FLL - Level 3
 *
 * Project: Example
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides the common type structures.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _example_common_type_h
#define _example_common_type_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The example main program cache.
 *
 * buffer: A generic buffer.
 */
#ifndef _di_example_cache_t_
  typedef struct {
    f_string_dynamic_t buffer;
  } example_cache_t;

  #define example_cache_t_initialize \
    { \
      f_string_dynamic_t_initialize, \
    }
#endif // _di_example_cache_t_

/**
 * The example main program settings.
 *
 * This is passed to the program-specific main entry point to designate program settings.
 * These program settings are often processed from the program arguments (often called the command line arguments).
 *
 * flag: Flags passed to the main function.
 *
 * status_signal: A status used eclusively by the threaded signal handler.
 * state:         The state data used when processing the FSS data.
 */
#ifndef _di_example_setting_t_
  typedef struct {
    uint16_t flag;

    f_status_t status_signal;
    f_state_t state;

    const f_string_static_t *program_name;
    const f_string_static_t *program_name_long;
  } example_setting_t;

  #define example_setting_t_initialize \
    { \
      example_main_flag_none_e, \
      F_okay, \
      f_state_t_initialize, \
      0, \
      0, \
    }
#endif // _di_example_setting_t_

/**
 * The main program data as a single structure.
 *
 * program: The main program data.
 * setting: The settings data.
 */
#ifndef _di_example_main_t_
  typedef struct {
    fll_program_data_t program;
    example_setting_t setting;
    example_cache_t cache;
  } example_main_t;

  #define example_main_t_initialize \
    { \
      fll_program_data_t_initialize, \
      example_setting_t_initialize, \
      example_cache_t_initialize, \
    }
#endif // _di_example_main_t_

/**
 * Deallocate main program data.
 *
 * @param cache
 *   The program cache.
 *
 *   Must not be NULL.
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_example_cache_delete_
  extern void example_cache_delete(example_cache_t * const cache);
#endif // _di_example_cache_delete_

/**
 * Deallocate main program data.
 *
 * @param main
 *   The main program data.
 *
 *   Must not be NULL.
 *
 *   This does not alter main.setting.state.status.
 *
 * @see example_cache_delete()
 * @see example_setting_delete()
 * @see fll_program_data_delete()
 */
#ifndef _di_example_main_delete_
  extern void example_main_delete(example_main_t * const main);
#endif // _di_example_main_delete_

/**
 * Delete the program main setting data.
 *
 * @param setting
 *   The program main setting data.
 *
 *   Must not be NULL.
 *
 *   This does not alter setting.state.status.
 */
#ifndef _di_example_setting_delete_
  extern void example_setting_delete(example_setting_t * const setting);
#endif // _di_example_setting_delete_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _example_common_type_h
