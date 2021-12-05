#!/bin/bash

while read idVerdetto msgVerdetto; do
    idPers=`grep $idVerdetto processi.txt | cut -b 1-2`
    grep $idPers denunce.txt | \
        while read nome cognome id reato; do
            echo "${nome} ${cognome}:"
            echo "Reato: ${reato}."
            echo "Verdetto: ${msgVerdetto}."
            echo ""
        done
done < verdetti.txt