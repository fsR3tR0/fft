#! /bin/bash

read -p "Forditando program: " be
echo $be
read -p "Mi legyen a neve: " be2
echo $be2
gcc $be -o $be2 `sdl2-config --cflags --libs` -lSDL2_gfx -lSDL2_ttf -lSDL2_image -lSDL2_mixer
echo "[+] Forditas kesz!"
