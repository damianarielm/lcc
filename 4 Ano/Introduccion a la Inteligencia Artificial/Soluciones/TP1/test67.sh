#!/bin/bash

files="bigCorners bigMaze contoursMaze greedySearch mediumCorners mediumMaze \
       openMaze smallMaze testSearch"

declare -a agents=("AStarCornersAgent" "AStarFoodSearchAgent")

command="python pacman.py -q"
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
