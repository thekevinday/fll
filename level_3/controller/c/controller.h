/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.5
 * Licenses: lgplv2.1
 *
 * This is the Controller program.
 *
 * This program utilizes the Featureless Linux Library.
 * This program provides system service management, much like sysvcontroller and controllerng.
 * This program can be controlled from user-space via the "control" program.
 */
#ifndef _controller_h

// libc includes

// fll-0 includes
#include <level_0/type.h>
#include <level_0/status.h>
#include <level_0/memory.h>
#include <level_0/string.h>
#include <level_0/utf.h>
#include <level_0/console.h>
#include <level_0/directory.h>
#include <level_0/file.h>
#include <level_0/fss.h>
#include <level_0/pipe.h>
#include <level_0/print.h>

// fll-1 includes
#include <level_1/color.h>
#include <level_1/console.h>
#include <level_1/fss.h>
#include <level_1/string.h>

// fll-2 includes
#include <level_2/error.h>
#include <level_2/fss.h>
#include <level_2/fss_basic_list.h>
#include <level_2/fss_extended.h>
#include <level_2/fss_extended_list.h>
#include <level_2/program.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_version_
  #define controller_major_version "0"
  #define controller_minor_version "5"
  #define controller_micro_version "2"
  #define controller_version controller_major_version "." controller_minor_version "." controller_micro_version
#endif // _di_controller_version_

#ifndef _di_controller_name_
  #define controller_name "controller"
  #define controller_name_long "Controller Program"
#endif // _di_controller_name_

#ifndef _di_controller_defines_
  #define controller_string_create      "create"
  #define controller_string_command     "command"
  #define controller_string_define      "define"
  #define controller_string_environment "environment"
  #define controller_string_group       "group"
  #define controller_string_name        "name"
  #define controller_string_pid         "pid"
  #define controller_string_restart     "restart"
  #define controller_string_reload      "reload"
  #define controller_string_script      "script"
  #define controller_string_service     "service"
  #define controller_string_settings    "settings"
  #define controller_string_start       "start"
  #define controller_string_stop        "stop"
  #define controller_string_use         "use"
  #define controller_string_user        "user"

  #define controller_string_create_length      6
  #define controller_string_command_length     7
  #define controller_string_define_length      6
  #define controller_string_environment_length 11
  #define controller_string_group_length       5
  #define controller_string_name_length        4
  #define controller_string_pid_length         3
  #define controller_string_restart_length     7
  #define controller_string_reload_length      6
  #define controller_string_script_length      6
  #define controller_string_service_length     7
  #define controller_string_settings_length    8
  #define controller_string_start_length       5
  #define controller_string_stop_length        4
  #define controller_string_use_length         3
  #define controller_string_user_length        4

  enum {
    controller_parameter_help,
    controller_parameter_light,
    controller_parameter_dark,
    controller_parameter_no_color,
    controller_parameter_verbosity_quiet,
    controller_parameter_verbosity_normal,
    controller_parameter_verbosity_verbose,
    controller_parameter_verbosity_debug,
    controller_parameter_version,
  };

  #define controller_console_parameter_t_initialize \
    { \
      f_console_parameter_t_initialize(f_console_standard_short_help, f_console_standard_long_help, 0, 0, f_console_type_normal), \
      f_console_parameter_t_initialize(f_console_standard_short_light, f_console_standard_long_light, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_dark, f_console_standard_long_dark, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_no_color, f_console_standard_long_no_color, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_quiet, f_console_standard_long_quiet, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_normal, f_console_standard_long_normal, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_verbose, f_console_standard_long_verbose, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_debug, f_console_standard_long_debug, 0, 0, f_console_type_inverse), \
      f_console_parameter_t_initialize(f_console_standard_short_version, f_console_standard_long_version, 0, 0, f_console_type_inverse), \
    }

  #define controller_total_parameters 9
#endif // _di_controller_defines_

#ifndef _di_controller_data_t_
  typedef struct {
    f_console_parameter_t parameters[controller_total_parameters];

    f_string_lengths_t remaining;
    bool process_pipe;

    f_file_t output;
    fll_error_print_t error;
    fll_error_print_t warning;

    f_color_context_t context;
  } controller_data_t;

  #define controller_data_initialize \
    { \
      controller_console_parameter_t_initialize, \
      f_string_lengths_t_initialize, \
      F_false, \
      f_macro_file_t_initialize(f_type_output, f_type_descriptor_output, f_file_flag_write_only), \
      fll_error_print_t_initialize, \
      fll_macro_error_print_t_initialize_warning(), \
      f_color_context_t_initialize, \
    }
#endif // _di_controller_data_t_

#ifndef _di_controller_rule_action_t_
  enum {
    controller_rule_action_type_extended = 1,
    controller_rule_action_type_extended_list,
  };

  enum {
    controller_rule_action_intent_create = 1,
    controller_rule_action_intent_group,
    controller_rule_action_intent_restart,
    controller_rule_action_intent_reload,
    controller_rule_action_intent_start,
    controller_rule_action_intent_stop,
    controller_rule_action_intent_use,
    controller_rule_action_intent_user,
  };

  typedef struct {
    f_string_length_t line;
    f_string_dynamics_t parameters;
  } controller_rule_action_t;

  #define controller_rule_action_t_initialize \
    { \
      0, \
      f_string_dynamics_t_initialize, \
    }

  #define f_macro_controller_rule_action_t_delete_simple(action) \
    f_macro_string_dynamics_t_delete_simple(action.parameters)
#endif // _di_controller_rule_action_t_

#ifndef _di_controller_rule_actions_t_
  typedef struct {
    uint8_t type;
    uint8_t intent;

    controller_rule_action_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_rule_actions_t;

  #define controller_rule_actions_t_initialize \
    { \
      0, \
      0, \
      0, \
      0, \
      0, \
    }

  #define f_macro_controller_rule_actions_t_delete_simple(actions) \
    actions.used = actions.size; \
    while (actions.used > 0) { \
      actions.used--; \
      f_macro_controller_rule_item_t_delete_simple(actions.array[actions.used]); \
      if (!actions.used) { \
        if (f_memory_delete((void **) & actions.array, sizeof(controller_rule_action_t), actions.size)) { \
          actions.size = 0; \
        } \
      } \
    }
#endif // _di_controller_rule_actions_t_

#ifndef _di_controller_rule_item_t_
  enum {
    controller_rule_item_type_command = 1,
    controller_rule_item_type_script,
    controller_rule_item_type_service,
    controller_rule_item_type_settings,
  };

  typedef struct {
    uint8_t type;
    f_string_length_t line;

    controller_rule_actions_t create;
    controller_rule_actions_t group;
    controller_rule_actions_t restart;
    controller_rule_actions_t reload;
    controller_rule_actions_t start;
    controller_rule_actions_t stop;
    controller_rule_actions_t use;
    controller_rule_actions_t user;
  } controller_rule_item_t;

  #define controller_rule_item_t_initialize \
    { \
      0, \
      0, \
      controller_rule_actions_t_initialize, \
      controller_rule_actions_t_initialize, \
      controller_rule_actions_t_initialize, \
      controller_rule_actions_t_initialize, \
      controller_rule_actions_t_initialize, \
      controller_rule_actions_t_initialize, \
      controller_rule_actions_t_initialize, \
      controller_rule_actions_t_initialize, \
    }

  #define f_macro_controller_rule_item_t_delete_simple(item) \
    f_macro_controller_rule_actions_t_delete_simple(item.create) \
    f_macro_controller_rule_actions_t_delete_simple(item.group) \
    f_macro_controller_rule_actions_t_delete_simple(item.restart) \
    f_macro_controller_rule_actions_t_delete_simple(item.reload) \
    f_macro_controller_rule_actions_t_delete_simple(item.start) \
    f_macro_controller_rule_actions_t_delete_simple(item.stop) \
    f_macro_controller_rule_actions_t_delete_simple(item.use) \
    f_macro_controller_rule_actions_t_delete_simple(item.user)
#endif // _di_controller_rule_item_t_

#ifndef _di_controller_rule_items_t_
  typedef struct {
    controller_rule_item_t *array;

    f_array_length_t size;
    f_array_length_t used;
  } controller_rule_items_t;

  #define controller_rule_items_initialize \
    { \
      0, \
      0, \
      0, \
    }

  #define f_macro_controller_rule_items_t_delete_simple(items) \
    items.used = items.size; \
    while (items.used > 0) { \
      items.used--; \
      f_macro_controller_rule_item_t_delete_simple(items.array[items.used]); \
      if (!items.used) { \
        if (f_memory_delete((void **) & items.array, sizeof(controller_rule_item_t), items.size)) { \
          items.size = 0; \
        } \
      } \
    }
#endif // _di_controller_rule_items_t_

#ifndef _di_controller_rule_setting_t_
  typedef struct {
    f_string_dynamic_t name;
    f_string_dynamic_t pid;

    f_string_dynamics_t defines; // @todo this probably should a list of name and value pairs.
    f_string_dynamics_t environment;
  } controller_rule_setting_t;

  #define controller_rule_setting_t_initialize \
    { \
      f_string_dynamic_t_initialize, \
      f_string_dynamic_t_initialize, \
      f_string_dynamics_t_initialize, \
      f_string_dynamics_t_initialize, \
    }

  #define f_macro_controller_rule_setting_t_delete_simple(setting) \
    f_string_dynamic_t_delete_simple(setting.name) \
    f_string_dynamic_t_delete_simple(setting.pid) \
    f_string_dynamics_t_delete_simple(setting.defines) \
    f_string_dynamics_t_delete_simple(setting.environments)
#endif // _di_controller_rule_setting_t_

/**
 * Print help.
 *
 * @param output
 *   The file to print to.
 * @param context
 *   The color context settings.
 *
 * @return
 *   F_none on success.
 */
#ifndef _di_controller_print_help_
  extern f_return_status controller_print_help(const f_file_t output, const f_color_context_t context);
#endif // _di_controller_print_help_

/**
 * Execute main program.
 *
 * Be sure to call controller_delete_data() after executing this.
 *
 * @param arguments
 *   The parameters passed to the process.
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see controller_delete_data()
 */
#ifndef _di_controller_main_
  extern f_return_status controller_main(const f_console_arguments_t arguments, controller_data_t *data);
#endif // _di_controller_main_

/**
 * Deallocate data.
 *
 * Be sure to call this after executing controller_main().
 *
 * @param data
 *   The program data.
 *
 * @return
 *   F_none on success.
 *
 *   Status codes (with error bit) are returned on any problem.
 *
 * @see controller_main()
 */
#ifndef _di_controller_delete_data_
  extern f_return_status controller_delete_data(controller_data_t *data);
#endif // _di_controller_delete_data_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_h
