#include <iostream>
#include <array>

const int BOARD_HEIGHT = 5;
const int BOARD_WIDTH = 5;

// Easiest way to store two points ¯\_(-.-)_/¯
struct Move {
	int x, y;
};

// Array of tuples containing the valid relative moves
const std::array<Move, 8> validMoves = {
		(2, 1),
		(2, -1),
		(-2, 1),
		(-2, -1),
		(1, 2),
		(1, -2),
		(-1, 2),
		(-1, -2)
};

struct Board {
	std::array<std::array<int, BOARD_WIDTH>, BOARD_HEIGHT> array = {};

	/**
	 * @param column
	 * @param row
	 * @return reference to the position
	 */
	int &at(int column, int row) {
		return array[row][column];
	}
};

std::ostream &operator<<(std::ostream &stream, Board &board) {

	for (int row = 0; row < board.array.size(); row++) {

		for (int column = 0; column < board.array.at(row).size(); column++) {

			const int position = board.at(column, row);

			// Need to prepend a 0
			if (position <= 9) {
				stream << "0" << position;
			} else stream << position;

			// This puts spaces between each entry and none at the end of a row,,,
			stream << (column < board.array.at(row).size() - 1 ? " " : "");
		}
		stream << "\n";
	}

	return stream;
}

/** ================================================================
(* Recursively solves the knights tour using brute force
 * Prints any solutions it finds.
 *
 * @param board - the board we’re working with (contains all moves-to-date)
 * @param row   - row we’re going to attempt to place the knight on this move.
 * @param column   - column we’re going to attempt to place the knight on this move.
 * @param currentMoveNumber - the move# we’re making (1=first move)
 *
 * @return The number of solutions the given board and move leads to
 * =================================================================
 */
int solveKnightsTour(Board board, int row, int column, int currentMove = 1) {
	// Move outside bounds of the board
	if (row > BOARD_WIDTH || column > BOARD_HEIGHT) return 0;

	// Check current move and increment after
	if (currentMove++ == 1) {
		board.at(column, row) = currentMove - 1;
		return solveKnightsTour(board, row, column, currentMove);
	}

	// Try each valid move
	for (const auto [x, y]: validMoves) {
//		auto temp = solveKnightsTour(board, row + x, column + y, currentMove);

	}

	std::cout << board;
	return 0;
}

int main() {
	using std::cout;

	Board board;

	// Gets roughly the center of the board for all odd numbers
	// close to center for all even
	int knightX = board.array[0].size() / 2;
	int knightY = board.array.size() / 2;

	cout << "Welcome to the Knight’s Tour solver!\n";
	cout << "Starting position (" << knightX + 1 << ", " << knightY + 1 << ")\n";
	cout << "Calculating...\n" << std::endl;
	solveKnightsTour(board, knightY, knightX);

	return 0;
}
