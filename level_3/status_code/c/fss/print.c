#include "status_code.h"
#include "../main/status_code.h"
#include "print.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_status_code_fss_print_help_detail_
  void status_code_fss_print_help_detail(void * const setting, const fl_print_t print) {

    fl_print_format("  The FLL programs use a %[16-bit unsigned integer%] to represent the return status of programs and functions.%r%r", print.to, print.set->notable, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Programs may print a generic error with one of these codes.%r", print.to, f_string_eol_s);
    fl_print_format("  This is a tool for converting to or converting from these codes.%r%r", print.to, f_string_eol_s, f_string_eol_s);

    fl_print_format("  The %[16-bit unsigned integer%] also has the first two high-order bits used to represent flags.%r", print.to, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  These flags are the %[error%] bit and the %[warning%] bit.%r", print.to, print.set->notable, print.set->notable, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  When neither of these flags are set, then the status is considered %[fine%].%r%r", print.to, print.set->notable, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  This operates identical to the %[status_codes%] program except that this program handles additional codes regarding FSS.%r", print.to, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  These special codes numericaly appear after the %[F_status_code_last%] code.%r", print.to, print.set->notable, print.set->notable, f_string_eol_s);
    fl_print_format("  These codes stop at the %[F_fss_status_code_last%] code.%r%r", print.to, print.set->notable, print.set->notable, f_string_eol_s, f_string_eol_s);

    fl_print_format("  Each code will be printed on its own line.%r", print.to, f_string_eol_s);
    fl_print_format("  Errors regarding each code may be printed on its own line.%r", print.to, f_string_eol_s);
  }
#endif // _di_status_code_fss_print_help_detail_

#ifdef __cplusplus
} // extern "C"
#endif
