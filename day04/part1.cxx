#include <vector>
#include <tuple>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

typedef vector<vector<vector<tuple<int, bool>>>> bingo_boards;
typedef vector<vector<tuple<int, bool>>> single_board; 
typedef vector<tuple<int, bool>> board_row;
typedef tuple<int, bool> square;

void print_board(bingo_boards*);

int main()
{
	// Part 1, declare all vars and read complex input
	bingo_boards boards;
	bingo_boards transposed_boards;
	single_board board;
	string numbers = "";
	stringstream ss; 
	
	cin >> numbers;
	cin.ignore();
	ss << numbers;

	string board_line = "";
	getline(cin, board_line); // read useless line

	while (getline(cin, board_line))
	{
		if (board_line == "")
		{
			boards.push_back(board);
			board.clear();
			continue;
		}

		board_row row;
		stringstream ss2(board_line);
		int bingo_square = 0;
		string row_line = "";
	
		while (getline(ss2, row_line))
		{
			stringstream ss3(row_line);
			while (ss3 >> bingo_square)
				row.push_back(make_tuple(bingo_square, false));
		}

		board.push_back(row);
		row.clear();

		if (cin.peek() == EOF)
		{
			boards.push_back(board);
			break;
		}
	}

	// Transpose the boards
	for (int b = 0; b < boards.size(); b++)
	{
		single_board tboard;
		for (int i = 0; i < 5; i++)
		{
			board_row trow;
			for (int j = 0; j < 5; j++)
				trow.push_back(make_tuple(get<0>(boards[b][j][i]), false));
			tboard.push_back(trow);
			trow.clear();
		}

		transposed_boards.push_back(tboard);
		tboard.clear();
	}

	// go through and set all called squares
	string strNum;
	int num = 0;
	int winningBoard = 0;
	bool rowBoardWon = false;
	bool columnBoardWon = false;
	int boardNum = 0;
	int winningRowBoard = 0;
	int winningColumnBoard = 0;
	while (getline(ss, strNum, ','))
	{
		num = stoi(strNum);
		for (int boardNum = 0; boardNum < boards.size(); boardNum++)
		{
			// Set the appropriate squares to true
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (get<0>(boards[boardNum][i][j]) == num)
						get<1>(boards[boardNum][i][j]) = true;

					if (get<0>(transposed_boards[boardNum][j][i]) == num)
						get<1>(transposed_boards[boardNum][j][i]) = true;
				}
			}

			// After each number is set we must check if there is a win along a row or a column
			for (int i = 0; i < 5; i++)
			{
				if (all_of(boards[boardNum][i].begin(), boards[boardNum][i].end(), [&](square sq) { return get<1>(sq); }))
				{
					rowBoardWon = true;
					break;
				}
			}
			
			if (rowBoardWon)
			{
				winningRowBoard = boardNum;
				break;
			}

			// Check column winners
			for (int i = 0; i < 5; i++)
			{
				if (all_of(transposed_boards[boardNum][i].begin(), transposed_boards[boardNum][i].end(), [&](square sq) { return get<1>(sq); }))
				{
					columnBoardWon = true;
					break;
				}
			}

			if (columnBoardWon)
			{
				winningColumnBoard = boardNum;
				break;
			}
		}

		if (rowBoardWon || columnBoardWon)
			break;
	}

	winningBoard = (winningRowBoard > winningColumnBoard) ? winningRowBoard : winningColumnBoard;

	int unmarkedSum = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (rowBoardWon)
				unmarkedSum += (get<1>(boards[winningBoard][i][j]) == false) ? get<0>(boards[winningBoard][i][j]) : 0; 
			else
				unmarkedSum += (get<1>(transposed_boards[winningBoard][j][i]) == false) ? get<0>(transposed_boards[winningBoard][j][i]) : 0; 
		}
	}

	cout << (unmarkedSum * num) << endl;

	return 0;
}
