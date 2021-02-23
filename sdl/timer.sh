#! /usr/bin/bash

gcc labda.c sdl_ablak.c sdl_timer.c -o timer2 `sdl2-config --cflags --libs` -lSDL2_gfx -lSDL2_ttf -lSDL2_image -lSDL2_mixer

