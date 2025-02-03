To Do list:

- Mieux Organiser les classes
- Formes canonique

- Mise en places des commandes (et implementer la gestion des canaux de maniere generale)
      : -Join (deja commence)
        -PART (quitter channel)
        -Quit
        -Nick
        -User
        -Topic
        -List
        -Mode
        -Kick
        -Pong
- Gerer les droits

- Relier l'affichage a hexchat en implementant le protocole IRC (aled)

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

  NICK!NAME@DOMAINE du sender a tester mais les : serait reserve au serv?

Serveur client

  Nom du serv


CMD = soit un mot, soit 3 chiffres (reponse serveur)


param = :x x x si plusieurs param


Verifier caracteres interdit et taille max 512 char
