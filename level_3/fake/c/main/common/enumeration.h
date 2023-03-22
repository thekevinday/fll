/**
 * FLL - Level 3
 *
 * Project: Featureless Make
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * Provides common enumeration functionality.
 *
 * This is auto-included and should not need to be explicitly included.
 */
#ifndef _fake_common_enumeration_h
#define _fake_common_enumeration_h

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The main program parameters.
 */
#ifndef _di_fake_parameter_e_
  enum {
    fake_parameter_help_e,
    fake_parameter_copyright_e,
    fake_parameter_light_e,
    fake_parameter_dark_e,
    fake_parameter_no_color_e,
    fake_parameter_verbosity_quiet_e,
    fake_parameter_verbosity_error_e,
    fake_parameter_verbosity_normal_e,
    fake_parameter_verbosity_verbose_e,
    fake_parameter_verbosity_debug_e,
    fake_parameter_version_e,
    fake_parameter_line_first_no_e,
    fake_parameter_line_last_no_e,

    fake_parameter_build_e,
    fake_parameter_data_e,
    fake_parameter_define_e,
    fake_parameter_documents_e,
    fake_parameter_fakefile_e,
    fake_parameter_licenses_e,
    fake_parameter_mode_e,
    fake_parameter_process_e,
    fake_parameter_settings_e,
    fake_parameter_sources_e,
    fake_parameter_work_e,

    fake_parameter_documents_disable_e,
    fake_parameter_documents_enable_e,
    fake_parameter_shared_disable_e,
    fake_parameter_shared_enable_e,
    fake_parameter_static_disable_e,
    fake_parameter_static_enable_e,

    fake_parameter_operation_build_e,
    fake_parameter_operation_clean_e,
    fake_parameter_operation_make_e,
    fake_parameter_operation_skeleton_e,
  }; // enum

  #define fake_console_parameter_t_initialize \
    { \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_help_s,          f_console_standard_long_help_s,          0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_copyright_s,     f_console_standard_long_copyright_s,     0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_light_s,         f_console_standard_long_light_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_dark_s,          f_console_standard_long_dark_s,          0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_no_color_s,      f_console_standard_long_no_color_s,      0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_quiet_s,         f_console_standard_long_quiet_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_error_s,         f_console_standard_long_error_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_normal_s,        f_console_standard_long_normal_s,        0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_verbose_s,       f_console_standard_long_verbose_s,       0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_debug_s,         f_console_standard_long_debug_s,         0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_version_s,       f_console_standard_long_version_s,       0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_line_first_no_s, f_console_standard_long_line_first_no_s, 0, f_console_flag_inverse_e), \
      macro_f_console_parameter_t_initialize_3(f_console_standard_short_line_last_no_s,  f_console_standard_long_line_last_no_s,  0, f_console_flag_inverse_e), \
      \
      macro_f_console_parameter_t_initialize_3(fake_short_build_s,     fake_long_build_s,     1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_data_s,      fake_long_data_s,      1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_define_s,    fake_long_define_s,    1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_documents_s, fake_long_documents_s, 1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_fakefile_s,  fake_long_fakefile_s,  1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_licenses_s,  fake_long_licenses_s,  1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_mode_s,      fake_long_mode_s,      1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_process_s,   fake_long_process_s,   1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_settings_s,  fake_long_settings_s,  1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_sources_s,   fake_long_sources_s,   1, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_3(fake_short_work_s,      fake_long_work_s,      1, f_console_flag_normal_e), \
      \
      macro_f_console_parameter_t_initialize_5(fake_long_documents_disabled_s, 0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_5(fake_long_documents_enabled_s,  0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_5(fake_long_shared_disabled_s,    0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_5(fake_long_shared_enabled_s,     0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_5(fake_long_static_disabled_s,    0, f_console_flag_normal_e), \
      macro_f_console_parameter_t_initialize_5(fake_long_static_enabled_s,     0, f_console_flag_normal_e), \
      \
      macro_f_console_parameter_t_initialize_6(fake_other_operation_build_s,    0, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize_6(fake_other_operation_clean_s,    0, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize_6(fake_other_operation_make_s,     0, f_console_flag_simple_e), \
      macro_f_console_parameter_t_initialize_6(fake_other_operation_skeleton_s, 0, f_console_flag_simple_e), \
    }

  #define fake_total_parameters_d 34
#endif // _di_fake_parameter_e_

/**
 * Flags passed to the main function or program.
 *
 * fake_main_flag_*_e:
 *   - none:               No flags set.
 *   - copyright:          Print copyright.
 *   - enable_documents:   Enable documents, as in --enable-doc (not specifying means --disable-doc).
 *   - enable_shared:      Enable shared, as in --enable-shared (not specifying means --disable-shared).
 *   - enable_static:      Enable static, as in --enable-static (not specifying means --disable-static).
 *   - header:             Enable printing of headers.
 *   - help:               Print help.
 *   - operation:          Designate that an operation is explicitly passed.
 *   - operation_build:    The build operation is designated.
 *   - operation_clean:    The clean operation is designated.
 *   - operation_make:     The make operation is designated (or enabled as default).
 *   - operation_skeleton: The skeleton operation is designated.
 *   - print_first:        When set, print new line to message output on program begin after loading settings.
 *   - print_last:         When set, print new line to message output on program end.
 *   - separate:           Enable printing of separators.
 *   - strip_invalid:      Using strip invalid character mode.
 *   - verify:             Using verify mode.
 *   - version:            Print version.
 */
#ifndef _di_fake_main_flag_e_
  enum {
    fake_main_flag_none_e               = 0x0,
    fake_main_flag_copyright_e          = 0x1,
    fake_main_flag_enable_documents_e   = 0x2,
    fake_main_flag_enable_shared_e      = 0x4,
    fake_main_flag_enable_static_e      = 0x8,
    fake_main_flag_header_e             = 0x10,
    fake_main_flag_help_e               = 0x20,
    fake_main_flag_operation_e          = 0x40,
    fake_main_flag_operation_build_e    = 0x80,
    fake_main_flag_operation_clean_e    = 0x100,
    fake_main_flag_operation_make_e     = 0x200,
    fake_main_flag_operation_skeleton_e = 0x400,
    fake_main_flag_print_first_e        = 0x800,
    fake_main_flag_print_last_e         = 0x1000,
    fake_main_flag_separate_e           = 0x2000,
    fake_main_flag_strip_invalid_e      = 0x4000,
    fake_main_flag_verify_e             = 0x8000,
    fake_main_flag_version_e            = 0x10000,
  }; // enum
#endif // _di_fake_main_flag_e_

/**
 * The program operation enumerations.
 *
 * fake_operation_*_e:
 *   - none:     No operation.
 *   - build:    The build operation.
 *   - clean:    The clean operation.
 *   - make:     The make operation.
 *   - skeleton: The skeleton operation.
 */
#ifndef _di_fake_operation_e_
  enum {
    fake_operation_none_e = 0,
    fake_operation_build_e,
    fake_operation_clean_e,
    fake_operation_make_e,
    fake_operation_skeleton_e,
  }; // enum
#endif // _di_fake_operation_e_

/**
 * Operation types enumerations.
 *
 * fake_make_operation_type_*_e:
 *   - none:      No operation type.
 *   - and:       The "and" operation.
 *   - break:     The "break" operation.
 *   - build:     The "build" operation.
 *   - clean:     The "clean" operation.
 *   - clone:     The "clone" operation.
 *   - compile:   The "compile" operation.
 *   - copy:      The "copy" operation.
 *   - define:    The "define" operation.
 *   - delete:    The "delete" operation.
 *   - deletes:   The "deletes" operation.
 *   - else:      The "else" operation.
 *   - exit:      The "exit" operation.
 *   - fail:      The "fail" operation.
 *   - group:     The "group" operation.
 *   - groups:    The "groups" operation.
 *   - if:        The "if" operation.
 *   - index:     The "index" operation.
 *   - link:      The "link" operation.
 *   - mode:      The "mode" operation.
 *   - modes:     The "modes" operation.
 *   - move:      The "move" operation.
 *   - operate:   The "operate" operation.
 *   - or:        The "or" operation.
 *   - owner:     The "owner" operation.
 *   - owners:    The "owners" operation.
 *   - parameter: The "parameter" operation.
 *   - pop:       The "pop" operation.
 *   - print:     The "print" operation.
 *   - run:       The "run" operation.
 *   - shell:     The "shell" operation.
 *   - skeleton:  The "skeleton" operation.
 *   - to:        The "to" operation.
 *   - top:       The "top" operation.
 *   - touch:     The "touch" operation.
 *   - write:     The "write" operation.
 */
#ifndef _di_fake_make_operation_type_e_
  enum {
    fake_make_operation_type_none_e = 0,
    fake_make_operation_type_and_e,
    fake_make_operation_type_break_e,
    fake_make_operation_type_build_e,
    fake_make_operation_type_clean_e,
    fake_make_operation_type_clone_e,
    fake_make_operation_type_compile_e,
    fake_make_operation_type_copy_e,
    fake_make_operation_type_define_e,
    fake_make_operation_type_delete_e,
    fake_make_operation_type_deletes_e,
    fake_make_operation_type_else_e,
    fake_make_operation_type_exit_e,
    fake_make_operation_type_fail_e,
    fake_make_operation_type_group_e,
    fake_make_operation_type_groups_e,
    fake_make_operation_type_if_e,
    fake_make_operation_type_index_e,
    fake_make_operation_type_link_e,
    fake_make_operation_type_mode_e,
    fake_make_operation_type_modes_e,
    fake_make_operation_type_move_e,
    fake_make_operation_type_operate_e,
    fake_make_operation_type_or_e,
    fake_make_operation_type_owner_e,
    fake_make_operation_type_owners_e,
    fake_make_operation_type_parameter_e,
    fake_make_operation_type_pop_e,
    fake_make_operation_type_print_e,
    fake_make_operation_type_run_e,
    fake_make_operation_type_shell_e,
    fake_make_operation_type_skeleton_e,
    fake_make_operation_type_to_e,
    fake_make_operation_type_top_e,
    fake_make_operation_type_touch_e,
    fake_make_operation_type_write_e,
  }; // enum
#endif // _di_fake_make_operation_type_e_

/**
 * Operation if-condition types enumerations.
 *
 * fake_make_operation_if_type_*_e:
 *   - none:             No condition.
 *   - else:             The else condition.
 *   - if:               The if condition.
 *   - if_define:        The if defined condition.
 *   - if_equal:         The if equal to condition.
 *   - if_equal_not:     The if not equal to condition.
 *   - if_exist:         The if exists condition.
 *   - if_failure:       The if is failure condition.
 *   - if_greater:       The if greater than condition.
 *   - if_greater_equal: The if greater than or equal to condition.
 *   - if_group:         The if group is condition.
 *   - if_is:            The if is condition.
 *   - if_less:          The if less than condition.
 *   - if_less_equal:    The if less than or equal to condition.
 *   - if_mode:          The if mode is condition.
 *   - if_not:           The if is not condition.
 *   - if_not_define:    The if not defined condition.
 *   - if_not_exist:     The if does not exist condition.
 *   - if_not_group:     The if is not group condition.
 *   - if_not_is:        The if is not condition.
 *   - if_not_mode:      The if is not mode condition.
 *   - if_not_owner:     The if is not owner condition.
 *   - if_not_parameter: The if is not parameter condition.
 *   - if_parameter:     The if is parameter condition.
 *   - if_owner:         The if is owner condition.
 *   - if_success:       The if is success condition.
 */
#ifndef _di_fake_make_operation_if_type_e_
  enum {
    fake_make_operation_if_type_none_e = 0,
    fake_make_operation_if_type_else_e,
    fake_make_operation_if_type_if_e,
    fake_make_operation_if_type_if_define_e,
    fake_make_operation_if_type_if_equal_e,
    fake_make_operation_if_type_if_equal_not_e,
    fake_make_operation_if_type_if_exist_e,
    fake_make_operation_if_type_if_failure_e,
    fake_make_operation_if_type_if_greater_e,
    fake_make_operation_if_type_if_greater_equal_e,
    fake_make_operation_if_type_if_group_e,
    fake_make_operation_if_type_if_is_e,
    fake_make_operation_if_type_if_less_e,
    fake_make_operation_if_type_if_less_equal_e,
    fake_make_operation_if_type_if_mode_e,
    fake_make_operation_if_type_if_not_e,
    fake_make_operation_if_type_if_not_define_e,
    fake_make_operation_if_type_if_not_exist_e,
    fake_make_operation_if_type_if_not_group_e,
    fake_make_operation_if_type_if_not_is_e,
    fake_make_operation_if_type_if_not_mode_e,
    fake_make_operation_if_type_if_not_owner_e,
    fake_make_operation_if_type_if_not_parameter_e,
    fake_make_operation_if_type_if_parameter_e,
    fake_make_operation_if_type_if_owner_e,
    fake_make_operation_if_type_if_success_e,
  }; // enum
#endif // _di_fake_make_operation_if_type_e_

/**
 * Operation failure types enumerations.
 *
 * fake_make_operation_fail_*_e:
 *   - none:   No failure type.
 *   - exit:   The "exit" operation.
 *   - ignore: The "ignore" operation.
 *   - warn:   The "warn" operation.
 */
#ifndef _di_fake_make_operation_fail_e_
  enum {
    fake_make_operation_fail_none_e = 0,
    fake_make_operation_fail_exit_e,
    fake_make_operation_fail_ignore_e,
    fake_make_operation_fail_warn_e,
  }; // enum
#endif // _di_fake_make_operation_fail_e_

/**
 * Designate the current process block state.
 *
 * fake_condition_result_*_e:
 *   - none:    No if-condition is set.
 *   - operate: The condition passed or perform condition, process the next operation or the condition.
 *   - skip:    The condition failed, skip the next operation.
 *   - done:    After the condition passed, the next operation was performed, all future operations within block are skipped.
 */
#ifndef _di_fake_state_process_block_e_
  enum {
    fake_state_process_block_none_e = 0,
    fake_state_process_block_operate_e,
    fake_state_process_block_skip_e,
    fake_state_process_block_done_e,
  }; // enum
#endif // _di_fake_state_process_block_e_

/**
 * Designate that the if state is true, false, or undefined (none).
 *
 * fake_condition_result_*_e:
 *   - none:  The result of the if-condition is not set.
 *   - false: The result of the if-condition is false.
 *   - true:  The result of the if-condition is true.
 *   - error: An error occurred, any if-condition is to be skipped, falling back to the else condition, if any.
 */
#ifndef _di_fake_condition_result_e_
  enum {
    fake_condition_result_none_e = 0,
    fake_condition_result_false_e,
    fake_condition_result_true_e,
    fake_condition_result_error_e,
  }; // enum
#endif // _di_fake_condition_result_e_

/**
 * Flags for fine-tuned print control.
 *
 * fake_print_flag_*_e:
 *   - none:      No flags set.
 *   - debug:     Stream is for debug printing.
 *   - error:     Stream is for error printing.
 *   - message:   Stream is for message printing.
 *   - warning:   Stream is for warning printing.
 *   - file_to:   Stream is a destination file.
 *   - file_from: Stream is a source file.
 */
#ifndef _di_fake_print_flag_e_
  enum {
    fake_print_flag_none_e      = 0x0,
    fake_print_flag_debug_e     = 0x1,
    fake_print_flag_error_e     = 0x2,
    fake_print_flag_message_e   = 0x4,
    fake_print_flag_warning_e   = 0x8,
    fake_print_flag_file_to_e   = 0x10,
    fake_print_flag_file_from_e = 0x20,
  }; // enum
#endif // _di_fake_print_flag_e_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _fake_common_enumeration_h
