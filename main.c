/* Program to assist in the challenge of solving sudoku puzzles.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2021, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: Wei Herng Moo Yong 1239979
   Dated:     2/9/2021

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* these #defines provided as part of the initial skeleton */

#define NDIM 3		/* sudoku dimension, size of each inner square */
#define NDIG (NDIM*NDIM)
			/* total number of values in each row */
#define NGRP 3		/* number of sets each cell is a member of */
#define NSET (NGRP*NDIG)
			/* total number of sets in the sudoku */
#define NCLL (NDIG*NDIG)
			/* total number of cells in the sudoku */

#define ERROR	(-1)	/* error return value from some functions */

/* these global constant arrays provided as part of the initial skeleton,
   you may use them in your code but must not alter them in any way,
   regard them as being completely fixed. They describe the relationships
   between the cells in the sudoku and provide a basis for all of the
   sudoku processing loops */

/* there are 27 different different sets of elements that need to be
   checked against each other, this array converts set numbers to cells,
   that's why its called s2c */
int s2c[NSET][NDIM*NDIM] = {
	/* the first group of nine sets describe the sudoku's rows */
	{  0,  1,  2,  3,  4,  5,  6,  7,  8 },
	{  9, 10, 11, 12, 13, 14, 15, 16, 17 },
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35 },
	{ 36, 37, 38, 39, 40, 41, 42, 43, 44 },
	{ 45, 46, 47, 48, 49, 50, 51, 52, 53 },
	{ 54, 55, 56, 57, 58, 59, 60, 61, 62 },
	{ 63, 64, 65, 66, 67, 68, 69, 70, 71 },
	{ 72, 73, 74, 75, 76, 77, 78, 79, 80 },
	/* the second group of nine sets describes the sudoku's columns */
	{  0,  9, 18, 27, 36, 45, 54, 63, 72 },
	{  1, 10, 19, 28, 37, 46, 55, 64, 73 },
	{  2, 11, 20, 29, 38, 47, 56, 65, 74 },
	{  3, 12, 21, 30, 39, 48, 57, 66, 75 },
	{  4, 13, 22, 31, 40, 49, 58, 67, 76 },
	{  5, 14, 23, 32, 41, 50, 59, 68, 77 },
	{  6, 15, 24, 33, 42, 51, 60, 69, 78 },
	{  7, 16, 25, 34, 43, 52, 61, 70, 79 },
	{  8, 17, 26, 35, 44, 53, 62, 71, 80 },
	/* the last group of nine sets describes the inner squares */
	{  0,  1,  2,  9, 10, 11, 18, 19, 20 },
	{  3,  4,  5, 12, 13, 14, 21, 22, 23 },
	{  6,  7,  8, 15, 16, 17, 24, 25, 26 },
	{ 27, 28, 29, 36, 37, 38, 45, 46, 47 },
	{ 30, 31, 32, 39, 40, 41, 48, 49, 50 },
	{ 33, 34, 35, 42, 43, 44, 51, 52, 53 },
	{ 54, 55, 56, 63, 64, 65, 72, 73, 74 },
	{ 57, 58, 59, 66, 67, 68, 75, 76, 77 },
	{ 60, 61, 62, 69, 70, 71, 78, 79, 80 },
};


/* there are 81 cells in a dimension-3 sudoku, and each cell is a
   member of three sets, this array gets filled by the function
   fill_c2s(), based on the defined contents of the array s2c[][] */
int c2s[NCLL][NGRP];

void
fill_c2s() {
	int s=0, d=0, c;
	for ( ; s<NSET; s++) {
		/* record the first set number each cell is part of */
		for (c=0; c<NDIM*NDIM; c++) {
			c2s[s2c[s][c]][d] = s;
		}
		if ((s+1)%(NGRP*NDIM) == 0) {
			d++;
		}
	}
#if 0
	/* this code available here if you want to see the array
	   c2s[][] that gets created, just change that 0 two lines back
	   to a 1 and recompile */
	for (c=0; c<NCLL; c++) {
		printf("cell %2d: sets ", c);
		for (s=0; s<NGRP; s++) {
			printf("%3d", c2s[c][s]);
		}
		printf("\n");
	}
	printf("\n");
#endif
	return;
}

/* find the row number a cell is in, counting from 1
*/
int
rownum(int c) {
	return 1 + (c/(NDIM*NDIM));
}

/* find the column number a cell is in, counting from 1
*/
int
colnum(int c) {
	return 1 + (c%(NDIM*NDIM));
}

/* find the minor square number a cell is in, counting from 1
*/
int
sqrnum(int c) {
	return 1 + 3*(c/NSET) + (c/NDIM)%NDIM;
}

/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration
*/

#define TRUE 1
#define FALSE 0
#define LAST_ROW (NDIG - 1)
#define LAST_COLUMN (2*NDIG - 1)

int print_grid(int grid[]);
int check_grid(int grid[]);
void reset_array(int array[], int buddy);
int strategy1(int grid[], int* unknown_count, int* assignment_array);

/****************************************************************/


/****************************************************************/

/* main program controls all the action
*/
int
main(int argc, char *argv[]) {

    int grid[NCLL];
    int i;
    int unknown_count;
    int changes_made = TRUE;
    int assignment_array[NCLL] = {0};

    //read input
    for (i = 0; i < NCLL; i++) {
        scanf("%d", &grid[i]);
    }

    //print sudoku in a nicer format
    unknown_count = print_grid(grid);
    printf("\n%d cells are unknown", unknown_count);

    //check for invalid inputs
    if (check_grid(grid) == ERROR) {
        exit(EXIT_FAILURE);
    }

    //attempt strategy 1, keep looping if changes were made
    while (changes_made == TRUE && unknown_count > 0) {
        changes_made = strategy1(grid, &unknown_count, assignment_array);
        reset_array(assignment_array, NCLL);
    }

    // final output
    print_grid(grid);
    printf("\n %d cells are unknown", unknown_count);
    if (!unknown_count) {
        printf("\n\nta daa!!!\n");
    }

	/* all done, so pack up bat and ball and head home */
	return 0;
	//algorithms are fun
}

/****************************************************************/

/* prints the sudoku in nicer format,
 and returns number of empty cells.
*/
int print_grid(int grid[]) {
    int unknown_count = 0;
    int i;

    printf("\n");

    for (i = 0; i < NCLL; i++) {
        //print value
        if (grid[i] == 0) {
            printf(".");
            unknown_count++;
        }
        else {
            printf("%d", grid[i]);
        }

        //formatting
        if ((i+1)%(NDIM*NDIG)== 0 && i != NCLL - 1) {
            printf("\n------+-------+------\n"); // row divider
        }
        else if ((i+1)%NDIG == 0) {
            printf("\n"); // new row
        }
        else if ((i+1)%NDIM == 0) {
            printf(" | "); //column divider
        }
        else {
            printf(" ");
        }
    }

    return unknown_count;
}

/* checks if there are invalid cells combinations,
returns TRUE if none and ERROR otherwise*/
int check_grid(int grid[]) {

    int cell_value;
    int set_number;
    int cell_check;
    int value;
    int count_array[NDIG];
    int set_violations = 0;
    int has_violation;
    int total_violations = 0;

    fill_c2s();

    printf("\n");

    //check every set for possible violations
    for (set_number = 0; set_number < NSET; set_number++) {
        reset_array(count_array, NDIG);
        for (cell_check = 0; cell_check < NDIG; cell_check++) {
            cell_value = grid[s2c[set_number][cell_check]];
            if (cell_value) {
                //record frequency of specific value
                count_array[--cell_value]++;
            }
        }

        has_violation = FALSE;

        for (value = 0; value<NDIG; value++) {
            //violations present
            if (count_array[value] > 1) {
                has_violation = TRUE;
                total_violations++;
                printf("\nset %2d ", set_number);
                if (set_number <= LAST_ROW ) {
                    printf("(row %d):", set_number + 1);
                }
                else if (set_number <= LAST_COLUMN) {
                    printf("(col %d):", set_number - LAST_ROW);
                }
                else {
                    printf("(sqr %d):", set_number - LAST_COLUMN);
                }
                printf(" %d instances of %d", count_array[value], value + 1);
            }
        }

        if (has_violation) {
            set_violations++;
        }
    }

    if (has_violation) {
        printf("\n\n%d different sets have violations\n", set_violations);
        printf("%d violations in total\n", total_violations);
        return ERROR;
    }

    return TRUE;
}

//reset array for next use
void reset_array(int array[], int buddy) {
    int i;
    for (i = 0; i < buddy; i++) {
        array[i] = 0;
    }
}

/*goes through each cell and fills it in if only one possible value,
returns if any changes were made to grid*/
int strategy1(int grid[], int* unknown_count, int assignment_array[]) {

    int possible_values[NDIG] = {0};
    int num_of_possible;
    int first_possible;
    int possible_value;
    int changes_made = FALSE;
    int cell_value;
    int i;
    int set;
    int cell;

    //consider every empty cell
    for (i = 0; i < NCLL; i++) {
        if (grid[i]) {
            continue;
        }

        // loop for every cell related to current cell
        for (set = 0; set < NGRP; set++) {
            for (cell = 0; cell < NDIG; cell++) {
                cell_value = grid[s2c[c2s[i][set]][cell]];
                if (cell_value) {
                    possible_values[cell_value - 1] = TRUE;
                }
            }
        }

        //check possible values
        first_possible = 0;
        num_of_possible = 0;
        for (possible_value = 0; possible_value < NDIG; possible_value++) {
            if (!possible_values[possible_value]) {
                num_of_possible++;
                if (!first_possible) {
                    first_possible = possible_value + 1;
                }
            }
        }

        //assign value if only one possibility
        if (num_of_possible == 1) {
            assignment_array[i] = first_possible;
            changes_made = TRUE;
        }
        reset_array(possible_values, NDIG);
    }

    if (changes_made == TRUE) {
        printf("\nstrategy one\n");
    }

    for (i = 0; i < NCLL; i++) {
        //report and make change if there are any to be made
        if (assignment_array[i]) {
            grid[i] = assignment_array[i];
            *unknown_count -= 1;
            printf("row %d col %d must be %d\n", rownum(i), colnum(i),
                   grid[i]);
        }
    }

    return changes_made;
}

