#include <iostream>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid = getpid();   
    std::cout << "PID = " << pid << "\n";
    int a = 1, b = 3;
    while (1) {
        if (a == b) {
            std::cout << "H00k3d\n";
            exit(EXIT_SUCCESS);
        }
        std::cout << "Wait ... \n";
        sleep(10);
    }
    return 0;
}