/***************************************/
/* Luke McDougall -- CS241             */
/* Lab 4: Sudoku Solver                */
/* 08/01/21                            */
/***************************************/
#include <stdio.h>

int scanPuzzle(int puzzle[9][9]);
int isSafe(int puzzle[9][9], int index, int num);
int checkForError(int puzzle[9][9]);
int solvePuzzle(int puzzle[9][9], int index);
int noSolution(int puzzle[9][9]);
void printPuzzle(int puzzle[9][9]);

int main (void)
{
  int puzzle[9][9];
  int index = 0;
  int error;

  while ((error = scanPuzzle(puzzle)) != EOF)
  {
    error += checkForError(puzzle);

    if (error)
    {
      printf("Error\n\n");
    } 
    else
    {
      solvePuzzle(puzzle, index);
      if (!noSolution(puzzle))
      {
        printPuzzle(puzzle);
      }
    }
  }
  return 0;
}


/* scanPuzzle() fills the 9x9 2Darray for the puzzle scaned from the standard
   input. If an incorrect value is found and/or the puzzle is longer/shorter than 81 
   chars an error is returned.
 */
int scanPuzzle(int puzzle[9][9])
{
  int currentNum;
  int row;
  int col;
  int error = 0;

  int i;
  for (i = 0; (currentNum = getchar()) != '\n'; i++)
    {
      if (currentNum == EOF)
      {
        return EOF;
      }
      putchar(currentNum);
      if ((currentNum < '1' || currentNum > '9') && (currentNum != '.'))
      {
        error = 1;
      }
      if (currentNum == '.')
      {
        currentNum = '0';
      } 

      row = (i / 9) % 9;
      col = i % 9;
      puzzle[row][col] = currentNum - '0';
    }
  putchar('\n');
  if (i != 81)
  {
    error = 1;
  }
  return error;
}

/* isSafe() checks if the variable num is a valid number to be added into
   the puzzle the the specified index.
 */
int isSafe(int puzzle[9][9], int index, int num)
{
  int i, j;
  int row = index / 9;
  int col = index % 9;
  int boxStartRow = row - (row % 3);
  int boxStartCol = col - (col % 3);

  for (i = 0; i < 9; i++)
  {
    if (puzzle[row][i] == num)
    {
      return 0;
    }
  }
          
  for (i = 0; i < 9; i++)
  {
    if (puzzle[i][col] == num)
      {
        return 0;
      }
  }
 
  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 3; j++)
    {
      if (puzzle[boxStartRow + i][boxStartCol + j] == num)
      {
        return 0;
      }
    }
  }

  return 1;
}

/* checkForError() function checks to see if there is a duplicate entry in any
  row, column, and 3x3 box. If an error is found 1 is returned if no error
  was found, 0 is returned.
 */
int checkForError(int puzzle[9][9])
{
  int row;
  int col;
  int i;
  int j;
  
  for (row = 0; row < 9; row++)
  {
    for (col = 0; col < 9; col++)
    {
      for (i = col + 1; i < 9; i++)
      {
        if ( (puzzle[row][col] != 0) && (puzzle[row][col] == puzzle[row][i]) )
        {
          return 1;
        }
      }
    }
  }

  for (col = 0; col < 9; col++)
  {
    for (row = 0; row < 9; row++)
    {
      for (i = row + 1; i < 9; i++)
      {
        if ( (puzzle[row][col] != 0) && (puzzle[row][col] == puzzle[i][col]) )
        {
          return 1;
        }
      }
    }
  }

  for (row = 0; row < 9; row += 3)
  {
    for (col = 0; col < 9; col += 3)
    {
      for (i = 0; i < 9; i++)
      {
        for (j = i + 1; j < 9; j++)
        {
          if ( (puzzle[row + i / 3][col + i % 3] != 0) &&
               (puzzle[row + i / 3][col + i % 3] ==
                puzzle[row + j / 3][col + j % 3]) )
            {
              return 1;
            }
        }
      }
    }
  }
  return 0;
}

/* noSolution() checks to see if the puzzle returned from
   solvePuzzle doesn't have any 0's. If the puzzle does not have a solution, 
   it prints "No solution".
 */
int noSolution(int puzzle[9][9])
{
  int row;
  int col;

  for (row = 0; row < 9; row++)
  {
    for (col = 0; col < 9; col++)
    {
      if (!puzzle[row][col])
      {
        printf("No solution\n\n");
        return 1;
      }
    }
  }
  return 0;
}


/* printPuzzle() prints the puzzle from the 2D array 
 */
void printPuzzle(int puzzle[9][9])
  {
    int row;
    int col;

    for (row = 0; row < 9; row++)
      {

        for (col = 0; col < 9; col++)
          {
            if (puzzle[row][col])
            {
              printf("%d", puzzle[row][col]);
            } 
            else
            {
              printf(".");
            }
          }
      }
    printf("\n\n");
  }


/* solvePuzzle() recursively solves the puzzle once the puzzle has been
   checked for any errors
 */
int solvePuzzle(int puzzle[9][9], int index)
{
  int num;
  int row = index / 9;
  int col = index % 9;

  if (index == 81)
  {
    return 1;
  }
  
  if (puzzle[row][col] != 0)
  {
    return solvePuzzle(puzzle, ++index);
  }

  else
  {
    for (num = 1; num <= 9; num++)
    {
      if (isSafe(puzzle, index, num))
      {
        puzzle[row][col] = num;
        if (solvePuzzle(puzzle, index))
        {
          return 1;
        }
        puzzle[row][col] = 0;
      }
    }
    return 0;    
  }
}
