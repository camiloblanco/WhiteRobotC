/****************************************************************************************
* Project		:	AlgoTrading Jorge, David, Camilo, Shanka
* File			:	RobotMenu.cpp
* Lenguaje		:	C++
* License		:	Apache License Ver 2.0, www.apache.org/licenses/LICENSE-2.0
* Description	:	main CPP file for the program, entry point.
*
* References	:	- B. Stroustrup: The C++ Programming Language (Fourth Edition).
*					  Addison Wesley. Reading Mass. USA. May 2013. ISBN 0-321-56384-0.
*					- M.Capinski and T.Zastawniak, Numerical Methods in Finance with C++,
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
	//cout << "\x1B[2J\x1B[H"; //Linux
	system("CLS"); //Windows

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


// Test if the data file is correct and display content
void RobotMenu::testData() {
	WhiteRobot robot;
	robot.loadData("index_data.csv");
	clearConsole();
	cout << "****************************************************************************" << endl;
	cout << "			Test and print the data from the CSV File " << endl;
	cout << "****************************************************************************" << endl << endl;
	robot.printPrices();
	menuPause();
}

// Execute one instance of the White Robot
void RobotMenu::executeWhite () {
	
	int maPointsS, maPointsM, maPointsL, slopePoints, modeUp, modeDown;
	double slopeMin, intialCash, stopLoss;
	clearConsole();
	cout << "****************************************************************************" << endl;
	cout << "			2. Single White Robot simulation " << endl;
	cout << "****************************************************************************" << endl << endl;
	cout << " Enter the parameters of the simulation:" << endl << endl;
	
	cout << "Please enter the small window points size (Example:14): " << endl;
	cin >> maPointsS;
	cout << "Please enter the medium window points size (Example:21): " << endl;
	cin >> maPointsM;
	cout << "Please enter the large window points size (Example:40): " << endl;
	cin >> maPointsL;
	cout << "Please enter the number of points to use for calculating the Slope (3 months its about 400 points for H4): " << endl;
	cin >> slopePoints;
	cout << "Please enter the minimun slope to establish a trend (Example:0.01): " << endl;
	cin >> slopeMin;
	cout << "Please enter the Stop-loss parameter (Example:0.05): " << endl;
	cin >> stopLoss;
	cout << "Please enter the logic Mode for Long Trades [1-7]: " << endl;
	cin >> modeUp;
	cout << "Please enter the logic Mode for Short Trades [1-7]: " << endl;
	cin >> modeDown;

	cout << "Please enter the initial cash invesment (Example:1000) " << endl;
	cin >> intialCash;
	

	WhiteRobot robot(maPointsS, maPointsM, maPointsL, slopePoints, slopeMin, stopLoss, modeUp, modeDown);
	robot.loadData("index_data.csv");
	robot.whiteStrategy(intialCash);
	robot.printResults();
	robot.saveSimulation("simulations.csv");
	robot.saveSimulationData("portfolio_simulation.csv");

	menuPause();
}



// EExecute a series of random White Robots
void RobotMenu::radomWhite() {

	int max_maPointsS, max_maPointsM, max_maPointsL, max_slopePoints, testNumber;
	double max_slopeMin, max_stopLoss;
	int max_modeUp=7;
	int max_modeDown = 7;
	double intialCash = 1000;

	clearConsole();
	cout << "****************************************************************************" << endl;
	cout << "			3. Set of random White Robot simulations " << endl;
	cout << "****************************************************************************" << endl << endl;
	cout << " Enter the parameters of the simulations:" << endl << endl;

	cout << "Please enter the maximum small window points size (Example:20): " << endl;
	cin >> max_maPointsS;
	cout << "Please enter the maximum medium window points size (Example:40): " << endl;
	cin >> max_maPointsM;
	cout << "Please enter the maximum large window points size (Example:60): " << endl;
	cin >> max_maPointsL;
	cout << "Please enter the maximum number of points to use for calculating the Slope (Example:300): " << endl;
	cin >> max_slopePoints;
	cout << "Please enter the maximum slope to establish a trend (Example:0.5): " << endl;
	cin >> max_slopeMin;
	cout << "Please enter the maximum Stop-loss parameter (Example:0.2): " << endl;
	cin >> max_stopLoss;
	cout << "Please enter the number of simulations to execute: " << endl;
	cin >> testNumber;

	cout << "All simulations are done with an initial cash invesment of 1000 " << endl;
	
	int maPointsS, maPointsM, maPointsL, slopePoints, modeUp,modeDown;
	double slopeMin, stopLoss;

	maPointsS = max_maPointsS;
	maPointsM = max_maPointsM;
	maPointsL = max_maPointsL;
	slopePoints = max_slopePoints;
	slopeMin = max_slopeMin;
	stopLoss = max_stopLoss;
	modeUp = 1;
	modeDown= 2;

	WhiteRobot robot;
	robot.loadData("index_data.csv");


	for (int i = 0; i < testNumber; i++)
	{
		robot.setParameters(maPointsS, maPointsM, maPointsL, slopePoints, slopeMin, stopLoss, modeUp, modeDown);
		robot.whiteStrategy(intialCash);
		robot.saveSimulation("simulations.csv");
	}

	menuPause();
}



//Main menu for accesing White Robot program 
void RobotMenu::mainMenu() {

	int option = 9;

	while (option != 0) {
		clearConsole();
		cout << "****************************************************************************" << endl;
		cout << "	White Robot C++ an algorimic trading backtesting program " << endl << endl;
		cout << "		Version 1.5: Flexible brain		" << endl << endl;
		cout << "Select an option by entering the given number:" << endl << endl;
		cout << "1. Test and print the data from the CSV File" << endl;
		cout << "2. Execute a single instance of the White Robot strategy" << endl;
		cout << "3. Simulate a series of random White Robots" << endl;
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
		else if (option == 3) {
			radomWhite();
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
