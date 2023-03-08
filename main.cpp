#include <iostream>
#include <array>

const int BOARD_HEIGHT = 5;
const int BOARD_WIDTH = 5;

// Easiest way to store two points ¯\_(-.-)_/¯
struct Move {
	int x, y;
};

// Array of valid moves IE the L shape
const std::array<Move, 8> validMoves = {
		Move{2, 1},
		{2, -1},
		{-2, 1},
		{-2, -1},
		{1, 2},
		{1, -2},
		{-1, 2},
		{-1, -2}
};

class Board {

	using Row = std::array<int, BOARD_WIDTH>;
	// The actual board
	std::array<Row, BOARD_HEIGHT> board = {};

public:

	/**
	 * Wrapper over the array function
	 *
	 * @param column
	 * @param row
	 * @return reference to the position
	 */
	const int &at(int column, int row) const {
		return board.at(row).at(column);
	}

	/**
	 * Exposes the row arrays
	 *
	 * @param row
	 * @return The board row
	 */
	Row &operator[](int row) {
		return board[row];
	}

	/// @return The width of the board (how many columns)
	int width() const {
		return board[0].size();
	}

	/// @return The height of the board (how many rows)
	int height() const {
		return board.size();
	}

	/**
	 * Returns if the passed in row and colum are inside the board
	 *
	 * @param column
	 * @param row
	 * @return In bounds
	 */
	bool isInBounds(int column, int row) const {
		// Move outside bounds of the board
		if (row > width() - 1 || column > height() - 1) return false;
		if (row < 0 || column < 0) return false;

		return true;
	}
};

/**
 * Allows boards to be output to output streams such as cout
 *
 * @param stream
 * @param board
 * @return
 */
std::ostream &operator<<(std::ostream &stream, Board &board) {

	for (int row = 0; row < board.height(); row++) {

		for (int column = 0; column < board.width(); column++) {

			const int position = board.at(column, row);

			// Need to prepend a 0
			if (position <= 9) {
				stream << "0" << position;
			} else stream << position;

			// This puts spaces between each entry and none at the end of a row,,,
			stream << (column < board.width() - 1 ? " " : "");
		}
		stream << "\n";
	}

	return stream;
}

/** ==================================================================
 * Recursively solves the knights tour using brute force
 * Prints any solutions it finds.
 *
 * @param board - the board we’re working with (contains all moves-to-date)
 * @param row   - row we’re going to attempt to place the knight on this move.
 * @param column   - column we’re going to attempt to place the knight on this move.
 * @param currentMoveNumber - the move# we’re making (1=first move)
 *
 * @return The number of solutions the given board and move leads to
 * ==================================================================
 */
int solveKnightsTour(Board board, int row, int column, int currentMove = 1) {
	// This would need to be changed if we want to calculate this more than once per program
	// so in other words I know this wouldn't work out in real life sue me
	static int solution = 1;

	// Move outside bounds of the board
	if (!board.isInBounds(column, row)) return 0;
	// Does this spot already have a move
	if (board.at(column, row) != 0) return 0;

	// Safe to set our move number now
	board[row][column] = currentMove;

	// Final move
	if (currentMove == BOARD_HEIGHT * BOARD_WIDTH) {
		std::cout << "Solution #" << solution++ << "\n";
		std::cout << board << std::endl; // New line and flush
		return 1;
	}

	currentMove++;

	int totalSolutions = 0;
	// Try each valid move
	for (const auto [moveX, moveY]: validMoves) {
		// Accumulate the total totalSolutions
		totalSolutions += solveKnightsTour(board, row + moveY, column + moveX, currentMove);
	}

	return totalSolutions;
}

int main() {
	using std::cout;

	Board board;

	// Gets roughly the center of the board for all odd numbers
	// close to center for all evens
	int knightX = board.width() / 2;
	int knightY = board.height() / 2;

	cout << "Welcome to the Knight’s Tour solver!\n";
	cout << "Starting position (row, col): (" << knightY + 1 << ", " << knightX + 1 << ")\n";
	cout << "Calculating...\n" << std::endl;
	const int solutions = solveKnightsTour(board, knightY, knightX);
	cout << "Total solutions: " << solutions << std::endl;

	return 0;
}
