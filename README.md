To Do list:

-Formes canonique
-Mettre listen dans la poll!!!
-Mise en places des commandes (et implementer la gestion des canaux de maniere generale)
      : -Join :200 characte channel, no space, no comma
        -PART (quitter channel)
        -Quit
        -Nick   9 character max
        -User  
        -Topic : FINI!!!
        -Kick
        -Mode: 
			-i Définir/supprimer le canal sur invitation uniquement
			-t Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs de canaux
			-k Définir/supprimer la clé du canal (mot de passe)
			-o Donner/retirer le privilège de l’opérateur de canal
			-l Définir/supprimer la limite d’utilisateurs pour le canal
			idee, gerer en binaire (1,1,1,1) ou faire tableau d'admin. Voir struc sur Channel.hpp



Verifier caracteres interdit et taille max 512 char

Upon successful completion of the registration process, the server MUST send, in this order:

    RPL_WELCOME (001),
    RPL_YOURHOST (002),
    RPL_CREATED (003),
    RPL_MYINFO (004),
    at least one RPL_ISUPPORT (005) numeric to the client.
    The server MAY then send other numerics and messages.
    The server SHOULD then respond as though the client sent the LUSERS command and return the appropriate numerics.
    The server MUST then respond as though the client sent it the MOTD command, i.e. it must send either the successful Message of the Day numerics or the ERR_NOMOTD (422) numeric.
    If the user has client modes set on them automatically upon joining the network, the server SHOULD send the client the RPL_UMODEIS (221) reply or a MODE message with the client as target, preferably the former.
