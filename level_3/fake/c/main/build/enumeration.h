/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides build enumeration functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_build_enumeration_h
#define _fake_build_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The build language enumerations.
 *
 * fake_build_language_*_e:
 *   - bash: The GNU Bash language.
 *   - c:    The C language.
 *   - cpp:  The C++ language.
 *   - zsh:  The ZSH language (Similar to and somewhat compatible with GNU Bash).
 */
#ifndef _di_fake_build_language_e_
  enum {
    fake_build_language_none_e = 0,
    fake_build_language_bash_e,
    fake_build_language_c_e,
    fake_build_language_cpp_e,
    fake_build_language_zsh_e,
  }; // enum
#endif // _di_fake_build_language_e_

/**
 * Build settings flag enumeration.
 *
 * data_build_setting_flag_*:
 *   - none:            No flag set.
 *   - has_environment: Designate that the "environment" is specified in the "settings" Section of the Fakefile.
 */
#ifndef _di_fake_build_setting_flag_e_
  enum {
    data_build_setting_flag_none_e            = 0x0,
    data_build_setting_flag_has_environment_e = 0x1,
  }; // enum
#endif // _di_fake_build_setting_flag_e_

/**
 * The program version enumerations.
 *
 * fake_build_version_*_e:
 *   - none:  No version number.
 *   - major: The major version number.
 *   - minor: The minor version number.
 *   - micro: The micro version number (sometimes called the patch version number).
 *   - nano:  The nano version number.
 */
#ifndef _di_fake_build_version_e_
  enum {
    fake_build_version_none_e = 0,
    fake_build_version_major_e,
    fake_build_version_minor_e,
    fake_build_version_micro_e,
    fake_build_version_nano_e,
  }; // enum
#endif // _di_fake_build_version_e_

/**
 * Build Types.
 *
 * fake_build_type_*:
 *   - library: A library build type.
 *   - object:  An object build type.
 *   - program: A program build type.
 */
#ifndef _di_fake_build_type_e_
  enum {
    fake_build_type_library_e = 1,
    fake_build_type_object_e,
    fake_build_type_program_e,
  }; // enum
#endif // _di_fake_build_type_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_build_enumeration_h
