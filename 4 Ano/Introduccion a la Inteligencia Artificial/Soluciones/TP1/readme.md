# PositionSearchProblem

```bash
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
```

## Cost

|     | tiny | medium | big    | contours | mediumSc | open  | small  | test | trappedCl |
| --- | ---- | ------ | ------ | -------- | -------- | ----- | ------ | ---- | --------- |
| dfs | 10   | 130    | 210    | 85       |  96      | 298   | 49     | 7    | 5         |
| bfs | 8    | 68     | 210    | 13       |  72      | 54    | 19     | 7    | 5         |
| ucs | 8    | 68     | 210    | 13       |  72      | 54    | 19     | 7    | 5         |
| SEA | 1    | 1      | 5      | 1        |  1       | 1     | 1      | 0    | 1         |
| SWA | 48   | 1718.. | 5904.. | 1030     |  68719.. | 343.. | 2380.. | 254  | 18        |
| ASM | 10   | 130    | 210    | 85       |  96      | 298   | 49     | 7    | 5         |
| ASE | 10   | 130    | 210    | 85       |  96      | 298   | 49     | 7    | 5         |

## Nodes expanded

|     | tiny | medium | big    | contours | mediumSc | open  | small  | test | trappedCl |
| --- | ---- | ------ | ------ | -------- | -------- | ----- | ------ | ---- | --------- |
| dfs | 15   | 146    | 390    | 85       |  96      | 576   | 59     | 7    | 5         |
| bfs | 15   | 269    | 620    | 170      |  279     | 682   | 92     | 7    | 7         |
| ucs | 15   | 268    | 619    | 167      |  279     | 682   | 91     | 7    | 7         |
| SEA | 13   | 260    | 637    | 169      |  230     | 668   | 85     | 7    | 7         |
| SWA | 11   | 173    | 496    | 36       |  108     | 288   | 58     | 7    | 5         |
| ASM | 15   | 146    | 390    | 85       |  96      | 576   | 59     | 7    | 5         |
| ASE | 15   | 146    | 390    | 85       |  96      | 576   | 59     | 7    | 5         |

## Score

|     | tiny | medium | big    | contours | mediumSc | open  | small  | test | trappedCl |
| --- | ---- | ------ | ------ | -------- | -------- | ----- | ------ | ---- | --------- |
| dfs | 500  | 380    | 300    | 425      |  414     | 212   | 461    | 503  | -502      |
| bfs | 502  | 442    | 300    | 497      |  -513    | 456   | 491    | 503  | -502      |
| ucs | 502  | 442    | 300    | 497      |  -532    | 456   | 491    | 503  | -497      |
| SEA | 502  | 436    | 300    | 479      |  -542    | 424   | 491    | 503  | -502      |
| SWA | 500  | 358    | 300    | 497      |  418     | 456   | 481    | 503  | -502      |
| ASM | 500  | 380    | 300    | 425      |  414     | 212   | 461    | 503  | -502      |
| ASE | 500  | 380    | 300    | 425      |  414     | 212   | 461    | 530  | -502      |

# CornersProblem

```bash
#!/bin/bash

files="mediumMaze bigMaze contoursMaze mediumScaryMaze \
       openMaze smallMaze testMaze trappedClassic bigCorners \
       capsuleClassic contestClassic  greedySearch mediumCorners \
       mediumClassic originalClassic smallClassic \
       openClassic testClassic tinyCorners trappedClassic trickyClassic"
declare -a agents=("SearchAgent -a fn=dfs" "SearchAgent -a fn=bfs")
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
```

## Cost

| Maze            | dfs | bfs |
| --------------- | --- | --- |
| mediumMaze      | 231 | 134 |
| bigMaze         | 462 | 260 |
| contoursMaze    | 255 | 47  |
| mediumScaryMaze | 353 | 139 |
| openMaze        | 400 | 116 |
| smallMaze       | 153 | 81  |
| testMaze        | 14  | 9   |
| trappedClassic  | 20  | 14  |
| bigCorners      | 302 | 162 |
| capsuleClassic  | 53  | 31  |
| contestClassic  | 123 | 53  |
| greedySearch    | 20  | 16  |
| mediumCorners   | 371 | 106 |
| mediumClasic    | 125 | 49  |
| originalClassic | 350 | 104 |
| smallClassic    | 75  | 37  |
| openClassic     | 185 | 37  |
| testClassic     | 27  | 13  |
| tinyCorners     | 47  | 28  |
| trappedClassic  | 20  | 14  |
| trickyClassic   | 140 | 57  |
