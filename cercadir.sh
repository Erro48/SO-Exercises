#!/bin/bash

DIR="/usr/include/"
for elem in `ls ${DIR}`; do
	if [[ -d ${DIR}${elem} && -r ${DIR}${elem} && ${DIR}${elem} -nt "/usr/include/sudo_plugin.h" ]]; then
		echo ${DIR}${elem}
	fi
done
