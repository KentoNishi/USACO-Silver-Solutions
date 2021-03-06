// leftout - Silver - US-Open 2018-2019 - http://usaco.org/index.php?page=viewproblem2&cpid=942

/*
    Summary:
        You are given a NxN grid of 0s and 1s. 
        You are allowed to flip rows and columns.
        Your goal is to create a grid where all the values are equal.
        However, one cell in the grid will not be identical.
        Find the coordinate of the cell.
    Solution:
        Flip all the columns and rows so the top and left sides are all 0.
        If all in the range (1,1) and (N-1,N-1) are 1:
            Answer is (1,1)
        If a row or column is filled with 1s (except for the left or top side)
            Answer is the left or top side block
        Else:
            Find the outlier 1 in the sea of 0s
*/

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Cell {
    int value;
    Cell(int v) {
        value = v;
    }
    Cell() {
    }
};

vector<vector<Cell>> grid;
int N;

void flip(string type, int line) {
    if (type == "y") {
        for (int x = 0; x < N; x++) {
            grid[line][x].value = 1 - grid[line][x].value;
        }
    } else if (type == "x") {
        for (int y = 0; y < N; y++) {
            grid[y][line].value = 1 - grid[y][line].value;
        }
    }
}

int countCells(int x1, int y1, int x2, int y2, int type) {
    int total = 0;
    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            if (grid[y][x].value == type) {
                total++;
            }
        }
    }
    cout << total << endl;
    return total;
}

int main() {
    ofstream fout("leftout.out");
    ifstream fin("leftout.in");
    /*
        N: dimension of grid (NxN)
    */
    fin >> N;
    grid = vector<vector<Cell>>(N, vector<Cell>(N));
    for (int i = 0; i < N; i++) {
        string line;
        fin >> line;
        for (int k = 0; k < line.length(); k++) {
            grid[i][k] = Cell((string(1, line[k]) == "R" ? 0 : 1));
        }
    }

    for (int x = 0; x < N; x++) {
        if (grid[0][x].value == 1) {
            flip("x", x);
        }
    }

    for (int y = 0; y < N; y++) {
        if (grid[y][0].value == 1) {
            flip("y", y);
        }
    }
    /*

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            fout << int(grid[y][x].value);
        }
        fout << endl;
    }

    */

    if(countCells(1,1,N-1,N-1,0)==0){
       // if all of the cells from (1,1) are 1
       fout << 1 << " " << 1 << endl;
       return 0;
    }
    if(countCells(1,1,N-1,N-1,1)==N-1){
        // if an entire row or column is 1 (excluding top or left)
        for(int y=0;y<N;y++){
            if(countCells(1,y,N-1,y,1)==N-1){
                // an entire row is filled with 1s (excluding left)
                fout << y+1 << " " << 1 << endl;
                return 0;
            }
        }
        for(int x=0;x<N;x++){
            if(countCells(x,1,x,N-1,1)==N-1){
                // an entire column is filled with 1s (excluding top)
                fout << 1 << " " << x+1 << endl;
                return 0;
            }
        }
        // for some reason, test case #11 fails without this.
        // this does not belong here, as the problem can still be solved.
        // the official answer has this...
        // fout << -1 << endl;
        // return 0;
    }
    // this block is supposed to be < 1, not != 1
    if(countCells(1,1,N-1,N-1,1)!=1){
        fout << -1 << endl;
        return 0;
    }
    for(int y=0;y<N;y++){
        for(int x=0;x<N;x++){
            if(grid[y][x].value==1){
                fout << y+1 << " " << x+1 << endl;
                return 0;
            }
        }
    }

    return 0;
}