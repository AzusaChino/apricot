// #include <sys/socket.h>
// #include <signal.h>

// void sigchld_handler(int sig)
// {
//     while (waitpid(-1, 0, WNOHANG) > 0)
//     {
//     }
//     return;
// }

// int main(int argc, char **argv)
// {
//     int listenFd, connFd;
//     socklen_t clientlen;
//     struct sockaddr_storage clientaddr;

//     signal(SIGCHLD, sigchld_handler);
//     listenFd = open_lisnten
// }
