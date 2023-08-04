#include "../control.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_control_print_debug_packet_header_object_and_content_
  f_status_t control_print_debug_packet_header_object_and_content(fl_print_t * const print, const f_string_static_t object, const f_string_static_t content, const f_string_range_t content_range) {

    if (!print) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    f_file_stream_lock(print->to);

    fl_print_format("Packet header Object '%[%Q%]", print->to, print->set->notable, object, print->set->notable);
    fl_print_format("' has value '%[%/Q%]'.%r", print->to, print->set->notable, content, content_range, print->set->notable, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_debug_packet_header_object_and_content_

#ifndef _di_control_print_debug_packet_message_
  f_status_t control_print_debug_packet_message(fl_print_t * const print, const f_string_t message, const f_string_static_t *buffer, const f_string_range_t *range) {

    if (!print || !print->custom) return F_status_set_error(F_output_not);
    if (print->verbosity < f_console_verbosity_debug_e) return F_output_not;

    control_main_t * const main = (control_main_t *) print->custom;

    f_file_stream_lock(print->to);

    fl_print_format("%s", print->to, message);

    if (buffer) {
      if (range) {
        fl_print_format("'%[%/Q%]'", print->to, print->set->notable, *buffer, *range, print->set->notable);
      }
      else {
        fl_print_format("'%[%/Q%]'", print->to, print->set->notable, *buffer, print->set->notable);
      }
    }

    if (main->setting.state.status) {
      fl_print_format(", with status code %[%ui%]'", print->to, print->set->notable, main->setting.state.status, print->set->notable);
    }

    fl_print_format(".%r", print->to, f_string_eol_s);

    f_file_stream_unlock(print->to);

    return F_none;
  }
#endif // _di_control_print_debug_packet_message_

#ifdef __cplusplus
} // extern "C"
#endif
