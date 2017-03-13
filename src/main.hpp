/*
 * main.hpp
 *
 *  Created on: Feb 23, 2017
 *      Author: ryanatkins
 */

#ifndef MAIN_HPP_
#define MAIN_HPP_

// Global Variables for Board Settings
# define ROWS 8
# define COLS 8

# define EMPTY_PIECE "   "
# define OFF_PIECE " - "
# define PLAYER_PIECE "-0-"
# define COMPUTER_PIECE "-X-"


// Initialize & Console Print Functions
void initialize_board(std::string (&b)[ROWS][COLS]);
void print_board(std::string (&b)[ROWS][COLS]);
void print_input_error();


// Gameplay Functions
void get_computer_move(int &fr_r, int &fr_c, int &to_r, int &to_c, 
					   std::vector<std::pair<int,int>> &from_p, std::vector<std::pair<int,int>> &to_p, int to_begin, int from_end);
void play_move(int fr_r, int fr_c, int to_r, int to_c, std::string (&p), int &pp, int &cp, std::string (&b)[ROWS][COLS]);
void change_player(std::string (&p), std::string (&current_turn));
bool check_winner(int &pp, int &cp, bool &c);


// Validate Move Functions
bool validate_within_limits(int a,int b);
bool check_in_range(int fr_r, int fr_c, int to_r, int to_c);
bool check_from_occupied(int fr_r, int fr_c, std::string (p), std::string (&b)[ROWS][COLS]);
bool check_to_occupied(int to_r, int to_c, std::string (&b)[ROWS][COLS]);
bool check_diagonal(int fr_r, int fr_c, int to_r, int to_c);
bool check_forward(int fr_r, int fr_c, int to_r, int to_c, std::string (p));
bool check_jump(int fr_r, int fr_c, int to_r, int to_c, std::string (&p));
bool check_valid_jump(int fr_r, int fr_c, int to_r, int to_c, std::string (&p), std::string (&b)[ROWS][COLS]);




#endif /* MAIN_HPP_ */
