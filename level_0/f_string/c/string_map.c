#include "string.h"
#include "private-string.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_string_map_multis_adjust_
  f_status_t f_string_map_multis_adjust(const f_string_length_t length, f_string_map_multis_t *map_multis) {
    #ifndef _di_level_0_parameter_checking_
      if (!map_multis) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_map_multis_adjust(length, map_multis);
  }
#endif // _di_f_string_map_multis_adjust_

#ifndef _di_f_string_map_multis_decimate_by_
  f_status_t f_string_map_multis_decimate_by(const f_array_length_t amount, f_string_map_multis_t *map_multis) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!map_multis) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (map_multis->size - amount > 0) {
      return private_f_string_map_multis_adjust(map_multis->size - amount, map_multis);
    }

    return private_f_string_map_multis_adjust(0, map_multis);
  }
#endif // _di_f_string_map_multis_decimate_by_

#ifndef _di_f_string_map_multis_decrease_by_
  f_status_t f_string_map_multis_decrease_by(const f_array_length_t amount, f_string_map_multis_t *map_multis) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!map_multis) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (map_multis->size - amount > 0) {
      return private_f_string_map_multis_resize(map_multis->size - amount, map_multis);
    }

    return private_f_string_map_multis_resize(0, map_multis);
  }
#endif // _di_f_string_map_multis_decrease_by_

#ifndef _di_f_string_map_multis_increase_
  f_status_t f_string_map_multis_increase(f_string_map_multis_t *map_multis) {
    #ifndef _di_level_0_parameter_checking_
      if (!map_multis) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (map_multis->used + 1 > map_multis->size) {
      f_array_length_t size = map_multis->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (map_multis->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_string_map_multis_resize(size, map_multis);
    }

    return F_data_not;
  }
#endif // _di_f_string_map_multis_increase_

#ifndef _di_f_string_map_multis_increase_by_
  f_status_t f_string_map_multis_increase_by(const f_array_length_t amount, f_string_map_multis_t *map_multis) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!map_multis) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (map_multis->used + amount > map_multis->size) {
      if (map_multis->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_string_map_multis_resize(map_multis->used + amount, map_multis);
    }

    return F_data_not;
  }
#endif // _di_f_string_map_multis_increase_by_

#ifndef _di_f_string_map_multis_resize_
  f_status_t f_string_map_multis_resize(const f_string_length_t length, f_string_map_multis_t *map_multis) {
    #ifndef _di_level_0_parameter_checking_
      if (!map_multis) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_map_multis_resize(length, map_multis);
  }
#endif // _di_f_string_map_multis_resize_

#ifndef _di_f_string_maps_adjust_
  f_status_t f_string_maps_adjust(const f_string_length_t length, f_string_maps_t *maps) {
    #ifndef _di_level_0_parameter_checking_
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_maps_adjust(length, maps);
  }
#endif // _di_f_string_maps_adjust_

#ifndef _di_f_string_maps_decimate_by_
  f_status_t f_string_maps_decimate_by(const f_array_length_t amount, f_string_maps_t *maps) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (maps->size - amount > 0) {
      return private_f_string_maps_adjust(maps->size - amount, maps);
    }

    return private_f_string_maps_adjust(0, maps);
  }
#endif // _di_f_string_maps_decimate_by_

#ifndef _di_f_string_maps_decrease_by_
  f_status_t f_string_maps_decrease_by(const f_array_length_t amount, f_string_maps_t *maps) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (maps->size - amount > 0) {
      return private_f_string_maps_resize(maps->size - amount, maps);
    }

    return private_f_string_maps_resize(0, maps);
  }
#endif // _di_f_string_maps_decrease_by_

#ifndef _di_f_string_maps_increase_
  f_status_t f_string_maps_increase(f_string_maps_t *maps) {
    #ifndef _di_level_0_parameter_checking_
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (maps->used + 1 > maps->size) {
      f_array_length_t size = maps->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (maps->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_string_maps_resize(size, maps);
    }

    return F_data_not;
  }
#endif // _di_f_string_maps_increase_

#ifndef _di_f_string_maps_increase_by_
  f_status_t f_string_maps_increase_by(const f_array_length_t amount, f_string_maps_t *maps) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (maps->used + amount > maps->size) {
      if (maps->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_string_maps_resize(maps->used + amount, maps);
    }

    return F_data_not;
  }
#endif // _di_f_string_maps_increase_by_

#ifndef _di_f_string_maps_resize_
  f_status_t f_string_maps_resize(const f_string_length_t length, f_string_maps_t *maps) {
    #ifndef _di_level_0_parameter_checking_
      if (!maps) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_string_maps_resize(length, maps);
  }
#endif // _di_f_string_maps_resize_

#ifdef __cplusplus
} // extern "C"
#endif
