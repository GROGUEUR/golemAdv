#!/bin/bash

if [ ! -d "GolemAdventure" ];then
    mkdir GolemAdventure
    cd GolemAdventure

    wget -P . https://raw.githubusercontent.com/GROGUEUR/golemAdv/main/GolemAdventures.tar.gz

    # Dézipper l'archive
    tar -xvzf GolemAdventure.tar.gz

    rm -f GolemAdventure.tar.gz
else
    cd GolemAdventure
fi

# Exécuter make run
make run
