// A config.h file for defining all code being disabled for compiling the stand alone Featureless Make.
// To assist in building this file use (may need to omit --defined-only): "nm --defined-only -f p programs/shared/fake | grep -oP '^(f|fl|fll)_[^\s]+'".
// To get the list of all possible functions, use something like: "grep -horP '\b_di_f_\w*\b' level_0/f_color/".
//
// Note that some special defines may need to be manually added, such as:
//   #define _di_private_inline_f_print_to_error_
//   #define _di_private_inline_private_f_print_to_error_
//
// Example:
//   echo > /tmp/all.txt
//   for i in f_type f_status f_memory f_type_array f_string f_utf f_account f_capability f_color f_compare f_console f_control_group f_conversion f_directory f_environment f_execute f_file f_fss f_iki f_limit f_network f_parse f_path f_pipe f_print f_rip f_signal f_socket f_thread f_time ; do grep -horP '\b_di_f_\w*\b' level_0/$i/c >> /tmp/all.txt ; grep -horP '\b_di_macro_\w*\b' level_0/$i/c >> /tmp/all.txt ; done
//   for i in fl_control_group fl_conversion fl_directory fl_environment fl_execute fl_fss fl_iki fl_path fl_print ; do grep -horP '\b_di_fl_\w*\b' level_1/$i/c >> /tmp/all.txt ; grep -horP '\b_di_macro_\w*\b' level_1/$i/c >> /tmp/all.txt ; done
//   for i in fll_error fll_execute fll_file fll_fss fll_print fll_program ; do grep -horP '\b_di_fll_\w*\b' level_2/$i/c >> /tmp/all.txt ; grep -horP '\b_di_macro_\w*\b' level_2/$i/c >> /tmp/all.txt ; done
//   sort /tmp/all.txt | uniq | sed -e 's|^_|#define &|g' > /tmp/sorted.txt
//   echo "#define _di_private_inline_f_print_to_error_" >> /tmp/sorted.txt
//   echo "#define _di_private_inline_private_f_print_to_error_" >> /tmp/sorted.txt
