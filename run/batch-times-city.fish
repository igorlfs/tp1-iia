#!/usr/bin/env fish

set BIN "./bin"

set MAP "./maps/cidade.map"

for i in BFS IDS UCS Greedy Astar
    for j in 15 31 63 127 255
        echo $i $j "Base"
        time $BIN $MAP $i 0 0 $j $j >> /dev/null 2>&1
        echo $i $j "Reverse"
        time $BIN $MAP $i $j $j 0 0 >> /dev/null 2>&1
    end
end
