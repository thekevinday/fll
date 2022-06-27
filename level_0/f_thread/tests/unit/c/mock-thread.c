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

int __wrap_pthread_attr_getaffinity_np(const pthread_attr_t *__attr, size_t __cpusetsize, cpu_set_t *__cpuset) {

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

int __wrap_pthread_attr_getguardsize(const pthread_attr_t *restrict attr, size_t *restrict guardsize) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_getinheritsched(const pthread_attr_t *restrict attr, int *restrict inheritsched) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_getschedparam(const pthread_attr_t *restrict attr, struct sched_param *restrict param) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_setaffinity_np(pthread_t __id, size_t __cpusetsize, const cpu_set_t *__cpuset) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_barrier_destroy(pthread_barrier_t barrier) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_condattr_getclock(const pthread_condattr_t *__restrict __attr, clockid_t *__restrict __clock_id) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_condattr_setclock(pthread_condattr_t *__attr, clockid_t __clock_id) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_condattr_getpshared(const pthread_condattr_t *__attr, int *__pshared) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_condattr_setpshared(pthread_condattr_t *__attr, int __pshared) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_getattr_default_np(pthread_attr_t *attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_setattr_default_np(const pthread_attr_t *attr) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_attr_init(pthread_attr_t *__attr) {

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

int __wrap_pthread_attr_setschedparam(pthread_attr_t *restrict attr, const struct sched_param *restrict param) {

  const bool failure = mock_type(bool);

  if (failure) {
    return mock_type(int);
  }

  return 0;
}

int __wrap_pthread_key_delete(pthread_key_t key) {

  return mock_type(int);
}

void stub(void) {
}

#ifdef __cplusplus
} // extern "C"
#endif
