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
```

## Cost

|     | tiny | medium | big | contoursMaze | mediumScaryMaze | openMaze | smallMaze | testMaze |
| --- | ---- | ------ | --- | ------------ | --------------- | -------- | --------- | -------- |
| dfs | 10   | 130    | 210 | 85           |  72             | 298      | 49        | 7        |
| bfs | 8    | 68     | 210 | 13           |  72             | 54       | 19        | 7        |
| ucs | 8    | 68     | 210 | 13           |  72             | 54       | 19        | 7        |

## Nodes expanded

|     | tiny | medium | big | contoursMaze | mediumScaryMaze | openMaze | smallMaze | testMaze |
| --- | ---- | ------ | --- | ------------ | --------------- | -------- | --------- | -------- |
| dfs | 15   | 146    | 390 | 85           | 279             | 576      | 59        | 7        |
| bfs | 15   | 269    | 620 | 170          | 279             | 682      | 92        | 7        |
| ucs | 15   | 268    | 619 | 167          | 279             | 682      | 91        | 7        |

## Score

|     | tiny | medium | big | contoursMaze | mediumScaryMaze | openMaze | smallMaze | testMaze |
| --- | ---- | ------ | --- | ------------ | --------------- | -------- | --------- | -------- |
| dfs | 500  | 300    | 300 | 425          | -513            | 212      | 461       | 503      |
| bfs | 502  | 442    | 300 | 497          | -524            | 456      | 491       | 503      |
| ucs | 502  | 442    | 300 | 497          | 438             | 456      | 491       | 503      |

# StaySearchAgents

```shell
python pacman.py -l mediumDottedMaze -p StayEastSearchAgent
python pacman.py -l mediumScaryMaze -p StayWestSearchAgent
```

# Eight Puzzle

```shell
python eightpuzzle.py
```

