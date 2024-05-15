cmake_minimum_required(VERSION 3.27)
project(untitled60 C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled60 main.c
        intestazione.h
        preparazione.c
        azioni_mazzo.c
        libreria_funzioni.h
        GIOCO.c
        effetti_cartePunto.c
        effetti_carteIstantanee.c
        fase_punteggio.c
        scelta_azione.c
        scelta_1.c
        fase_carteIstantanee.c)

