#include "fake.h"

/**
 * Standard entry point for fake program.
 *
 * @param argc
 *   The number of arguments.
 * @param argv
 *   The array of arguments.
 *
 * @return
 *   0 on success.
 *   1 on error.
 *
 * @see exit()
 */
int main(const int argc, const f_string_t *argv, const f_string_t *envp) {

  const f_console_arguments_t arguments = { argc, argv, envp };
  fake_main_t data = fake_main_t_initialize;

  fll_program_standard_setup(&data.signal);

  f_file_umask_get(&data.umask);

  const f_status_t status = fake_main(&data, &arguments);

  fll_program_standard_setdown(&data.signal);

  if (status == F_child) {
    exit(data.child);
  }

  if (F_status_is_error(status)) return 1;

  return 0;
}
