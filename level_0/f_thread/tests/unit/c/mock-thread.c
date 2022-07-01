#include "mock-thread.h"

#ifdef __cplusplus
extern "C" {
#endif

int __wrap_pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void)) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_destroy(pthread_attr_t *attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_getaffinity_np(const pthread_attr_t *attr, size_t cpusetsize, cpu_set_t *cpuset) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_getguardsize(const pthread_attr_t * restrict attr, size_t * restrict guardsize) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_getinheritsched(const pthread_attr_t * restrict attr, int * restrict inheritsched) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_getschedparam(const pthread_attr_t * restrict attr, struct sched_param * restrict param) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_getschedpolicy(const pthread_attr_t * restrict attr, int * restrict policy) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_getscope(const pthread_attr_t *attr, int *contentionscope) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_getstack(const pthread_attr_t *attr, void **stackaddr, size_t *stacksize) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_getstacksize(const pthread_attr_t *attr, size_t *stacksize) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_init(pthread_attr_t *attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_setaffinity_np(pthread_t id, size_t cpusetsize, const cpu_set_t *cpuset) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_setguardsize(pthread_attr_t *attr, size_t guardsize) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_setinheritsched(pthread_attr_t *attr, int inheritsched) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_setschedparam(pthread_attr_t * restrict attr, const struct sched_param * restrict param) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_setscope(pthread_attr_t *attr, int contentionscope) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_setstack(pthread_attr_t *attr, void *stackaddr, size_t stacksize) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_barrier_destroy(pthread_barrier_t *barrier) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, unsigned count) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_barrier_wait(pthread_barrier_t *barrier) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_barrierattr_destroy(pthread_barrierattr_t *attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_barrierattr_init(pthread_barrierattr_t *attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_barrierattr_getpshared(const pthread_barrierattr_t *attr, int *pshared) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_barrierattr_setpshared(pthread_barrierattr_t *attr, int pshared) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_cancel(pthread_t pthread) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_cond_broadcast(pthread_cond_t *__cond) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}
int __wrap_pthread_cond_destroy(pthread_cond_t *__mutex) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}
int __wrap_pthread_cond_init(pthread_cond_t *__cond, const pthread_condattr_t *__attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_cond_signal(pthread_cond_t *__cond) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_cond_timedwait(pthread_cond_t *__cond, pthread_mutex_t *__mutex, const struct timespec *__abstime) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_cond_wait(pthread_cond_t *__cond, pthread_mutex_t *__mutex) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_condattr_destroy(pthread_condattr_t *__attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_condattr_getclock(const pthread_condattr_t * restrict attr, clockid_t * restrict clock_id) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_condattr_getpshared(const pthread_condattr_t *attr, int *pshared) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_condattr_init(pthread_condattr_t *__attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_condattr_setclock(pthread_condattr_t *attr, clockid_t clock_id) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_condattr_setpshared(pthread_condattr_t *attr, int pshared) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_create(pthread_t *pthread, const pthread_attr_t  *attr, void *(*routine)(void *), void *arg) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_detach(pthread_t pthread) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_equal(pthread_t __t1, pthread_t __t2) {

  return mock_type(int);
}

void __wrap_pthread_exit(void *value) {

  if (value) {
    int *v = (int *) value;

    *v = mock_type(int);
  }
}

int __wrap_pthread_getattr_default_np(pthread_attr_t *attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_getconcurrency(void) {

  return mock_type(int);
}

int __wrap_pthread_getcpuclockid(pthread_t thread, clockid_t *clock_id) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_getschedparam(pthread_t pthread, int *policy, struct sched_param *param) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

void *__wrap_pthread_getspecific(pthread_key_t key) {

  return mock_type(void *);
}

int __wrap_pthread_join(pthread_t pthread, void **value_ptr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_key_create(pthread_key_t *key, void (*destructor)(void *)) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_key_delete(pthread_key_t key) {

  return mock_type(int);
}

int __wrap_pthread_kill(pthread_t thread, int sig) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

pthread_t __wrap_pthread_self(void) {

  return mock_type(int);
}

int __wrap_pthread_setattr_default_np(const pthread_attr_t *attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_setcancelstate(int state, int *oldstate) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_setcanceltype(int type, int *oldtype) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_setconcurrency(int new_level) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_setschedparam(pthread_t pthread, int policy, const struct sched_param *param) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_setschedprio(pthread_t thread, int prio) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_setspecific(pthread_key_t key, const void *value) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_sigqueue(pthread_t thread, int sig, const union sigval value) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_spin_destroy(pthread_spinlock_t *spinlock) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_spin_init(pthread_spinlock_t *spinlock, int pshared) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_spin_lock(pthread_spinlock_t *spinlock) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_spin_trylock(pthread_spinlock_t *spinlock) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_spin_unlock(pthread_spinlock_t *spinlock) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

void __wrap_pthread_testcancel(void) {
}

int __wrap_pthread_timedjoin_np(pthread_t thread, void **retval) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_tryjoin_np(pthread_t thread, void **retval, const struct timespec *abstime) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_rwlock_destroy(pthread_rwlock_t *rwlock) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_rwlock_rdlock(pthread_rwlock_t *rwlock) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_rwlock_timedrdlock(pthread_rwlock_t *rwlock, const struct timespec *abstime) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_rwlock_timedwrlock(pthread_rwlock_t *rwlock, const struct timespec *abstime) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_rwlock_unlock(pthread_rwlock_t *rwlock) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_rwlock_wrlock(pthread_rwlock_t *rwlock) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_rwlockattr_destroy(pthread_rwlockattr_t *attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_rwlockattr_init(pthread_rwlockattr_t *attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *attr, int *pshared) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_rwlockattr_setpshared(pthread_rwlockattr_t *attr, int pshared) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutex_destroy(pthread_mutex_t *mutex) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutex_getprioceiling(const pthread_mutex_t * restrict mutex, int *prioceiling) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutex_lock(pthread_mutex_t *mutex) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutex_setprioceiling(pthread_mutex_t *mutex, int prioceiling, int *old_ceiling) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *timeout) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutex_trylock(pthread_mutex_t *mutex) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutex_unlock(pthread_mutex_t *mutex) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutexattr_destroy(pthread_mutexattr_t *attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutexattr_init(pthread_mutexattr_t *attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *attr, int *prioceiling) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutexattr_getprotocol(const pthread_mutexattr_t *attr, int *protocol) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutexattr_getpshared(const pthread_mutexattr_t *attr, int *pshared) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, int *kind) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutexattr_setprioceiling(pthread_mutexattr_t *attr, int prioceiling) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutexattr_setprotocol(pthread_mutexattr_t *attr, int protocol) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_mutexattr_settype(pthread_mutexattr_t *attr, int kind) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_once(pthread_once_t *once_control, void (*init_routine)(void)) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_sem_close(sem_t *sem) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_sem_destroy(sem_t *sem) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_sem_getvalue(sem_t * restrict sem, int * restrict sval) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_sem_init(sem_t *sem, int pshared, unsigned int value) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

sem_t *__wrap_sem_open(const char *name, int oflag, ...) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return SEM_FAILED;
  }

  return ((sem_t *) 1);
}

int __wrap_sem_post(sem_t *sem) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_sem_timedwait(sem_t * restrict sem, const struct timespec * restrict abs_timeout) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_sem_trywait(sem_t *sem) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_sem_unlink(const char *name) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

int __wrap_sem_wait(sem_t *sem) {

  const bool failure = mock_type(bool);

  if (failure) {
    errno = mock_type(int);

    return -1;
  }

  return 0;
}

void stub(void) {
}

void stub_other(void *arguments) {
}

void * stub_callback(void * const arguments) {

  return 0;
}

#ifdef __cplusplus
} // extern "C"
#endif
