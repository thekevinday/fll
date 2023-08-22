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
      f_status_t status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &listing->block.array, &listing->block.used, &listing->block.size, &f_string_dynamics_delete_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &listing->character.array, &listing->character.used, &listing->character.size, &f_string_dynamics_delete_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &listing->directory.array, &listing->directory.used, &listing->directory.size, &f_string_dynamics_delete_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &listing->regular.array, &listing->regular.used, &listing->regular.size, &f_string_dynamics_delete_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &listing->link.array, &listing->link.used, &listing->link.size, &f_string_dynamics_delete_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &listing->fifo.array, &listing->fifo.used, &listing->fifo.size, &f_string_dynamics_delete_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &listing->socket.array, &listing->socket.used, &listing->socket.size, &f_string_dynamics_delete_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &listing->unknown.array, &listing->unknown.used, &listing->unknown.size, &f_string_dynamics_delete_callback);
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
      f_status_t status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &listing->block.array, &listing->block.used, &listing->block.size, &f_string_dynamics_destroy_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &listing->character.array, &listing->character.used, &listing->character.size, &f_string_dynamics_destroy_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &listing->directory.array, &listing->directory.used, &listing->directory.size, &f_string_dynamics_destroy_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &listing->regular.array, &listing->regular.used, &listing->regular.size, &f_string_dynamics_destroy_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &listing->link.array, &listing->link.used, &listing->link.size, &f_string_dynamics_destroy_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &listing->fifo.array, &listing->fifo.used, &listing->fifo.size, &f_string_dynamics_destroy_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &listing->socket.array, &listing->socket.used, &listing->socket.size, &f_string_dynamics_destroy_callback);
      if (F_status_is_error(status)) return status;

      status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &listing->unknown.array, &listing->unknown.used, &listing->unknown.size, &f_string_dynamics_destroy_callback);
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

        status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].block.array, &array[i].block.used, &array[i].block.size, &f_string_dynamics_delete_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].character.array, &array[i].character.used, &array[i].character.size, &f_string_dynamics_delete_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].directory.array, &array[i].directory.used, &array[i].directory.size, &f_string_dynamics_delete_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].regular.array, &array[i].regular.used, &array[i].regular.size, &f_string_dynamics_delete_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].link.array, &array[i].link.used, &array[i].link.size, &f_string_dynamics_delete_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].fifo.array, &array[i].fifo.used, &array[i].fifo.size, &f_string_dynamics_delete_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].socket.array, &array[i].socket.used, &array[i].socket.size, &f_string_dynamics_delete_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].unknown.array, &array[i].unknown.used, &array[i].unknown.size, &f_string_dynamics_delete_callback);
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

        status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].block.array, &array[i].block.used, &array[i].block.size, &f_string_dynamics_destroy_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].character.array, &array[i].character.used, &array[i].character.size, &f_string_dynamics_destroy_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].directory.array, &array[i].directory.used, &array[i].directory.size, &f_string_dynamics_destroy_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].regular.array, &array[i].regular.used, &array[i].regular.size, &f_string_dynamics_destroy_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].link.array, &array[i].link.used, &array[i].link.size, &f_string_dynamics_destroy_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].fifo.array, &array[i].fifo.used, &array[i].fifo.size, &f_string_dynamics_destroy_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].socket.array, &array[i].socket.used, &array[i].socket.size, &f_string_dynamics_destroy_callback);
        if (F_status_is_error(status)) return status;

        status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].unknown.array, &array[i].unknown.used, &array[i].unknown.size, &f_string_dynamics_destroy_callback);
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

          status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].block.array, &array[i].array[j].block.used, &array[i].array[j].block.size, &f_string_dynamics_delete_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].character.array, &array[i].array[j].character.used, &array[i].array[j].character.size, &f_string_dynamics_delete_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].directory.array, &array[i].array[j].directory.used, &array[i].array[j].directory.size, &f_string_dynamics_delete_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].regular.array, &array[i].array[j].regular.used, &array[i].array[j].regular.size, &f_string_dynamics_delete_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].link.array, &array[i].array[j].link.used, &array[i].array[j].link.size, &f_string_dynamics_delete_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].fifo.array, &array[i].array[j].fifo.used, &array[i].array[j].fifo.size, &f_string_dynamics_delete_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].socket.array, &array[i].array[j].socket.used, &array[i].array[j].socket.size, &f_string_dynamics_delete_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_resize(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].unknown.array, &array[i].array[j].unknown.used, &array[i].array[j].unknown.size, &f_string_dynamics_delete_callback);
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

          status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].block.array, &array[i].array[j].block.used, &array[i].array[j].block.size, &f_string_dynamics_destroy_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].character.array, &array[i].array[j].character.used, &array[i].array[j].character.size, &f_string_dynamics_destroy_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].directory.array, &array[i].array[j].directory.used, &array[i].array[j].directory.size, &f_string_dynamics_destroy_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].regular.array, &array[i].array[j].regular.used, &array[i].array[j].regular.size, &f_string_dynamics_destroy_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].link.array, &array[i].array[j].link.used, &array[i].array[j].link.size, &f_string_dynamics_destroy_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].fifo.array, &array[i].array[j].fifo.used, &array[i].array[j].fifo.size, &f_string_dynamics_destroy_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].socket.array, &array[i].array[j].socket.used, &array[i].array[j].socket.size, &f_string_dynamics_destroy_callback);
          if (F_status_is_error(status)) return status;

          status = f_memory_arrays_adjust(0, sizeof(f_string_dynamic_t), (void **) &array[i].array[j].unknown.array, &array[i].array[j].unknown.used, &array[i].array[j].unknown.size, &f_string_dynamics_destroy_callback);
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
