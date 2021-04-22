#!/bin/bash

files="bigMaze contoursMaze mediumMaze openMaze smallMaze testMaze tinyMaze"

declare -a agents=("SearchAgent" "SearchAgent -a fn=bfs" "SearchAgent -a fn=ucs" \
                   "SearchAgent -a fn=astar,heuristic=euclideanHeuristic" \
                   "SearchAgent -a fn=astar,heuristic=manhattanHeuristic")

command="python2 pacman.py -q"
grep="grep cost\|nodes"

for file in $files; do
    echo -e "$file"
    for agent in "${agents[@]}"; do
        echo -e "\n$agent"
        echo "-------------------"
        $command -l $file -p $agent | $grep | head -n3
    done
    echo "==========================================================="
done
