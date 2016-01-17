/* FLL - Level 0
 * Project:       Memory
 * Version:       0.5.0
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provide means to use memory routines, with error checking.
 */
#include <level_0/memory.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_new_
  f_return_status f_new_array(f_void_p *pointer, f_const f_memory_size_t type, f_const f_memory_length length) {
    #ifndef _di_level_0_parameter_checking_
      if (type <= 0) return f_error_set_error(f_invalid_parameter);
      if (pointer == 0) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    // prevent double-allocations
    if (*pointer != 0) return f_none;

    // some people use malloc(type * length) to produce the same results
    // I have noticed this sometimes causes an increase in L1/L2 cache misses (0.02% L1 increase, 0.01% L2 increase)
    *pointer = calloc(type, length);

    if (*pointer) {
      //memset(*pointer, 0, type * length);
      return f_none;
    }

    return f_error_set_error(f_allocation_error);
  }
#endif // _di_f_new_

#if ! ( defined (_di_f_delete_) || defined (_f_memory_FORCE_secure_memory_) )
  f_return_status f_delete(f_void_p *pointer, f_const f_memory_size_t type, f_const f_memory_length length) {
    #ifndef _di_level_0_parameter_checking_
      if (pointer == 0) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    // prevent double-frees
    if (*pointer == 0) return f_none;

    free(*pointer);

    // it has been deallocated, so reset the pointer
    if (*pointer != 0) *pointer = 0;

    return f_none;
  }
#endif // ! ( defined (_di_f_delete_) || defined (_f_memory_FORCE_secure_memory_) )

#if ! ( defined (_di_f_destroy_) || defined (_f_memory_FORCE_fast_memory_) )
  f_return_status f_destroy(f_void_p *pointer, f_const f_memory_size_t type, f_const f_memory_length length) {
    #ifndef _di_level_0_parameter_checking_
      if (length <  0) return f_error_set_error(f_invalid_parameter);
      if (type <= 0) return f_error_set_error(f_invalid_parameter);
      if (pointer == 0) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    // prevent double-frees
    if (*pointer == 0) return f_none;

    if (length > 0) {
      memset(*pointer, 0, type * length);
    }

    free(*pointer);

    // it has been deallocated, so reset the pointer
    if (*pointer != 0) *pointer = 0;

    return f_none;
  }
#endif // ! ( defined (_di_f_destroy_) || defined (_f_memory_FORCE_fast_memory_) )

#if ! ( defined (_di_f_resize_) || defined (_f_memory_FORCE_secure_memory_) )
  f_return_status f_resize(f_void_p *pointer, f_const f_memory_size_t type, f_const f_memory_length old_length, f_const f_memory_length new_length) {
    #ifndef _di_level_0_parameter_checking_
      if (type <= 0) return f_error_set_error(f_invalid_parameter);
      if (old_length < 0) return f_error_set_error(f_invalid_parameter);
      if (new_length < 0) return f_error_set_error(f_invalid_parameter);
      if (pointer == 0) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    // don't be wasteful
    if (old_length == new_length) return f_none;

    if (*pointer != 0) {
      f_void_p new_pointer = 0;

      // allocate new space
      if (new_length > 0) {
        new_pointer = realloc(*pointer, type * new_length);
      } else {
        free(*pointer);

        // it has been deallocated, so reset the pointer
        if (*pointer != 0) *pointer = 0;

        return f_none;
      }

      if (new_pointer) {
        if (new_pointer != *pointer) {
          if (new_length > old_length) {
            // bool * is of a data type size of 1, casting it to bool should result in a single-length increment
            // this is done to avoid problems with (f_void_p) having arithmetic issues
            memset(((char *) new_pointer) + (type * old_length), 0, type * (new_length - old_length));
          }

          *pointer = new_pointer;
        }

        return f_none;
      }
    } else if (new_length > 0) {
      *pointer = calloc(type, new_length);

      if (*pointer) {
        return f_none;
      }
    } else {
      return f_none;
    }

    return f_error_set_error(f_reallocation_error);
  }
#endif // ! ( defined (_di_f_resize_) || defined (_f_memory_FORCE_secure_memory_) )

#if ! ( defined (_di_f_adjust_) || defined (_f_memory_FORCE_fast_memory_) )
  f_return_status f_adjust(f_void_p *pointer, f_const f_memory_size_t type, f_const f_memory_length old_length, f_const f_memory_length new_length) {
    #ifndef _di_level_0_parameter_checking_
      if (type <= 0) return f_error_set_error(f_invalid_parameter);
      if (old_length < 0) return f_error_set_error(f_invalid_parameter);
      if (new_length < 0) return f_error_set_error(f_invalid_parameter);
      if (pointer == 0) return f_error_set_error(f_invalid_parameter);
    #endif // _di_level_0_parameter_checking_

    // don't be wasteful
    if (old_length == new_length) return f_none;

    if (*pointer != 0) {
      f_void_p new_pointer = 0;

      if (old_length > 0) {
        if (new_length < old_length) {
          // bool * is of a data type size of 1, casting it to bool should result in a single-length increment
          // this is done to avoid problems with (f_void_p) having arithmetic issues
          memset(((char *)*pointer) + new_length, 0, type * (old_length - new_length));
        }
      }

      // allocate new space
      if (new_length > 0) {
        new_pointer = realloc(*pointer, type * new_length);
      } else {
        free(*pointer);

        // it has been deallocated, so reset the pointer
        if (*pointer != 0) *pointer = 0;

        return f_none;
      }

      if (new_pointer) {
        if (new_pointer != *pointer) {
          if (new_length > old_length) {
            // char * is of a data type size of 1, casting it to bool should result in a single-length increment
            // this is done to avoid problems with (f_void_p) having arithmetic issues
            memset(((char *)new_pointer) + (type * old_length), 0, type * (new_length - old_length));
          }

          *pointer = new_pointer;
        }

        return f_none;
      }
    } else if (new_length > 0) {
      *pointer = calloc(type, new_length);

      if (*pointer) {
        return f_none;
      }
    } else {
      return f_none;
    }

    return f_error_set_error(f_reallocation_error);
  }
#endif // ! ( defined (_di_f_adjust_) || defined (_f_memory_FORCE_fast_memory_) )

#ifdef __cplusplus
} // extern "C"
#endif
