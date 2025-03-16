#include <iostream>
#include <unistd.h>       // Pour read, write, close, fork
#include <sys/socket.h>   // Pour socketpair
#include <poll.h>         // Pour poll
#include <cstdlib>        // Pour exit()

int main() {
    int sock[2];

    // Création du socketpair (domaine UNIX, SOCK_STREAM)
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sock) == -1) {
        perror("socketpair");
        return 1;
    }

    struct pollfd fds;
    fds.fd = sock[0];  // On surveille le premier socket
    fds.events = POLLIN; // On veut détecter des données en lecture

    if (fork() == 0) { // Processus enfant
        close(sock[0]); // Ferme le côté de lecture
        sleep(1); // Simule un délai avant d'envoyer
        write(sock[1], "Hello", 5); // Écrit un message
        close(sock[1]); // Ferme après écriture
        exit(0);
    }

    close(sock[1]); // Ferme l'écriture dans le parent

    int ret = poll(&fds, 1, 5000); // Attend jusqu'à 5 secondes
    if (ret > 0 && (fds.revents & POLLIN)) {
        char buf[10] = {0};
        read(sock[0], buf, sizeof(buf));
        std::cout << "Reçu: " << buf << std::endl;
    } else {
        std::cout << "Timeout ou erreur" << std::endl;
    }

    close(sock[0]);
    return 0;
}
