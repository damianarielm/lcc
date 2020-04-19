# SearchAgent

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

|     | tiny | medium | big    | contours | mediumSc | open | small | test | trappedCl |
| --- | ---- | ------ | ------ | -------- | -------- | ---- | ----- | ---- | --------- |
| dfs | 10   | 130    | 210    | 85       |  96      | 298  | 49    | 7    | 5         |
| bfs | 8    | 68     | 210    | 13       |  72      | 54   | 19    | 7    | 5         |
| ucs | 8    | 68     | 210    | 13       |  72      | 54   | 19    | 7    | 5         |
| SEA | 1    | 1      | 5      | 1        |  1       | 1    | 1     | 0    | 1         |
| SWA | 48   | 1718.. | 5904.. | 1030     |  68719.. | 343. | 238.. | 254  | 18        |
| ASM | 10   | 130    | 210    | 85       |  96      | 298  | 49    | 7    | 5         |
| ASE | 10   | 130    | 210    | 85       |  96      | 298  | 49    | 7    | 5         |

## Nodes expanded

|     | tiny | medium | big | contours | mediumScary | open | small | test | trappedClassic |
| --- | ---- | ------ | --- | -------- | ----------- | ---- | ----- | ---- | -------------- |
| dfs | 15   | 146    | 390 | 85       | 96          | 576  | 59    | 7    | 5              |
| bfs | 15   | 269    | 620 | 170      | 279         | 682  | 92    | 7    | 7              |
| ucs | 15   | 268    | 619 | 167      | 279         | 682  | 91    | 7    | 7              |

## Score

|     | tiny | medium | big | contours | mediumScary | open | small | test | trappedClassic |
| --- | ---- | ------ | --- | -------- | ----------- | ---- | ----- | ---- | -------------- |
| dfs | 500  | 380    | 300 | 425      | 414         | 212  | 461   | 503  | -502           |
| bfs | 502  | 442    | 300 | 497      | -522        | 456  | 491   | 503  | -497           |
| ucs | 502  | 442    | 300 | 497      | -512        | 456  | 491   | 503  | -502           |
