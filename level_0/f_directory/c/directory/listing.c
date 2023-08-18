#include "../directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_f_directory_listing_delete_
  f_status_t f_directory_listing_delete(f_directory_listing_t * const listing) {
    #ifndef _di_level_0_parameter_checking_
      if (!listing) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = f_string_dynamics_resize(0, &listing->block);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_resize(0, &listing->character);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_resize(0, &listing->directory);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_resize(0, &listing->regular);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_resize(0, &listing->link);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_resize(0, &listing->fifo);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_resize(0, &listing->socket);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_resize(0, &listing->unknown);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_f_directory_listing_delete_

#ifndef _di_f_directory_listing_destroy_
  f_status_t f_directory_listing_destroy(f_directory_listing_t * const listing) {
    #ifndef _di_level_0_parameter_checking_
      if (!listing) return F_status_set_error(F_parameter);
    #endif // _di_level_0_parameter_checking_

    {
      f_status_t status = f_string_dynamics_adjust(0, &listing->block);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_adjust(0, &listing->character);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_adjust(0, &listing->directory);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_adjust(0, &listing->regular);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_adjust(0, &listing->link);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_adjust(0, &listing->fifo);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_adjust(0, &listing->socket);
      if (F_status_is_error(status)) return status;

      status = f_string_dynamics_adjust(0, &listing->unknown);
      if (F_status_is_error(status)) return status;
    }

    return F_okay;
  }
#endif // _di_f_directory_listing_destroy_

#ifndef _di_f_directory_listings_delete_callback_
  f_status_t f_directory_listings_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_directory_listing_t * const array = (f_directory_listing_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_string_dynamics_resize(0, &array[i].block);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_resize(0, &array[i].character);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_resize(0, &array[i].directory);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_resize(0, &array[i].regular);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_resize(0, &array[i].link);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_resize(0, &array[i].fifo);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_resize(0, &array[i].socket);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_resize(0, &array[i].unknown);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_directory_listings_delete_callback_

#ifndef _di_f_directory_listings_destroy_callback_
  f_status_t f_directory_listings_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_directory_listing_t * const array = (f_directory_listing_t *) void_array;
      f_status_t status = F_okay;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        status = f_string_dynamics_adjust(0, &array[i].block);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_adjust(0, &array[i].character);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_adjust(0, &array[i].directory);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_adjust(0, &array[i].regular);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_adjust(0, &array[i].link);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_adjust(0, &array[i].fifo);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_adjust(0, &array[i].socket);
        if (F_status_is_error(status)) return status;

        status = f_string_dynamics_adjust(0, &array[i].unknown);
        if (F_status_is_error(status)) return status;
      } // for
    }

    return F_okay;
  }
#endif // _di_f_directory_listings_destroy_callback_

#ifndef _di_f_directory_listingss_delete_callback_
  f_status_t f_directory_listingss_delete_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_directory_listings_t * const array = (f_directory_listings_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_string_dynamics_resize(0, &array[i].array[j].block);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_resize(0, &array[i].array[j].character);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_resize(0, &array[i].array[j].directory);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_resize(0, &array[i].array[j].regular);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_resize(0, &array[i].array[j].link);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_resize(0, &array[i].array[j].fifo);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_resize(0, &array[i].array[j].socket);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_resize(0, &array[i].array[j].unknown);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_resize(0, sizeof(f_directory_listing_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_directory_listingss_delete_callback_

#ifndef _di_f_directory_listingss_destroy_callback_
  f_status_t f_directory_listingss_destroy_callback(const f_number_unsigned_t start, const f_number_unsigned_t stop, void * const void_array) {

    {
      f_directory_listings_t * const array = (f_directory_listings_t *) void_array;
      f_status_t status = F_okay;
      f_number_unsigned_t j = 0;

      for (f_number_unsigned_t i = start; i < stop; ++i) {

        for (j = 0; j < array[i].size; ++j) {

          status = f_string_dynamics_adjust(0, &array[i].array[j].block);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_adjust(0, &array[i].array[j].character);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_adjust(0, &array[i].array[j].directory);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_adjust(0, &array[i].array[j].regular);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_adjust(0, &array[i].array[j].link);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_adjust(0, &array[i].array[j].fifo);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_adjust(0, &array[i].array[j].socket);
          if (F_status_is_error(status)) return status;

          status = f_string_dynamics_adjust(0, &array[i].array[j].unknown);
          if (F_status_is_error(status)) return status;
        } // for

        if (array[i].size) {
          status = f_memory_array_adjust(0, sizeof(f_directory_listing_t), (void **) &array[i].array, &array[i].used, &array[i].size);
          if (F_status_is_error(status)) return status;
        }
      } // for
    }

    return F_okay;
  }
#endif // _di_f_directory_listingss_destroy_callback_

#ifdef __cplusplus
} // extern "C"
#endif
