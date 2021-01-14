#include "fss.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_fss_items_adjust_) || !defined(_di_f_fss_items_decimate_by_)
  f_status_t private_f_fss_items_adjust(const f_array_length_t length, f_fss_items_t *items) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < items->size; ++i) {
      f_macro_fss_item_t_adjust(status, items->array[i], 0)
    } // for

    status = f_memory_adjust((void **) & items->array, sizeof(f_fss_item_t), items->size, length);

    if (F_status_is_error_not(status)) {
      items->size = length;

      if (items->used > items->size) {
        items->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_items_adjust_) || !defined(_di_f_fss_items_decimate_by_)

#if !defined(_di_f_fss_items_decrease_by_) || !defined(_di_f_fss_items_increase_) || !defined(_di_f_fss_items_increase_by_) || !defined(_di_f_fss_items_resize_)
  f_status_t private_f_fss_items_resize(const f_array_length_t length, f_fss_items_t *items) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < items->size; ++i) {
      f_macro_fss_item_t_resize(status, items->array[i], 0)
    } // for

    status = f_memory_resize((void **) & items->array, sizeof(f_fss_item_t), items->size, length);

    if (F_status_is_error_not(status)) {
      items->size = length;

      if (items->used > items->size) {
        items->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_items_decrease_by_) || !defined(_di_f_fss_items_increase_) || !defined(_di_f_fss_items_increase_by_) || !defined(_di_f_fss_items_resize_)

#if !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)
  f_status_t private_f_fss_named_adjust(const f_array_length_t length, f_fss_named_t *named) {
    f_status_t status = F_none;

    f_macro_string_ranges_t_adjust(status, named->objects, length)
    if (F_status_is_error(status)) return status;

    f_macro_string_rangess_t_adjust(status, named->contents, length)
    if (F_status_is_error(status)) return status;

    f_macro_uint8ss_t_adjust(status, named->quotess, length)

    return status;
  }
#endif // !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)

#if !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_) || !defined(_di_f_fss_nameds_resize_)
  f_status_t private_f_fss_named_resize(const f_array_length_t length, f_fss_named_t *named) {
    f_status_t status = F_none;

    f_macro_string_ranges_t_resize(status, named->objects, length)
    if (F_status_is_error(status)) return status;

    f_macro_string_rangess_t_resize(status, named->contents, length)
    if (F_status_is_error(status)) return status;

    f_macro_uint8ss_t_resize(status, named->quotess, length)

    return status;
  }
#endif // !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_) || !defined(_di_f_fss_nameds_resize_)

#if !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)
  f_status_t private_f_fss_nameds_adjust(const f_array_length_t length, f_fss_nameds_t *nameds) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < nameds->size; ++i) {
      status = private_f_fss_named_adjust(0, &nameds->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust((void **) & nameds->array, sizeof(f_fss_named_t), nameds->size, length);

    if (F_status_is_error_not(status)) {
      nameds->size = length;

      if (nameds->used > nameds->size) {
        nameds->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_)

#if !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_) || !defined(_di_f_fss_nameds_resize_)
  f_status_t private_f_fss_nameds_resize(const f_array_length_t length, f_fss_nameds_t *nameds) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < nameds->size; ++i) {
      status = private_f_fss_named_resize(0, &nameds->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize((void **) & nameds->array, sizeof(f_fss_named_t), nameds->size, length);

    if (F_status_is_error_not(status)) {
      nameds->size = length;

      if (nameds->used > nameds->size) {
        nameds->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_) || !defined(_di_f_fss_nameds_resize_)

#if !defined(_di_f_fss_nest_adjust_) || !defined(_di_f_fss_nest_decimate_by_)
  f_status_t private_f_fss_nest_adjust(const f_array_length_t length, f_fss_nest_t *nest) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < nest->size; ++i) {
      status = private_f_fss_items_adjust(0, &nest->depth[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust((void **) & nest->depth, sizeof(f_fss_items_t), nest->size, length);

    if (F_status_is_error_not(status)) {
      nest->size = length;

      if (nest->used > nest->size) {
        nest->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_nest_adjust_) || !defined(_di_f_fss_nest_decimate_by_)

#if !defined(_di_f_fss_nest_decrease_by_) || !defined(_di_f_fss_nest_increase_) || !defined(_di_f_fss_nest_increase_by_) || !defined(_di_f_fss_nest_resize_)
  f_status_t private_f_fss_nest_resize(const f_array_length_t length, f_fss_nest_t *nest) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < nest->size; ++i) {
      status = private_f_fss_items_resize(0, &nest->depth[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize((void **) & nest->depth, sizeof(f_fss_items_t), nest->size, length);

    if (F_status_is_error_not(status)) {
      nest->size = length;

      if (nest->used > nest->size) {
        nest->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_nest_decrease_by_) || !defined(_di_f_fss_nest_increase_) || !defined(_di_f_fss_nest_increase_by_) || !defined(_di_f_fss_nest_resize_)

#if !defined(_di_f_fss_nests_adjust_) || !defined(_di_f_fss_nests_decimate_by_)
  f_status_t private_f_fss_nests_adjust(const f_array_length_t length, f_fss_nests_t *nests) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < nests->size; ++i) {
      status = private_f_fss_nest_adjust(0, &nests->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust((void **) & nests->array, sizeof(f_fss_nest_t), nests->size, length);

    if (F_status_is_error_not(status)) {
      nests->size = length;

      if (nests->used > nests->size) {
        nests->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_nests_adjust_) || !defined(_di_f_fss_nests_decimate_by_)

#if !defined(_di_f_fss_nests_decrease_by_) || !defined(_di_f_fss_nests_increase_) || !defined(_di_f_fss_nests_increase_by_) || !defined(_di_f_fss_nests_resize_)
  f_status_t private_f_fss_nests_resize(const f_array_length_t length, f_fss_nests_t *nests) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < nests->size; ++i) {
      status = private_f_fss_nest_resize(0, &nests->array[i]);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize((void **) & nests->array, sizeof(f_fss_nest_t), nests->size, length);

    if (F_status_is_error_not(status)) {
      nests->size = length;

      if (nests->used > nests->size) {
        nests->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_nests_decrease_by_) || !defined(_di_f_fss_nests_increase_) || !defined(_di_f_fss_nests_increase_by_) || !defined(_di_f_fss_nests_resize_)

#if !defined(_di_f_fss_set_adjust_) || !defined(_di_f_fss_set_decimate_by_)
  f_status_t private_f_fss_set_adjust(const f_array_length_t length, f_fss_set_t *set) {
    f_status_t status = F_none;

    f_macro_fss_objects_t_adjust(status, set->objects, length);
    if (F_status_is_error(status)) return status;

    f_macro_fss_contents_t_adjust(status, set->contents, length);

    return status;
  }
#endif // !defined(_di_f_fss_set_adjust_) || !defined(_di_f_fss_set_decimate_by_)

#if !defined(_di_f_fss_set_decrease_by_) || !defined(_di_f_fss_set_increase_) || !defined(_di_f_fss_set_increase_by_) || !defined(_di_f_fss_set_resize_)
  f_status_t private_f_fss_set_resize(const f_array_length_t length, f_fss_set_t *set) {
    f_status_t status = F_none;

    f_macro_fss_objects_t_resize(status, set->objects, length);
    if (F_status_is_error(status)) return status;

    f_macro_fss_contents_t_resize(status, set->contents, length);

    return status;
  }
#endif // !defined(_di_f_fss_set_decrease_by_) || !defined(_di_f_fss_set_increase_) || !defined(_di_f_fss_set_increase_by_) || !defined(_di_f_fss_set_resize_)

#if !defined(_di_f_fss_set_quote_adjust_) || !defined(_di_f_fss_set_quote_decimate_by_)
  f_status_t private_f_fss_set_quote_adjust(const f_array_length_t length, f_fss_set_quote_t *set_quote) {
    f_status_t status = F_none;

    f_macro_fss_objects_t_adjust(status, set_quote->objects, length);
    if (F_status_is_error(status)) return status;

    f_macro_fss_contents_t_adjust(status, set_quote->contents, length);
    if (F_status_is_error(status)) return status;

    f_macro_fss_quotes_t_adjust(status, set_quote->objects_quote, length);
    if (F_status_is_error(status)) return status;

    f_macro_fss_quotess_t_adjust(status, set_quote->contents_quote, length);

    return status;
  }
#endif // !defined(_di_f_fss_set_quote_adjust_) || !defined(_di_f_fss_set_quote_decimate_by_)

#if !defined(_di_f_fss_set_quote_decrease_by_) || !defined(_di_f_fss_set_quote_increase_) || !defined(_di_f_fss_set_quote_increase_by_) || !defined(_di_f_fss_set_quote_resize_)
  f_status_t private_f_fss_set_quote_resize(const f_array_length_t length, f_fss_set_quote_t *set_quote) {
    f_status_t status = F_none;

    f_macro_fss_objects_t_resize(status, set_quote->objects, length);
    if (F_status_is_error(status)) return status;

    f_macro_fss_contents_t_resize(status, set_quote->contents, length);
    if (F_status_is_error(status)) return status;

    f_macro_fss_quotes_t_resize(status, set_quote->objects_quote, length);
    if (F_status_is_error(status)) return status;

    f_macro_fss_quotess_t_resize(status, set_quote->contents_quote, length);

    return status;
  }
#endif // !defined(_di_f_fss_set_quote_decrease_by_) || !defined(_di_f_fss_set_quote_increase_) || !defined(_di_f_fss_set_quote_increase_by_) || !defined(_di_f_fss_set_quote_resize_)

#if !defined(_di_f_fss_set_quotes_adjust_) || !defined(_di_f_fss_set_quotes_decimate_by_)
  f_status_t private_f_fss_set_quotes_adjust(const f_array_length_t length, f_fss_set_quotes_t *set_quotes) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < set_quotes->size; ++i) {

      f_macro_fss_objects_t_adjust(status, set_quotes->array[i].objects, 0);
      if (F_status_is_error(status)) return status;

      f_macro_fss_contents_t_adjust(status, set_quotes->array[i].contents, 0);
      if (F_status_is_error(status)) return status;

      f_macro_fss_quotes_t_adjust(status, set_quotes->array[i].objects_quote, 0);
      if (F_status_is_error(status)) return status;

      f_macro_fss_quotess_t_adjust(status, set_quotes->array[i].contents_quote, 0);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_adjust((void **) & set_quotes->array, sizeof(f_fss_set_quote_t), set_quotes->size, length);

    if (F_status_is_error_not(status)) {
      set_quotes->size = length;

      if (set_quotes->used > set_quotes->size) {
        set_quotes->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_set_quotes_adjust_) || !defined(_di_f_fss_set_quotes_decimate_by_)

#if !defined(_di_f_fss_set_quotes_decrease_by_) || !defined(_di_f_fss_set_quotes_increase_) || !defined(_di_f_fss_set_quotes_increase_by_) || !defined(_di_f_fss_set_quotes_resize_)
  f_status_t private_f_fss_set_quotes_resize(const f_array_length_t length, f_fss_set_quotes_t *set_quotes) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < set_quotes->size; ++i) {

      f_macro_fss_objects_t_resize(status, set_quotes->array[i].objects, 0);
      if (F_status_is_error(status)) return status;

      f_macro_fss_contents_t_resize(status, set_quotes->array[i].contents, 0);
      if (F_status_is_error(status)) return status;

      f_macro_fss_quotes_t_resize(status, set_quotes->array[i].objects_quote, 0);
      if (F_status_is_error(status)) return status;

      f_macro_fss_quotess_t_resize(status, set_quotes->array[i].contents_quote, 0);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize((void **) & set_quotes->array, sizeof(f_fss_set_quote_t), set_quotes->size, length);

    if (F_status_is_error_not(status)) {
      set_quotes->size = length;

      if (set_quotes->used > set_quotes->size) {
        set_quotes->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_set_quotes_decrease_by_) || !defined(_di_f_fss_set_quotes_increase_) || !defined(_di_f_fss_set_quotes_increase_by_) || !defined(_di_f_fss_set_quotes_resize_)

#if !defined(_di_f_fss_sets_adjust_) || !defined(_di_f_fss_sets_decimate_by_)
  f_status_t private_f_fss_sets_adjust(const f_array_length_t length, f_fss_sets_t *sets) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < sets->size; ++i) {

      f_macro_fss_objects_t_adjust(status, sets->array[i].objects, 0);
      if (F_status_is_error(status)) return status;

      f_macro_fss_contents_t_adjust(status, sets->array[i].contents, 0);
      if (F_status_is_error(status)) return status;
    } // for

    f_memory_adjust((void **) & sets->array, sizeof(f_fss_set_t), sets->size, length);

    if (F_status_is_error_not(status)) {
      sets->size = length;

      if (sets->used > sets->size) {
        sets->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_sets_adjust_) || !defined(_di_f_fss_sets_decimate_by_)

#if !defined(_di_f_fss_sets_decrease_by_) || !defined(_di_f_fss_sets_increase_) || !defined(_di_f_fss_sets_increase_by_) || !defined(_di_f_fss_sets_resize_)
  f_status_t private_f_fss_sets_resize(const f_array_length_t length, f_fss_sets_t *sets) {
    f_status_t status = F_none;

    for (f_array_length_t i = length; i < sets->size; ++i) {

      f_macro_fss_objects_t_resize(status, sets->array[i].objects, 0);
      if (F_status_is_error(status)) return status;

      f_macro_fss_contents_t_resize(status, sets->array[i].contents, 0);
      if (F_status_is_error(status)) return status;
    } // for

    status = f_memory_resize((void **) & sets->array, sizeof(f_fss_set_t), sets->size, length);

    if (F_status_is_error_not(status)) {
      sets->size = length;

      if (sets->used > sets->size) {
        sets->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_sets_decrease_by_) || !defined(_di_f_fss_sets_increase_) || !defined(_di_f_fss_sets_increase_by_) || !defined(_di_f_fss_sets_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
