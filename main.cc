#include <iostream>
#include "board.h"
#include "player.h"
#include "textDisplay.h"
#include "graphicsDisplay.h"

using namespace std; 


int main () {
	Board *board = new Board(); // NYI
	Player *players[2] = {nullptr}; // NYI
	float score[2] = {0, 0};
	string cmd;
	TextDisplay *td = new TextDisplay(board);
	GraphicsDisplay *gd = new GraphicsDisplay(board);
	gd->initDisplay();
	
	// Variables that need to be reset each game
	int curTurn = 0; // Red is 0, Blue is 1
	int totalTurns = 0;
	bool manualSetup = false;
	bool gameStarted = false;
	bool gameOver = false;

	// Welcome message
	cout << "\nWelcome to Capture the Flag - Strategy Game!" << endl;

	while (true) {

		if(gameStarted){
			cout << "\n---------------" << endl;
			td->printTD();
			cout << "---------------" << endl;
			cout << "Turn " << totalTurns << endl;
			cout << "---------------" << endl;

			if ( curTurn == 0 ) {
				cout << "Red's Turn" << endl;
			} else {
				cout << "White's Turn" << endl;
			}

			cout << "---------------" << endl;
		}

	
		// Command Message
		cout << "\nCommands:\n\nType 'game' to start a new game\nType 'resign' to resign your current game"
		 	 <<	"\nType 'move' to make your current move \nType 'setup' to setup the board to your specifications" << endl;
		cin >> cmd; 

		if(cin.fail()) break;

		if (cmd == "game") {
			string playerType;
			Colour c;

			if ( gameStarted ) {
				cout << "You already have an ongoing game" << endl;
			} else {
				for (int i = 1; i >= 0; --i) {

					// set up 2 players
				}

				//if we havent setup up the board with our own specific specifications
				if (!manualSetup) {
					board->setDefault();
				}
				
				//Print out Board
				gameStarted = true;
				gd->updateDisplay();
				td->printTD();
			}

			
				
		}
		else if (cmd == "resign") {

			if ( !gameStarted ) {
				cout << "You cannot resign before the game has started" << endl;
			} else {
				if ( curTurn == 1 ) {
					cout << "\nBlue Resigned so Red Wins!!!" << endl;
				} else {
					cout << "\nRed Resigned so Blue Wins!!!" << endl;
				}

				cout << "\n---------------" << endl;

				// Give player who didnt resign a point
				score[!curTurn]++;
				
				gameStarted = false;
				gameOver = true;
			}
			

		}
		else if (cmd == "move") {
			
			if (!gameStarted) {
				cout << "You cannot play the game before you have started the game" << endl;
			} else {
				int o_x, o_y, n_x, n_y;

				// Side effects: changes the given coords
				players[curTurn]->getCoords(o_x, o_y, n_x, n_y); 
				
				if (board->move(o_x, o_y, n_x, n_y, !curTurn)) {
					curTurn = !curTurn;
					totalTurns++;
					gd->updateDisplay();
				}

			}

		}
		else if (cmd == "setup") {
			
			if (gameStarted) {
				cout << "You cannot enter setup while a game is running" << endl;
			} else {
				manualSetup = true;
				board->setup(curTurn, td, gd); 
			}
			
		}

		if(gameOver){
			string choice;
			cout << "Type 'p' to play again or 'q' to quit" << endl;
			cin >> choice;

			// resets settings to default
			if(choice == "p"){
				int curTurn = 0; // Red is 0, Blue is 1
				bool manualSetup = false;
				bool gameStarted = false;
				bool gameOver = false;
				board->wipe();
			}

			// leave loop and dealloacte object memory
			else{
				break;
			}
		}

	}
	

	

	delete board;
	delete td;
	delete gd;
	cout << "Final Score:" << endl;
	cout << "White: " << score[1] << endl;
	cout << "Black: " << score[0] << endl;
} 
