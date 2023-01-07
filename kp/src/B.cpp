#include "utils.h"

int main(int args, char* argv[])
{
    int fdAB[2];
    fdAB[0] = atoi(argv[0]);
    fdAB[1] = atoi(argv[1]);
    int fdBC[2];
    fdBC[0] = atoi(argv[2]);
    fdBC[1] = atoi(argv[3]);
    sem_t* semA = sem_open("_semA", O_CREAT, 0777, 1);
    sem_t* semB = sem_open("_semB", O_CREAT, 0777, 0);
    sem_t* semC = sem_open("_semC", O_CREAT, 0777, 0);
    while (1)
    {
        int size;
        read(fdAB[0], &size, sizeof(int));
        std::cout << "Number of input symbols is " << size << std::endl;
        
        sem_post(semC);
        sem_wait(semB);

        read(fdBC[0], &size, sizeof(int));
        std::cout << "Number of output symbols is " << size << std::endl;
        
        sem_post(semA);
        sem_wait(semB);
       
    }
    sem_close(semA);
    sem_close(semB);
    sem_close(semC);
    close(fdAB[0]);
    close(fdAB[1]);
    close(fdBC[0]);
    close(fdBC[1]);
    return 0;
}