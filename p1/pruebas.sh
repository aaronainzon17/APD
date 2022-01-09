#!/bin/bash

PRUEBAS=$(ls pruebasEntrega/)

make

for PROG in $PRUEBAS; do
        ./practica1 R "pruebasEntrega/"$PROG
        ./practica1 H "pruebasEntrega/"$PROG
        
done;

make clean
