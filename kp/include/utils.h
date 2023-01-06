#ifndef OS_LABS_PARENT_H
#define OS_LABS_PARENT_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <signal.h>

void human_set(sem_t *semaphore, int n);
int human_get(sem_t *semaphore);


#endif // OS_LABS_PARENT_H