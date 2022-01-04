#include "../controller.h"
#include "../private-common.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_thread_delete_simple_
  void controller_thread_delete_simple(controller_thread_t * const thread) {

    controller_lock_delete_simple(&thread->lock);
    controller_processs_resize(0, &thread->processs);
    controller_cache_delete_simple(&thread->cache);
  }
#endif // _di_controller_thread_delete_simple_

#ifdef __cplusplus
} // extern "C"
#endif
