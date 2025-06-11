#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* MY HELPER FUNCTIONS */

/**
 * Checks if a cell in the sudoku board is empty.
 *
 * This function checks whether a specific cell on the sudoku board is empty, with '.'
 * representing empty cells.
 *
 * @param row - the row index of the cell (0-8).
 * @param column - the column index of the cell (0-8).
 * @param board - a 9x9 character array representing the sudoku board.
 *
 * @return true - if the cell is empty, otherwise, return false if it contains a digit.
 */
bool is_cell_empty(int row, int column, const char board[9][9])
{
  return board[row][column] == '.';
}

/**
 * Checks if coordinates are within valid board bounds.
 *
 * This function verifies that the given row and column indices are within the valid
 * range for a 9x9 sudoku board (0-8 for both row and column).
 *
 * @param row - the row index to check (should be 0-8).
 * @param column - the column index to check (should be 0-8).
 *
 * @return true - if both row and column are within bounds, otherwise false.
 */
bool are_coordinates_valid(int row, int column)
{
  return (row >= 0 && row < 9 && column >= 0 && column < 9);
}

/**
 * Checks if a digit is in valid range.
 *
 * This function verifies that the given digit character is within the valid range
 * for sudoku ('1' to '9').
 *
 * @param digit - the character digit to validate.
 *
 * @return true - if digit is between '1' and '9', otherwise false.
 */
bool is_digit_valid(char digit)
{
  return (digit >= '1' && digit <= '9');
}

/**
 * Checks if a digit already exists in the specified row.
 *
 * This function searches through all columns in a given row to determine if
 * the specified digit already exists there.
 *
 * @param row - the row index to check (0-8).
 * @param digit - the digit character to search for.
 * @param board - a 9x9 character array representing the sudoku board.
 *
 * @return true - if the digit exists in the row, otherwise false.
 */
bool is_digit_in_row(int row, char digit, const char board[9][9])
{
  for (int col = 0; col < 9; col++) 
  {
    if (board[row][col] == digit) 
    {
      return true;
    }
  }
  return false;
}

/**
 * Checks if a digit already exists in the specified column.
 *
 * This function searches through all rows in a given column to determine if
 * the specified digit already exists there.
 *
 * @param column - the column index to check (0-8).
 * @param digit - the digit character to search for.
 * @param board - a 9x9 character array representing the sudoku board.
 *
 * @return true - if the digit exists in the column, otherwise false.
 */
bool is_digit_in_column(int column, char digit, const char board[9][9])
{
  for (int row = 0; row < 9; row++) 
  {
    if (board[row][column] == digit) 
    {
      return true;
    }
  }
  return false;
}

/**
 * Checks if a digit can be placed in a 3x3 subgrid and ensures the placement isn't invalid.
 *
 * This function checks that a specified digit does not already exist in the 3x3 subgrid
 * containing the specific row and column. The board is divided into nine 3x3 subgrids, and this
 * function ensures that the digit is unique for this particular subgrid.
 *
 * @param row - the row index of the cell (0-8).
 * @param column - the column index of the cell (0-8).
 * @param digit - the digit being checked within the 3x3 subgrid (1-9).
 * @param board - a 9x9 character array representing the sudoku board.
 *
 * @return true - if the digit exists in the 3x3 subgrid, otherwise false.
 */
bool is_digit_in_subgrid(int row, int column, char digit, const char board[9][9])
{
  // Calculate the starting position of the 3x3 subgrid
  int start_row = (row / 3) * 3;
  int start_column = (column / 3) * 3;
  
  // Loop checks each 3x3 subgrid of a cell and returns true if the digit
  // is already placed there
  for (int i = start_row; i < start_row + 3; i++) 
  {
    for (int j = start_column; j < start_column + 3; j++) 
    {
      if (board[i][j] == digit) 
      {
        return true;
      }
    }
  }
  return false; // Return false if the digit is unique in the 3x3 subgrid
}

/**
 * Comprehensive validation function for move validity.
 *
 * This function combines all the validation checks needed to determine if a move
 * is valid in sudoku. It checks coordinates, digit validity, whether a cell is empty,
 * and whether there are any conflicts in row, column, and subgrid.
 *
 * @param row - the row index of the cell (0-8).
 * @param column - the column index of the cell (0-8).
 * @param digit - the digit character to be placed.
 * @param board - a 9x9 character array representing the sudoku board.
 *
 * @return true - if the move is valid, otherwise false.
 */
bool is_move_valid(int row, int column, char digit, const char board[9][9])
{
  return are_coordinates_valid(row, column) &&
         is_digit_valid(digit) &&
         is_cell_empty(row, column, board) &&
         !is_digit_in_row(row, digit, board) &&
         !is_digit_in_column(column, digit, board) &&
         !is_digit_in_subgrid(row, column, digit, board);
}

/**
 * Finds the next empty cell on the sudoku board and updates the row and column.
 *
 * This function finds the next empty cell on the 9x9 sudoku board (i.e., a cell
 * containing a '.'). Once this is found, it updates the row and column parameters to
 * the coordinates of this cell. This begins at the top left (i.e., 'A1') and continues right
 * (next, to 'A2') and once the end of a row is reached (i.e., 'A8'), we then drop down to the
 * next row (next, to 'B1'). It stops at the first empty cell found.
 *
 * @param row - a reference to the row index of the cell that will be updated to the empty
 *        cell's row.
 * @param column - a reference to the column index of the cell that will be updated to the empty
 *        cell's column.
 * @param board - a 9x9 character array representing the sudoku board, with '.' representing empty cells.
 *
 * @return true - if an empty cell is found, false if no empty cells remain.
 */
bool find_next_empty_cell(int& row, int& column, const char board[9][9])
{
  // Loop through each cell and find the coordinates of the first empty cell 
  for (int r = 0; r < 9; r++) 
  {
    for (int c = 0; c < 9; c++) 
    {
      if (is_cell_empty(r, c, board)) 
      { 
        // If an empty cell is found, update row and column and return true
        row = r;
        column = c;
        return true; // Ensures we exit after we find the first empty cell
      }
    }
  }
  return false; // No empty cell found - board is complete
}

/* QUESTION 1 */

/**
 *  Checks if all positions on the board are filled with valid digits.
 *
 *  This function iterates over each cell in a 9x9 sudoku board and verifies
 *  if each cell contains a digit from '1' to '9'. If any cell is empty or
 *  contains an invalid character, the function returns false, showing that
 *  the board is incomplete. If every cell has a valid digit, it returns true.
 *
 *  @param board - a 9x9 character array representing the Sudoku board. Each
 *         cell should contain a character digit from '1' to '9'.
 *
 *  @return true - if all cells contain valid digits ('1' to '9'), false otherwise.
 */
bool is_complete(const char board[9][9])
{
  // Loop through each cell and return false if any cell within the board
  // contains an invalid digit (not between '1' and '9')
  for (int row = 0; row < 9; row++) 
  {
    for (int column = 0; column < 9; column++) 
    {
      if (!is_digit_valid(board[row][column])) 
      {
        return false;
      }
    }
  }
  return true;
}

/* QUESTION 2 */

/**
 * Attempts to place a digit on a specific position on the Sudoku board.
 *
 * This function checks the validity of a move in a 9x9 Sudoku grid. The
 * position string (e.g., 'A1') is converted into row and column indices.
 * The function then verifies:
 *      - Whether the digit is within the valid range ('1' to '9')
 *      - Whether the position indices are valid (within bounds of the board)
 *      - Whether the digit is not already in the specified row or column
 *      - Whether the cell already holds a digit
 *      - Whether the digit does not already appear in the 3x3 subgrid
 *
 * If all checks pass, the digit is placed on the board, and the function
 * returns true. Otherwise, the function returns false.
 *
 * @param position - a string indicating the specific cell, within 'A' and 'I'
 *        as rows and '1'-'9' as columns.
 * @param digit - the character representing the digit to be placed (must be '1'
 *        to '9').
 * @param board - a 9x9 character array representing the current state of the
 *        Sudoku board.
 *
 * @return true - if the move is valid and the digit was successfully placed,
 *         otherwise, return false.
 */
bool make_move(const char* position, const char digit, char board[9][9])
{
  // Convert position string variable to a row integer and column integer index
  const int row = position[0] - 'A';
  const int column = position[1] - '1';

  // Use centralized validation function to check all conditions
  if (!is_move_valid(row, column, digit, board)) 
  {
    return false;
  }

  // If none of the above apply, place the digit in the sudoku 
  board[row][column] = digit;
  return true;
}

/* QUESTION 3 */

/**
 * Saves the current state of the sudoku board to a file.
 *
 * This function writes the content of a 9x9 sudoku board to a specified file.
 * Each cell in the board array is written to the file with each row on a new
 * line. It does the following:
 *      - Opens the output file stream with the given filename.
 *      - Checks if the file stream opened successfully.
 *      - Writes each cell to the file, separating rows by new lines.
 *      - Closes the file and verifies if there were any output errors.
 *
 * @param filename - a C-string representing the name of the file to save the
 *        board to.
 * @param board - a 9x9 character array representing the sudoku board state.
 *
 * @return true - if the board was successfully saved, otherwise, return false if an error occurred.
 */
bool save_board(const char filename[], const char board[9][9])
{
  ofstream out_stream;

  // Open the output-file stream 
  out_stream.open(filename);

  // Check whether the stream opened successfully 
  if (out_stream.fail()) 
  {
    return false;
  }

  // Loop that outputs each cell value into the file
  for (int row = 0; row < 9; row++) 
  {
    for (int column = 0; column < 9; column++) 
    {
      out_stream.put(board[row][column]);
    }
    out_stream << endl;
  }

  // Close the stream
  out_stream.close();

  // Check again that there has not been any output errors 
  if (out_stream.fail()) 
  {
    return false;
  }

  // If no failure exists, the file has been successfully saved and return true 
  return true;
}

/* QUESTION 4 */

/**
 * Recursively attempt to solve the sudoku board.
 *
 * This function employs a recursive 'backtracking' algorithm to solve the sudoku board.
 * It starts by finding the next empty cell and trying each possible digit ('1' to '9') in
 * that particular cell. For each digit, it verifies if the move is valid and, if so, places
 * the digit. The function then calls itself recursively to attempt to solve the rest of the
 * board.
 *
 * If a valid solution is found, it returns true. If an invalid state is reached, it backtracks
 * by removing the digit and trying the next one. If all digits fail for a cell, the function
 * returns false, indicating that the board has no possible solutions.
 *
 * @param board - a 9x9 character array representing the current board state.
 *
 * @return true - if a solution is found and the board is solved, otherwise, return false, if
 *         the board cannot be solved.
 */
bool solve_board(char board[9][9])
{
  int row, column;
  
  // If no empty cell found, the sudoku is already solved, so we return true
  if (!find_next_empty_cell(row, column, board)) 
  {
    return true;
  }

  // For this empty cell, try every valid digit ('1' - '9') and if it is valid, place it in the cell 
  for (char digit = '1'; digit <= '9'; digit++) 
  {
    if (is_move_valid(row, column, digit, board)) 
    { // If the digit is valid for the cell, place it 
      board[row][column] = digit; // Place the digit
      if (solve_board(board)) 
      { // Attempt to recursively solve the board with the placement  
        return true; // Solution has been found
      }
      board[row][column] = '.'; // Reset the cell if the digit didn't get a solution and backtrack
    }
  }
  return false; // Otherwise, the board has no solutions and is impossible to solve,
                // given we've tried every valid digit 
}

/* QUESTION 5 */

/**
 * Attempts to solve the sudoku board and counts the number of backtracking steps.
 *
 * This polymorphic version of solve_board applies a recursive backtracking algorithm to solve a 9x9 sudoku
 * board while counting how many times the function 'backtracks' due to an invalid move (i.e., when it has to
 * remove a previously placed digit and try a new, potentially valid one.
 *
 * @param board - a 9x9 character array representing the sudoku board, with '.' representing empty cells.
 * @param count - an integer reference used to count the number of backtracking steps. This value increments
 *                each time that the function backtracks.
 *
 * @return true - if the board is successfully solved, otherwise, return false if no solution is found.
 */
bool solve_board(char board[9][9], int& count)
{
  int row, column;

  // If no empty cell found, the sudoku is already solved, so we return true
  if (!find_next_empty_cell(row, column, board)) 
  {
    return true;
  }

  // Try each digit (1-9) in the empty cell
  for (char digit = '1'; digit <= '9'; digit++) 
  {
    // Check if the move is valid and if so, place the valid digit in the cell
    if (is_move_valid(row, column, digit, board)) 
    {
      board[row][column] = digit; // Place digit in the cell
      if (solve_board(board, count)) 
      { // Recursively try to solve the board with this placement
        return true; // Solution has been found
      }

      // If no solution has been found, we backtrack
      count++; // Increment count for each backtracking step taken
      board[row][column] = '.'; // Reset the cell 
    }
  }
  return false; // Otherwise, return false as we couldn't find a solution
}

/**
 * Counts the total number of valid moves for each cell in the sudoku board.
 *
 * This function iterates over each cell on the sudoku board and calculates the number of valid moves that
 * are available. Each time a valid digit is found for a particular cell, the counter is incremented.
 *
 * @param board - a 9x9 character array representing the sudoku board.
 *
 * @return the total count of all valid moves for the current board state.
 */
int total_valid_moves(const char board[9][9])
{
  int valid_move_counter = 0;

  // Loop through each board cell and count the number of valid moves 
  for (int row = 0; row < 9; row++) 
  {
    for (int column = 0; column < 9; column++) 
    {
      // Only check empty cells for valid moves
      if (is_cell_empty(row, column, board)) 
      {
        for (char digit = '1'; digit <= '9'; digit++) 
        {
          if (is_move_valid(row, column, digit, board)) 
          {
            valid_move_counter++;
          }
        }
      }
    }
  }
  return valid_move_counter;
}

/**
 * Checks if a specified digit can be validly placed at a given position on the sudoku board.
 *
 * This overloaded version of 'make_move' accepts integer parameters for the row, column and digit,
 * which allows us to check whether a digit's placement is valid without actually changing the board. We
 * do not want to update the board with a new move, but instead, just check if the actual move is 
 * hypothetically valid.
 *
 * @param row - an integer representing the row index of the cell (0-8).
 * @param column - an integer representing the column index of the cell (0-8).
 * @param digit - an integer representing the digit to be placed on the board (1-9)
 * @param board - a 9x9 character array representing the current sudoku board state.
 *
 * @return true - if the digit can be validly placed in the specified cell according to the previous make_move
 *                function rules for a 'valid move'. Otherwise, return false.
 */
bool make_move(int row, int column, int digit, const char board[9][9])
{
  char digit_char = '0' + digit; // Convert integer digit to its corresponding character
  return is_move_valid(row, column, digit_char, board);
}