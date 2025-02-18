To Do list:

- Formes canonique
-Mettre listen dans la poll!!!
- Mise en places des commandes (et implementer la gestion des canaux de maniere generale)
      : -Join :200 characte channel, no space, no comma
        -PART (quitter channel)
        -Quit
        -Nick   9 character max
        -User  
        -Topic : FINI!!!
        -Kick: depend de part
        -Mode: 
			-i Définir/supprimer le canal sur invitation uniquement
			-t Définir/supprimer les restrictions de la commande TOPIC pour les opérateurs de canaux
			-k Définir/supprimer la clé du canal (mot de passe)
			-o Donner/retirer le privilège de l’opérateur de canal
			-l Définir/supprimer la limite d’utilisateurs pour le canal
			idee, gerer en binaire (1,1,1,1,1) ou faire tableau d'admin. Voir struc sur Channel.hpp

- Replication server client

Done :

- Communication client serveur


Syntaxe IRC :

[{:}{prefix}{SP}]{COMMANDE}[{SP}{PARAMETRES}]{CRLF}

:prefix CMD param


 prefix = 

 Client => serveur

NICK

Client client

  :NICK!NAME@DOMAINE du sender

Serveur client

  :Nom du serv


CMD = soit un mot, soit 3 chiffres (reponse serveur)


param = :x x x si plusieurs param


Verifier caracteres interdit et taille max 512 char
