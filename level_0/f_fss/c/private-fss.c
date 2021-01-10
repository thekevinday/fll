#include "fss.h"
#include "private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_fss_item_adjust_) || !defined(_di_f_fss_item_decimate_by_) || !defined(_di_f_fss_item_destroy_)
  f_status_t private_f_fss_item_adjust(const f_array_length_t length, f_fss_item_t *item) {
    f_status_t status = F_none;

    if (length < item->content.size) {

      // item->object has no allocatable child elements.

      for (f_array_length_t i = item->content.size - length; i < item->content.size; ++i) {
        f_macro_fss_content_t_destroy(status, item->content);
        if (F_status_is_error(status)) return status;
      } // for
    }

    status = f_memory_adjust((void **) & item->content.array, sizeof(f_fss_content_t), item->content.size, length);

    if (F_status_is_error_not(status)) {
      if (!length) {
        item->object.start = 1;
        item->object.stop = 0;
        item->parent = 0;
      }

      item->content.size = length;

      if (item->content.used > item->content.size) {
        item->content.used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_item_adjust_) || !defined(_di_f_fss_item_decimate_by_) || !defined(_di_f_fss_item_destroy_)

#if !defined(_di_f_fss_item_decrease_by_) || !defined(_di_f_fss_item_delete_) || !defined(_di_f_fss_item_increase_) || !defined(_di_f_fss_item_increase_by_) || !defined(_di_f_fss_item_resize_)
  f_status_t private_f_fss_item_resize(const f_array_length_t length, f_fss_item_t *item) {
    f_status_t status = F_none;

    if (length < item->content.size) {

      // item->object has no allocatable child elements.

      for (f_array_length_t i = item->content.size - length; i < item->content.size; ++i) {
        f_macro_fss_content_t_delete(status, item->content);
        if (F_status_is_error(status)) return status;
      } // for
    }

    status = f_memory_resize((void **) & item->content.array, sizeof(f_fss_content_t), item->content.size, length);

    if (F_status_is_error_not(status)) {
      if (!length) {
        item->object.start = 1;
        item->object.stop = 0;
        item->parent = 0;
      }

      item->content.size = length;

      if (item->content.used > item->content.size) {
        item->content.used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_item_decrease_by_) || !defined(_di_f_fss_item_delete_) || !defined(_di_f_fss_item_increase_) || !defined(_di_f_fss_item_increase_by_) || !defined(_di_f_fss_item_resize_)

#if !defined(_di_f_fss_items_adjust_) || !defined(_di_f_fss_items_decimate_by_) || !defined(_di_f_fss_items_destroy_)
  f_status_t private_f_fss_items_adjust(const f_array_length_t length, f_fss_items_t *items) {
    f_status_t status = F_none;

    if (length < items->size) {
      for (f_array_length_t i = items->size - length; i < items->size; ++i) {
        status = private_f_fss_item_adjust(0, &items->array[i]);
        if (F_status_is_error(status)) return status;
      } // for
    }

    status = f_memory_adjust((void **) & items->array, sizeof(f_fss_item_t), items->size, length);

    if (F_status_is_error_not(status)) {
      items->size = length;

      if (items->used > items->size) {
        items->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_items_adjust_) || !defined(_di_f_fss_items_decimate_by_) || !defined(_di_f_fss_items_destroy_)

#if !defined(_di_f_fss_items_decrease_by_) || !defined(_di_f_fss_items_delete_) || !defined(_di_f_fss_items_increase_) || !defined(_di_f_fss_items_increase_by_) || !defined(_di_f_fss_items_resize_)
  f_status_t private_f_fss_items_resize(const f_array_length_t length, f_fss_items_t *items) {
    f_status_t status = F_none;

    if (length < items->size) {
      for (f_array_length_t i = items->size - length; i < items->size; ++i) {
        status = private_f_fss_item_resize(0, &items->array[i]);
        if (F_status_is_error(status)) return status;
      } // for
    }

    status = f_memory_resize((void **) & items->array, sizeof(f_fss_item_t), items->size, length);

    if (F_status_is_error_not(status)) {
      items->size = length;

      if (items->used > items->size) {
        items->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_items_decrease_by_) || !defined(_di_f_fss_items_delete_) || !defined(_di_f_fss_items_increase_) || !defined(_di_f_fss_items_increase_by_) || !defined(_di_f_fss_items_resize_)

#if !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_destroy_) || !defined(_di_f_fss_nameds_decimate_by_)
  f_status_t private_f_fss_named_destroy(f_fss_named_t *named) {
    f_status_t status = F_none;

    f_macro_string_ranges_t_destroy(status, named->objects);
    if (F_status_is_error(status)) return status;

    named->objects.size = 0;
    named->objects.used = 0;

    f_macro_string_rangess_t_destroy(status, named->contents);
    if (F_status_is_error(status)) return status;

    named->contents.size = 0;
    named->contents.used = 0;

    f_macro_uint8ss_t_destroy(status, named->quotess);

    if (F_status_is_error_not(status)) {
      named->quotess.size = 0;
      named->quotess.used = 0;
    }

    return status;
  }
#endif // !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_destroy_) || !defined(_di_f_fss_nameds_decimate_by_)

#if !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_delete_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_)
  f_status_t private_f_fss_named_delete(f_fss_named_t *named) {
    f_status_t status = F_none;

    f_macro_string_ranges_t_delete(status, named->objects);
    if (F_status_is_error(status)) return status;

    named->objects.size = 0;
    named->objects.used = 0;

    f_macro_string_rangess_t_delete(status, named->contents);
    if (F_status_is_error(status)) return status;

    named->contents.size = 0;
    named->contents.used = 0;

    f_macro_uint8ss_t_delete(status, named->quotess);

    if (F_status_is_error_not(status)) {
      named->quotess.size = 0;
      named->quotess.used = 0;
    }

    return status;
  }
#endif // !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_delete_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_)

#if !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_) || !defined(_di_f_fss_nameds_destroy_)
  f_status_t private_f_fss_nameds_adjust(const f_array_length_t length, f_fss_nameds_t *nameds) {
    f_status_t status = F_none;

    if (length < nameds->size) {
      for (f_array_length_t i = nameds->size - length; i < nameds->size; ++i) {
        status = private_f_fss_named_destroy(&nameds->array[i]);
        if (F_status_is_error(status)) return status;
      } // for
    }

    status = f_memory_adjust((void **) & nameds->array, sizeof(f_fss_named_t), nameds->size, length);

    if (F_status_is_error_not(status)) {
      nameds->size = length;

      if (nameds->used > nameds->size) {
        nameds->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_nameds_adjust_) || !defined(_di_f_fss_nameds_decimate_by_) || !defined(_di_f_fss_nameds_destroy_)

#if !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_delete_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_) || !defined(_di_f_fss_nameds_resize_)
  f_status_t private_f_fss_nameds_resize(const f_array_length_t length, f_fss_nameds_t *nameds) {
    f_status_t status = F_none;

    if (length < nameds->size) {
      for (f_array_length_t i = nameds->size - length; i < nameds->size; ++i) {
        status = private_f_fss_named_delete(&nameds->array[i]);
        if (F_status_is_error(status)) return status;
      } // for
    }

    status = f_memory_resize((void **) & nameds->array, sizeof(f_fss_named_t), nameds->size, length);

    if (F_status_is_error_not(status)) {
      nameds->size = length;

      if (nameds->used > nameds->size) {
        nameds->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_nameds_decrease_by_) || !defined(_di_f_fss_nameds_delete_) || !defined(_di_f_fss_nameds_increase_) || !defined(_di_f_fss_nameds_increase_by_) || !defined(_di_f_fss_nameds_resize_)

#if !defined(_di_f_fss_nest_adjust_) || !defined(_di_f_fss_nest_decimate_by_) || !defined(_di_f_fss_nest_destroy_)
  f_status_t private_f_fss_nest_adjust(const f_array_length_t length, f_fss_nest_t *nest) {
    f_status_t status = F_none;

    if (length < nest->size) {
      for (f_array_length_t i = nest->size - length; i < nest->size; ++i) {
        status = private_f_fss_items_adjust(0, &nest->depth[i]);
        if (F_status_is_error(status)) return status;
      } // for
    }

    status = f_memory_adjust((void **) & nest->depth, sizeof(f_fss_items_t), nest->size, length);

    if (F_status_is_error_not(status)) {
      nest->size = length;

      if (nest->used > nest->size) {
        nest->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_nest_adjust_) || !defined(_di_f_fss_nest_decimate_by_) || !defined(_di_f_fss_nest_destroy_)

#if !defined(_di_f_fss_nest_decrease_by_) || !defined(_di_f_fss_nest_delete_) || !defined(_di_f_fss_nest_increase_) || !defined(_di_f_fss_nest_increase_by_) || !defined(_di_f_fss_nest_resize_)
  f_status_t private_f_fss_nest_resize(const f_array_length_t length, f_fss_nest_t *nest) {
    f_status_t status = F_none;

    if (length < nest->size) {
      if (length) {
        for (f_array_length_t i = nest->size - length; i < nest->size; ++i) {
          status = private_f_fss_items_resize(0, &nest->depth[i]);
          if (F_status_is_error(status)) return status;
        } // for
      }
    }

    status = f_memory_resize((void **) & nest->depth, sizeof(f_fss_items_t), nest->size, length);

    if (F_status_is_error_not(status)) {
      nest->size = length;

      if (nest->used > nest->size) {
        nest->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_nest_decrease_by_) || !defined(_di_f_fss_nest_delete_) || !defined(_di_f_fss_nest_increase_) || !defined(_di_f_fss_nest_increase_by_) || !defined(_di_f_fss_nest_resize_)

#if !defined(_di_f_fss_nests_adjust_) || !defined(_di_f_fss_nests_decimate_by_) || !defined(_di_f_fss_nests_destroy_)
  f_status_t private_f_fss_nests_adjust(const f_array_length_t length, f_fss_nests_t *nests) {
    f_status_t status = F_none;

    if (length < nests->size) {
      for (f_array_length_t i = nests->size - length; i < nests->size; ++i) {
        status = private_f_fss_nest_adjust(0, &nests->array[i]);
        if (F_status_is_error(status)) return status;
      } // for
    }

    status = f_memory_adjust((void **) & nests->array, sizeof(f_fss_nest_t), nests->size, length);

    if (F_status_is_error_not(status)) {
      nests->size = length;

      if (nests->used > nests->size) {
        nests->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_nests_adjust_) || !defined(_di_f_fss_nests_decimate_by_) || !defined(_di_f_fss_nests_destroy_)

#if !defined(_di_f_fss_nests_decrease_by_) || !defined(_di_f_fss_nests_delete_) || !defined(_di_f_fss_nests_increase_) || !defined(_di_f_fss_nests_increase_by_) || !defined(_di_f_fss_nests_resize_)
  f_status_t private_f_fss_nests_resize(const f_array_length_t length, f_fss_nests_t *nests) {
    f_status_t status = F_none;

    if (length < nests->size) {
      for (f_array_length_t i = nests->size - length; i < nests->size; ++i) {
        status = private_f_fss_nest_resize(0, &nests->array[i]);
        if (F_status_is_error(status)) return status;
      } // for
    }

    status = f_memory_resize((void **) & nests->array, sizeof(f_fss_nest_t), nests->size, length);

    if (F_status_is_error_not(status)) {
      nests->size = length;

      if (nests->used > nests->size) {
        nests->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_nests_decrease_by_) || !defined(_di_f_fss_nests_delete_) || !defined(_di_f_fss_nests_increase_) || !defined(_di_f_fss_nests_increase_by_) || !defined(_di_f_fss_nests_resize_)

#if !defined(_di_f_fss_set_adjust_) || !defined(_di_f_fss_set_decimate_by_) || !defined(_di_f_fss_set_destroy_)
  f_status_t private_f_fss_set_adjust(const f_array_length_t length, f_fss_set_t *set) {
    f_status_t status = F_none;

    if (length < set->objects.size) {
      f_array_length_t i = set->objects.size - length;

      // set->objects has no allocatable child elements.

      if (length < set->contents.size) {
        if (length) {
          for (i = set->contents.size - length; i < set->contents.size; ++i) {
            f_macro_fss_content_t_destroy(status, set->contents.array[i]);
            if (F_status_is_error(status)) return status;
          } // for
        }
        else {
          f_macro_fss_contents_t_destroy(status, set->contents);
        }
      }
    }

    f_macro_fss_objects_t_adjust(status, set->objects, length);
    if (F_status_is_error(status)) return status;

    f_macro_fss_contents_t_adjust(status, set->contents, length);
    if (F_status_is_error(status)) return status;

    return status;
  }
#endif // !defined(_di_f_fss_set_adjust_) || !defined(_di_f_fss_set_decimate_by_) || !defined(_di_f_fss_set_destroy_)

#if !defined(_di_f_fss_set_decrease_by_) || !defined(_di_f_fss_set_delete_) || !defined(_di_f_fss_set_increase_) || !defined(_di_f_fss_set_increase_by_) || !defined(_di_f_fss_set_resize_)
  f_status_t private_f_fss_set_resize(const f_array_length_t length, f_fss_set_t *set) {
    f_status_t status = F_none;

    if (length < set->objects.size) {
      f_array_length_t i = set->objects.size - length;

      // set->objects has no allocatable child elements.

      if (length < set->contents.size) {
        if (length) {
          for (i = set->contents.size - length; i < set->contents.size; ++i) {
            f_macro_fss_content_t_delete(status, set->contents.array[i]);
            if (F_status_is_error(status)) return status;
          } // for
        }
        else {
          f_macro_fss_contents_t_delete(status, set->contents);
        }
      }
    }

    f_macro_fss_objects_t_resize(status, set->objects, length);
    if (F_status_is_error(status)) return status;

    f_macro_fss_contents_t_resize(status, set->contents, length);
    if (F_status_is_error(status)) return status;

    return status;
  }
#endif // !defined(_di_f_fss_set_decrease_by_) || !defined(_di_f_fss_set_delete_) || !defined(_di_f_fss_set_increase_) || !defined(_di_f_fss_set_increase_by_) || !defined(_di_f_fss_set_resize_)

#if !defined(_di_f_fss_set_quote_adjust_) || !defined(_di_f_fss_set_quote_decimate_by_) || !defined(_di_f_fss_set_quote_destroy_)
  f_status_t private_f_fss_set_quote_adjust(const f_array_length_t length, f_fss_set_quote_t *set_quote) {
    f_status_t status = F_none;

    if (length < set_quote->objects.size) {
      f_array_length_t i = set_quote->contents.size - length;

      // set_quote->objects has no allocatable child elements.

      if (length < set_quote->contents.size) {
        if (length) {
          for (; i < set_quote->contents.size; ++i) {
            f_macro_fss_content_t_destroy(status, set_quote->contents.array[i]);
            if (F_status_is_error(status)) return status;
          } // for
        }
        else {
          f_macro_fss_contents_t_destroy(status, set_quote->contents);
        }
      }

      // set_quote->objects_quote has no allocatable child elements.

      if (length < set_quote->contents_quote.size) {
        if (length) {
          for (i = set_quote->contents_quote.size - length; i < set_quote->contents_quote.size; ++i) {
            f_macro_fss_quotes_t_destroy(status, set_quote->contents_quote.array[i]);
            if (F_status_is_error(status)) return status;
          } // for
        }
        else {
          f_macro_fss_quotess_t_delete(status, set_quote->contents_quote);
        }
      }
    }

    status = f_memory_adjust((void **) & set_quote->objects.array, sizeof(f_fss_objects_t), set_quote->objects.size, length);
    if (F_status_is_error(status)) return status;

    set_quote->objects.size = length;

    if (set_quote->objects.used > set_quote->objects.size) {
      set_quote->objects.used = length;
    }

    status = f_memory_adjust((void **) & set_quote->contents.array, sizeof(f_fss_contents_t), set_quote->contents.size, length);
    if (F_status_is_error(status)) return status;

    set_quote->contents.size = length;

    if (set_quote->contents.used > set_quote->contents.size) {
      set_quote->contents.used = length;
    }

    status = f_memory_adjust((void **) & set_quote->objects_quote.array, sizeof(f_fss_quotes_t), set_quote->objects_quote.size, length);
    if (F_status_is_error(status)) return status;

    set_quote->objects_quote.size = length;

    if (set_quote->objects_quote.used > set_quote->objects_quote.size) {
      set_quote->objects_quote.used = length;
    }

    status = f_memory_adjust((void **) & set_quote->contents_quote.array, sizeof(f_fss_quotess_t), set_quote->contents_quote.size, length);
    if (F_status_is_error(status)) return status;

    set_quote->contents_quote.size = length;

    if (set_quote->contents_quote.used > set_quote->contents_quote.size) {
      set_quote->contents_quote.used = length;
    }

    return status;
  }
#endif // !defined(_di_f_fss_set_quote_adjust_) || !defined(_di_f_fss_set_quote_decimate_by_) || !defined(_di_f_fss_set_quote_destroy_)

#if !defined(_di_f_fss_set_quote_decrease_by_) || !defined(_di_f_fss_set_quote_delete_) || !defined(_di_f_fss_set_quote_increase_) || !defined(_di_f_fss_set_quote_increase_by_) || !defined(_di_f_fss_set_quote_resize_)
  f_status_t private_f_fss_set_quote_resize(const f_array_length_t length, f_fss_set_quote_t *set_quote) {
    f_status_t status = F_none;

    if (length < set_quote->objects.size) {
      f_array_length_t i = set_quote->contents.size - length;

      // set_quote->objects has no allocatable child elements.

      if (length < set_quote->contents.size) {
        if (length) {
          for (; i < set_quote->contents.size; ++i) {
            f_macro_fss_content_t_delete(status, set_quote->contents.array[i]);
            if (F_status_is_error(status)) return status;
          } // for
        }
        else {
          f_macro_fss_contents_t_delete(status, set_quote->contents);
        }
      }

      // set_quote->objects_quote has no allocatable child elements.

      if (length < set_quote->contents_quote.size) {
        if (length) {
          for (i = set_quote->contents_quote.size - length; i < set_quote->contents_quote.size; ++i) {
            f_macro_fss_quotes_t_delete(status, set_quote->contents_quote.array[i]);
            if (F_status_is_error(status)) return status;
          } // for
        }
        else {
          f_macro_fss_quotess_t_delete(status, set_quote->contents_quote);
        }
      }
    }

    status = f_memory_resize((void **) & set_quote->objects.array, sizeof(f_fss_objects_t), set_quote->objects.size, length);
    if (F_status_is_error(status)) return status;

    set_quote->objects.size = length;

    if (set_quote->objects.used > set_quote->objects.size) {
      set_quote->objects.used = length;
    }

    status = f_memory_resize((void **) & set_quote->contents.array, sizeof(f_fss_contents_t), set_quote->contents.size, length);
    if (F_status_is_error(status)) return status;

    set_quote->contents.size = length;

    if (set_quote->contents.used > set_quote->contents.size) {
      set_quote->contents.used = length;
    }

    status = f_memory_resize((void **) & set_quote->objects_quote.array, sizeof(f_fss_quotes_t), set_quote->objects_quote.size, length);
    if (F_status_is_error(status)) return status;

    set_quote->objects_quote.size = length;

    if (set_quote->objects_quote.used > set_quote->objects_quote.size) {
      set_quote->objects_quote.used = length;
    }

    status = f_memory_resize((void **) & set_quote->contents_quote.array, sizeof(f_fss_quotess_t), set_quote->contents_quote.size, length);
    if (F_status_is_error(status)) return status;

    set_quote->contents_quote.size = length;

    if (set_quote->contents_quote.used > set_quote->contents_quote.size) {
      set_quote->contents_quote.used = length;
    }

    return status;
  }
#endif // !defined(_di_f_fss_set_quote_decrease_by_) || !defined(_di_f_fss_set_quote_delete_) || !defined(_di_f_fss_set_quote_increase_) || !defined(_di_f_fss_set_quote_increase_by_) || !defined(_di_f_fss_set_quote_resize_)

#if !defined(_di_f_fss_set_quotes_adjust_) || !defined(_di_f_fss_set_quotes_decimate_by_) || !defined(_di_f_fss_set_quotes_destroy_)
  f_status_t private_f_fss_set_quotes_adjust(const f_array_length_t length, f_fss_set_quotes_t *set_quotes) {
    f_status_t status = F_none;

    if (length < set_quotes->size) {
      for (f_array_length_t i = set_quotes->size - length; i < set_quotes->size; ++i) {

        f_macro_fss_objects_t_destroy(status, set_quotes->array[i].objects);
        if (F_status_is_error(status)) return status;

        f_macro_fss_contents_t_destroy(status, set_quotes->array[i].contents);
        if (F_status_is_error(status)) return status;

        f_macro_fss_quotes_t_destroy(status, set_quotes->array[i].objects_quote);
        if (F_status_is_error(status)) return status;

        f_macro_fss_quotess_t_destroy(status, set_quotes->array[i].contents_quote);
        if (F_status_is_error(status)) return status;
      } // for
    }

    status = f_memory_adjust((void **) & set_quotes->array, sizeof(f_fss_set_quote_t), set_quotes->size, length);

    if (F_status_is_error_not(status)) {
      set_quotes->size = length;

      if (set_quotes->used > set_quotes->size) {
        set_quotes->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_set_quotes_adjust_) || !defined(_di_f_fss_set_quotes_decimate_by_) || !defined(_di_f_fss_set_quotes_destroy_)

#if !defined(_di_f_fss_set_quotes_decrease_by_) || !defined(_di_f_fss_set_quotes_delete_) || !defined(_di_f_fss_set_quotes_increase_) || !defined(_di_f_fss_set_quotes_increase_by_) || !defined(_di_f_fss_set_quotes_resize_)
  f_status_t private_f_fss_set_quotes_resize(const f_array_length_t length, f_fss_set_quotes_t *set_quotes) {
    f_status_t status = F_none;

    if (length < set_quotes->size) {
      for (f_array_length_t i = set_quotes->size - length; i < set_quotes->size; ++i) {

        f_macro_fss_objects_t_delete(status, set_quotes->array[i].objects);
        if (F_status_is_error(status)) return status;

        f_macro_fss_contents_t_delete(status, set_quotes->array[i].contents);
        if (F_status_is_error(status)) return status;

        f_macro_fss_quotes_t_delete(status, set_quotes->array[i].objects_quote);
        if (F_status_is_error(status)) return status;

        f_macro_fss_quotess_t_delete(status, set_quotes->array[i].contents_quote);
        if (F_status_is_error(status)) return status;
      } // for
    }

    status = f_memory_resize((void **) & set_quotes->array, sizeof(f_fss_set_quote_t), set_quotes->size, length);

    if (F_status_is_error_not(status)) {
      set_quotes->size = length;

      if (set_quotes->used > set_quotes->size) {
        set_quotes->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_set_quotes_decrease_by_) || !defined(_di_f_fss_set_quotes_delete_) || !defined(_di_f_fss_set_quotes_increase_) || !defined(_di_f_fss_set_quotes_increase_by_) || !defined(_di_f_fss_set_quotes_resize_)

#if !defined(_di_f_fss_sets_adjust_) || !defined(_di_f_fss_sets_decimate_by_) || !defined(_di_f_fss_sets_destroy_)
  f_status_t private_f_fss_sets_adjust(const f_array_length_t length, f_fss_sets_t *sets) {
    f_status_t status = F_none;

    if (length < sets->size) {
      for (f_array_length_t i = sets->size - length; i < sets->size; ++i) {

        f_macro_fss_objects_t_destroy(status, sets->array[i].objects);
        if (F_status_is_error(status)) return status;

        f_macro_fss_contents_t_destroy(status, sets->array[i].contents);
        if (F_status_is_error(status)) return status;
      } // for
    }

    f_memory_adjust((void **) & sets->array, sizeof(f_fss_set_t), sets->size, length);

    if (F_status_is_error_not(status)) {
      sets->size = length;

      if (sets->used > sets->size) {
        sets->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_sets_adjust_) || !defined(_di_f_fss_sets_decimate_by_) || !defined(_di_f_fss_sets_destroy_)

#if !defined(_di_f_fss_sets_decrease_by_) || !defined(_di_f_fss_sets_delete_) || !defined(_di_f_fss_sets_increase_) || !defined(_di_f_fss_sets_increase_by_) || !defined(_di_f_fss_sets_resize_)
  f_status_t private_f_fss_sets_resize(const f_array_length_t length, f_fss_sets_t *sets) {
    f_status_t status = F_none;

    if (length < sets->size) {
      for (f_array_length_t i = sets->size - length; i < sets->size; ++i) {

        f_macro_fss_objects_t_delete(status, sets->array[i].objects);
        if (F_status_is_error(status)) return status;

        f_macro_fss_contents_t_delete(status, sets->array[i].contents);
        if (F_status_is_error(status)) return status;
      } // for
    }

    status = f_memory_resize((void **) & sets->array, sizeof(f_fss_set_t), sets->size, length);

    if (F_status_is_error_not(status)) {
      sets->size = length;

      if (sets->used > sets->size) {
        sets->used = length;
      }
    }

    return status;
  }
#endif // !defined(_di_f_fss_sets_decrease_by_) || !defined(_di_f_fss_sets_delete_) || !defined(_di_f_fss_sets_increase_) || !defined(_di_f_fss_sets_increase_by_) || !defined(_di_f_fss_sets_resize_)

#ifdef __cplusplus
} // extern "C"
#endif
