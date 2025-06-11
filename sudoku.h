#ifndef SUDOKU_H
#define SUDOKU_H

/* PREDEFINED HELPER FUNCTIONS */

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

/* FUNCTIONS MENTIONED IN SPEC */

/**
 * Checks if the sudoku board is fully complete (all cells are filled).
 *
 * This function iterates through each cell on the sudoku board to check if every cell
 * contains a digit.
 *
 * @param board - a 9x9 character array representing the current state of the sudoku board.
 *
 * @return true - if all cells contain digits, otherwise, return false if a
 *         cell is empty.
 */

bool is_complete(const char board[9][9]);




/**
 * Attempts to place a digit at a specified position on the board.
 *
 * This function checks if a specified digit can be placed at a given
 * position on the board (given as a string, e.g., 'C3'), and places it
 * if valid.
 *
 * @param position - a constant character pointer representing the cell
 *        position (e.g., 'D6').
 * @param digit - a character representing the digit to be placed.
 * @param board - a 9x9 character array representing the sudoku board.
 *
 * @return true - if the move is valid. Otherwise, it returns false.
 */

bool make_move(const char* position, const char digit, char board[9][9]);




/**
 * Saves the current state of the sudoku board to a file.
 *
 * This function writes the content of the sudoku board to a file, but still
 * keeps the current board state intact.
 *
 * @param filename - a constant character array for the output-file path.
 * @param board - a 9x9 character array representing the current sudoku board.
 *
 * @return true - if the board is successfully saved. Otherwise, it returns false.
 */

bool save_board(const char filename[], const char board[9][9]);




/**
 * Attempts to solve the sudoku board.
 *
 * This function uses a recursive backtracking algorithm to solve the sudoku board by
 * filling empty cells with valid digits.
 *
 * @param board - a 9x9 character array representing the current sudoku board.
 *
 * @return true - if the board is successfully solved. Otherwise, it returns false.
 */

bool solve_board(char board[9][9]);




/**
 * Solves the sudoku board and counts the number of recursive calls made.
 *
 * This function is an overloaded version of 'solve_board' that both solves the board
 * and counts the number of recursive calls made during the solving process.
 *
 * @param board - a 9x9 character array representing the current sudoku board.
 * @param count - an integer reference that will store the recursion count.
 *
 * @return true - if the board is successfully solved. Otherwise, it returns false if no
 *         solution is found.
 */
 
bool solve_board(char board[9][9], int& count);




/**
 * Counts the number of valid moves available on the board.
 *
 * This function iterates through each cell and counts the number of valid moves based on the
 * previously established validity rules in the make_move function from Question 2.
 *
 * @param board - a 9x9 character array representing the current sudoku board.
 *
 * @return the total number of valid moves available on the board as an integer.
 */
 
int total_valid_moves(const char board[9][9]);




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

bool is_cell_empty(int row, int column, const char board[9][9]);




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
bool are_coordinates_valid(int row, int column);




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
bool is_digit_valid(char digit);




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
bool is_digit_in_row(int row, char digit, const char board[9][9]);




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
bool is_digit_in_column(int column, char digit, const char board[9][9]);




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
bool is_digit_in_subgrid(int row, int column, char digit, const char board[9][9]);




/**
 * Function for move validity.
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
bool is_move_valid(int row, int column, char digit, const char board[9][9]);




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
bool find_next_empty_cell(int& row, int& column, const char board[9][9]);




/**
 * Checks if a specified digit can be validly placed at a given position on the sudoku board.
 *
 * This overloaded version of 'make_move' accepts integer parameters for the row, column and digit,
 * which allows us to check whether a digit's placement is valid without actually changing the board. We
 * do not want to update the board with a new move, but rather, just check if the actual move is 
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
bool make_move(int row, int column, int digit, const char board[9][9]);

#endif