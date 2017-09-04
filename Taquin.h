/* CSCI 261 : Final Project
*
* Header file for the class Taquin
* 
*/

#pragma once
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;

using namespace std;

class Taquin {
public:
	Taquin();
	bool isCompleted();
	void Introduction(Font font);
	void Play(int a, int b);
	string getNumber(int i, int j) const;
	string getMoves() const;
	void moreMoves();
	
private:
	static const int ROWS = 4;
	static const int COLUMNS = 4;
	string _grid[ROWS][COLUMNS];
	string _completed[ROWS][COLUMNS];
	int _xBlank;
	int _yBlank;
	int _moves;
	void MagicSwap(int a, int b, int c, int d);
};