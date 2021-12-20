#!/bin/bash

if (( $# > 9 )); then
    echo "Numero di argomenti massimo: 9";
    echo "Numero di argomenti passato: $#";
    exit;
fi

