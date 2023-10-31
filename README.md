
# GameOfLife
Conway's Game of Life in C with raylib

### Controls

R to reset\
S to save to file\
SPACE to pause\
left click to draw

### Installation

GameOfLife depends on raylib to work.

#### Arch Linux

`$ sudo pacman -S raylib`\
`$ make` inside the build folder

#### Building from source

Of course, raylib can be [built from source](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux).

### Running

`$ ./gameoflife <options>`\
A file containing a board can be specified to be loaded, otherwise an empty canvas of 160x90 will be used as the default.

#### File format

The file format should be:
```
C L sizex sizey
matrix
```
C and L are the number os columns and lines of the input matrix, and the sizes control the canvas size.\
Matrix values should be separated by spaces, any tabs or CRs will be ignored.

Avoid using a canvas ratio different from screen aspect ratio to avoid issues.
