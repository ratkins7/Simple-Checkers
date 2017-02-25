//============================================================================
// Name        : Simple Checkers
// Author      : Ryan Atkins
// Version     : v1.0
// Copyright   : Your copyright notice
// Description : Simple Checkers
//============================================================================


#include <iostream>
#include "main.hpp"
using namespace std;


void initialize_board(string (&b)[ROWS][COLS]){
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++){
			b[i][j] = "--.";
		}
	}

	// Setup Computer Pieces 	-> X
	b[0][1] = "--X";
	b[0][3] = "--X";
	b[0][5] = "--X";
	b[0][7] = "--X";

	b[1][0] = "--X";
	b[1][2] = "--X";
	b[1][4] = "--X";
	b[1][6] = "--X";

	b[2][1] = "--X";
	b[2][3] = "--X";
	b[2][5] = "--X";
	b[2][7] = "--X";

	// Setup Player Pieces 	-> 0
	b[5][0] = "--0";
	b[5][2] = "--0";
	b[5][4] = "--0";
	b[5][6] = "--0";

	b[6][1] = "--0";
	b[6][3] = "--0";
	b[6][5] = "--0";
	b[6][7] = "--0";

	b[7][0] = "--0";
	b[7][2] = "--0";
	b[7][4] = "--0";
	b[7][6] = "--0";

}


void print_board(string (&b)[ROWS][COLS]){
	cout << endl;

	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++){
			cout << b[i][j];
		}
		cout << "--\n";
	}

	cout << endl;
}


void print_error(){
	cout << flush << endl;
	cin.clear();
	cin.ignore(INT_MAX,'\n');
	cout << "Oops, you entered an invalid move!\n"
			"Please enter an int (the row) followed by\n"
			"pressing space bar followed by an int (the column)" << endl;
}


bool validate_within_limits(int a,int b,int c,int d){
	return a >= 0 && a < ROWS && b >=0 && b <= COLS && c >=0 && c < ROWS && d >=0 && d < COLS;
}


void get_computer_move(int &fr_r, int &fr_c, int &to_r, int &to_c, string (&b)[ROWS][COLS]){

//	int from_pair = {{0,1},{0,3},{0,5},{0,7},{1,0},{1,2},{1,4},{1,6},
//					 {2,1},{2,3},{2,5},{2,7}};
//
//	int to_pair = {{3,0},{3,2},{3,4},{3,6},{4,1},{4,3},{4,5},{4,7},
//				   {5,0},{5,2},{5,4},{5,6},{6,1},{6,3},{6,5},{6,7},
//				   {7,0},{7,2},{7,4},{7,6}};

	// Plan would be for computer to pick randomly from spaces on the board where
	//  it has a piece and look through the list of spaces possible to move to from the
	//  array of 'to_pair' until it found a valid move.
	// Did not have enough time to keep track of where the computer currently has pieces
	//  after the initial board setup in order to run the game for awhile.
	// Currently, computer will just make two valid moves.

}


bool check_in_range(int fr_r, int fr_c, int to_r, int to_c){
	return fr_r >= 0 && fr_r < ROWS
		&& fr_c >= 0 && fr_c < COLS
		&& to_r >= 0 && to_r < ROWS
		&& to_c >= 0 && to_c < COLS;
}


bool check_from_occupied(int fr_r, int fr_c, string p, string (&b)[ROWS][COLS]){
	return b[fr_r][fr_c] == p;
}


bool check_to_occupied(int to_r, int to_c, string (&b)[ROWS][COLS]){
	return b[to_r][to_c] == "--.";
}


bool check_diagonal(int fr_r, int fr_c, int to_r, int to_c){

	// right
	if(fr_r == to_r && fr_c + 1 == to_c)
		return false;

	// left
	if(fr_r == to_r && fr_c - 1 == to_c)
		return false;

	// up
	if(fr_r - 1 == to_r && fr_c == to_c)
		return false;

	// down
	if(fr_r + 1 == to_r && fr_c == to_c)
		return false;

	return true;
}


bool check_forward(int fr_r, int fr_c, int to_r, int to_c, string p){
	// Computer Orientation
	if(p == "--X"){
		if(fr_r > to_r)
			return false;

	} else {
		// Player Orientation
		if(fr_r < to_r)
			return false;
	}

	return true;

}


bool check_jump(int fr_r, int fr_c, int to_r, int to_c, string &p){
	// Computer Orientation
	if(p == "--X"){
		if(to_r - fr_r == 2){
			return true;
		}

	} else {
		// Player Orientation
		if(fr_r - to_r == 2){
			return true;
		}
	}

	return false;
}


bool check_valid_jump(int fr_r, int fr_c, int to_r, int to_c, string &p, string (&b)[ROWS][COLS]){
	// Computer Orientation
	if(p == "--X"){
		// Right
		if(fr_c < to_c){
			if(b[fr_r+1][fr_c+1] != "--0")
				return false;
		} else{
			// Left
			if(b[fr_r+1][fr_c-1] != "--0")
				return false;
		}

	} else {
		// Player Orientation

		// Right
		if(fr_c < to_c){
			if(b[fr_r-1][fr_c+1] != "--0")
				return false;
		} else{
			// Left
			if(b[fr_r-1][fr_c-1] != "--0")
				return false;
		}
	}

	return true;

}


void play_move(int fr_r, int fr_c, int to_r, int to_c, string &p, string (&b)[ROWS][COLS]){
	// From [fr_r,fr_c] to [to_r,to_c]
	b[fr_r][fr_c] = "--.";
	b[to_r][to_c] = p;
}


void change_player(string &p, string &current_turn){
	if(current_turn == "Player"){
		current_turn = "Computer";
		p = "--X";
	} else {
		current_turn = "Player";
		p = "--0";
	}
}


bool check_winner(int &pp, int &cp, bool &c){
	if(pp == 0){
		return true;
	} else if(cp == 0){
		c = true;
		return true;
	}

	return false;
}



int main(){

	int player_pieces = 12;
	int computer_pieces = 12;
	bool winner   = false; // True when either the Player or Computer has won the game
	bool champion = false; // True when Player defeats the Computer
	string current_turn = "Player";
	string piece = "--0";

	// Dummy var since computer logic not fully implemented.
	int count = 0;

	cout << "Welcome to Simple Checkers" << endl;
	cout << "Game board is "<< ROWS << " x " << COLS << endl;
	cout << "Player, you control pieces -> 0" << endl << "Computer controls pieces   -> X" << endl;

	// Setup the game board and display empty board.
	string game_board[ROWS][COLS];

	initialize_board(game_board);

	// Primary game loop, while there is no winner, run the game.
	// When either the Player or Computer wins, close the game and display the winner.

	while(!winner){
		// Display current board
		print_board(game_board);
		cout << "Turn: " << current_turn << endl;

		// Get move from player whose turn it is
		int a = 10, b = 10, c = 10, d = 10;
		bool valid_move = false;

		while(!valid_move){
			if(current_turn == "Player"){

				bool input_error1 = true;
				bool input_error2 = true;


				while(input_error1 | input_error2){
					cout << "FROM [row _space_ col]: " << flush;
					cin >> a >> b;
					if(cin.good()){
						input_error1 = false;
						cin.clear();
						cout << "TO [row _space_ col]: " << flush;
						cin >> c >> d;
						if(cin.good()){
							input_error2 = false;
						} else{
							print_error();
						}
					} else {
						print_error();
					}
				}

			} else {
				cout << "Computer moving..." << endl;
				// get_computer_move(a,b,c,d,game_board);
				if(count == 0){
					a = 2;
					b = 7;
					c = 3;
					d = 6;
					count++;

				} else if(count == 1){
					a = 2;
					b = 1;
					c = 3;
					d = 0;
					count++;

				} else if(count == 2){
					a = 2;
					b = 3;
					c = 3;
					d = 2;
					count++;

				} else {
					return 0;
				}
			}



			// Check for valid move
			if(check_in_range(a,b,c,d)){

				if(check_from_occupied(a,b,piece,game_board)){

					if(check_to_occupied(c,d,game_board)){

						if(check_diagonal(a,b,c,d)){

							if(check_forward(a,b,c,d,piece)){

								if(!check_jump(a,b,c,d,piece)){
									valid_move = true;

								} else {
									if(check_valid_jump(a,b,c,d,piece,game_board)){
										valid_move = true;
									} else {
										cout << "Error -> Not a valid jump" << endl;
									}
								}

								// valid_move = true;

							} else {
								cout << "Error -> Moving backwards is not allowed" << endl;
							}

						} else {
							cout << "Error -> Move must be a diagonal one" << endl;
						}

					} else {
						cout << "Error -> TO space cannot be occupied" << endl;
					}

				} else {
					cout << "Error -> FROM space not occupied by your piece" << endl;
				}

			} else {
				cout << "Error -> Moves not on the board" << endl;
			}

		}


		// Play move on the board
		play_move(a,b,c,d,piece,game_board);


		// Check for winner
		winner = check_winner(player_pieces,computer_pieces,champion);


		// No winner, change player
		change_player(piece,current_turn);

	}

	if(champion){
		cout << "!!! Congratulations !!!" << endl;
		cout << "Player, you have beat the computer!"<< endl;
	} else {
		cout << "!!! I'm sorry !!!" << endl;
		cout << "Player, you have been defeated!"<< endl;
	}



	return 0;
}


