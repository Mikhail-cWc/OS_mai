#include "utils.h"

int human_get(sem_t *semaphore)
{
    int s;
    sem_getvalue(semaphore, &s);
    return s;
}

void human_set(sem_t *semaphore, int n)
{
    while (human_get(semaphore) < n)
    {
        sem_post(semaphore);
    }
    while (human_get(semaphore) > n)
    {
        sem_wait(semaphore);
    }
}
