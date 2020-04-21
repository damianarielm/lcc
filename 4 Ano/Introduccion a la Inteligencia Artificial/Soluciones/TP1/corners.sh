#!/bin/bash

files="mediumMaze bigMaze contoursMaze mediumScaryMaze \
       openMaze smallMaze testMaze trappedClassic bigCorners \
       capsuleClassic contestClassic  greedySearch mediumCorners \
       mediumClassic originalClassic smallClassic \
       openClassic testClassic tinyCorners trappedClassic trickyClassic"
declare -a agents=("SearchAgent -a fn=dfs" "SearchAgent -a fn=bfs" \
"SearchAgent -a fn=aStarSearch,heuristic=cornersHeuristic")
command="python2 pacman.py -q"
grep="grep --color=always cost\|nodes\|Score"

for file in $files; do
    echo -e "\e[97m\e[4m$file\e[0m"
    for agent in "${agents[@]}"; do
        echo -e "\n\e[97m$agent,prob=CornersProblem\e[0m"
        $command -l $file -p $agent,prob=CornersProblem | $grep | head -n3
    done
    echo "==========================================================="
done
