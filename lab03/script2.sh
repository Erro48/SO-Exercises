#!/bin/bash

NARGS=$#
STR=""
for arg in "$@"; do
	STR="$STR ${!NARGS}"
	(( NARGS=$NARGS-1 ))
done

echo $STR
