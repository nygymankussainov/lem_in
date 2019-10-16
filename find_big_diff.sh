#!/bin/bash
while (true)
do
	./generator --big-superposition > map1
	a=`cat map1 | grep -w -m 1 "#Here" | cut -b 40,41,42`
	b=`./lem-in < map1 | ./verifier`
	let "c = b - a"
	if [ "$c" -le "-7" ]; then break ;
	fi
	echo $c
done
