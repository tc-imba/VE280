#!/bin/bash

echo "Begin tc-imba tests:"

# exceptions
for i in $(seq 0 22)
do
    bash exceptions/$i.sh > exceptions/$i.out
    diff -q exceptions/$i.out exceptions/$i.ans
    if [ $? = 0 ]; then
        echo "exception $i: Accepted"
    else
        echo "exception $i: Wrong Answer"
    fi
done

# worlds
worlds=(aworld bworld cnmworld sjtu)
for world in ${worlds[@]}
do
    ./p3 species/species2 worlds/$world 50 > worlds/$world.concise.out
    diff -q worlds/$world.concise.out worlds/$world.concise.answer
    if [ $? = 0 ]; then
        echo "$world concise: Accepted"
    else
        echo "$world concise: Wrong Answer"
    fi
    ./p3 species/species2 worlds/$world 50 v > worlds/$world.verbose.out
    diff -q worlds/$world.verbose.out worlds/$world.verbose.answer
    if [ $? = 0 ]; then
        echo "$world verbose: Accepted"
    else
        echo "$world verbose: Wrong Answer"
    fi
done

echo ""
