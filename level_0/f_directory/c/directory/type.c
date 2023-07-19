#include "../directory.h"
#include "private-type.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_directory_listing_delete_
  f_status_t f_directory_listing_delete(f_directory_listing_t * const listing) {
    #ifndef _di_level_0_parameter_checking_
      if (!listing) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_string_dynamics_resize(0, &listing->block);
    f_string_dynamics_resize(0, &listing->character);
    f_string_dynamics_resize(0, &listing->directory);
    f_string_dynamics_resize(0, &listing->regular);
    f_string_dynamics_resize(0, &listing->link);
    f_string_dynamics_resize(0, &listing->fifo);
    f_string_dynamics_resize(0, &listing->socket);
    f_string_dynamics_resize(0, &listing->unknown);

    return F_none;
  }
#endif // _di_f_directory_listing_delete_

#ifndef _di_f_directory_listing_destroy_
  f_status_t f_directory_listing_destroy(f_directory_listing_t * const listing) {
    #ifndef _di_level_0_parameter_checking_
      if (!listing) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_string_dynamics_adjust(0, &listing->block);
    f_string_dynamics_adjust(0, &listing->character);
    f_string_dynamics_adjust(0, &listing->directory);
    f_string_dynamics_adjust(0, &listing->regular);
    f_string_dynamics_adjust(0, &listing->link);
    f_string_dynamics_adjust(0, &listing->fifo);
    f_string_dynamics_adjust(0, &listing->socket);
    f_string_dynamics_adjust(0, &listing->unknown);

    return F_none;
  }
#endif // _di_f_directory_listing_destroy_

#ifndef _di_f_directory_recurse_do_delete_
  f_status_t f_directory_recurse_do_delete(f_directory_recurse_do_t * const recurse) {
    #ifndef _di_level_0_parameter_checking_
      if (!recurse) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_directory_listing_delete(&recurse->listing);

    f_string_dynamic_resize(0, &recurse->path);
    f_string_dynamic_resize(0, &recurse->path_cache);

    return F_none;
  }
#endif // _di_f_directory_recurse_do_delete_

#ifndef _di_f_directory_recurse_do_destroy_
  f_status_t f_directory_recurse_do_destroy(f_directory_recurse_do_t * const recurse) {
    #ifndef _di_level_0_parameter_checking_
      if (!recurse) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    f_directory_listing_destroy(&recurse->listing);

    f_string_dynamic_adjust(0, &recurse->path);
    f_string_dynamic_adjust(0, &recurse->path_cache);

    return F_none;
  }
#endif // _di_f_directory_recurse_do_destroy_

#ifndef _di_f_directory_statuss_adjust_
  f_status_t f_directory_statuss_adjust(const f_number_unsigned_t length, f_directory_statuss_t * const statuss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statuss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_directory_statuss_adjust(length, statuss);
  }
#endif // _di_f_directory_statuss_adjust_

#ifndef _di_f_directory_statuss_decimate_by_
  f_status_t f_directory_statuss_decimate_by(const f_number_unsigned_t amount, f_directory_statuss_t * const statuss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statuss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_directory_statuss_adjust((statuss->size - amount > 0) ? statuss->size - amount : 0, statuss);
  }
#endif // _di_f_directory_statuss_decimate_by_

#ifndef _di_f_directory_statuss_decrease_by_
  f_status_t f_directory_statuss_decrease_by(const f_number_unsigned_t amount, f_directory_statuss_t * const statuss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statuss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    if (!amount) return F_data_not;

    return private_f_directory_statuss_resize((statuss->size - amount > 0) ? statuss->size - amount : 0, statuss);
  }
#endif // _di_f_directory_statuss_decrease_by_

#ifndef _di_f_directory_statuss_increase_
  f_status_t f_directory_statuss_increase(const f_number_unsigned_t step, f_directory_statuss_t * const statuss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statuss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase(step, sizeof(f_directory_status_t), (void **) &statuss->array, &statuss->used, &statuss->size);
  }
#endif // _di_f_directory_statuss_increase_

#ifndef _di_f_directory_statuss_increase_by_
  f_status_t f_directory_statuss_increase_by(const f_number_unsigned_t amount, f_directory_statuss_t * const statuss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statuss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return f_memory_array_increase_by(amount, sizeof(f_directory_status_t), (void **) &statuss->array, &statuss->used, &statuss->size);
  }
#endif // _di_f_directory_statuss_increase_by_

#ifndef _di_f_directory_statuss_resize_
  f_status_t f_directory_statuss_resize(const f_number_unsigned_t length, f_directory_statuss_t * const statuss) {
    #ifndef _di_level_0_parameter_checking_
      if (!statuss) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    return private_f_directory_statuss_resize(length, statuss);
  }
#endif // _di_f_directory_statuss_resize_

#ifdef __cplusplus
} // extern "C"
#endif
