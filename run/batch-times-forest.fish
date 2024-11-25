#!/usr/bin/env fish

set BIN "./bin"

set MAP "./maps/floresta.map"

for i in BFS IDS UCS Greedy Astar
    for j in 17,16 35,31 102,63 132,127 208,255
        echo $exp | read -d , arg1 arg2
        echo $i $j "Base"
        time $BIN $MAP $i 0 0 $arg1 $arg2 >> /dev/null 2>&1
        echo $i $j "Reverse"
        time $BIN $MAP $i $arg1 $arg2 0 0 >> /dev/null 2>&1
    end
end
