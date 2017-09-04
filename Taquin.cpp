/* CSCI 261 : Final Project
* 
* Ressource file for the class taquin
*
*/

#include "Taquin.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

void Taquin::MagicSwap(int a, int b, int c, int d) {	// Swaps 2 cells of the grid
	string temp = _grid[a][b];
	_grid[a][b] = _grid[c][d];
	_grid[c][d] = temp;
}

Taquin::Taquin() {
	int i, j;
	_moves=0; // Initialize the number of moves
	int counter(0);
	srand(time(0));
	int permutations;

	for (i = 0; i < ROWS; ++i) {  // Fills the completed grid and the grid used to play
		for (j = 0; j < COLUMNS; ++j) {
			counter++;
			_completed[i][j] = to_string(counter);
			_grid[i][j] = to_string(counter);
		}
	}
	_completed[3][3] = " ";
	_grid[3][3] = " ";

	
	permutations = 2 * (rand() % 200); // Swaps non-empty cells in the grid an even number of times (so the grid is solvable)

	int a, b, c, d;
	/*for (i = 0; i < permutations; ++i) {
		do {
			a = rand() % ROWS;
			b = rand() % COLUMNS;
			c = rand() % ROWS;
			d = rand() % COLUMNS;
		} while ((a == c && b == d) || _grid[a][b] == " " || _grid[c][d] == " ");

		MagicSwap(a, b, c, d);
	}

	
	//Position of the empty cell
	int e = rand() % ROWS, f = rand() % COLUMNS;
	for (int x = 3; x > f; x--)
		MagicSwap(3, x - 1, 3, x);
	for (int y = 3; y > e; y--)
		MagicSwap(y - 1, f, y, f); */
	
	
	MagicSwap(3, 2, 3, 3); // If you want to test the win of the user without solving a completely random game, comment from line 44 to line 62 
	// and uncomment line 65
}

void Taquin::Introduction(Font font) {  // Prints the introduction of the game to the user
	RenderWindow window(VideoMode(625, 250), "Welcome!");
	while (window.isOpen()){
		window.clear();
		Text text;
		text.setFont(font);
		text.setFillColor(Color::White);
		text.setString("Welcome to the game of 'Taquin'!");
		text.setCharacterSize(float(30));
		text.setPosition(Vector2f(100,80));
		window.draw(text);


		Text text2;
		text2.setFont(font);
		text2.setFillColor(Color::White);
		text2.setString("Close this window to start the game.");
		text2.setCharacterSize(float(30));
		text2.setPosition(Vector2f(85, 120));
		window.draw(text2);
		window.display();

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
	}
}


bool Taquin::isCompleted() {  // Check if the grid is completed by comparing the entries in the play grid and in the completed grid
	bool completed = true;
	int counter(0);
	int i, j;
	for (i = 0; i < ROWS; ++i) {
		for (j = 0; j < COLUMNS; ++j) {
			counter++;
			if (!(_grid[i][j] == to_string(counter))) {
				if ((counter == 16) && (_grid[i][j] == " ")) {
				}
				else {
					completed = false;
				}
			}
		}
	}
	return completed;
}

void Taquin::Play(int a, int b) {  // Allows the user to swap the empty cell with an adjacent cell
	int i, j;
	for (i = 0; i < ROWS; ++i) {
		for (j = 0; j < COLUMNS; ++j) {
			if (_grid[i][j] == " ") {
				_xBlank = i;
				_yBlank = j;
			}
		}
	}

	if ((a <= 4) && (b <= 4) && (a > 0) && (b > 0)) {
		if (((a == _xBlank) && (b == _yBlank + 1)) || ((a == _xBlank + 1) && (b == _yBlank)) || ((a == _xBlank + 1) && (b == _yBlank + 2)) || ((a == _xBlank + 2) && (b == _yBlank + 1))) {
			MagicSwap(a - 1, b - 1, _xBlank, _yBlank);
		}
		else {
			cerr << "Invalid input" << endl;
		}
	}
	else {
		cerr << "Invalid input" << endl;
	}
}

string Taquin::getNumber(int i, int j) const {
	return (_grid[i][j]);
}

string Taquin::getMoves() const {
	return to_string(_moves);
}

void Taquin::moreMoves() {
	_moves+=1;
}