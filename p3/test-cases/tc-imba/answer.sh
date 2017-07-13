#!/bin/sh

for i in $(seq 0 22)
do
    sh exceptions/$i.sh > exceptions/$i.ans
done

worlds=(aworld bworld cnmworld sjtu)
for world in ${worlds[@]}
do
    ./p3 species/species2 worlds/$world 50 > worlds/$world.concise.answer
    ./p3 species/species2 worlds/$world 50 v > worlds/$world.verbose.answer
done
