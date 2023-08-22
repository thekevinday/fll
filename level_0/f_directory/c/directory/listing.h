/**
 * FLL - Level 0
 *
 * Project: Directory
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Defines type-specific data to be used for/by project directory.
 *
 * This is auto-included by directory.h and should not need to be explicitly included.
 */
#ifndef _F_directory_listing_h
#define _F_directory_listing_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A structure representing a listing of paths found within a directory.
 *
 * Each property represents a set of paths grouped by directory entity file type.
 *
 * Properties:
 *   - block:     For S_IFBLK.
 *   - character: For S_IFCHR.
 *   - directory: For S_IFDIR.
 *   - regular:   For S_IFREG.
 *   - link:      For S_IFLNK.
 *   - fifo:      For S_IFIFO.
 *   - socket:    For S_IFSOCK.
 *   - unknown:   For anything else.
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

  #define macro_f_directory_listing_t_initialize_1(block, character, directory, regular, link, fifo, socket, unknown) { \
    block, \
    character, \
    directory, \
    regular, \
    link, \
    fifo, \
    socket, \
    unknown, \
  }
#endif // _di_f_directory_listing_t_

/**
 * An array of directory listing.
 *
 * Properties:
 *   - array: An array of directory listing.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_directory_listings_t_
  typedef struct {
    f_directory_listing_t *array;
    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_directory_listings_t;

  #define f_directory_listings_t_initialize { 0, 0, 0 }

  #define macro_f_directory_listings_t_initialize_1(content, size, used) { array, size, used }
  #define macro_f_directory_listings_t_initialize_2(array, length) { array, length, length }

  #define macro_f_directory_listings_t_clear(structures) macro_f_memory_structures_clear(structures)
#endif // _di_f_directory_listings_t_

/**
 * An array of an array of directory listing.
 *
 * Properties:
 *   - array: An array of an array of directory listing.
 *   - size:  Total amount of allocated space.
 *   - used:  Total number of allocated spaces used.
 */
#ifndef _di_f_directory_listingss_t_
  typedef struct {
    f_directory_listings_t *array;
    f_number_unsigned_t size;
    f_number_unsigned_t used;
  } f_directory_listingss_t;

  #define f_directory_listingss_t_initialize { 0, 0, 0 }

  #define macro_f_directory_listingss_t_initialize_1(content, size, used) { array, size, used }
  #define macro_f_directory_listingss_t_initialize_2(array, length) { array, length, length }

  #define macro_f_directory_listingss_t_clear(structures) macro_f_memory_structures_clear(structures)
#endif // _di_f_directory_listingss_t_

/**
 * Delete all arrays within the listing.
 *
 * @param listing
 *   The listing to fully delete.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_directory_listing_delete_
  extern f_status_t f_directory_listing_delete(f_directory_listing_t * const listing);
#endif // _di_f_directory_listing_delete_

/**
 * Destroy all arrays within the listing.
 *
 * @param listing
 *   The listing to fully destroy.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 */
#ifndef _di_f_directory_listing_destroy_
  extern f_status_t f_directory_listing_destroy(f_directory_listing_t * const listing);
#endif // _di_f_directory_listing_destroy_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_directory_listings_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_directory_listings_delete_callback_
  extern f_status_t f_directory_listings_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_directory_listings_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_directory_listings_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 */
#ifndef _di_f_directory_listings_destroy_callback_
  extern f_status_t f_directory_listings_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_directory_listings_destroy_callback_

/**
 * A callback intended to be passed to f_memory_arrays_resize() for an f_directory_listingss_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_resize().
 *
 * @see f_memory_array_resize()
 */
#ifndef _di_f_directory_listingss_delete_callback_
  extern f_status_t f_directory_listingss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_directory_listingss_delete_callback_

/**
 * A callback intended to be passed to f_memory_arrays_adjust() for an f_directory_listingss_t structure.
 *
 * This is only called when shrinking the array and generally should perform deallocations.
 *
 * This does not do parameter checking.
 *
 * @param start
 *   The inclusive start position in the array to start deleting.
 * @param stop
 *   The exclusive stop position in the array to stop deleting.
 * @param array
 *   The array structure to delete all values of.
 *   Must not be NULL.
 *
 * @return
 *   F_okay on success.
 *
 *   F_parameter (with error bit) if a parameter is invalid.
 *
 *   Errors (with error bit) from: f_memory_array_adjust().
 *
 * @see f_memory_array_adjust()
 */
#ifndef _di_f_directory_listingss_destroy_callback_
  extern f_status_t f_directory_listingss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const array);
#endif // _di_f_directory_listingss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_directory_listing_h
