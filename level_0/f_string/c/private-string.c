#include "string.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_string_dynamic_adjust_)
  f_status_t private_f_string_dynamic_adjust(const f_string_length_t length, f_string_dynamic_t *string) {
    f_status_t status = F_none;

    f_macro_string_dynamic_t_adjust(status, (*string), length);

    return status;
  }
#endif // !defined(_di_f_string_dynamic_adjust_)

#if !defined(_di_f_string_append_) || !defined(_di_f_string_dynamic_append_) || !defined(_di_f_string_dynamic_mash_) || !defined(_di_f_string_mash_)
  f_status_t private_f_string_append(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {
    f_status_t status = F_none;

    if (destination->used + length > destination->size) {
      status = private_f_string_dynamic_increase_by(length, destination);
      if (F_status_is_error(status)) return status;
    }

    memcpy(destination->string + destination->used, source, length);
    destination->used = destination->used + length;

    return F_none;
  }
#endif // !defined(_di_f_string_append_) || !defined(_di_f_string_dynamic_append_) || !defined(_di_f_string_dynamic_mash_) || !defined(_di_f_string_mash_)

#if !defined(_di_f_string_append_nulless_) || !defined(_di_f_string_dynamic_append_nulless_) || !defined(_di_f_string_dynamic_mash_nulless_) || !defined(_di_f_string_mash_nulless_)
  f_status_t private_f_string_append_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {

    if (destination->used + length > f_string_length_t_size) {
      return F_status_set_error(F_string_too_large);
    }

    f_status_t status = F_none;

    f_string_length_t i = 0;
    f_string_length_t first = 0;
    f_string_length_t size = 0;

    for (; i < length; i++) {

      if (source[i]) continue;

      if (i && i > first) {
        size = i - first;

        if (destination->used + size > destination->size) {
          status = private_f_string_dynamic_increase_by(size, destination);
          if (F_status_is_error(status)) return status;
        }

        memcpy(destination->string + destination->used, source + first, size);
        destination->used = destination->used + size;
      }

      while (i + 1 < length && !source[i + 1]) {
        i++;
      } // while

      first = i + 1;
    } // for

    if (i > first) {
      size = i - first;

      if (destination->used + size > destination->size) {
        status = private_f_string_dynamic_increase_by(size, destination);
        if (F_status_is_error(status)) return status;
      }

      memcpy(destination->string + destination->used, source + first, size);
      destination->used = destination->used + size;
    }

    return F_none;
  }
#endif // !defined(_di_f_string_append_nulless_) || !defined(_di_f_string_dynamic_append_nulless_) || !defined(_di_f_string_dynamic_mash_nulless_) || !defined(_di_f_string_mash_nulless_)

#if !defined(_di_f_string_dynamic_decrease_) || !defined(_di_f_string_dynamic_decrease_by_) || !defined(_di_f_string_dynamic_delete_)
  f_status_t private_f_string_dynamic_delete(f_string_dynamic_t *string) {
    f_status_t status = F_none;

    f_macro_string_dynamic_t_delete(status, (*string));

    return status;
  }
#endif // !defined(_di_f_string_dynamic_decrease_) || !defined(_di_f_string_dynamic_decrease_by_) || !defined(_di_f_string_dynamic_delete_)

#if !defined(_di_f_string_dynamic_decimate_) || !defined(_di_f_string_dynamic_decimate_by_) || !defined(_di_f_string_dynamic_delete_)
  f_status_t private_f_string_dynamic_destroy(f_string_dynamic_t *string) {
    f_status_t status = F_none;

    f_macro_string_dynamic_t_destroy(status, (*string));

    return status;
  }
#endif // !defined(_di_f_string_dynamic_decimate_) || !defined(_di_f_string_dynamic_decimate_by_) || !defined(_di_f_string_dynamic_delete_)

#if !defined(_di_f_string_dynamic_increase_by_) || !defined(_di_f_string_append_) || !defined(_di_f_string_dynamic_append_) || !defined(_di_f_string_append_mash_) || !defined(_di_f_string_dynamic_mash_) || !defined(_di_f_string_append_nulless_) || !defined(_di_f_string_dynamic_append_nulless_) || !defined(_di_f_string_mash_nulless_) || !defined(_di_f_string_dynamic_mash_nulless_) || !defined(_di_f_string_prepend_) || !defined(_di_f_string_dynamic_prepend_) || !defined(_di_f_string_prepend_nulless_) || !defined(_di_f_string_dynamic_prepend_nulless_)
  f_status_t private_f_string_dynamic_increase_by(const f_string_length_t amount, f_string_dynamic_t *string) {

    if (string->used + amount > string->size) {
      if (string->used + amount > f_string_length_t_size) {
        return F_status_set_error(F_string_too_large);
      }

      return private_f_string_dynamic_resize(string->used + amount, string);
    }

    return F_none;
  }
#endif // !defined(_di_f_string_dynamic_increase_by_) || !defined(_di_f_string_append_) || !defined(_di_f_string_dynamic_append_) || !defined(_di_f_string_append_mash_) || !defined(_di_f_string_dynamic_mash_) || !defined(_di_f_string_append_nulless_) || !defined(_di_f_string_dynamic_append_nulless_) || !defined(_di_f_string_mash_nulless_) || !defined(_di_f_string_dynamic_mash_nulless_) || !defined(_di_f_string_prepend_) || !defined(_di_f_string_dynamic_prepend_) || !defined(_di_f_string_prepend_nulless_) || !defined(_di_f_string_dynamic_prepend_nulless_)

#if !defined(_di_f_string_dynamic_decrease_) || !defined(_di_f_string_dynamic_decrease_by_) || !defined(_di_f_string_dynamic_increase_) || !defined(_di_f_string_dynamic_increase_by_) || !defined(_di_f_string_dynamic_terminate_) || !defined(_di_f_string_dynamic_terminate_after_)
  f_status_t private_f_string_dynamic_resize(const f_string_length_t length, f_string_dynamic_t *string) {
    f_status_t status = F_none;

    f_macro_string_dynamic_t_resize(status, (*string), length);

    return status;
  }
#endif // !defined(_di_f_string_dynamic_decrease_) || !defined(_di_f_string_dynamic_decrease_by_) || !defined(_di_f_string_dynamic_increase_) || !defined(_di_f_string_dynamic_increase_by_) || !defined(_di_f_string_dynamic_terminate_) || !defined(_di_f_string_dynamic_terminate_after_)

#if !defined(_di_f_string_dynamics_adjust_)
  f_status_t private_f_string_dynamics_adjust(const f_string_length_t length, f_string_dynamics_t *strings) {
    f_status_t status = F_none;

    f_macro_string_dynamics_t_adjust(status, (*strings), length);

    return status;
  }
#endif // !defined(_di_f_string_dynamics_adjust_)

#if !defined(_di_f_string_dynamics_decrease_) || !defined(_di_f_string_dynamics_decrease_by_) || !defined(_di_f_string_dynamics_delete_)
  f_status_t private_f_string_dynamics_delete(f_string_dynamics_t *string) {
    f_status_t status = F_none;

    f_macro_string_dynamics_t_delete(status, (*string));

    return status;
  }
#endif // !defined(_di_f_string_dynamics_decrease_) || !defined(_di_f_string_dynamics_decrease_by_) || !defined(_di_f_string_dynamics_delete_)

#if !defined(_di_f_string_dynamics_decimate_) || !defined(_di_f_string_dynamics_decimate_by_) || !defined(_di_f_string_dynamics_destroy_)
  f_status_t private_f_string_dynamics_destroy(f_string_dynamics_t *string) {
    f_status_t status = F_none;

    f_macro_string_dynamics_t_destroy(status, (*string));

    return status;
  }
#endif // !defined(_di_f_string_dynamics_decimate_) || !defined(_di_f_string_dynamics_decimate_by_) || !defined(_di_f_string_dynamics_destroy_)

#if !defined(_di_f_string_dynamics_decrease_) || !defined(_di_f_string_dynamics_decrease_by_) || !defined(_di_f_string_dynamics_increase_) || !defined(_di_f_string_dynamics_increase_by_)
  f_status_t private_f_string_dynamics_resize(const f_string_length_t length, f_string_dynamics_t *strings) {
    f_status_t status = F_none;

    f_macro_string_dynamics_t_resize(status, (*strings), length);

    return status;
  }
#endif // !defined(_di_f_string_dynamics_decrease_) || !defined(_di_f_string_dynamics_decrease_by_) || !defined(_di_f_string_dynamics_increase_) || !defined(_di_f_string_dynamics_increase_by_)

#if !defined(_di_f_string_maps_adjust_)
  f_status_t private_f_string_maps_adjust(const f_string_length_t length, f_string_maps_t *maps) {
    f_status_t status = F_none;

    f_macro_string_maps_t_adjust(status, (*maps), length);

    return status;
  }
#endif // !defined(_di_f_string_maps_adjust_)

#if !defined(f_string_maps_decrease) || !defined(f_string_maps_decrease_by) || !defined(_di_f_string_maps_delete_)
  f_status_t private_f_string_maps_delete(f_string_maps_t *maps) {
    f_status_t status = F_none;

    f_macro_string_maps_t_delete(status, (*maps));

    return status;
  }
#endif // !defined(f_string_maps_decrease) || !defined(f_string_maps_decrease_by) || !defined(_di_f_string_maps_delete_)

#if !defined(f_string_maps_decimate) || !defined(f_string_maps_decimate_by) || !defined(_di_f_string_maps_destroy_)
  f_status_t private_f_string_maps_destroy(f_string_maps_t *maps) {
    f_status_t status = F_none;

    f_macro_string_maps_t_destroy(status, (*maps));

    return status;
  }
#endif // !defined(f_string_maps_decimate) || !defined(f_string_maps_decimate_by) || !defined(_di_f_string_maps_destroy_)

#if !defined(_di_f_string_maps_decrease_) || !defined(_di_f_string_maps_decrease_by_) || !defined(_di_f_string_maps_increase_) || !defined(_di_f_string_maps_increase_by_) || !defined(_di_f_string_maps_terminate_) || !defined(_di_f_string_maps_terminate_after_)
  f_status_t private_f_string_maps_resize(const f_string_length_t length, f_string_maps_t *maps) {
    f_status_t status = F_none;

    f_macro_string_maps_t_resize(status, (*maps), length);

    return status;
  }
#endif // !defined(_di_f_string_maps_decrease_) || !defined(_di_f_string_maps_decrease_by_) || !defined(_di_f_string_maps_increase_) || !defined(_di_f_string_maps_increase_by_) || !defined(_di_f_string_maps_terminate_) || !defined(_di_f_string_maps_terminate_after_)

#if !defined(_di_f_string_dynamic_mish_) || !defined(_di_f_string_dynamic_partial_mish_) || !defined(_di_f_string_dynamic_partial_prepend_assure_) || !defined(_di_f_string_dynamic_partial_prepend_) || !defined(_di_f_string_dynamic_prepend_assure_) || !defined(_di_f_string_dynamic_prepend_) || !defined(_di_f_string_mish_) || !defined(_di_f_string_prepend_assure_) || !defined(_di_f_string_prepend_)
  f_status_t private_f_string_prepend(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {

    if (destination->used + length > f_string_length_t_size) {
      return F_status_set_error(F_string_too_large);
    }

    if (destination->used + length > destination->size) {
      const f_status_t status = private_f_string_dynamic_increase_by(length, destination);
      if (F_status_is_error(status)) return status;
    }

    if (destination->used) {
      memmove(destination->string + length, destination->string, destination->used);
      memcpy(destination->string, source, length);
    }
    else {
      memcpy(destination->string, source, length);
    }

    destination->used = destination->used + length;
    return F_none;
  }
#endif // !defined(_di_f_string_dynamic_mish_) || !defined(_di_f_string_dynamic_partial_mish_) || !defined(_di_f_string_dynamic_partial_prepend_assure_) || !defined(_di_f_string_dynamic_partial_prepend_) || !defined(_di_f_string_dynamic_prepend_assure_) || !defined(_di_f_string_dynamic_prepend_) || !defined(_di_f_string_mish_) || !defined(_di_f_string_prepend_assure_) || !defined(_di_f_string_prepend_)

#if !defined(_di_f_string_dynamic_mish_nulless_) || !defined(_di_f_string_dynamic_partial_mish_nulless_) || !defined(_di_f_string_dynamic_partial_prepend_assure_nulless_) || !defined(_di_f_string_dynamic_partial_prepend_nulless_) || !defined(_di_f_string_dynamic_prepend_assure_nulless_) || !defined(_di_f_string_dynamic_prepend_nulless_) || !defined(_di_f_string_mish_nulless_) || !defined(_di_f_string_prepend_assure_nulless_) || !defined(_di_f_string_prepend_nulless_)
  f_status_t private_f_string_prepend_nulless(const f_string_t source, const f_string_length_t length, f_string_dynamic_t *destination) {

    if (destination->used + length > f_string_length_t_size) {
      return F_status_set_error(F_string_too_large);
    }

    f_status_t status = F_none;

    f_string_length_t first = 0;
    f_string_length_t offset = 0;

    f_string_length_t size = 0;

    for (f_string_length_t i = 0; i <= length; i++) {

      if (i == length) {
        if (i > first) {
          size = i - first;

          if (destination->used + size > destination->size) {
            status = private_f_string_dynamic_increase_by(size, destination);
            if (F_status_is_error(status)) return status;
          }

          memmove(destination->string + offset + size, destination->string + offset, destination->used - offset);
          memcpy(destination->string + offset, source + first, size);

          destination->used = destination->used + size;
          offset += size;
        }

        break;
      }

      if (!source[i]) {
        if (i > 0) {
          if (i > first) {
            size = i - first;

            if (destination->used + size > destination->size) {
              status = private_f_string_dynamic_increase_by(size, destination);
              if (F_status_is_error(status)) return status;
            }

            memmove(destination->string + offset + size, destination->string + offset, destination->used - offset);
            memcpy(destination->string + offset, source + first, size);

            destination->used = destination->used + size;
            offset += size;
          }
        }

        while (i + 1 < length && !source[i + 1]) {
          i++;
        } // while

        first = i + 1;
        continue;
      }
    } // for

    return F_none;
  }
#endif // !defined(_di_f_string_dynamic_mish_nulless_) || !defined(_di_f_string_dynamic_partial_mish_nulless_) || !defined(_di_f_string_dynamic_partial_prepend_assure_nulless_) || !defined(_di_f_string_dynamic_partial_prepend_nulless_) || !defined(_di_f_string_dynamic_prepend_assure_nulless_) || !defined(_di_f_string_dynamic_prepend_nulless_) || !defined(_di_f_string_mish_nulless_) || !defined(_di_f_string_prepend_assure_nulless_) || !defined(_di_f_string_prepend_nulless_)

#if !defined(_di_f_string_quantitys_adjust_)
  f_status_t private_f_string_quantitys_adjust(const f_string_length_t length, f_string_quantitys_t *quantitys) {
    f_status_t status = F_none;

    f_macro_string_quantitys_t_adjust(status, (*quantitys), length);

    return status;
  }
#endif // !defined(_di_f_string_quantitys_adjust_)

#if !defined(f_string_quantitys_decrease) || !defined(f_string_quantitys_decrease_by) || !defined(_di_f_string_quantitys_delete_)
  f_status_t private_f_string_quantitys_delete(f_string_quantitys_t *quantitys) {
    f_status_t status = F_none;

    f_macro_string_quantitys_t_delete(status, (*quantitys));

    return status;
  }
#endif // !defined(f_string_quantitys_decrease) || !defined(f_string_quantitys_decrease_by) || !defined(_di_f_string_quantitys_delete_)

#if !defined(f_string_quantitys_decimate) || !defined(f_string_quantitys_decimate_by) || !defined(_di_f_string_quantitys_destroy_)
  f_status_t private_f_string_quantitys_destroy(f_string_quantitys_t *quantitys) {
    f_status_t status = F_none;

    f_macro_string_quantitys_t_destroy(status, (*quantitys));

    return status;
  }
#endif // !defined(f_string_quantitys_decimate) || !defined(f_string_quantitys_decimate_by) || !defined(_di_f_string_quantitys_destroy_)

#if !defined(_di_f_string_quantitys_decrease_) || !defined(_di_f_string_quantitys_decrease_by_) || !defined(_di_f_string_quantitys_increase_) || !defined(_di_f_string_quantitys_increase_by_) || !defined(_di_f_string_quantitys_terminate_) || !defined(_di_f_string_quantitys_terminate_after_)
  f_status_t private_f_string_quantitys_resize(const f_string_length_t length, f_string_quantitys_t *quantitys) {
    f_status_t status = F_none;

    f_macro_string_quantitys_t_resize(status, (*quantitys), length);

    return status;
  }
#endif // !defined(_di_f_string_quantitys_decrease_) || !defined(_di_f_string_quantitys_decrease_by_) || !defined(_di_f_string_quantitys_increase_) || !defined(_di_f_string_quantitys_increase_by_) || !defined(_di_f_string_quantitys_terminate_) || !defined(_di_f_string_quantitys_terminate_after_)

#if !defined(_di_f_string_ranges_adjust_)
  f_status_t private_f_string_ranges_adjust(const f_string_length_t length, f_string_ranges_t *ranges) {
    f_status_t status = F_none;

    f_macro_string_ranges_t_adjust(status, (*ranges), length);

    return status;
  }
#endif // !defined(_di_f_string_ranges_adjust_)

#if !defined(f_string_ranges_decrease) || !defined(f_string_ranges_decrease_by) || !defined(_di_f_string_ranges_delete_)
  f_status_t private_f_string_ranges_delete(f_string_ranges_t *ranges) {
    f_status_t status = F_none;

    f_macro_string_ranges_t_delete(status, (*ranges));

    return status;
  }
#endif // !defined(f_string_ranges_decrease) || !defined(f_string_ranges_decrease_by) || !defined(_di_f_string_ranges_delete_)

#if !defined(f_string_ranges_decimate) || !defined(f_string_ranges_decimate_by) || !defined(_di_f_string_ranges_destroy_)
  f_status_t private_f_string_ranges_destroy(f_string_ranges_t *ranges) {
    f_status_t status = F_none;

    f_macro_string_ranges_t_destroy(status, (*ranges));

    return status;
  }
#endif // !defined(f_string_ranges_decimate) || !defined(f_string_ranges_decimate_by) || !defined(_di_f_string_ranges_destroy_)

#if !defined(_di_f_string_ranges_decrease_) || !defined(_di_f_string_ranges_decrease_by_) || !defined(_di_f_string_ranges_increase_) || !defined(_di_f_string_ranges_increase_by_) || !defined(_di_f_string_ranges_terminate_) || !defined(_di_f_string_ranges_terminate_after_)
  f_status_t private_f_string_ranges_resize(const f_string_length_t length, f_string_ranges_t *ranges) {
    f_status_t status = F_none;

    f_macro_string_ranges_t_resize(status, (*ranges), length);

    return status;
  }
#endif // !defined(_di_f_string_ranges_decrease_) || !defined(_di_f_string_ranges_decrease_by_) || !defined(_di_f_string_ranges_increase_) || !defined(_di_f_string_ranges_increase_by_) || !defined(_di_f_string_ranges_terminate_) || !defined(_di_f_string_ranges_terminate_after_)

#if !defined(_di_f_string_triples_adjust_)
  f_status_t private_f_string_triples_adjust(const f_string_length_t length, f_string_triples_t *triples) {
    f_status_t status = F_none;

    f_macro_string_triples_t_adjust(status, (*triples), length);

    return status;
  }
#endif // !defined(_di_f_string_triples_adjust_)

#if !defined(f_string_triples_decrease) || !defined(f_string_triples_decrease_by) || !defined(_di_f_string_triples_delete_)
  f_status_t private_f_string_triples_delete(f_string_triples_t *triples) {
    f_status_t status = F_none;

    f_macro_string_triples_t_delete(status, (*triples));

    return status;
  }
#endif // !defined(f_string_triples_decrease) || !defined(f_string_triples_decrease_by) || !defined(_di_f_string_triples_delete_)

#if !defined(f_string_triples_decimate) || !defined(f_string_triples_decimate_by) || !defined(_di_f_string_triples_destroy_)
  f_status_t private_f_string_triples_destroy(f_string_triples_t *triples) {
    f_status_t status = F_none;

    f_macro_string_triples_t_destroy(status, (*triples));

    return status;
  }
#endif // !defined(f_string_triples_decimate) || !defined(f_string_triples_decimate_by) || !defined(_di_f_string_triples_destroy_)

#if !defined(_di_f_string_triples_decrease_) || !defined(_di_f_string_triples_decrease_by_) || !defined(_di_f_string_triples_increase_) || !defined(_di_f_string_triples_increase_by_) || !defined(_di_f_string_triples_terminate_) || !defined(_di_f_string_triples_terminate_after_)
  f_status_t private_f_string_triples_resize(const f_string_length_t length, f_string_triples_t *triples) {
    f_status_t status = F_none;

    f_macro_string_triples_t_resize(status, (*triples), length);

    return status;
  }
#endif // !defined(_di_f_string_triples_decrease_) || !defined(_di_f_string_triples_decrease_by_) || !defined(_di_f_string_triples_increase_) || !defined(_di_f_string_triples_increase_by_) || !defined(_di_f_string_triples_terminate_) || !defined(_di_f_string_triples_terminate_after_)

#ifdef __cplusplus
} // extern "C"
#endif
