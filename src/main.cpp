//============================================================================
// Name        : Checkers
// Author      : Ryan Atkins
// Version     : v1.0
// Copyright   : Your copyright notice
// Description : Simple Checkers
//============================================================================


#include <iostream>
#include <vector>
#include <stdlib.h>
#include "main.hpp"
using namespace std;


void initialize_board(string (&b)[ROWS][COLS]){
	for(int i = 0; i < ROWS; i++){
		for(int j = 0; j < COLS; j++){
			b[i][j] = EMPTY_PIECE;
		}
	}

	// Setup OFF_PIECES; Locations that will not be apart of the game.
	for(int i = 0; i < 7; i += 2){
		for(int j = 0; j < 7; j += 2){
			b[i][j] = OFF_PIECE;
		}
	}

	for(int i = 1; i < 8; i += 2){
		for(int j = 1; j < 8; j += 2){
			b[i][j] = OFF_PIECE;
		}
	}


	// Setup COMPUTER_PIECE 	-> -X-
	b[0][1] = COMPUTER_PIECE;
	b[0][3] = COMPUTER_PIECE;
	b[0][5] = COMPUTER_PIECE;
	b[0][7] = COMPUTER_PIECE;

	b[1][0] = COMPUTER_PIECE;
	b[1][2] = COMPUTER_PIECE;
	b[1][4] = COMPUTER_PIECE;
	b[1][6] = COMPUTER_PIECE;

	b[2][1] = COMPUTER_PIECE;
	b[2][3] = COMPUTER_PIECE;
	b[2][5] = COMPUTER_PIECE;
	b[2][7] = COMPUTER_PIECE;

	// Setup PLAYER_PIECE 	-> -0-
	b[5][0] = PLAYER_PIECE;
	b[5][2] = PLAYER_PIECE;
	b[5][4] = PLAYER_PIECE;
	b[5][6] = PLAYER_PIECE;

	b[6][1] = PLAYER_PIECE;
	b[6][3] = PLAYER_PIECE;
	b[6][5] = PLAYER_PIECE;
	b[6][7] = PLAYER_PIECE;

	b[7][0] = PLAYER_PIECE;
	b[7][2] = PLAYER_PIECE;
	b[7][4] = PLAYER_PIECE;
	b[7][6] = PLAYER_PIECE;

}


void print_board(string (&b)[ROWS][COLS]){
	cout << endl;
	cout << "     1     2     3     4     5     6     7     8" << endl;
	cout << "  |-----|-----|-----|-----|-----|-----|-----|-----|" << endl;

	for(int i = 0; i < ROWS; i++){
		cout << i+1 << " | ";
		for(int j = 0; j < COLS; j++){
			cout << b[i][j] << " | ";
		}
		cout << "\n";
		cout << "  |-----|-----|-----|-----|-----|-----|-----|-----|" << endl;
	}

	cout << endl;

}


void print_input_error(){
	cout << flush << endl;
	cin.clear();
	cin.ignore(INT_MAX,'\n');
	cout << "Oops, you entered an invalid move!\n"
			"Please enter an int (the row) followed by\n"
			"pressing space bar followed by an int (the column)" << endl;

}


bool validate_within_limits(int a,int b){
	return a >= 0 && a < ROWS && b >=0 && b <= COLS;

}


void get_computer_move(int &fr_r, int &fr_c, int &to_r, int &to_c, 
					   vector<pair<int,int>> &from_p, vector<pair<int,int>> &to_p, int to_begin, int from_end){

	// Computer to pick randomly from spaces on the board where
	//  it has a piece and look through the list of spaces possible to move to from the
	//  array of 'to_pair' until it finds a valid move.

	fr_r = from_p.at(from_end).first;
	fr_c = from_p.at(from_end).second;

	to_r = to_p.at(to_begin).first;
	to_c = to_p.at(to_begin).second;

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
	return b[to_r][to_c] == EMPTY_PIECE;

}


bool check_diagonal(int fr_r, int fr_c, int to_r, int to_c){

	// One Space Diagonal
	if(validate_within_limits(fr_r-1,fr_c-1)){
		if(fr_r - 1 == to_r && fr_c - 1 == to_c)
			return true;
	}

	if(validate_within_limits(fr_r-1,fr_c+1)){
		if(fr_r - 1 == to_r && fr_c + 1 == to_c)
			return true;
	}

	if(validate_within_limits(fr_r+1,fr_c-1)){
		if(fr_r + 1 == to_r && fr_c - 1 == to_c)
			return true;
	}

	if(validate_within_limits(fr_r+1,fr_c+1)){
		if(fr_r + 1 == to_r && fr_c + 1 == to_c)
			return true;
	}

	// Two Space Diagonal -> Possible Jump
	if(validate_within_limits(fr_r-2,fr_c-2)){
		if(fr_r - 2 == to_r && fr_c - 2 == to_c)
			return true;
	}

	if(validate_within_limits(fr_r-2,fr_c+2)){
		if(fr_r - 2 == to_r && fr_c + 2 == to_c)
			return true;
	}

	if(validate_within_limits(fr_r+2,fr_c-2)){
		if(fr_r + 2 == to_r && fr_c - 2 == to_c)
			return true;
	}

	if(validate_within_limits(fr_r+1,fr_c+1)){
		if(fr_r + 2 == to_r && fr_c + 2 == to_c)
			return true;
	}

	return false;

}


bool check_forward(int fr_r, int fr_c, int to_r, int to_c, string p){
	// Computer Orientation
	if(p == COMPUTER_PIECE){
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
	if(p == COMPUTER_PIECE){
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
	if(p == COMPUTER_PIECE){
		// Right
		if(fr_c < to_c){
			if(b[fr_r+1][fr_c+1] != PLAYER_PIECE)
				return false;
		} else{
			// Left
			if(b[fr_r+1][fr_c-1] != PLAYER_PIECE)
				return false;
		}

	} else {
		// Player Orientation

		// Right
		if(fr_c < to_c){
			if(b[fr_r-1][fr_c+1] != COMPUTER_PIECE)
				return false;
		} else{
			// Left
			if(b[fr_r-1][fr_c-1] != COMPUTER_PIECE)
				return false;
		}
	}

	return true;

}


void play_move(int fr_r, int fr_c, int to_r, int to_c, string &p, int &pp, int &cp, string (&b)[ROWS][COLS]){
	// From [fr_r,fr_c] to [to_r,to_c]
	b[fr_r][fr_c] = EMPTY_PIECE;
	b[to_r][to_c] = p;

	// If this is a jump, remove jumped piece
	if(abs(fr_r-to_r) == 2){
		if(p == COMPUTER_PIECE){
			// Player loses a piece
			pp--;
			if(fr_c > to_c){
				b[fr_r+1][fr_c-1] = EMPTY_PIECE;
			} else {
				b[fr_r+1][fr_c+1] = EMPTY_PIECE;
			}

		} else {
			// Computer loses a piece
			cp--;
			if(fr_c > to_c){
				b[fr_r-1][fr_c-1] = EMPTY_PIECE;
			} else {
				b[fr_r-1][fr_c+1] = EMPTY_PIECE;
			}
		}

	}
}


void change_player(string &p, string &current_turn){
	if(current_turn == "Player"){
		current_turn = "Computer";
		p = COMPUTER_PIECE;
	} else {
		current_turn = "Player";
		p = PLAYER_PIECE;
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


class range_exception:public exception{
public:
	virtual const char* what() const throw(){return "Error -> Move is not on the board";}
} range_except;


class from_exception:public exception{
public:
	virtual const char* what() const throw(){return "Error -> FROM space not occupied by your piece";}
} from_except;


class to_exception:public exception{
public:
	virtual const char* what() const throw(){return "Error -> TO space cannot be occupied";}
} to_except;


class diagonal_exception:public exception{
public:
	virtual const char* what() const throw(){return "Error -> Move must be a diagonal one";}
} diagonal_except;


class backwards_exception:public exception{
public:
  virtual const char* what() const throw(){return "Error -> Moving backwards is not allowed";}
} backwards_except;


class invalid_jump_exception:public exception{
  virtual const char* what() const throw(){return "Error -> Not a valid jump";}
} invalid_jump_except;



int main(){

	int player_pieces 	= 12;
	int computer_pieces = 12;
	bool winner   		= false;	// True when either the Player or Computer has won the game
	bool champion 		= false;	// True when Player defeats the Computer
	string current_turn = "Player";
	string piece 		= PLAYER_PIECE;
	

	// Computer structures to see the board.
	// from_pairs : locations of all computer occupied spaces
	// to_pairs   : locations of all possible moves for computer
	vector<pair<int,int> > from_pairs = {{0,1},{0,3},{0,5},{0,7},
										 {1,0},{1,2},{1,4},{1,6},
										 {2,1},{2,3},{2,5},{2,7}  };

	vector<pair<int,int> > to_pairs = {{1,0},{1,2},{1,4},{1,6},
									   {2,1},{2,3},{2,5},{2,7},
									   {3,0},{3,2},{3,4},{3,6},
									   {4,1},{4,3},{4,5},{4,7},
									   {5,0},{5,2},{5,4},{5,6},
									   {6,1},{6,3},{6,5},{6,7},
									   {7,0},{7,2},{7,4},{7,6}  };


	// Vector counters for Computer AI.
	int count_begin = 0;
	int count_end = from_pairs.size() - 1;


	cout << "Welcome to Simple Checkers" << endl;
	cout << "Game board is "<< ROWS << " x " << COLS << endl;
	cout << "Player, you control pieces -> 0" << endl << "Computer controls pieces   -> X" << endl;


	// Setup the game board and display empty board.
	string game_board[ROWS][COLS];

	initialize_board(game_board);


	// Primary game loop: 
	// While there is no winner, run the game.
	// When either the Player or Computer wins, close the game and display the winner.
	while(!winner){
		
		// Display current board with Game information
		print_board(game_board);
		cout << "Turn: " << current_turn << endl;
		cout << "Player Pieces: " << player_pieces << "  Computer Pieces: " << computer_pieces << endl;


		// Request a move from the player whose turn it is
		int a = 10, b = 10, c = 10, d = 10;
		bool valid_move = false;


		// While the input for a move is not Valid, continue to ask for valid numbers for a move. 
		while(!valid_move){
			if(current_turn == "Player"){

				// Track user input for 'FROM' location and 'TO' location
				bool input_error1 = true;
				bool input_error2 = true;

				// If there is an error in either the FROM location or TO location,
				// Ask for correct input. 
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
							print_input_error();
						}
					} else {
						print_input_error();
					}
				}

				// Account for zero-based indexing for the user input.
				a--;
				b--;
				c--;
				d--;

			} else {
				
				// Reset counter for selecting Computer move.
				if(count_begin >= to_pairs.size()){
					count_begin = 0;
					count_end--;
				}
				
				get_computer_move(a,b,c,d,from_pairs,to_pairs,count_begin,count_end);
				count_begin++;

			}

			// Check for valid move
			try {
				if(!check_in_range(a,b,c,d))
					throw range_except;

				if(!check_from_occupied(a,b,piece,game_board))
					throw from_except;

				if(!check_to_occupied(c,d,game_board))
					throw to_except;

				if(!check_diagonal(a,b,c,d))
					throw diagonal_except;

				if(!check_forward(a,b,c,d,piece))
					throw backwards_except;

				if(!check_jump(a,b,c,d,piece)){
					valid_move = true;

				} else {
					if(check_valid_jump(a,b,c,d,piece,game_board)){
						// Player will jump a computer piece.
						//  Update from_pairs for Computer.
						if(current_turn == "Player"){
							int x = 0, y = 0;
							// Computer loses a piece
							if(b > d){
								x = a-1;
								y = b-1;
							} else {
								x = a-1;
								y = b+1;
							}

							for(int i = 0; i < from_pairs.size(); i++){
								if(from_pairs.at(i).first == x && from_pairs.at(i).second == y)
									from_pairs.erase(from_pairs.begin()+i);
							}

							count_end = from_pairs.size() - 1;
						}

						valid_move = true;

					} else {
						throw invalid_jump_except;
					}
				}
			}

			catch (exception& e){
				// Only Print Error message for Player moves. 
				if(current_turn=="Player"){
					cout << e.what() << '\n';
				}
				
			}

		}


		// When it is the Computer's turn and a valid move has been made,
		//  Update the from_pair vector and the to_pair vector.
		if(current_turn == "Computer"){

			for(int i = 0; i < from_pairs.size();i++){
				if(from_pairs.at(i).first == a && from_pairs.at(i).second == b)
					from_pairs.erase(from_pairs.begin()+i);
			}

			from_pairs.push_back({c,d});

			count_begin = 0;
			count_end   = from_pairs.size() - 1;

			// cout << "Updating Computer vectors..." << endl;
			// cout << from_pairs.back().first << ":" << from_pairs.back().second;
		}

		// Play move on the board
		play_move(a,b,c,d,piece,player_pieces,computer_pieces,game_board);


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

