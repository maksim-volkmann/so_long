#include <stdio.h>

void floodFill(char map[][7], int x, int y, int *collectables, int *exit_found) {
    // Base cases
    if (x < 0 || x >= 4 || y < 0 || y >= 6 || map[x][y] == '1' || map[x][y] == 'F') return;
    if (map[x][y] == 'C') (*collectables)++;
    if (map[x][y] == 'E') *exit_found = 1;

    // Mark the current cell as visited
    map[x][y] = 'F'; // F for Flooded/Visited

    // Recursive calls for four adjacent directions
    floodFill(map, x+1, y, collectables, exit_found);
    floodFill(map, x-1, y, collectables, exit_found);
    floodFill(map, x, y+1, collectables, exit_found);
    floodFill(map, x, y-1, collectables, exit_found);
}

int checkMap(char map[][7]) {
    int collectables = 0, exit_found = 0;

    // Assuming player's starting position is known (for example: (1, 1))
    floodFill(map, 1, 1, &collectables, &exit_found);

    // Assuming total_collectables is the total number of collectables in the map
    int total_collectables = 1; // For this example
    return collectables == total_collectables && exit_found;
}

int main() {
    if (checkMap(map)) {
        printf("Map is valid.\n");
    } else {
        printf("Map is invalid.\n");
    }
    return 0;
}

Initial Call: floodFill(map, 2, 1, &collectables, &exit_found);

1. Checks (2,1), finds 'P', marks it 'F'.
2. Calls floodFill for (3,1), (1,1), (2,2), (2,0).
   - Since (2,0) and (2,2) are walls ('1'), those calls return immediately.
   - (3,1) is open, so it explores further in the next set of recursive calls.
   - (1,1) would similarly explore its adjacent cells.
3. This process continues until all paths are explored.
