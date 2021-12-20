#!/bin/bash

if (( $# == 0 )); then
    echo "Numero di argomenti insufficiente, minimo 1";
fi

if (( $# > 9 )); then
    echo "Numero di argomenti massimo: 9";
    echo "Numero di argomenti passato: $#";
    exit;
fi

index=1;
totpari=0;
totdispari=0;
while (( $index <= $# )); do
    righe=`wc -l ${!index}`;
    righe=${righe%% *}
    if (( $index % 2 == 0 )); then
        # se è pari
        (( totpari=$totpari+$righe ))
    else
        (( totdispari=$totdispari+$righe ))
    fi
    (( index = $index + 1 ))
done

echo "Tot pari: ${totpari}"
echo "Tot dispari: ${totdispari}" >&2