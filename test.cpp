#include <iostream>
#include <vector>
#include <cstring>   // memset
#include <unistd.h>  // close
#include <arpa/inet.h>
#include <poll.h>

#define PORT 6697
#define MAX_CLIENTS 10

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen = sizeof(address);
    
    // Création du socket serveur
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Erreur socket");
        return 1;
    }

    // Configuration de l'adresse du serveur
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Liaison du socket à l'adresse
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Erreur bind");
        close(server_fd);
        return 1;
    }

    // Écoute des connexions entrantes
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Erreur listen");
        close(server_fd);
        return 1;
    }

    std::cout << "Serveur en écoute sur le port " << PORT << "...\n";

    // Tableau pour `poll()`
    std::vector<pollfd> fds;
    fds.push_back({server_fd, POLLIN, 0}); // Ajoute le socket du serveur

    while (true) 
	{
        int activity = poll(fds.data(), fds.size(), -1); // Attente infinie jusqu'à un événement

        if (activity < 0) {
            perror("Erreur poll");
            break;
        }

        // Vérifier si une nouvelle connexion arrive
        if (fds[0].revents & POLLIN) 
		{
            new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
            if (new_socket < 0)
			{
                // perror("Erreur accept");
                continue;
            }
            std::cout << "Nouveau client connecté : " << inet_ntoa(address.sin_addr) << "\n";
            fds.push_back({new_socket, POLLIN, 0}); // Ajouter le client à `poll()`
        }

        // Vérifier l'activité des clients existants
        for (size_t i = 1; i < fds.size(); i++) {
            if (fds[i].revents & POLLIN) {
                char buffer[1024] = {0};
                int valread = read(fds[i].fd, buffer, sizeof(buffer));
                if (valread <= 0) {
                    // Déconnexion du client
                    std::cout << "Client déconnecté.\n";
                    close(fds[i].fd);
                    fds.erase(fds.begin() + i);
                    i--; // Ajuster l'index
                } else {
                    std::cout << "Message reçu : " << buffer << "\n";
                }
            }
        }
    }

    close(server_fd);
    return 0;
}
