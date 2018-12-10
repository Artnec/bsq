#!/bin/bash
# generates 100 random maps and checks if output of two different executables matches
max=100
for i in `seq 0 $max`
do
	perl perl_map_generator.pl $max $max $i > tmp_map
	./bsq tmp_map > tmp_f1
	./bsq_test tmp_map > tmp_f2
	if [[ ! -z "$(diff tmp_f1 tmp_f2)" ]]; then
		echo error on map \#$i
		break
	fi
	rm -f tmp_f1 tmp_f2 tmp_map
done
echo ok
