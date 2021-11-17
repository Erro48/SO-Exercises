#!/bin/bash

# nome_file = $1

if [[ $# != 1 ]]; then echo "Devi passare 1 file"; exit 1; fi
if [[ ! -r $1 ]]; then echo "File inesistente o illeggibile"; exit 2; fi

OUT=""

while read prima seconda altro; do
	OUT="${OUT}${seconda}"
done < $1

echo $OUT
