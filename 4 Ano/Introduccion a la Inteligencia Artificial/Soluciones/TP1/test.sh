#!/bin/bash

files="tinyMaze mediumMaze bigMaze contoursMaze mediumScaryMaze \
       openMaze smallMaze testMaze trappedClassic"
declare -a agents=("SearchAgent" "SearchAgent -a fn=bfs" "SearchAgent -a fn=ucs" \
                   "StayEastSearchAgent" "StayWestSearchAgent" \
                   "SearchAgent -a fn=astar,heuristic=manhattanHeuristic" \
                   "SearchAgent -a fn=astar,heuristic=euclideanHeuristic")
command="python2 pacman.py -q"
grep="grep --color=always cost\|nodes\|Score"

for file in $files; do
    echo -e "\e[97m\e[4m$file\e[0m"
    for agent in "${agents[@]}"; do
        echo -e "\n\e[97m$agent\e[0m"
        $command -l $file -p $agent | $grep | head -n3
    done
    echo "==========================================================="
done
