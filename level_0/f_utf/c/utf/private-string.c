#include "../utf.h"
#include "private-dynamic.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(_di_f_utf_string_dynamic_partial_append_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_triples_append_)
  f_status_t private_f_utf_string_append(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {

    if (destination->used + length + 1 > destination->size) {
      const f_status_t status = private_f_utf_string_dynamic_increase_by(length + 1, destination);
      if (F_status_is_error(status)) return status;
    }

    memcpy(destination->string + destination->used, source, sizeof(f_utf_char_t) * length);
    destination->used += length;
    destination->string[destination->used] = 0;

    return F_none;
  }
#endif // !defined(_di_f_utf_string_append_) || !defined(_di_f_utf_string_append_assure_) || !defined(_di_f_utf_string_dynamic_append_) || !defined(_di_f_utf_string_dynamic_append_assure_) || !defined(_di_f_utf_string_dynamic_mash_) || !defined(_di_f_utf_string_dynamic_partial_append_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_) || !defined(_di_f_utf_string_dynamic_partial_mash_) || !defined(_di_f_utf_string_dynamics_append_) || !defined(_di_f_utf_string_map_multis_append_) || !defined(_di_f_utf_string_mash_) || !defined(_di_f_utf_string_maps_append_) || !defined(_di_f_utf_string_triples_append_)

#if !defined(_di_f_utf_string_append_assure_nulless_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_assure_nulless_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_nulless_) || !defined(_di_f_utf_string_dynamic_partial_mash_nulless_) || !defined(_di_f_utf_string_mash_nulless_)
  f_status_t private_f_utf_string_append_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {

    f_status_t status = F_none;

    f_array_length_t i = 0;
    f_array_length_t size = 0;

    // Count all of the NULLs and subtract them from the total size.
    for (; i < length; ++i) {
      if (source[i]) ++size;
    } // for

    if (destination->used + size + 1 > destination->size) {
      status = private_f_utf_string_dynamic_increase_by(size + 1, destination);
      if (F_status_is_error(status)) return status;
    }

    f_array_length_t first = 0;

    for (i = 0, size = 0; i < length; ++i) {

      if (source[i]) continue;

      if (i && i > first) {
        size = i - first;

        memcpy(destination->string + destination->used, source + first, sizeof(f_utf_char_t) * size);
        destination->used += size;
      }

      while (i + 1 < length && !source[i + 1]) {
        ++i;
      } // while

      first = i + 1;
    } // for

    if (i > first) {
      size = i - first;

      memcpy(destination->string + destination->used, source + first, sizeof(f_utf_char_t) * size);
      destination->used += size;
    }

    destination->string[destination->used] = 0;

    return F_none;
  }
#endif // !defined(_di_f_utf_string_append_assure_nulless_) || !defined(_di_f_utf_string_append_nulless_) || !defined(_di_f_utf_string_dynamic_append_assure_nulless_) || !defined(_di_f_utf_string_dynamic_append_nulless_) || !defined(_di_f_utf_string_dynamic_mash_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_assure_nulless_) || !defined(_di_f_utf_string_dynamic_partial_append_nulless_) || !defined(_di_f_utf_string_dynamic_partial_mash_nulless_) || !defined(_di_f_utf_string_mash_nulless_)

#if !defined(_di_f_utf_string_dynamic_mish_) || !defined(_di_f_utf_string_dynamic_partial_mish_) || !defined(_di_f_utf_string_dynamic_partial_prepend_assure_) || !defined(_di_f_utf_string_dynamic_partial_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_assure_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_mish_) || !defined(_di_f_utf_string_prepend_assure_) || !defined(_di_f_utf_string_prepend_)
  f_status_t private_f_utf_string_prepend(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {

    if (destination->used + length > F_string_t_size_d) {
      return F_status_set_error(F_string_too_large);
    }

    if (destination->used + length > destination->size) {
      const f_status_t status = private_f_utf_string_dynamic_increase_by(length, destination);
      if (F_status_is_error(status)) return status;
    }

    if (destination->used) {
      memmove(destination->string + length, destination->string, sizeof(f_utf_char_t) * destination->used);
      memcpy(destination->string, source, sizeof(f_utf_char_t) * length);
    }
    else {
      memcpy(destination->string, source, sizeof(f_utf_char_t) * length);
    }

    destination->used += length;

    return F_none;
  }
#endif // !defined(_di_f_utf_string_dynamic_mish_) || !defined(_di_f_utf_string_dynamic_partial_mish_) || !defined(_di_f_utf_string_dynamic_partial_prepend_assure_) || !defined(_di_f_utf_string_dynamic_partial_prepend_) || !defined(_di_f_utf_string_dynamic_prepend_assure_) || !defined(_di_f_utf_string_dynamic_prepend_) || !defined(_di_f_utf_string_mish_) || !defined(_di_f_utf_string_prepend_assure_) || !defined(_di_f_utf_string_prepend_)

#if !defined(_di_f_utf_string_dynamic_mish_nulless_) || !defined(_di_f_utf_string_dynamic_partial_mish_nulless_) || !defined(_di_f_utf_string_dynamic_partial_prepend_assure_nulless_) || !defined(_di_f_utf_string_dynamic_partial_prepend_nulless_) || !defined(_di_f_utf_string_dynamic_prepend_assure_nulless_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_mish_nulless_) || !defined(_di_f_utf_string_prepend_assure_nulless_) || !defined(_di_f_utf_string_prepend_nulless_)
  f_status_t private_f_utf_string_prepend_nulless(const f_utf_string_t source, const f_array_length_t length, f_utf_string_dynamic_t * const destination) {

    if (destination->used + length > F_string_t_size_d) {
      return F_status_set_error(F_string_too_large);
    }

    f_status_t status = F_none;

    f_array_length_t first = 0;
    f_array_length_t offset = 0;

    f_array_length_t size = 0;

    for (f_array_length_t i = 0; i <= length; ++i) {

      if (i == length) {
        if (i > first) {
          size = i - first;

          if (destination->used + size > destination->size) {
            status = private_f_utf_string_dynamic_increase_by(size, destination);
            if (F_status_is_error(status)) return status;
          }

          memmove(destination->string + offset + size, destination->string + offset, sizeof(f_utf_char_t) * (destination->used - offset));
          memcpy(destination->string + offset, source + first, sizeof(f_utf_char_t) * size);

          destination->used += size;
          offset += size;
        }

        break;
      }

      if (!source[i]) {
        if (i > 0) {
          if (i > first) {
            size = i - first;

            if (destination->used + size > destination->size) {
              status = private_f_utf_string_dynamic_increase_by(size, destination);
              if (F_status_is_error(status)) return status;
            }

            memmove(destination->string + offset + size, destination->string + offset, sizeof(f_utf_char_t) * (destination->used - offset));
            memcpy(destination->string + offset, source + first, sizeof(f_utf_char_t) * size);

            destination->used += size;
            offset += size;
          }
        }

        while (i + 1 < length && !source[i + 1]) {
          ++i;
        } // while

        first = i + 1;

        continue;
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_utf_string_dynamic_mish_nulless_) || !defined(_di_f_utf_string_dynamic_partial_mish_nulless_) || !defined(_di_f_utf_string_dynamic_partial_prepend_assure_nulless_) || !defined(_di_f_utf_string_dynamic_partial_prepend_nulless_) || !defined(_di_f_utf_string_dynamic_prepend_assure_nulless_) || !defined(_di_f_utf_string_dynamic_prepend_nulless_) || !defined(_di_f_utf_string_mish_nulless_) || !defined(_di_f_utf_string_prepend_assure_nulless_) || !defined(_di_f_utf_string_prepend_nulless_)

#ifdef __cplusplus
} // extern "C"
#endif
