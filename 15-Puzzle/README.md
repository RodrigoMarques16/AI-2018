## 15-Puzzle

## Development Environment 
SO: Fedora

Language: C++11

## Compiling
To build the project simply run `make`

## Running

To run, call the executable built by the makefile:
`./15puzzle file`

Where 'file' is the path to a file with the initial and target boards in numeric sequence form


During execution you'll be asked which algorithm and heuristic you want to run, these are in the format

``` "algorithm" "heuristic" ```

Where 'algorithm' is the name of the algorithm you want to run, and 'heuristic' can be the name of the heuristic you want to use for that algorithm **OR** an integer to limit the depth the algorithm will search, eg:

```
  - a_star manhattan 
  - bfs
  - dfs 20
```
### Implemented algorithms
  - dfs (int: limit)
  - bfs (int: limit)
  - iddfs (int: limit)
  - greedy ("hamming" | "manhattan")
  - a_star ("hamming" | "manhattan")
  
 ## Example run
 ```
 ./15puzzle input2.txt
 dfs 20
 greedy hamming
```
