#!/bin/bash

if [ ! -d "Golem_Adventure" ];then
    mkdir Golem_Adventure
    cd Golem_Adventure

    wget -P . https://raw.githubusercontent.com/GROGUEUR/golemAdv/main/Golem_Adventure.tar.gz

    # Dézipper l'archive
    tar -xvzf Golem_Adventure.tar.gz

    rm -f Golem_Adventure.tar.gz
else
    cd Golem_Adventure
fi

# Exécuter make run
make run
