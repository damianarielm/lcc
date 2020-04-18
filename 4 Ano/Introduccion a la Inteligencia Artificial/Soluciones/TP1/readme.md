# SearchAgent

```shell
python pacman.py -l tinyMaze -p SearchAgent
python pacman.py -l tinyMaze -p SearchAgent -a fn=bfs
python pacman.py -l tinyMaze -p SearchAgent -a fn=ucs

python pacman.py -l mediumMaze -p SearchAgent
python pacman.py -l mediumMaze -p SearchAgent -a fn=bfs
python pacman.py -l mediumMaze -p SearchAgent -a fn=ucs

python pacman.py -l bigMaze -z .5 -p SearchAgent
python pacman.py -l bigMaze -z .5 -p SearchAgent -a fn=bfs
python pacman.py -l bigMaze -z .5 -p SearchAgent -a fn=ucs

python pacman.py -l contoursMaze -p SearchAgent
python pacman.py -l contoursMaze -p SearchAgent -a fn=bfs
python pacman.py -l contoursMaze -p SearchAgent -a fn=ucs

python pacman.py -l mediumScaryMaze -p SearchAgent
python pacman.py -l mediumScaryMaze -p SearchAgent -a fn=bfs
python pacman.py -l mediumScaryMaze -p SearchAgent -a fn=ucs

python pacman.py -l openMaze -p SearchAgent
python pacman.py -l openMaze -p SearchAgent -a fn=bfs
python pacman.py -l openMaze -p SearchAgent -a fn=ucs

python pacman.py -l smallMaze -p SearchAgent
python pacman.py -l smallMaze -p SearchAgent -a fn=bfs
python pacman.py -l smallMaze -p SearchAgent -a fn=ucs

python pacman.py -l testMaze -p SearchAgent
python pacman.py -l testMaze -p SearchAgent -a fn=bfs
python pacman.py -l testMaze -p SearchAgent -a fn=ucs

python pacman.py -l trappedClassic -p SearchAgent
python pacman.py -l trappedClassic -p SearchAgent -a fn=bfs
python pacman.py -l trappedClassic -p SearchAgent -a fn=ucs
```

## Cost

|     | tiny | medium | big | contours | mediumScary | open | small | test | trappedClassic |
| --- | ---- | ------ | --- | -------- | ----------- | ---- | ----- | ---- | -------------- |
| dfs | 10   | 130    | 210 | 85       |  96         | 298  | 49    | 7    | 5              |
| bfs | 8    | 68     | 210 | 13       |  72         | 54   | 19    | 7    | 5              |
| ucs | 8    | 68     | 210 | 13       |  72         | 54   | 19    | 7    | 5              |

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

# StaySearchAgents

```shell
python pacman.py -l mediumDottedMaze -p StayEastSearchAgent
python pacman.py -l mediumScaryMaze -p StayWestSearchAgent
```

# Eight Puzzle

```shell
python eightpuzzle.py
```

