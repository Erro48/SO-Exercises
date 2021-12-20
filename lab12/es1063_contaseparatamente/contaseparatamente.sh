#!/bin/bash

if (( $# > 9 )); then
    echo "Numero di argomenti massimo: 9";
    echo "Numero di argomenti passato: $#";
    exit;
fi

index=1;
while (( $index <= $# )); do
    if (( $index % 2 == 0 )); then
        # se è pari
        echo `wc -l ${!index}`
    else
        echo `wc -l ${!index}` >&2
    fi
    (( index = $index + 1 ))
done