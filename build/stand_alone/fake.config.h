// A config.h file for defining all code being disabled for compiling the stand alone Featureless Make.
// To assist in building this file use (may need to omit --defined-only): "nm --defined-only -f p programs/shared/fake | grep -oP '^(f|fl|fll)_[^\s]+'".
// To get the list of all possible functions, use something like: "grep -horP '\b_di_f_\w*\b' level_0/f_color/".
//
// Example: echo > /tmp/all.txt
//          for i in f_type f_status f_memory f_type_array f_string f_utf f_color f_console f_conversion f_file f_pipe f_print f_signal ; do grep -horP '\b_di_f_\w*\b' level_0/$i/c >> /tmp/all.txt ; grep -horP '\b_di_macro_\w*\b' level_0/$i/c >> /tmp/all.txt ; done
//          sort /tmp/all.txt | uniq | sed -e 's|^_|#define &|g' > /tmp/sorted.txt

// @todo Re-create this.
