#!/bin/bash
i=0
while (true)
do
	./generator --big-superposition > map
	./lem-in < map
	if [[ $? -eq 139 ]]; then break ; fi
	((i++))
	echo $i
done

