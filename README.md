# bsq

algorithm that finds largest empty square on a map, filled with obstacles. 

to generate random maps use perl script perl_map_generator.pl.

how to use perl_map_generator.pl:
```
perl perl_map_generator.pl 20 10 2 > map   will generate map with height 10, length 20, 
                                           and around 10% (20 / 2), of points as obstacles
```

first line of bsq input must contain number(map height), and three characters that tell us what symbols will represent
empty point, obstacle point, and filled point of largest square that we found.
from second line to the end is the map itself.

how to use bsq:
```
perl perl_map_generator.pl 20 10 2 > map

cat map
10.ox
...................o
...o.......o.....o..
oo..o..o............
.......o............
....o...o....o......
..............o....o
..o.................
.o.........o........
....o...o......o....
..........oo........

./bsq map
............xxxx...o
...o.......oxxxx.o..
oo..o..o....xxxx....
.......o....xxxx....
....o...o....o......
..............o....o
..o.................
.o.........o........
....o...o......o....
..........oo........

```

after writing working algorithm, i decided to optimize its working speed. to check its correctness after every
optimization, i renamed unoptimised bsq to bsq_test and made bash script (test.sh) that executed both script on
large number of randomly generated maps with increasing amount of obstacles, and looked for differences in outputs.
if no differences were found i concluded that improved algorithm worked correctly.
