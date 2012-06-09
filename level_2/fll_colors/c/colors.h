/* FLL - Level 2
 * Project:       Colors
 * Version:       0.3.x
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provide standard color handling
 */
#ifndef _FLL_colors_h
#define _FLL_colors_h

// libc includes
#include <stdarg.h>
#include <string.h>

// fll-0 includes
#include <level_0/types.h>
#include <level_0/strings.h>
#include <level_0/colors.h>

// fll-1 includes
#include <level_1/colors.h>

#ifdef __cplusplus
extern "C"{
#endif

#ifndef _di_fll_color_context_
  typedef struct {
    f_colors         color_list;
    f_colors_format  color_format;
    f_dynamic_string reset;
    f_dynamic_string warning;
    f_dynamic_string error;
    f_dynamic_string title;
    f_dynamic_string notable;
    f_dynamic_string important;
    f_dynamic_string standout;
    f_dynamic_string normal;
    f_dynamic_string normal_reset;
  } fll_color_context;

  #define fll_color_context_initialize { f_colors_initialize_linux, f_colors_format_initialize_linux, f_dynamic_string_initialize, f_dynamic_string_initialize, f_dynamic_string_initialize, f_dynamic_string_initialize, f_dynamic_string_initialize, f_dynamic_string_initialize, f_dynamic_string_initialize, f_dynamic_string_initialize, f_dynamic_string_initialize }

  #define fll_new_color_context(status, color_context) \
    f_resize_dynamic_string(status, color_context.reset, f_color_max_size + 1); \
    if (f_error_is_not_error(status)) f_resize_dynamic_string(status, color_context.warning,      f_color_max_size + 1); \
    if (f_error_is_not_error(status)) f_resize_dynamic_string(status, color_context.error,        f_color_max_size + 1); \
    if (f_error_is_not_error(status)) f_resize_dynamic_string(status, color_context.title,        f_color_max_size + 1); \
    if (f_error_is_not_error(status)) f_resize_dynamic_string(status, color_context.notable,      f_color_max_size + 1); \
    if (f_error_is_not_error(status)) f_resize_dynamic_string(status, color_context.important,    f_color_max_size + 1); \
    if (f_error_is_not_error(status)) f_resize_dynamic_string(status, color_context.standout,     f_color_max_size + 1); \
    if (f_error_is_not_error(status)) f_resize_dynamic_string(status, color_context.normal,       f_color_max_size + 1); \
    if (f_error_is_not_error(status)) f_resize_dynamic_string(status, color_context.normal_reset, f_color_max_size + 1);

  #define fll_delete_color_context(status, color_context) \
    f_delete_dynamic_string(status, color_context.reset); \
    if (f_error_is_not_error(status)) f_delete_dynamic_string(status, color_context.warning); \
    if (f_error_is_not_error(status)) f_delete_dynamic_string(status, color_context.error); \
    if (f_error_is_not_error(status)) f_delete_dynamic_string(status, color_context.title); \
    if (f_error_is_not_error(status)) f_delete_dynamic_string(status, color_context.notable); \
    if (f_error_is_not_error(status)) f_delete_dynamic_string(status, color_context.important); \
    if (f_error_is_not_error(status)) f_delete_dynamic_string(status, color_context.standout); \
    if (f_error_is_not_error(status)) f_delete_dynamic_string(status, color_context.normal); \
    if (f_error_is_not_error(status)) f_delete_dynamic_string(status, color_context.normal_reset);

  #define fll_destroy_color_context(status, color_context, size) \
    f_destroy_dynamic_string(status, color_context.reset); \
    if (f_error_is_not_error(status)) f_destroy_dynamic_string(status, color_context.warning, size); \
    if (f_error_is_not_error(status)) f_destroy_dynamic_string(status, color_context.error, size); \
    if (f_error_is_not_error(status)) f_destroy_dynamic_string(status, color_context.title, size); \
    if (f_error_is_not_error(status)) f_destroy_dynamic_string(status, color_context.notable, size); \
    if (f_error_is_not_error(status)) f_destroy_dynamic_string(status, color_context.important, size); \
    if (f_error_is_not_error(status)) f_destroy_dynamic_string(status, color_context.standout, size); \
    if (f_error_is_not_error(status)) f_destroy_dynamic_string(status, color_context.normal); \
    if (f_error_is_not_error(status)) f_destroy_dynamic_string(status, color_context.normal_reset);
#endif // _di_fll_color_context_

#ifndef _di_fll_colors_load_context_
  // For any application that uses the standard color contexts, this function will load the appropriate colors to the structure
  // This will handle the difference betweem xorg terminals and linux consoles
  // If you wish to use non-standard colors either redefine this function or don't use it
  extern f_return_status fll_colors_load_context(fll_color_context *data, f_bool use_light_colors);
#endif // _di_fll_colors_load_context_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_colors_h
