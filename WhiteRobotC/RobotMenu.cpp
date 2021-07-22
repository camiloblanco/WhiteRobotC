/****************************************************************************************
* Project		:	AlgoTrading Jorge, David, Camilo, Shanka
* File			:	main.cpp
* Lenguaje		:	C++
* License		:	Apache License Ver 2.0, www.apache.org/licenses/LICENSE-2.0
* Description	:	main CPP file for the program, entry point.
*
* References	:	- M.Capinski and T.Zastawniak, Numerical Methods in Finance with C++,
*					  Cambridge, 2012, code: http://www.cambridge.org/9780521177160
* Other files	:
* Git Control	:	https://github.com/camiloblanco/WhiteRobotC
* Author - Year	:	Sahenjit Paul - Camilo Blanco Vargas - Year: 2021
* Mail - Web	:	shanks.p.95@gmail.com -:mail@camiloblanco.com
****************************************************************************************/

/****************************************************************************************
*								#INCLUDES AND #CONSTANTS								*
****************************************************************************************/

#include "RobotMenu.h"

/****************************************************************************************
*									MEMBER FUNCTIONS									*
****************************************************************************************/

//constructor
RobotMenu::RobotMenu() {
}

// Clear the whole console
void RobotMenu::clearConsole() {
	cout << "\x1B[2J\x1B[H";
}

// Pause execution waiting for a key
void RobotMenu::menuPause() {
	cout << endl << "Press any key to continue..." << endl;
	cin.ignore();
	cin.get();
}

// Read a line from the console including spaces
void RobotMenu::readLine(string& description) {
	cin.ignore();
	getline(cin, description);
}


//
void RobotMenu::testData() {
	WhiteRobot robot;
	robot.loadData("SPX500_USD_H4.CSV");
	robot.displayData();
	menuPause();
}

//
void RobotMenu::executeWhite () {
	WhiteRobot robot;
	int maPointsS, maPointsM, maPointsL, slopePoints;
	double slopeMin, intialCash, stopLoss;
	clearConsole();
	cout << "****************************************************************************" << endl;
	cout << "		White Robot C++ an algorimic trading program " << endl ;
	cout << "					Version 1.0.0					 " << endl << endl;
	cout << " Enter the parameters of the simulation:" << endl << endl;
	cout << "Please enter the number of points to use for calculating the Slope (3 months its about 395 points for H4): " << endl;
	cin >> slopePoints;
	cout << "Please enter the small window points size (Example:14): " << endl;
	cin >> maPointsS;
	cout << "Please enter the medium window points size (Example:21): " << endl;
	cin >> maPointsM;
	cout << "Please enter the large window points size (Example:40): " << endl;
	cin >> maPointsL;
	cout << "Please enter the minimun slope to establish a trend (Example:0.001): " << endl;
	cin >> slopeMin;
	cout << "Please enter the Stop-loss parameter (Example:0.02): " << endl;
	cin >> stopLoss;
	cout << "Please enter the initial cash invesment (Example:895.3) " << endl;
	cin >> intialCash;
	robot.loadData("SPX500_USD_H4.CSV");

	robot.whiteStrategy(maPointsS, maPointsM, maPointsL, slopePoints, slopeMin, stopLoss, intialCash);

	robot.saveSimulation("portfolio_simulation.csv");

	menuPause();
}

//Main menu for accesing the finlib
void RobotMenu::mainMenu() {

	int option = 9;

	while (option != 0) {
		clearConsole();
		cout << "****************************************************************************" << endl;
		cout << "		White Robot C++ an algorimic trading program " << endl << endl;
		cout << "Select an option by entering the given number:" << endl << endl;
		cout << "1. Test the data load from the CSV File" << endl;
		cout << "2. Execute the White robot strategy" << endl;
		cout << "0. To exit the program" << endl;
		cout << "****************************************************************************" << endl;
		cout << endl << "Please enter the option number:" << endl;
		cin >> option;
		if (option == 1) {
			testData();
		}
		else if (option == 2) {
			executeWhite();
		}
		else if (option == 0) {
			cout << endl << "Thank you for using the White Robot, have a nice day. " << endl << endl;
		}
		else {
			cout << "Invalid Option" << endl;
			menuPause();
		}

	}
}
