/* FLL - Level 0
 * Project:       Paths
 * Version:       svn
 * Licenses:      lgplv2.1
 * Programmers:   Kevin Day
 * Documentation:
 *
 * Provide locations to all fll-specific paths
 * It is planned to have this file auto-generated from a single /etc/fll file such that one file can be used for all supported languages.
 *
 * FIXME: this is very outdated due to numerous structural changes while I was developing turtle kevux
 */
#ifndef _F_fll_paths_h
#define _F_fll_paths_h

#include <level_0/filesystem_paths.h>

#ifdef __cplusplus
extern "C"{
#endif

// TODO: don't forget to completely restructure the paths layout before 0.1.0 is released
#ifndef _di_fll_paths_
  #define f_path_fll_base       f_path_system_settings "/fll" // directory
  #define f_path_fll_settings   "settings"  // directory
  #define f_path_fll_packages   "packages"  // directory
  #define f_path_fll_patches    "patches"   // directory
  #define f_path_fll_archive    "archive"   // directory
  #define f_path_fll_groups     "groups"    // directory
  #define f_path_fll_licenses   "licenses"  // directory
  #define f_path_fll_global     "global"    // file
  #define f_path_fll_paths      "paths"     // file
  #define f_path_fll_listing    "listing"   // file
  #define f_path_fll_headers    "headers"   // file
  #define f_path_fll_libraries  "libraries" // file
  #define f_path_fll_programs   "programs"  // file
  #define f_path_fll_scripts    "scripts"   // file
  #define f_path_fll_fakefile   "fakefile"  // file
#endif // _di_fll_paths_

#ifndef _di_fll_file_endings_
  #define f_fll_file_ending_package ".pkg"
  #define f_fll_file_ending_patch   ".patch"
#endif // _di_fll_file_endings_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _F_fll_paths_h
