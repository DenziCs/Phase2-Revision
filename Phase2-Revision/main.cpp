/*
Nathaniel Francis S. Filoteo
GD-PHYS S11
Programming Challenge 2

Developed using: 
IJW Engine
by Miguel Bravo & Nate Filoteo
*/

#include"Custom Classes/Game.h"
#include<iostream>
#include<iomanip>
using namespace std;
using namespace gdphys;

int main() {
	Game game;
	game.run();

	cout << fixed;
	cout << setprecision(2);
	cout << "Spinner has completed " << game.totalDegrees / 360.f << " revolutions." << endl;
	cout << "Spinner took " << game.totalTime << " seconds to reach minimum speed." << endl;
	// cout << game.finalVelocity << endl;

	system("pause");
	return EXIT_SUCCESS;
}