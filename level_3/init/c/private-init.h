/**
 * Private include file for init.c.
 */

#ifndef _PRIVATE_init_h
#define _PRIVATE_init_h

#ifdef __cplusplus
extern "C" {
#endif

// define a custom stack size for each handler.
// consider mmap():
// - http://www.evanjones.ca/software/threading.html
// - http://stackoverflow.com/questions/1083172/how-to-mmap-the-stack-for-the-clone-system-call-on-linux
// - f_void_p stack = mmap(0,initial_stacksize,PROT_WRITE|PROT_READ,MAP_PRIVATE|MAP_GROWSDOWN|MAP_ANONYMOUS,-1,0);
// - http://lwn.net/Articles/294001/
// - http://tiku.io/questions/659065/how-to-mmap-the-stack-for-the-clone-system-call-on-linux
#define init_stack_size_small_services      6144
#define init_stack_size_small_control_file  4096
#define init_stack_size_large_services      12288
#define init_stack_size_large_control_file  8192

#define init_stack_protections  PROT_WRITE | PROT_READ
#define init_stack_flags        MAP_PRIVATE | MAP_GROWSDOWN | MAP_ANONYMOUS

#define init_clone_flags  CLONE_FILES | CLONE_FS | CLONE_IO | CLONE_VM | CLONE_SIGHAND | CLONE_THREAD

#define init_panic_signal_sleep_seconds 9

#ifndef _di_init_rule_
  // rule [directory] [filename (no-extension)] [require] [last] [asynchronous] = execute a rule located in [directory][filename].rule.
  typedef struct {
    f_string_dynamic name;
    f_string_dynamic directory;
    f_string_dynamic file;
    f_bool require;
    f_bool asynchronous;
  } init_rule;

  #define init_rule_initialize \
    { \
      f_string_dynamic_initialize,
      f_string_dynamic_initialize,
      f_string_dynamic_initialize,
      f_bool_initialize,
      f_bool_initialize,
    }

  #define delete_init_rule(status, rule) \
    f_macro_string_dynamic_delete(status, rule.name); \
    if (status == f_none) { \
      f_macro_string_dynamic_delete(status, rule.directory); \
    } \
    if (status == f_none) { \
      f_macro_string_dynamic_delete(status, rule.file); \
    } \
    if (status == f_none) { \
      rule.require = 0; \
      rule.asynchronous = 0; \
    }

  #define destroy_init_rule(status, rule) \
    f_macro_string_dynamic_destroy(status, rule.name); \
    if (status == f_none) { \
      f_macro_string_dynamic_destroy(status, rule.directory); \
    } \
    if (status == f_none) { \
      f_macro_string_dynamic_destroy(status, rule.file); \
    } \
    if (status == f_none) { \
      rule.require = 0; \
      rule.asynchronous = 0; \
    }
#endif // _di_init_data_

// an array of dynamic strings
#ifndef _di_init_rules_
  typedef struct {
    init_rule *array;       // the array of init_rule
    f_string_length  size;  // total amount of allocated space
    f_string_length  used;  // total number of allocated spaces used
  } init_rules;

  #define init_rules_initialize { 0, 0, 0 }

  #define f_init_rules_delete(status, rules) \
    status = f_none; \
    while (rules.size > 0) { \
      --rules.size; \
      delete_init_rule(status, rules.array[rules.size]); \
      if (status != f_none) break; \
    } \
    if (status == f_none) status = f_memory_delete((f_void_p *) & rules.array, sizeof(init_rule), rules.size); \
    if (status == f_none) rules.used = 0;

  #define f_init_rules_destroy(status, rules) \
    status = f_none; \
    while (rules.size > 0) { \
      --rules.size; \
      destroy_init_rule(status, rules.array[rules.size]); \
      if (status != f_none) break; \
    } \
    if (status == f_none) status = f_memory_destroy((f_void_p *) & rules.array, sizeof(init_rule), rules.size); \
    if (status == f_none) rules.used = 0;

  #define f_init_rules_resize(status, rules, new_length) \
    status = f_none; \
    if (new_length < rules.size) { \
      f_string_length i = rules.size - new_length; \
      for (; i < rules.size; ++i) { \
        delete_init_rule(status, rules.array[i]); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_memory_resize((f_void_p *) & rules.array, sizeof(init_rule), rules.size, new_length); \
    if (status == f_none) { \
      if (new_length > rules.size) { \
        f_string_length i = rules.size; \
        for (; i < new_length; ++i) { \
          memset(&rules.array[i], 0, sizeof(f_string)); \
        } \
      } \
      rules.size = new_length; \
      if (rules.used > rules.size) rules.used = new_length; \
    }

  #define f_init_rules_adjust(status, rules, new_length) \
    status = f_none; \
    if (new_length < rules.size) { \
      f_string_length i = rules.size - new_length; \
      for (; i < rules.size; ++i) { \
        destroy_init_rule(status, rules.array[i]); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_memory_adjust((f_void_p *) & rules.array, sizeof(init_rule), rules.size, new_length); \
    if (status == f_none) { \
      if (new_length > rules.size) { \
        f_string_length i = rules.size; \
        for (; i < new_length; ++i) { \
          memset(&rules.array[i], 0, sizeof(init_rule)); \
        } \
      } \
      rules.size = new_length; \
      if (rules.used > rules.size) rules.used = new_length; \
    }
#endif // _di_init_rules_

#ifndef _di_init_category_
  // category [name] = execute rules in the specified list called [name].
  typedef struct {
    f_string_dynamic name;
    init_rule last;
  } init_category;

  #define init_rule_initialize \
    { \
      f_string_dynamic_initialize,
      init_rule_initialize,
    }

  #define delete_init_category(status, category) \
    f_macro_string_dynamic_delete(status, category.name); \
    if (status == f_none) { \
      delete_init_rule(status, category.last); \
    }

  #define destroy_init_category(status, category) \
    f_macro_string_dynamic_destroy(status, category.name); \
    if (status == f_none) { \
      destroy_init_rule(status, category.last); \
    }
#endif // _di_init_category_

// an array of dynamic strings
#ifndef _di_init_categorys_
  typedef struct {
    init_category *array;  // the array of init_category

    f_string_length size;  // total amount of allocated space
    f_string_length used;  // total number of allocated spaces used
  } init_categorys;

  #define init_categorys_initialize { 0, 0, 0 }

  #define f_init_categorys_delete(status, categorys) \
    status = f_none; \
    while (categorys.size > 0) { \
      --categorys.size; \
      delete_init_category(status, categorys.array[categorys.size]); \
      if (status != f_none) break; \
    } \
    if (status == f_none) status = f_memory_delete((f_void_p *) & categorys.array, sizeof(init_category), categorys.size); \
    if (status == f_none) categorys.used = 0;

  #define f_init_categorys_destroy(status, categorys) \
    status = f_none; \
    while (categorys.size > 0) { \
      --categorys.size; \
      destroy_init_category(status, categorys.array[categorys.size]); \
      if (status != f_none) break; \
    } \
    if (status == f_none) status = f_memory_destroy((f_void_p *) & categorys.array, sizeof(init_category), categorys.size); \
    if (status == f_none) categorys.used = 0;

  #define f_init_categorys_resize(status, categorys, new_length) \
    status = f_none; \
    if (new_length < categorys.size) { \
      f_string_length i = categorys.size - new_length; \
      for (; i < categorys.size; ++i) { \
        delete_init_category(status, categorys.array[i]); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_memory_resize((f_void_p *) & categorys.array, sizeof(init_category), categorys.size, new_length); \
    if (status == f_none) { \
      if (new_length > categorys.size) { \
        f_string_length i = categorys.size; \
        for (; i < new_length; ++i) { \
          memset(&categorys.array[i], 0, sizeof(f_string)); \
        } \
      } \
      categorys.size = new_length; \
      if (categorys.used > categorys.size) categorys.used = new_length; \
    }

  #define f_init_categorys_adjust(status, categorys, new_length) \
    status = f_none; \
    if (new_length < categorys.size) { \
      f_string_length i = categorys.size - new_length; \
      for (; i < categorys.size; ++i) { \
        destroy_init_category(status, categorys.array[i]); \
        if (status != f_none) break; \
      } \
    } \
    if (status == f_none) status = f_memory_adjust((f_void_p *) & categorys.array, sizeof(init_category), categorys.size, new_length); \
    if (status == f_none) { \
      if (new_length > categorys.size) { \
        f_string_length i = categorys.size; \
        for (; i < new_length; ++i) { \
          memset(&categorys.array[i], 0, sizeof(init_category)); \
        } \
      } \
      categorys.size = new_length; \
      if (categorys.used > categorys.size) categorys.used = new_length; \
    }
#endif // _di_init_categorys_

#ifndef _di_init_data_
  typedef struct {
    f_string socket_file;
    f_u_int  socket_port;
    f_u_int  socket_id_target;
    f_u_int  socket_id_client;

    f_u_short timeout_start;
    f_u_short timeout_stop;
    f_u_short timeout_kill;

    init_rules     main_rules;
    init_categorys main_categorys;
    init_rule      main_failsafe;
  } init_data;

  #define init_data_initialize \
    { \
      f_string_initialize, \
      0, \
      0, \
      0, \
      2, \
      2, \
      1, \
      init_rules_initialize, \
      init_categorys_initialize, \
      init_rule_initialize, \
    }
#endif // _di_init_data_

typedef struct {
  f_void_p services;
  f_void_p reporting;
  f_void_p time;
  f_void_p control_file;
  f_void_p control_port;
  f_void_p login_file;
  f_void_p login_port;

  init_argument argument;
  init_data data;
} init_stack_memory;

#define init_stack_memory_initialize \
  { \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    0, \
    init_argument_initialize, \
    init_data_initialize, \
  }

// custom settings to prepare the init process.
// this is not self-contained and depends on user space applications to exist.
#define init_program_umount  "umount"
#define init_program_mount   "mount"
#define init_program_mkdir   "mkdir"
#define init_program_chmod   "chmod"
#define init_program_chgrp   "chgrp"
#define init_program_mknod   "mknod"
#define init_program_ln      "ln"

#define init_path_device_console  init_paths_devices "console"
#define init_path_device_zero     init_paths_devices "zero"
#define init_path_device_null     init_paths_devices "null"
#define init_path_device_random   init_paths_devices "random"
#define init_path_device_urandom  init_paths_devices "urandom"

#define init_path_processes_cmdline  init_paths_processes "cmdline"
#define init_path_processes_mounts   init_paths_processes "mounts"

#ifndef _di_init_rule_buffer_
  f_return_status init_rule_buffer(const f_string filename, f_string_dynamic *buffer, f_fss_objects *objects, f_fss_contents *contents) f_gcc_attribute_visibility_internal;
#endif // _di_init_rule_buffer_

#ifndef _di_init_handler_child_services_
  // start, stop, and handle signals to services.
  f_return_status init_handler_child_services(f_void_p argument) f_gcc_attribute_visibility_internal;
#endif // _di_init_handler_child_services_

#ifndef _di_init_handler_child_control_file_
  // listens on a socket file and accepts control commands.
  f_return_status init_handler_child_control_file(f_void_p argument) f_gcc_attribute_visibility_internal;
#endif // _di_init_handler_child_socket_file_

#ifndef _di_init_initialize_stack_memory_
  f_return_status init_initialize_stack_memory(init_stack_memory *stack_memory) f_gcc_attribute_visibility_internal;
#endif // _di_init_initialize_stack_memory_

#ifndef _di_init_delete_stack_memory_
  f_return_status init_delete_stack_memory(init_stack_memory *stack_memory) f_gcc_attribute_visibility_internal;
#endif // _di_init_delete_stack_memory_

#ifndef _di_init_prepare_system_
  f_return_status init_prepare_system() f_gcc_attribute_visibility_internal;
#endif // _di_init_prepare_system_

#ifndef _di_init_prepare_init_
  f_return_status init_prepare_init() f_gcc_attribute_visibility_internal;
#endif // _di_init_prepare_init_

#ifndef _di_init_process_main_rule_
  f_return_status init_process_main_rule(const init_argument argument, f_string_dynamic *buffer, init_data *data) f_gcc_attribute_visibility_internal;
#endif // _di_init_process_main_rule_

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _PRIVATE_init_h
