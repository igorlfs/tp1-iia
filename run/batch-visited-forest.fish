#!/usr/bin/env fish

set BIN "./bin"

set MAP "./maps/floresta.map"

for i in BFS IDS UCS Greedy Astar
    for j in 17,16 35,31 102,63 132,127 208,255
        echo $j | read -d , arg1 arg2
        echo $i $arg2 "Base"
        $BIN $MAP $i 17 0 $arg1 $arg2
        echo $i $arg2 "Reverse"
        $BIN $MAP $i $arg1 $arg2 17 0
    end
end
