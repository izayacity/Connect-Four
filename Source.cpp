#include<iostream>
#include<vector>
using namespace std;

class connectFour {
private:
	int cols;
	int rows;
	int pieces;          //indicates how many pieces to win, range from 4 to 6
	int removeMode;      //flag for turning on bottom remove mode or not
public:
	vector< vector <char> > square;    //used as the game board;
	vector< vector <char> > position;  //used for storing the top position for each column and iterator
									   //define this vector because vector square has been initialized by '.'

	int gamePlay ();
	int isFull ();
	int isWin (int, int);    //parameters are cols and rows. will check the zone [1-pieces, pieces-1]^2 around a piece
	int checkRemove ();      //turn on bottom remove mode or not
	int xMove ();            //insert a piece X
	int oMove ();            //insert a piece O
	int xRemove ();          //remove a piece X
	int oRemove ();          //remove a piece O
	void printSquare ();
	void clearSquare ();
	void init ();
};

void connectFour::printSquare () {
	cout << endl;

	for (int j = 0; j < rows; j++) {
		for (int i = 0; i < cols; i++) {
			cout << square[i][j];
		}
		cout << endl;
	}
}

void connectFour::clearSquare () {
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			square[i][j] = '.';
		}
		square[i][0] = '1' + i;
		position[i].clear ();
	}
}

int connectFour::isFull () {
	for (int i = 0; i < cols; i++) {
		if (square[i][1] == '.')
			return 0;
	}
	return 1;
}

int connectFour::isWin (int col, int pos) {
	char player = square[col][pos]; //player role
	int count = 0;
	int i, j;

	// Vertical check
	for (j = ((pos - pieces + 1) > 0 ? (pos - pieces + 1) : 0); j <= pos + pieces - 1 && j < rows; j++) {
		if (square[col][j] == player)
			count++;
		else
			count = 0;

		if (count >= pieces)
			return 1;
	}

	// Horizontal check
	for (i = ((col - pieces + 1) > 0 ? (col - pieces + 1) : 0), count = 0; i <= col + pieces - 1 && i < cols; i++) {
		if (square[i][pos] == player)
			count++;
		else
			count = 0;

		if (count >= pieces)
			return 1;
	}

	// top-left to bottom-right - right diagonals
	for (int colStart = 1; colStart < cols - pieces + 1; colStart++) {
		for (i = colStart, j = 1, count = 0; i < cols && j < rows; i++, j++) {
			if (square[i][j] == player) {
				count++;
				if (count >= pieces) return 1;
			} else {
				count = 0;
			}
		}
	}

	// top-left to bottom-right - left diagonals
	for (int rowStart = 1; rowStart < rows - pieces + 1; rowStart++) {
		for (i = 0, j = rowStart, count = 0; i < cols && j < rows; i++, j++) {
			if (square[i][j] == player) {
				count++;
				if (count >= pieces) return 1;
			} else {
				count = 0;
			}
		}
	}

	// top-right to bottom-left - right diagonals
	for (int rowStart = 1; rowStart < rows - pieces + 1; rowStart++) {
		for (i = cols - 1, j = rowStart, count = 0; i >= 0 && j < rows; i--, j++) {
			if (square[i][j] == player) {
				count++;
				if (count >= pieces) return 1;
			} else {
				count = 0;
			}
		}
	}

	// top-right to bottom-left - left diagonals
	for (int colStart = cols - 2; colStart >= pieces - 1; colStart--) {
		for (i = colStart, j = 1, count = 0; i >= 0 && j < rows; i--, j++) {
			if (square[i][j] == player) {
				count++;
				if (count >= pieces) return 1;
			} else {
				count = 0;
			}
		}
	}

	return 0;
}

int connectFour::checkRemove () {
	if (removeMode) {
		cout << "Remove(a) or Insert a piece(b)? Default answer is b if wrong input" << endl;
		char ans;
		cin >> ans;
		if (tolower (ans) == 'a') {
			return 1;
		} else
			return 0;
	} else
		return 0;
}

int connectFour::xMove () {
	cout << "Type the column number to insert a piece: ";
	int col;
	cin >> col;
	cin.ignore (10000, '\n');

	while (cin.fail () || col > cols || col < 1) {
		cout << "I'm sorry, I don't understand. Please try again: ";
		cin.clear ();
		cin.ignore (10000, '\n');
		cin >> col;
		cin.ignore (10000, '\n');
	}

	while (position[col - 1].size () == rows - 1) {
		cout << "This column has been full. Please try another column: ";
		cin >> col;
		cin.ignore (10000, '\n');
	}

	position[col - 1].push_back ('X');
	size_t pos = position[col - 1].size () - 1;
	square[col - 1][rows - pos - 1] = 'X';

	printSquare ();

	if (isWin (col - 1, rows - pos - 1)) {
		return 1;
	} else
		return 0;
}

int connectFour::oMove () {
	cout << "Type the column number to insert a piece: ";
	int col;
	cin >> col;
	cin.ignore (10000, '\n');

	while (cin.fail () || col > cols || col < 1) {
		cout << "I'm sorry, I don't understand. Please try again: ";
		cin.clear ();
		cin.ignore (10000, '\n');
		cin >> col;
		cin.ignore (10000, '\n');
	}

	while (position[col - 1].size () == rows - 1) {
		cout << "This column has been full. Please try another column: ";
		cin >> col;
		cin.ignore (10000, '\n');
	}

	position[col - 1].push_back ('O');

	size_t pos = position[col - 1].size () - 1;
	square[col - 1][rows - pos - 1] = 'O';

	printSquare ();

	if (isWin (col - 1, rows - pos - 1)) {
		return 1;
	} else
		return 0;
}

int connectFour::xRemove () {
	cout << "Type the column number to remove a piece: ";
	int col;
	cin >> col;
	cin.ignore (10000, '\n');

	while (cin.fail () || col > cols || col < 1) {
		cout << "I'm sorry, I don't understand. Please try again: ";
		cin.clear ();
		cin.ignore (10000, '\n');
		cin >> col;
		cin.ignore (10000, '\n');
	}

	while (position[col - 1].size () == 0) {
		cout << "This column is empty. Please try another column: ";
		cin >> col;
		cin.ignore (10000, '\n');
	}

	while (square[col - 1][rows - 1] != 'X') {
		cout << "The piece at the bottom is not your piece X. Please try another column: ";
		cin >> col;
		cin.ignore (10000, '\n');
	}

	for (int j = rows - 1; j >= 2; j--) {
		square[col - 1][j] = square[col - 1][j - 1];
	}
	square[col - 1][1] = '.';
	position[col - 1].erase (position[col - 1].begin ());

	printSquare ();

	vector<char>::iterator pr;
	int pos = 0;
	for (pr = position[col - 1].begin (); pr != position[col - 1].end (); pr++, pos++) {
		if (isWin (col - 1, rows - pos - 1)) {
			return 1;
		}
	}
	return 0;
}

int connectFour::oRemove () {
	cout << "Type the column number to remove a piece: ";
	int col;
	cin >> col;
	cin.ignore (10000, '\n');

	while (cin.fail () || col > cols || col < 1) {
		cout << "I'm sorry, I don't understand. Please try again: ";
		cin.clear ();
		cin.ignore (10000, '\n');
		cin >> col;
		cin.ignore (10000, '\n');
	}

	while (position[col - 1].size () == 0) {
		cout << "This column is empty. Please try another column: ";
		cin >> col;
		cin.ignore (10000, '\n');
	}

	while (square[col - 1][rows - 1] != 'O') {
		cout << "The piece at the bottom is not your piece O. Please try another column: ";
		cin >> col;
		cin.ignore (10000, '\n');
	}

	for (int j = rows - 1; j >= 2; j--) {
		square[col - 1][j] = square[col - 1][j - 1];
	}
	square[col - 1][1] = '.';
	position[col - 1].erase (position[col - 1].begin ());

	printSquare ();

	vector<char>::iterator pr;
	int pos = 0;
	for (pr = position[col - 1].begin (); pr != position[col - 1].end (); pr++, pos++) {
		if (isWin (col - 1, rows - pos - 1)) {
			return 1;
		}
	}
	return 0;
}

void connectFour::init () {
	int i, j;
	removeMode = 0;

	cout << "Let's play Connect Four!" << endl;
	cout << "Do u wanna enable bottom remove mode?(y/n)" << endl;
	char ans;
	cin >> ans;
	if (tolower (ans) == 'y') {
		removeMode = 1;
		cout << "Bottom remove mode is on." << endl;
	} else
		cout << "Bottom remove mode is off." << endl;

	cout << "Columns for the game board(should be an integer between 7 and 10): " << endl;
	cin >> cols;
	while (cin.fail () || cols < 7 || cols > 10) {
		cout << "Columns should be an integer between 7 and 10. Please try again: ";
		cin.clear ();
		cin.ignore (10000, '\n');
		cin >> cols;
	}
	cin.ignore (10000, '\n');

	cout << "Rows for the game board(should be an integer between 7 and 10): " << endl;
	cin >> rows;
	while (cin.fail () || rows < 7 || rows > 10) {
		cout << "Rows should be an integer between 7 and 10. Please try again: ";
		cin.clear ();
		cin.ignore (10000, '\n');
		cin >> rows;
	}
	cin.ignore (10000, '\n');

	cout << "Pieces lined up to win for the game board(should be an integer between 4 and 6): " << endl;
	cin >> pieces;
	while (cin.fail () || pieces < 4 || pieces > 6) {
		cout << "Pieces should be an integer between 4 and 6. Please try again: ";
		cin.clear ();
		cin.ignore (10000, '\n');
		cin >> pieces;
	}
	cin.ignore (10000, '\n');

	square.resize (cols);
	position.resize (cols);

	for (i = 0; i < cols; i++) {
		for (j = 0; j < rows; j++) {
			square[i].push_back ('.');    //MARK: square[i][j] = '.' doesnot work. Vector out of range.
		}
		square[i][0] = '1' + i;
	}
}

int connectFour::gamePlay () {
	init ();
	printSquare ();

	while (1) {
		cout << "Player X's turn!" << endl;
		if (checkRemove ()) {
			if (xRemove ()) {
				cout << "Player X has won the Game!";
				break;
			}
		} else {
			if (xMove ()) {
				cout << "Player X has won the Game!";
				break;
			} else if (isFull ()) {
				cout << "Tie game!";
				break;
			}
		}

		cout << "Player O's turn!" << endl;
		if (checkRemove ()) {
			if (oRemove ()) {
				cout << "Player O has won the Game!";
				break;
			}
		} else {
			if (oMove ()) {
				cout << "Player O has won the Game!";
				break;
			} else if (isFull ()) {
				cout << "Tie game!";
				break;
			}
		}
	}

	cout << "Game over! Do you want to play again? (y/n, default answer is no if wrong input) ";
	char answer;
	cin >> answer;
	cin.ignore (10000, '\n');

	if (answer == 'y') {
		clearSquare ();
		return 1;
	} else {
		return 0;
	}
	return 0;
}

int main () {
	connectFour cnf;
	while (cnf.gamePlay ()) {}
	system ("pause");
	return 0;
}