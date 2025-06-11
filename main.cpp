#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

  char board[9][9];

  /* This section illustrates the use of the pre-supplied helper functions. */
  cout << "============= Pre-supplied functions =============\n\n";
  
  cout << "Calling load_board():\n";
  load_board("easy.dat", board);

  cout << '\n';
	cout << "Displaying Sudoku board with display_board():\n";
  display_board(board);
  cout << "Done!\n\n";

  cout << "=================== Question 1 ===================\n\n";

  load_board("easy.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  load_board("easy-solution.dat", board);
  cout << "Board is ";
  if (!is_complete(board)) {
    cout << "NOT ";
  }
  cout << "complete.\n\n";

  cout << "=================== Question 2 ===================\n\n";
  
  load_board("easy.dat", board);

  // Should be OK
  cout << "Putting '1' into I8 is ";
  if (!make_move("I8", '1', board)) {
    cout << "NOT ";
  }
  cout << "a valid move. The board is:\n\n";
  display_board(board);

  // write more tests

  cout << "\n\n";

  cout << "Using coordinates that are out of range to test our function - ";
  cout << "Putting '2' into J8 is ";
  if (!make_move("J8", '2', board))
    {
    cout << "NOT ";
    }
  cout << "a valid move. The board is:\n\n";
  display_board(board);

  cout << "\n\n";

  cout << "Using values that are out of range to test our function - ";
  cout << "Putting '0' into E4 is ";
  if (!make_move("E4", '0', board))
    {
    cout << "NOT ";
    }
  cout << "a valid move. The board is:\n\n";
  display_board(board);

  cout << "\n\n";

  cout << "Using a digit that is already in that row to test our function - ";
  cout << "Putting '2' into B4 is ";
  if (!make_move("B4", '2', board))
    {
    cout << "NOT ";
    }
  cout << "a valid move. The board is:\n\n";
  display_board(board);

  cout << "\n\n";

  cout << "Using a digit that is already in that column to test our function - ";
  cout << "Putting '6' into G8 is ";
  if (!make_move("G8", '6', board))
    {
    cout << "NOT ";
    }
  cout << "a valid move. The board is:\n\n";
  display_board(board);

  cout << "\n\n";

  cout << "Using a digit that is already in the 3x3 subgrid to test our function - ";
  cout << "Putting '4' into E1 is ";
  if (!make_move("E1", '4', board))
    {
    cout << "NOT ";
    }
  cout << "a valid move. The board is:\n\n";
  display_board(board);

  cout << "\n\n";

  cout << "Using a cell that already holds a digit to test our function - ";
  cout << "Putting '8' into H8 is ";
  if (!make_move("H8", '8', board))
    {
    cout << "NOT ";
    }
  cout << "a valid move. The board is:\n\n";
  display_board(board);

  cout << "\n\n";

  cout << "=================== Question 3 ===================\n\n";

  load_board("easy.dat", board);
  if (save_board("easy-copy.dat", board)) {
    cout << "Save board to 'easy-copy.dat' successful.\n";
  } else {
    cout << "Save board failed.\n";
  }
  cout << '\n';

  cout << "=================== Question 4 ===================\n\n";

  load_board("easy.dat", board);
  if (solve_board(board)) {
    cout << "The 'easy' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("medium.dat", board);
  if (solve_board(board)) {
    cout << "The 'medium' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  // write more tests

  load_board("mystery1.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery1' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("mystery2.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery2' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  load_board("mystery3.dat", board);
  if (solve_board(board)) {
    cout << "The 'mystery3' board has a solution:\n";
    display_board(board);
  } else {
    cout << "A solution cannot be found.\n";
  }
  cout << '\n';

  cout << "=================== Question 5 ===================\n\n";

  cout << "The difficulty of each board is determined by calcuating a board's 'move score' and 'backwards recursion score'.\n\n";
  cout << "The 'move score' calculates how many valid moves there are at the start of the sudoku, as determined by our make_move function.\n\n";
  cout << "The 'backwards recursion score' cumatively counts how many times the solve_board function removed an invalid digit from the board's cells.\n\n";
  
  
  // write more tests

  load_board("easy.dat", board);
  int count = 0;
  cout << "Move score: " << total_valid_moves(board) << endl;
  solve_board(board, count);
  cout << "Backwards recursion score: " << count << endl << endl;

  load_board("medium.dat", board);
  count = 0;
  cout << "Move score: " << total_valid_moves(board) << endl;
  solve_board(board, count);
  cout << "Backwards recursion score: " << count << endl << endl;

  load_board("mystery1.dat", board);
  count = 0;
  cout << "Move score: " << total_valid_moves(board) << endl;
  solve_board(board, count);
  cout << "Backwards recursion score: " << count << endl << endl;

  load_board("mystery2.dat", board);
  count = 0;
  cout << "Move score: " << total_valid_moves(board) << endl;
  solve_board(board, count);
  cout << "Backwards recursion score: " << count << endl << endl;

  load_board("mystery3.dat", board);
  count = 0;
  cout << "Move score: " << total_valid_moves(board) << endl;
  solve_board(board, count);
  cout << "Backwards recursion score: " << count << endl << endl;
	     
  return 0;
}

  
