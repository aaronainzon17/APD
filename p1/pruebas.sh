#!/bin/bash

PRUEBAS=$(ls pruebasEntrega/)
ONECLIQUE=$(ls testing/oneClique/)
TWOCLIQUE=$(ls testing/twoClique/)
RAND=$(ls testing/random/)
CIRCLE="testing/circle.txt"

make

for PROG in $PRUEBAS; do
        #echo "PROBANDO: pruebasEntrega/"$PROG
        ./practica1 R "pruebasEntrega/"$PROG
        ./practica1 H "pruebasEntrega/"$PROG
        
done;

make clean
