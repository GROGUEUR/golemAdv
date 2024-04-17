#!/bin/bash

if [! -d "Golem_Adventures1.9.6officiel" ];then
    mkdir Golem_Adventures1.9.6officiel
    cd Golem_Adventures1.9.6officiel

    wget -P . https://raw.githubusercontent.com/GROGUEUR/golemAdv/main/Golem_Adventures1.9.6officiel.tar.gz

    # Dézipper l'archive
    tar -xvzf Golem_Adventures1.9.6officiel.tar.gz

    rm -f Golem_Adventures1.9.6officiel.tar.gz
else
    cd Golem_Adventures1.9.6officiel
fi

# Exécuter make run
make run