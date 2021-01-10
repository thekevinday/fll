#include "fss.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_item_adjust_
  f_status_t f_fss_item_adjust(const f_string_length_t length, f_fss_item_t *item) {
    #ifndef _di_level_0_parameter_checking_
      if (!item) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_item_adjust(length, item);
  }
#endif // _di_f_fss_item_adjust_

#ifndef _di_f_fss_item_decimate_by_
  f_status_t f_fss_item_decimate_by(const f_array_length_t amount, f_fss_item_t *item) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!item) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (item->content.size - amount > 0) {
      return private_f_fss_item_adjust(item->content.size - amount, item);
    }

    return private_f_fss_item_adjust(0, item);
  }
#endif // _di_f_fss_item_decimate_by_

#ifndef _di_f_fss_item_decrease_by_
  f_status_t f_fss_item_decrease_by(const f_array_length_t amount, f_fss_item_t *item) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!item) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (item->content.size - amount > 0) {
      return private_f_fss_item_resize(item->content.size - amount, item);
    }

    return private_f_fss_item_resize(0, item);
  }
#endif // _di_f_fss_item_decrease_by_

#ifndef _di_f_fss_item_delete_
  f_status_t f_fss_item_delete(f_fss_item_t *item) {
    #ifndef _di_level_0_parameter_checking_
      if (!item) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_item_resize(0, item);
  }
#endif // _di_f_fss_item_delete_

#ifndef _di_f_fss_item_destroy_
  f_status_t f_fss_item_destroy(f_fss_item_t *item) {
    #ifndef _di_level_0_parameter_checking_
      if (!item) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_item_adjust(0, item);
  }
#endif // _di_f_fss_item_destroy_

#ifndef _di_f_fss_item_increase_
  f_status_t f_fss_item_increase(f_fss_item_t *item) {
    #ifndef _di_level_0_parameter_checking_
      if (!item) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (item->content.used + 1 > item->content.size) {
      f_array_length_t size = item->content.used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (item->content.used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_fss_item_resize(size, item);
    }

    return F_none;
  }
#endif // _di_f_fss_item_increase_

#ifndef _di_f_fss_item_increase_by_
  f_status_t f_fss_item_increase_by(const f_array_length_t amount, f_fss_item_t *item) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!item) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (item->content.used + amount > item->content.size) {
      if (item->content.used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_fss_item_resize(item->content.used + amount, item);
    }

    return F_none;
  }
#endif // _di_f_fss_item_increase_by_

#ifndef _di_f_fss_item_new_
  f_status_t f_fss_item_new(const f_string_length_t length, f_fss_item_t *item) {
    #ifndef _di_level_0_parameter_checking_
      if (!item) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_macro_fss_item_t_clear((*item));

    f_status_t status = F_none;

    f_macro_memory_structure_new(status, item->content, f_fss_content_t, length);

    return status;
  }
#endif // _di_f_fss_item_new_

#ifndef _di_f_fss_item_resize_
  f_status_t f_fss_item_resize(const f_string_length_t length, f_fss_item_t *item) {
    #ifndef _di_level_0_parameter_checking_
      if (!item) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_item_resize(length, item);
  }
#endif // _di_f_fss_item_resize_

#ifndef _di_f_fss_items_adjust_
  f_status_t f_fss_items_adjust(const f_string_length_t length, f_fss_items_t *items) {
    #ifndef _di_level_0_parameter_checking_
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_items_adjust(length, items);
  }
#endif // _di_f_fss_items_adjust_

#ifndef _di_f_fss_items_decimate_by_
  f_status_t f_fss_items_decimate_by(const f_array_length_t amount, f_fss_items_t *items) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (items->size - amount > 0) {
      return private_f_fss_items_adjust(items->size - amount, items);
    }

    return private_f_fss_items_adjust(0, items);
  }
#endif // _di_f_fss_items_decimate_by_

#ifndef _di_f_fss_items_decrease_by_
  f_status_t f_fss_items_decrease_by(const f_array_length_t amount, f_fss_items_t *items) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (items->size - amount > 0) {
      return private_f_fss_items_resize(items->size - amount, items);
    }

    return private_f_fss_items_resize(0, items);
  }
#endif // _di_f_fss_items_decrease_by_

#ifndef _di_f_fss_items_delete_
  f_status_t f_fss_items_delete(f_fss_items_t *items) {
    #ifndef _di_level_0_parameter_checking_
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_items_resize(0, items);
  }
#endif // _di_f_fss_items_delete_

#ifndef _di_f_fss_items_destroy_
  f_status_t f_fss_items_destroy(f_fss_items_t *items) {
    #ifndef _di_level_0_parameter_checking_
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_items_adjust(0, items);
  }
#endif // _di_f_fss_items_destroy_

#ifndef _di_f_fss_items_increase_
  f_status_t f_fss_items_increase(f_fss_items_t *items) {
    #ifndef _di_level_0_parameter_checking_
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (items->used + 1 > items->size) {
      f_array_length_t size = items->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (items->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_fss_items_resize(size, items);
    }

    return F_none;
  }
#endif // _di_f_fss_items_increase_

#ifndef _di_f_fss_items_increase_by_
  f_status_t f_fss_items_increase_by(const f_array_length_t amount, f_fss_items_t *items) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (items->used + amount > items->size) {
      if (items->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_fss_items_resize(items->used + amount, items);
    }

    return F_none;
  }
#endif // _di_f_fss_items_increase_by_

#ifndef _di_f_fss_items_resize_
  f_status_t f_fss_items_resize(const f_string_length_t length, f_fss_items_t *items) {
    #ifndef _di_level_0_parameter_checking_
      if (!items) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_items_resize(length, items);
  }
#endif // _di_f_fss_items_resize_

#ifndef _di_f_fss_nest_adjust_
  f_status_t f_fss_nest_adjust(const f_string_length_t length, f_fss_nest_t *nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nest_adjust(length, nest);
  }
#endif // _di_f_fss_nest_adjust_

#ifndef _di_f_fss_nest_decimate_by_
  f_status_t f_fss_nest_decimate_by(const f_array_length_t amount, f_fss_nest_t *nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nest->size - amount > 0) {
      return private_f_fss_nest_adjust(nest->size - amount, nest);
    }

    return private_f_fss_nest_adjust(0, nest);
  }
#endif // _di_f_fss_nest_decimate_by_

#ifndef _di_f_fss_nest_decrease_by_
  f_status_t f_fss_nest_decrease_by(const f_array_length_t amount, f_fss_nest_t *nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nest->size - amount > 0) {
      return private_f_fss_nest_resize(nest->size - amount, nest);
    }

    return private_f_fss_nest_resize(0, nest);
  }
#endif // _di_f_fss_nest_decrease_by_

#ifndef _di_f_fss_nest_delete_
  f_status_t f_fss_nest_delete(f_fss_nest_t *nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nest_resize(0, nest);
  }
#endif // _di_f_fss_nest_delete_

#ifndef _di_f_fss_nest_destroy_
  f_status_t f_fss_nest_destroy(f_fss_nest_t *nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nest_adjust(0, nest);
  }
#endif // _di_f_fss_nest_destroy_

#ifndef _di_f_fss_nest_increase_
  f_status_t f_fss_nest_increase(f_fss_nest_t *nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nest->used + 1 > nest->size) {
      f_array_length_t size = nest->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (nest->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_fss_nest_resize(size, nest);
    }

    return F_none;
  }
#endif // _di_f_fss_nest_increase_

#ifndef _di_f_fss_nest_increase_by_
  f_status_t f_fss_nest_increase_by(const f_array_length_t amount, f_fss_nest_t *nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nest->used + amount > nest->size) {
      if (nest->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_fss_nest_resize(nest->used + amount, nest);
    }

    return F_none;
  }
#endif // _di_f_fss_nest_increase_by_

#ifndef _di_f_fss_nest_resize_
  f_status_t f_fss_nest_resize(const f_string_length_t length, f_fss_nest_t *nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nest_resize(length, nest);
  }
#endif // _di_f_fss_nest_resize_

#ifndef _di_f_fss_nests_adjust_
  f_status_t f_fss_nests_adjust(const f_string_length_t length, f_fss_nests_t *nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nests_adjust(length, nests);
  }
#endif // _di_f_fss_nests_adjust_

#ifndef _di_f_fss_nests_decimate_by_
  f_status_t f_fss_nests_decimate_by(const f_array_length_t amount, f_fss_nests_t *nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nests->size - amount > 0) {
      return private_f_fss_nests_adjust(nests->size - amount, nests);
    }

    return private_f_fss_nests_adjust(0, nests);
  }
#endif // _di_f_fss_nests_decimate_by_

#ifndef _di_f_fss_nests_decrease_by_
  f_status_t f_fss_nests_decrease_by(const f_array_length_t amount, f_fss_nests_t *nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nests->size - amount > 0) {
      return private_f_fss_nests_resize(nests->size - amount, nests);
    }

    return private_f_fss_nests_resize(0, nests);
  }
#endif // _di_f_fss_nests_decrease_by_

#ifndef _di_f_fss_nests_delete_
  f_status_t f_fss_nests_delete(f_fss_nests_t *nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nests_resize(0, nests);
  }
#endif // _di_f_fss_nests_delete_

#ifndef _di_f_fss_nests_destroy_
  f_status_t f_fss_nests_destroy(f_fss_nests_t *nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nests_adjust(0, nests);
  }
#endif // _di_f_fss_nests_destroy_

#ifndef _di_f_fss_nests_increase_
  f_status_t f_fss_nests_increase(f_fss_nests_t *nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nests->used + 1 > nests->size) {
      f_array_length_t size = nests->used + f_memory_default_allocation_step;

      if (size > f_array_length_t_size) {
        if (nests->used + 1 > f_array_length_t_size) {
          return F_status_set_error(F_array_too_large);
        }

        size = f_array_length_t_size;
      }

      return private_f_fss_nests_resize(size, nests);
    }

    return F_none;
  }
#endif // _di_f_fss_nests_increase_

#ifndef _di_f_fss_nests_increase_by_
  f_status_t f_fss_nests_increase_by(const f_array_length_t amount, f_fss_nests_t *nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!amount) return F_status_set_error(F_parameter);
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (nests->used + amount > nests->size) {
      if (nests->used + amount > f_array_length_t_size) {
        return F_status_set_error(F_array_too_large);
      }

      return private_f_fss_nests_resize(nests->used + amount, nests);
    }

    return F_none;
  }
#endif // _di_f_fss_nests_increase_by_

#ifndef _di_f_fss_nests_resize_
  f_status_t f_fss_nests_resize(const f_string_length_t length, f_fss_nests_t *nests) {
    #ifndef _di_level_0_parameter_checking_
      if (!nests) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_fss_nests_resize(length, nests);
  }
#endif // _di_f_fss_nests_resize_

#ifdef __cplusplus
} // extern "C"
#endif
