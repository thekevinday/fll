/**
 * FLL - Level 0
 *
 * Project: Thread
 * API Version: 0.5
 * Licenses: lgpl-2.1-or-later
 *
 * Test the thread project.
 */
#ifndef _MOCK__thread_h
#define _MOCK__thread_h

// Libc includes.
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>

// cmocka includes.
#include <cmocka.h>

// FLL-0 includes.
#include <fll/level_0/thread.h>

#ifdef __cplusplus
extern "C" {
#endif

const static int mock_errno_generic = 32767;

extern int __wrap_pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void));
extern int __wrap_pthread_attr_destroy(pthread_attr_t *attr);
extern int __wrap_pthread_attr_getaffinity_np(const pthread_attr_t *attr, size_t cpusetsize, cpu_set_t *cpuset);
extern int __wrap_pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
extern int __wrap_pthread_attr_getguardsize(const pthread_attr_t *restrict attr, size_t *restrict guardsize);
extern int __wrap_pthread_attr_getinheritsched(const pthread_attr_t *restrict attr, int *restrict inheritsched);
extern int __wrap_pthread_attr_getschedparam(const pthread_attr_t *restrict attr, struct sched_param *restrict param);
extern int __wrap_pthread_attr_getschedpolicy(const pthread_attr_t *restrict attr, int *restrict policy);
extern int __wrap_pthread_attr_getscope(const pthread_attr_t *attr, int *contentionscope);
extern int __wrap_pthread_attr_getstack(const pthread_attr_t *attr, void **stackaddr, size_t *stacksize);
extern int __wrap_pthread_attr_getstacksize(const pthread_attr_t *attr, size_t *stacksize);
extern int __wrap_pthread_attr_init(pthread_attr_t *attr);
extern int __wrap_pthread_attr_setaffinity_np(pthread_t id, size_t cpusetsize, const cpu_set_t *cpuset);
extern int __wrap_pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
extern int __wrap_pthread_attr_setguardsize(pthread_attr_t *attr, size_t guardsize);
extern int __wrap_pthread_attr_setinheritsched(pthread_attr_t *attr, int inheritsched);
extern int __wrap_pthread_attr_setschedparam(pthread_attr_t *restrict attr, const struct sched_param *restrict param);
extern int __wrap_pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy);
extern int __wrap_pthread_attr_setscope(pthread_attr_t *attr, int contentionscope);
extern int __wrap_pthread_attr_setstack(pthread_attr_t *attr, void *stackaddr, size_t stacksize);
extern int __wrap_pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
extern int __wrap_pthread_barrierattr_destroy(pthread_barrierattr_t *attr);
extern int __wrap_pthread_barrierattr_init(pthread_barrierattr_t *attr);
extern int __wrap_pthread_barrierattr_getpshared(const pthread_barrierattr_t *attr, int *pshared);
extern int __wrap_pthread_barrierattr_setpshared(pthread_barrierattr_t *attr, int pshared);
extern int __wrap_pthread_barrier_destroy(pthread_barrier_t *barrier);
extern int __wrap_pthread_barrier_init(pthread_barrier_t *barrier, const pthread_barrierattr_t *attr, unsigned count);
extern int __wrap_pthread_barrier_wait(pthread_barrier_t *barrier);
extern int __wrap_pthread_condattr_getclock(const pthread_condattr_t * restrict attr, clockid_t * restrict clock_id);
extern int __wrap_pthread_condattr_getpshared(const pthread_condattr_t *attr, int *pshared);
extern int __wrap_pthread_condattr_setclock(pthread_condattr_t *attr, clockid_t clock_id);
extern int __wrap_pthread_condattr_setpshared(pthread_condattr_t *attr, int pshared);
extern int __wrap_pthread_getattr_default_np(pthread_attr_t *attr);
extern int __wrap_pthread_key_delete(pthread_key_t key);
extern int __wrap_pthread_setattr_default_np(const pthread_attr_t *attr);

/*
pthread_setcancelstate
pthread_testcancel
pthread_setcanceltype
pthread_getcpuclockid
pthread_equal
pthread_getconcurrency
pthread_setconcurrency
pthread_condattr_init
pthread_cond_init
pthread_cond_broadcast
pthread_cond_signal
pthread_cond_wait
pthread_cond_timedwait
pthread_create
pthread_detach
pthread_exit
pthread_join
pthread_tryjoin_np
pthread_timedjoin_np
pthread_key_create
pthread_getspecific
pthread_setspecific
pthread_rwlockattr_init
pthread_rwlockattr_getpshared
pthread_rwlockattr_setpshared
pthread_rwlock_init
pthread_rwlock_rdlock
pthread_rwlock_timedrdlock
pthread_rwlock_tryrdlock
pthread_rwlock_wrlock
pthread_rwlock_timedwrlock
pthread_rwlock_trywrlock
pthread_mutexattr_init
pthread_mutexattr_getprioceiling
pthread_mutexattr_setprioceiling
pthread_mutexattr_getpshared
pthread_mutexattr_setpshared
pthread_mutexattr_gettype
pthread_mutexattr_settype
pthread_mutexattr_getprotocol
pthread_mutexattr_setprotocol
pthread_mutex_init
pthread_mutex_lock
pthread_mutex_timedlock
pthread_mutex_trylock
sem_init
sem_open
sem_close
sem_unlink
sem_wait
sem_timedwait
sem_trywait
sem_post
sem_getvalue
pthread_mutex_getprioceiling
pthread_mutex_setprioceiling
pthread_mutex_unlock
pthread_once
pthread_getschedparam
pthread_setschedparam
pthread_setschedprio
pthread_sigmask
pthread_sigqueue
pthread_spin_init
pthread_spin_lock
pthread_spin_trylock
pthread_spin_unlock
pthread_rwlock_unlock
*/

/**
 * A stub intended to be used for passing to functions like f_thread_at_fork().
 */
extern void stub(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _MOCK__thread_h
