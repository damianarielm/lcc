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
```

## Cost

|     | tiny | medium | big | contoursMaze | mediumScaryMaze | openMaze | smallMaze |
| --- | ---- | ------ | --- | ------------ | --------------- | -------- | --------- |
| dfs | 10   | 130    | 210 | 85           |  72             | 298      | 49        |
| bfs | 8    | 68     | 210 | 13           |  72             | 54       | 19        |
| ucs | 8    | 68     | 210 | 13           |  72             | 54       | 19        |

## Nodes expanded

|     | tiny | medium | big | contoursMaze | mediumScaryMaze | openMaze | smallMaze |
| --- | ---- | ------ | --- | ------------ | --------------- | -------- | --------- |
| dfs | 15   | 146    | 390 | 85           | 279             | 576      | 59        |
| bfs | 15   | 269    | 620 | 170          | 279             | 682      | 92        |
| ucs | 15   | 268    | 619 | 167          | 279             | 682      | 91        |

## Score

|     | tiny | medium | big | contoursMaze | mediumScaryMaze | openMaze | smallMaze |
| --- | ---- | ------ | --- | ------------ | --------------- | -------- | --------- |
| dfs | 500  | 300    | 300 | 425          | -513            | 212      | 461       |
| bfs | 502  | 442    | 300 | 497          | -524            | 456      | 491       |
| ucs | 502  | 442    | 300 | 497          | 438             | 456      | 491       |

# StaySearchAgents

```shell
python pacman.py -l mediumDottedMaze -p StayEastSearchAgent
python pacman.py -l mediumScaryMaze -p StayWestSearchAgent
```

# Eight Puzzle

```shell
python eightpuzzle.py
```

