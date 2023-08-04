#include "../control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_print_warning_packet_header_duplicate_object_
  f_status_t control_print_warning_packet_header_duplicate_object(fl_print_t * const print, const f_string_static_t response_header) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe received response header '%]", print->to, print->set->warning, print->prefix, print->set->warning);
    fl_print_format("%[%Q%]", print->to, print->set->notable, response_header, print->set->notable);
    fl_print_format("%[' is repeated.%]%r", print->to, print->set->warning, print->set->warning, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_warning_packet_header_duplicate_object_

#ifndef _di_control_print_warning_packet_process_string_to_failed_
  f_status_t control_print_warning_packet_process_string_to_failed(fl_print_t * const print, const f_status_t status_of, const f_status_t status_error) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QFailed while calling f_status_string_to() for status%] ", print->to, print->set->warning, print->set->warning, print->set->warning);
    fl_print_format("%[%ui%]", print->to, print->set->notable, status_of, print->set->notable);
    fl_print_format("%[, failing with status code%] ", print->to, print->set->warning, status_error, print->set->warning);
    fl_print_format("%[%ui%]", print->to, print->set->notable, status_error, print->set->notable);
    fl_print_format("%[.%]%r", print->to, print->set->warning, print->set->warning, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_warning_packet_process_string_to_failed_

#ifndef _di_control_print_warning_packet_response_busy_
  f_status_t control_print_warning_packet_response_busy(fl_print_t * const print, const control_payload_header_t header, const f_string_static_t string_status) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_verbose_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("%[%QThe action '%]", print->to, print->set->warning, print->prefix, print->set->warning);
    fl_print_format("%[%q%]", print->to, print->set->notable, control_action_type_name(header.action), print->set->notable);
    fl_print_format("%[' could not be performed because the service is busy.%]%r", print->to, print->set->warning, print->set->warning, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_warning_packet_response_busy_

#ifdef __cplusplus
} // extern "C"
#endif
