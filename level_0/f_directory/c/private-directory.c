#include <level_0/directory.h>
#include "private-directory.h"

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(_di_f_directory_remove_)
  int private_f_directory_remove_recursively(const char *path, const struct stat *file_stat, int type, struct FTW *entity) {
    if (entity->level == 0) return 0;
    return remove(path);
  }
#endif // !defined(_di_f_directory_remove_)

#ifdef __cplusplus
} // extern "C"
#endif
