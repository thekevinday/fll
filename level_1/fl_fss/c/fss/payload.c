#include "payload.h"
#include "../private-fss.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fl_fss_payload_header_write_
  void fl_fss_payload_header_write(const f_abstruse_maps_t headers, const f_abstruse_maps_t * const signatures, f_string_dynamic_t * const destination, f_state_t * const state) {
    #ifndef _di_level_1_parameter_checking_
      if (!state) return;

      if (!destination) {
        state->status = F_status_set_error(F_parameter);

        return;
      }
    #endif // _di_level_1_parameter_checking_

    if (state->code & f_fss_payload_write_comment_header_e) {
      // @todo flag for writing "# fss-000c"
    }

    if (state->code & f_fss_payload_write_header_object_e) {
      // @todo flag for writing "header:"
    }

/*
    if (state->code & f_fss_payload_write_header_content_e) {
      for (f_number_unsigned_t i = 0; i < headers.used ; ++i) {

        switch () {
          f_abstruse_none_e:
          f_abstruse_void_e:
          f_abstruse_voids_e:
          f_abstruse_strings_e:
            break;

          f_abstruse_signed_e:
          f_abstruse_unsigned_e:
            // @todo
            break;

          f_abstruse_int8s_e:
          f_abstruse_int16s_e:
          f_abstruse_int32s_e:
          f_abstruse_int64s_e:
          f_abstruse_signeds_e:
            // @todo
            break;

          f_abstruse_uint8s_e:
          f_abstruse_uint16s_e:
          f_abstruse_uint32s_e:
          f_abstruse_uint64s_e:
          f_abstruse_unsigneds_e:
            // @todo
            break;

          f_abstruse_string_e:
          f_abstruse_strings_e:
            // @todo
            break;

          f_abstruse_dynamic_e:
          f_abstruse_dynamics_e:
            // @todo
            break;

          f_abstruse_map_e:
          f_abstruse_maps_e:
            // @todo
            break;

          f_abstruse_map_multi_e:
          f_abstruse_map_multis_e:
            // @todo
            break;

          f_abstruse_quantity_e:
          f_abstruse_quantitys_e:
            // @todo
            break;

          f_abstruse_range_e:
          f_abstruse_ranges_e:
            // @todo
            break;

          f_abstruse_triple_e:
          f_abstruse_triples_e:
            // @todo
            break;
        }
      } // for
    }

    if (state->code & f_fss_payload_write_signature_object_e) {
      // @todo flag for writing "signature:"
    }

    if ((state->code & f_fss_payload_write_signature_content_e) && !signatures) {
      for (f_number_unsigned_t i = 0; i < signatures->used ; ++i) {

        switch () {
          f_abstruse_none_e:
          f_abstruse_void_e:
          f_abstruse_voids_e:
          f_abstruse_strings_e:
            break;

          f_abstruse_signed_e:
          f_abstruse_unsigned_e:
            // @todo
            break;

          f_abstruse_int8s_e:
          f_abstruse_int16s_e:
          f_abstruse_int32s_e:
          f_abstruse_int64s_e:
          f_abstruse_signeds_e:
            // @todo
            break;

          f_abstruse_uint8s_e:
          f_abstruse_uint16s_e:
          f_abstruse_uint32s_e:
          f_abstruse_uint64s_e:
          f_abstruse_unsigneds_e:
            // @todo
            break;

          f_abstruse_string_e:
          f_abstruse_strings_e:
            // @todo
            break;

          f_abstruse_dynamic_e:
          f_abstruse_dynamics_e:
            // @todo
            break;

          f_abstruse_map_e:
          f_abstruse_maps_e:
            // @todo
            break;

          f_abstruse_map_multi_e:
          f_abstruse_map_multis_e:
            // @todo
            break;

          f_abstruse_quantity_e:
          f_abstruse_quantitys_e:
            // @todo
            break;

          f_abstruse_range_e:
          f_abstruse_ranges_e:
            // @todo
            break;

          f_abstruse_triple_e:
          f_abstruse_triples_e:
            // @todo
            break;
        }
      } // for
    }
*/
    if (state->code & f_fss_payload_write_payload_object_e) {
      // @todo flag for writing "payload:"
    }

    state->status = F_okay;
  }
#endif // _di_fl_fss_payload_header_write_

#ifdef __cplusplus
} // extern "C"
#endif
