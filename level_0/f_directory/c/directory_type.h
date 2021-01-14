/**
 * FLL - Level 0
 *
 * Project: Directory
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provides directory related data types.
 */
#ifndef _F_directory_type_h
#define _F_directory_type_h

// fll-0 includes
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/type.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure representing a listing of paths found within a directory.
 *
 * Each property represents a set of paths grouped by directory entity file type.
 */
#ifndef _di_f_directory_listing_t_
  typedef struct {
    f_string_dynamics_t block;     // S_IFBLK
    f_string_dynamics_t character; // S_IFCHR
    f_string_dynamics_t directory; // S_IFDIR
    f_string_dynamics_t regular;   // S_IFREG
    f_string_dynamics_t link;      // S_IFLNK
    f_string_dynamics_t fifo;      // S_IFIFO
    f_string_dynamics_t socket;    // S_IFSOCK
    f_string_dynamics_t unknown;
  } f_directory_listing_t;

  #define f_directory_listing_t_initialize { \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
    f_string_dynamics_t_initialize, \
  }

  #define f_macro_directory_listing_t_delete_simple(listing) \
    f_macro_string_dynamics_t_delete_simple(listing.block) \
    f_macro_string_dynamics_t_delete_simple(listing.character) \
    f_macro_string_dynamics_t_delete_simple(listing.directory) \
    f_macro_string_dynamics_t_delete_simple(listing.regular) \
    f_macro_string_dynamics_t_delete_simple(listing.link) \
    f_macro_string_dynamics_t_delete_simple(listing.fifo) \
    f_macro_string_dynamics_t_delete_simple(listing.socket) \
    f_macro_string_dynamics_t_delete_simple(listing.unknown)

  #define f_macro_directory_listing_t_destroy_simple(listing) \
    f_macro_string_dynamics_t_destroy_simple(listing.block) \
    f_macro_string_dynamics_t_destroy_simple(listing.character) \
    f_macro_string_dynamics_t_destroy_simple(listing.directory) \
    f_macro_string_dynamics_t_destroy_simple(listing.regular) \
    f_macro_string_dynamics_t_destroy_simple(listing.link) \
    f_macro_string_dynamics_t_destroy_simple(listing.fifo) \
    f_macro_string_dynamics_t_destroy_simple(listing.socket) \
    f_macro_string_dynamics_t_destroy_simple(listing.unknown)
#endif // _di_f_directory_listing_t_

/**
 * An association of a path and a status code.
 *
 * The allocation macros apply to the path.
 *
 * status: the status code.
 * path: the dynamically allocated path associated with the status code.
 */
#ifndef _di_f_directory_status_t_
  typedef struct {
    f_status_t status;
    f_string_dynamic_t path;
  } f_directory_status_t;

  #define f_directory_status_t_initialize { 0, f_string_dynamic_t_initialize }

  #define f_macro_directory_status_t_clear(directory) \
    directory.status = 0; \
    f_macro_string_dynamic_t_clear(directory.path);

  #define f_macro_directory_status_t_resize(status, statuses, new_length) f_macro_string_dynamic_t_resize(status, statuses.path, new_length)
  #define f_macro_directory_status_t_adjust(status, statuses, new_length) f_macro_string_dynamic_t_adjust(status, statuses.path, new_length)

  #define f_macro_directory_status_t_delete_simple(statuses)  f_macro_string_dynamic_t_delete_simple(statuses.path)
  #define f_macro_directory_status_t_destroy_simple(statuses) f_macro_string_dynamic_t_destroy_simple(statuses.path)

  #define f_macro_directory_status_t_increase(status, values)            f_macro_string_dynamic_t_increase(status, values)
  #define f_macro_directory_status_t_increase_by(status, values, amount) f_macro_string_dynamic_t_increase_by(status, values, amount)
  #define f_macro_directory_status_t_decrease_by(status, values, amount) f_macro_string_dynamic_t_decrease_by(status, values, amount)
  #define f_macro_directory_status_t_decimate_by(status, values, amount) f_macro_string_dynamic_t_decimate_by(status, values, amount)
#endif // _di_f_directory_status_t_

/**
 * An array of directory status.
 *
 * array: An array of directory status.
 * size:  Total amount of allocated space.
 * used:  Total number of allocated spaces used.
 */
#ifndef _di_f_directory_statuss_t_
  typedef struct {
    f_directory_status_t *array;
    f_array_length_t size;
    f_array_length_t used;
  } f_directory_statuss_t;

  #define f_directory_statuss_t_initialize { 0, 0, 0 }

  #define f_macro_directory_statuss_t_clear(structures) f_macro_memory_structures_clear(structures)

  #define f_macro_directory_statuss_t_resize(status, structures, new_length) \
    status = F_none; \
    if (new_length < structures.size) { \
      for (register f_array_length_t _macro__i = structures.size - new_length; _macro__i < structures.size; ++_macro__i) { \
        f_macro_directory_status_t_resize(status, structures.array[_macro__i], 0); \
        if (F_status_is_error(status)) break; \
      } \
    } \
    if (status == F_none) status = f_memory_resize((void **) & structures.array, sizeof(f_directory_status_t), structures.size, new_length); \
    if (status == F_none) { \
      structures.size = new_length; \
      if (structures.used > structures.size) structures.used = new_length; \
    }

  #define f_macro_directory_statuss_t_adjust(status, structures, new_length) \
    status = F_none; \
    if (new_length < structures.size) { \
      for (register f_array_length_t _macro__i = structures.size - new_length; _macro__i < structures.size; ++_macro__i) { \
        f_macro_directory_status_t_adjust(status, structures.array[_macro__i], 0); \
        if (F_status_is_error(status)) break; \
      } \
    } \
    if (status == F_none) status = f_memory_adjust((void **) & structures.array, sizeof(f_directory_status_t), structures.size, new_length); \
    if (status == F_none) { \
      structures.size = new_length; \
      if (structures.used > structures.size) structures.used = new_length; \
    }

  #define f_macro_directory_statuss_t_delete_simple(structures) \
    structures.used = structures.size; \
    while (structures.used > 0) { \
      structures.used--; \
      f_macro_directory_status_t_delete_simple(structures.array[structures.used]); \
    } \
    if (!structures.size) { \
      if (f_memory_resize((void **) & structures.array, sizeof(f_directory_status_t), structures.size, 0)) { \
        structures.size = 0; \
      } \
    }

  #define f_macro_directory_statuss_t_destroy_simple(structures) \
    structures.used = structures.size; \
    while (structures.used > 0) { \
      structures.used--; \
      f_macro_directory_status_t_destroy_simple(structures.array[structures.used]); \
    } \
    if (!structures.size) { \
      if (f_memory_adjust((void **) & structures.array, sizeof(f_directory_status_t), structures.size, 0)) { \
        structures.size = 0; \
      } \
    }
#endif // _di_f_directory_statuss_t_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_directory_type_h
