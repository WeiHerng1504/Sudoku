# Sudoku

## Description
The goal of sudoku is to complete a square grid of 9x9 cells using only numbers from 1 to 9, in a way that has exactly one instance of each digit appearing in each column. This project is a "sudoku assistant" designed to solve simple soduko puzzles. This project was a university assignment designed to test a the student's knowledge and understanding of arrays, strings, functions and typedef facility.


## How it works
In this projects cells are described by number and by "set". Sets are in the order of row, column, and grid. Sets 0 to 8 are row sets (top to bottom), sets 9 to 17 are column sets (left to right) and sets 18 to 26 are grid sets (left to right). Constant arrays c2s (cell-to-set) and s2c (set-to-cell) were provided as part of the skeleton code and are used for easy identification of which sets a cell belongs to and which cells a set contains. Array c2s has eighty one rows and three columns, with c2s[c] listing the ordinal numbers of the three sets that include cell c. Array s2c has twenty seven rows and nine columns, with s2c[s] listing the cells that make up set number s. 

<p width="100%" align="center">
<img src="https://user-images.githubusercontent.com/94183388/169522376-e7e60ce7-5cc6-455c-bb0e-893bd339bca3.png" width="200" height="200">
</p>

In the figure, cell number 51 is a member of set 5 (row-based set), set 15 (column-based set) and set 23 (grid-based set).


### Reading and printing
Input to the program should always be a 9x9 grid with 0 used to represent empty cells. Input is provided in a text file. The program reads the input in row-major order using a sequence of 81 calls in a loop and stored as a one dimensional array. 

The output from the program will be a neatly-formatted representation of the input data and a summary line. Below is an example of the input(left) and output(right) of the program.

<p width="100%" align="center">
<img src="https://user-images.githubusercontent.com/94183388/169520928-4e327f3e-ec0a-48d4-b5a6-0e62f5460c15.png" width="600" height="300">
</p>
                                                                                                                                                 
### Grid checking
The program checks the input grid mistakes, to ensure that none of the twenty seven sets in the puzzle have duplicate elements. If any errors are detected, the program will report the errors according to their set number, from 0 to 26, and also by the set type (“row”, “col”, or “sqr”) and the ordinal (counting from one) number of that set.

<p width="100%" align="center" justify-content="space-between" display="flex>
 <img src="https://user-images.githubusercontent.com/94183388/170006188-5fbbb619-5a4d-4d0b-b531-a22d1fff536d.png" width="600" height="300">
</p>


