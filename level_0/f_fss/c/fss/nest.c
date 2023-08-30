#include "../fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_fss_nest_delete_
  f_status_t f_fss_nest_delete(f_fss_nest_t * const nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = 0; i < nest->size; ++i) {

        for (j = 0; j < nest->depth[i].size; ++j) {

          if (nest->depth[i].array[j].content.size && nest->depth[i].array[j].content.array) {
            status = f_memory_array_resize(0, sizeof(f_string_range_t), (void **) &nest->depth[i].array[j].content.array, &nest->depth[i].array[j].content.used, &nest->depth[i].array[j].content.size);
            if (F_status_is_error(status)) return status;
          }
        } // for

        if (nest->depth[i].size && nest->depth[i].array) {
          status = f_memory_array_resize(0, sizeof(f_fss_item_t), (void **) &nest->depth[i].array, &nest->depth[i].used, &nest->depth[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    if (nest->size && nest->depth) {
      return f_memory_array_resize(0, sizeof(f_fss_items_t), (void **) &nest->depth, &nest->used, &nest->size);
    }

    return F_okay;
  }
#endif // _di_f_fss_nest_delete_

#ifndef _di_f_fss_nest_destroy_
  f_status_t f_fss_nest_destroy(f_fss_nest_t * const nest) {
    #ifndef _di_level_0_parameter_checking_
      if (!nest) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = 0; i < nest->size; ++i) {

        for (j = 0; j < nest->depth[i].size; ++j) {

          if (nest->depth[i].array[j].content.size && nest->depth[i].array[j].content.array) {
            status = f_memory_array_adjust(0, sizeof(f_string_range_t), (void **) &nest->depth[i].array[j].content.array, &nest->depth[i].array[j].content.used, &nest->depth[i].array[j].content.size);
            if (F_status_is_error(status)) return status;
          }
        } // for

        if (nest->depth[i].size && nest->depth[i].array) {
          status = f_memory_array_adjust(0, sizeof(f_fss_item_t), (void **) &nest->depth[i].array, &nest->depth[i].used, &nest->depth[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    if (nest->size && nest->depth) {
      return f_memory_array_adjust(0, sizeof(f_fss_items_t), (void **) &nest->depth, &nest->used, &nest->size);
    }

    return F_okay;
  }
#endif // _di_f_fss_nest_destroy_

#ifndef _di_f_fss_nests_delete_callback_
  f_status_t f_fss_nests_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_nest_t * const array = (f_fss_nest_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;
      f_number_unsigned_t k = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          for (k = 0; k < array[i].depth[j].size; ++k) {

            if (array[i].depth[j].array[k].content.size && array[i].depth[j].array[k].content.array) {
              status = f_memory_array_resize(0, sizeof(f_string_range_t), (void **) &array[i].depth[j].array[k].content.array, &array[i].depth[j].array[k].content.used, &array[i].depth[j].array[k].content.size);
              if (F_status_is_error(status)) return status;
            }
          } // for

          if (array[i].depth[j].size && array[i].depth[j].array) {
            status = f_memory_array_resize(0, sizeof(f_fss_item_t), (void **) &array[i].depth[j].array, &array[i].depth[j].used, &array[i].depth[j].size);
            if (F_status_is_error(status)) return status;
          }
        } // for

        if (array[i].size && array[i].depth) {
          status = f_memory_array_resize(0, sizeof(f_fss_items_t), (void **) &array[i].depth, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_nests_delete_callback_

#ifndef _di_f_fss_nests_destroy_callback_
  f_status_t f_fss_nests_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_nest_t * const array = (f_fss_nest_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;
      f_number_unsigned_t k = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          for (k = 0; k < array[i].depth[j].size; ++k) {

            if (array[i].depth[j].array[k].content.size && array[i].depth[j].array[k].content.array) {
              status = f_memory_array_adjust(0, sizeof(f_string_range_t), (void **) &array[i].depth[j].array[k].content.array, &array[i].depth[j].array[k].content.used, &array[i].depth[j].array[k].content.size);
              if (F_status_is_error(status)) return status;
            }
          } // for

          if (array[i].depth[j].size && array[i].depth[j].array) {
            status = f_memory_array_adjust(0, sizeof(f_fss_item_t), (void **) &array[i].depth[j].array, &array[i].depth[j].used, &array[i].depth[j].size);
            if (F_status_is_error(status)) return status;
          }
        } // for

        if (array[i].size && array[i].depth) {
          status = f_memory_array_adjust(0, sizeof(f_fss_items_t), (void **) &array[i].depth, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_nests_destroy_callback_

#ifndef _di_f_fss_nestss_delete_callback_
  f_status_t f_fss_nestss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_nests_t * const array = (f_fss_nests_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;
      f_number_unsigned_t k = 0;
      f_number_unsigned_t l = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          for (k = 0; k < array[i].array[j].size; ++k) {

            for (l = 0; l < array[i].array[j].depth[k].size; ++l) {

              if (array[i].array[j].depth[k].array[l].content.size && array[i].array[j].depth[k].array[l].content.array) {
                status = f_memory_array_resize(0, sizeof(f_string_range_t), (void **) &array[i].array[j].depth[k].array[l].content.array, &array[i].array[j].depth[k].array[l].content.used, &array[i].array[j].depth[k].array[l].content.size);
                if (F_status_is_error(status)) return status;
              }
            } // for

            if (array[i].array[j].depth[k].size && array[i].array[j].depth[k].array) {
              status = f_memory_array_resize(0, sizeof(f_fss_item_t), (void **) &array[i].array[j].depth[k].array, &array[i].array[j].depth[k].used, &array[i].array[j].depth[k].size);
              if (F_status_is_error(status)) return status;
            }
          } // for

          if (array[i].array[j].size && array[i].array[j].depth) {
            status = f_memory_array_resize(0, sizeof(f_fss_items_t), (void **) &array[i].array[j].depth, &array[i].array[j].used, &array[i].array[j].size);
            if (F_status_is_error(status)) return status;
          }
        } // for

        if (array[i].size && array[i].array) {
          status = f_memory_array_resize(0, sizeof(f_fss_nest_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_nestss_delete_callback_

#ifndef _di_f_fss_nestss_destroy_callback_
  f_status_t f_fss_nestss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_fss_nests_t * const array = (f_fss_nests_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;
      f_number_unsigned_t k = 0;
      f_number_unsigned_t l = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          for (k = 0; k < array[i].array[j].size; ++k) {

            for (l = 0; l < array[i].array[j].depth[k].size; ++l) {

              if (array[i].array[j].depth[k].array[l].content.size && array[i].array[j].depth[k].array[l].content.array) {
                status = f_memory_array_adjust(0, sizeof(f_string_range_t), (void **) &array[i].array[j].depth[k].array[l].content.array, &array[i].array[j].depth[k].array[l].content.used, &array[i].array[j].depth[k].array[l].content.size);
                if (F_status_is_error(status)) return status;
              }
            } // for

            if (array[i].array[j].depth[k].size && array[i].array[j].depth[k].array) {
              status = f_memory_array_adjust(0, sizeof(f_fss_item_t), (void **) &array[i].array[j].depth[k].array, &array[i].array[j].depth[k].used, &array[i].array[j].depth[k].size);
              if (F_status_is_error(status)) return status;
            }
          } // for

          if (array[i].array[j].size && array[i].array[j].depth) {
            status = f_memory_array_adjust(0, sizeof(f_fss_items_t), (void **) &array[i].array[j].depth, &array[i].array[j].used, &array[i].array[j].size);
            if (F_status_is_error(status)) return status;
          }
        } // for

        if (array[i].size && array[i].array) {
          status = f_memory_array_adjust(0, sizeof(f_fss_nest_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_fss_nestss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
