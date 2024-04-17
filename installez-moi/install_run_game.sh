#!/bin/bash

#Déplace dans le répertoire avant
cd .. || exit

wget -P . https://raw.githubusercontent.com/GROGUEUR/golemAdv/main/Golem_Adventures1.9.6officiel.tar.gz

# Dézipper l'archive
tar -xvzf Golem_Adventures1.9.6officiel.tar.gz

# Se déplacer dans le répertoire extrait
cd Golem_Adventures1.9.6officiel || exit

# Exécuter make run
make run