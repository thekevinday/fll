/**
 * FLL - Level 2
 *
 * Project: Colors
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * Provide standard color handling.
 */
#ifndef _FLL_colors_h
#define _FLL_colors_h

// libc includes
#include <stdarg.h>
#include <string.h>

// fll-0 includes
#include <level_0/colors.h>
#include <level_0/strings.h>
#include <level_0/types.h>

// fll-1 includes
#include <level_1/colors.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_fll_colors_load_context_
  /**
   * For any application that uses the standard color contexts, this function will load the appropriate colors to the structure.
   * This will handle the difference betweem xorg terminals and linux consoles.
   * If you wish to use non-standard colors either redefine this function or don't use it.
   */
  extern f_return_status fll_colors_load_context(fl_color_context *data, f_bool use_light_colors);
#endif // _di_fll_colors_load_context_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _FLL_colors_h
