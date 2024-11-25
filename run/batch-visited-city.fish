#!/usr/bin/env fish

set BIN "./bin"

set MAP "./maps/cidade.map"

for i in BFS IDS UCS Greedy Astar
    for j in 15 31 63 127 255
        echo $i "Base"
        $BIN $MAP $i 0 0 $j $j
        echo $i "Reverse"
        $BIN $MAP $i $j $j 0 0
    end
end
