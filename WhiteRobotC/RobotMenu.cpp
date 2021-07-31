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
	
	int maPointsS_long, maPointsM_long, maPointsL_long, mode_long, maPointsS_short, maPointsM_short, maPointsL_short, mode_short;
	double slopeMin_long, slopeMin_short;

	int slopePoints;
	double stopLoss, intialCash;

	clearConsole();
	cout << "****************************************************************************" << endl;
	cout << "			2. Single White Robot simulation " << endl;
	cout << "****************************************************************************" << endl << endl;
	cout << " Enter the parameters of the simulation:" << endl;
	cout << " (1 month is about 500 points for H1): " << endl;

	cout << endl << "Long trades Strategy parameters: " << endl;
	cout << " - Small window points size (Example:14): " << endl;
	cin >> maPointsS_long;
	cout << " - Medium window points size (Example:21): " << endl;
	cin >> maPointsM_long;
	cout << " - Large window points size (Example:40): " << endl;
	cin >> maPointsL_long;
	cout << " - Minimun slope to establish a trend (Example:0.01): " << endl;
	cin >> slopeMin_long;
	cout << "- Logic Mode for Long trades [0-7]: " << endl;
	cin >> mode_long;

	cout << endl << "Short trades Strategy parameters: " << endl;
	cout << " - Small window points size (Example:14): " << endl;
	cin >> maPointsS_short;
	cout << " - Medium window points size (Example:21): " << endl;
	cin >> maPointsM_short;
	cout << " - Large window points size (Example:40): " << endl;
	cin >> maPointsL_short;
	cout << " - Minimun slope to establish a trend (Example:0.01): " << endl;
	cin >> slopeMin_short;
	cout << "- Logic Mode for Short trades [0-7]: " << endl;
	cin >> mode_short;

	cout << endl << "General Strategy parametes: " << endl;
	cout << "Please enter the number of points to use for calculating the Slope" << endl;
	cin >> slopePoints;
	cout << "Please enter the Stop-loss parameter (Example:0.05): " << endl;
	cin >> stopLoss;


	cout << "Please enter the initial cash invesment (Example:1000) " << endl;
	cin >> intialCash;
	

	WhiteRobot robot(maPointsS_long, maPointsM_long, maPointsL_long, slopeMin_long, mode_long, maPointsS_short, maPointsM_short, maPointsL_short, slopeMin_short, mode_short, slopePoints, stopLoss);

	robot.loadData("index_data.csv");
	robot.whiteStrategy(intialCash);
	robot.printResults();
	robot.saveSimulation("simulations.csv");
	robot.saveSimulationData("portfolio_simulation.csv");

	menuPause();
}



// Execute a series of random White Robots
void RobotMenu::radomWhite() {

	int max_maPointsS_long, max_maPointsM_long, max_maPointsL_long, max_maPointsS_short, max_maPointsM_short, max_maPointsL_short;
	double max_slopeMin_long, max_slopeMin_short;

	int max_slopePoints, testNumber;
	double max_stopLoss;

	double intialCash = 1000;

	clearConsole();
	cout << "****************************************************************************" << endl;
	cout << "			3. Set of random White Robot simulations " << endl;
	cout << "****************************************************************************" << endl << endl;
	cout << " Enter the parameters for the simulations:" << endl << endl;
	cout << " (1 month is about 500 points for H1): " << endl;

	cout << endl << "Long trades Strategy parameters: " << endl;
	cout << " - Small window maximum points size (Example:30): " << endl;
	cin >> max_maPointsS_long;
	cout << " - Medium window maximum points size (Example:40): " << endl;
	cin >> max_maPointsM_long;
	cout << " - Large window maximum points size (Example:60): " << endl;
	cin >> max_maPointsL_long;
	cout << " - Maximun slope to establish a trend (Example:0.1): " << endl;
	cin >> max_slopeMin_long;
	

	cout << endl << "Short trades Strategy parameters: " << endl;
	cout << " - Small window maximum points size (Example:30): " << endl;
	cin >> max_maPointsS_short;
	cout << " - Medium window maximum points size (Example:40): " << endl;
	cin >> max_maPointsM_short;
	cout << " - Large window maximum points size (Example:60): " << endl;
	cin >> max_maPointsL_short;
	cout << " - Maximun slope to establish a trend (Example:0.1): " << endl;
	cin >> max_slopeMin_short;
	

	cout << endl << "General Strategy parametes: " << endl;
	cout << "Please enter the maximum number of points to use for calculating the Slope" << endl;
	cin >> max_slopePoints;
	cout << "Please enter the maximum Stop-loss parameter (Example:0.1): " << endl;
	cin >> max_stopLoss;
	cout << "Please enter the number of simulations to execute: " << endl;
	cin >> testNumber;
	cout << "All simulations are done with an initial cash invesment of 1000 " << endl << endl;
	
	int maPointsS_long, maPointsM_long, maPointsL_long, mode_long, maPointsS_short, maPointsM_short, maPointsL_short, mode_short;
	double slopeMin_long, slopeMin_short;

	int slopePoints;
	double stopLoss;

	random_device rd;     // only used once to initialise (seed) engine
	mt19937 rng(rd());    // random-number engine used (Mersenne-Twister)

	uniform_int_distribution<int> generator_maPointsS_long(2, max_maPointsS_long);
	uniform_int_distribution<int> generator_maPointsM_long(2, max_maPointsM_long);
	uniform_int_distribution<int> generator_maPointsL_long(2, max_maPointsL_long);
	uniform_real_distribution<double> generator_slopeMin_long(0, max_slopeMin_long);

	uniform_int_distribution<int> generator_maPointsS_short(2, max_maPointsS_short);
	uniform_int_distribution<int> generator_maPointsM_short(2, max_maPointsM_short);
	uniform_int_distribution<int> generator_maPointsL_short(2, max_maPointsL_short);
	uniform_real_distribution<double> generator_slopeMin_short(0, max_slopeMin_short);

	uniform_int_distribution<int> generator_mode(0,7);
	uniform_int_distribution<int> generator_slopePoints(2, max_slopePoints);
	uniform_real_distribution<double> generator_stopLoss(0, max_stopLoss);

	WhiteRobot robot;
	robot.loadData("index_data.csv");

	for (int i = 0; i < testNumber; i++)
	{
		maPointsS_long = generator_maPointsS_long(rng);
		maPointsM_long = generator_maPointsM_long(rng);
		maPointsL_long = generator_maPointsL_long(rng);
		slopeMin_long = floor((generator_slopeMin_long(rng) * 10000) + .5) / 10000;
		mode_long = generator_mode(rng);

		maPointsS_short = generator_maPointsS_short(rng);
		maPointsM_short = generator_maPointsM_short(rng);
		maPointsL_short = generator_maPointsL_short(rng);
		slopeMin_short = floor((generator_slopeMin_short(rng) * 10000) + .5) / 10000;
		mode_short = generator_mode(rng);

		slopePoints = generator_slopePoints(rng);
		stopLoss = floor((generator_stopLoss(rng) * 10000) + .5) / 10000;
		
		robot.setParameters(maPointsS_long, maPointsM_long, maPointsL_long, slopeMin_long, mode_long, maPointsS_short, maPointsM_short, maPointsL_short, slopeMin_short, mode_short, slopePoints, stopLoss);
		robot.whiteStrategy(intialCash);
		robot.saveSimulation("simulations.csv");

		if ((i + 1) % 100 == 0) {
			cout << "Simulation number: " << i+1 <<endl;
		}

	}

	menuPause();
}


// Execute a series of random White Robots with parameters in closed intervals
void RobotMenu::closedRadomWhite() {

	int testNumber;
	int max_maPointsS, max_maPointsM, max_maPointsL, max_slopePoints;
	int min_maPointsS, min_maPointsM, min_maPointsL, min_slopePoints;
	double max_slopeMin, max_stopLoss;
	double min_slopeMin, min_stopLoss;
	double intialCash = 1000;

	clearConsole();
	cout << "****************************************************************************" << endl;
	cout << "			4. Series of random White Robots with Closed range " << endl;
	cout << "****************************************************************************" << endl << endl;
	cout << " Enter the parameters of the simulations:" << endl << endl;

	cout << "Please enter the minimum small window points size (Example:2) min 2: " << endl;
	cin >> min_maPointsS;
	cout << "Please enter the maximum small window points size (Example:20): " << endl;
	cin >> max_maPointsS;
	cout << "Please enter the minimum medium window points size (Example:10) min 2: " << endl;
	cin >> min_maPointsM;
	cout << "Please enter the maximum medium window points size (Example:40): " << endl;
	cin >> max_maPointsM;
	cout << "Please enter the minimum large window points size (Example:15) min 2: " << endl;
	cin >> min_maPointsL;
	cout << "Please enter the maximum large window points size (Example:60): " << endl;
	cin >> max_maPointsL;

	cout << "Please enter the minimum number of points to use for calculating the Slope (Example:30) min 2: " << endl;
	cin >> min_slopePoints;
	cout << "Please enter the maximum number of points to use for calculating the Slope (Example:3000): " << endl;
	cin >> max_slopePoints;
	cout << "Please enter the minimum slope to establish a trend (Example:0): " << endl;
	cin >> min_slopeMin;
	cout << "Please enter the maximum slope to establish a trend (Example:0.2): " << endl;
	cin >> max_slopeMin;

	cout << "Please enter the minimum Stop-loss parameter (Example:0): " << endl;
	cin >> min_stopLoss;
	cout << "Please enter the maximum Stop-loss parameter (Example:0.2): " << endl;
	cin >> max_stopLoss;
	
	cout << "Please enter the number of simulations to execute: " << endl;
	cin >> testNumber;

	cout << "All simulations are done with an initial cash invesment of 1000 " << endl;

	int maPointsS, maPointsM, maPointsL, slopePoints, modeUp, modeDown;
	double slopeMin, stopLoss;

	random_device rd;     // only used once to initialise (seed) engine
	mt19937 rng(rd());    // random-number engine used (Mersenne-Twister)

	uniform_int_distribution<int> generator_maPointsS(min_maPointsS, max_maPointsS);
	uniform_int_distribution<int> generator_maPointsM(min_maPointsM, max_maPointsM);
	uniform_int_distribution<int> generator_maPointsL(min_maPointsL, max_maPointsL);
	uniform_int_distribution<int> generator_slopePoints(min_slopePoints, max_slopePoints);
	uniform_real_distribution<double> generator_slopeMin(min_slopeMin, max_slopeMin);
	uniform_real_distribution<double> generator_stopLoss(min_stopLoss, max_stopLoss);
	uniform_int_distribution<int> generator_mode(0, 7);

	WhiteRobot robot;
	robot.loadData("index_data.csv");

	for (int i = 0; i < testNumber; i++)
	{
		maPointsS = generator_maPointsS(rng);
		maPointsM = generator_maPointsM(rng);
		maPointsL = generator_maPointsL(rng);
		slopePoints = generator_slopePoints(rng);

		slopeMin = generator_slopeMin(rng);
		slopeMin = floor((slopeMin * 10000) + .5) / 10000;
		stopLoss = generator_stopLoss(rng);
		stopLoss = floor((stopLoss * 10000) + .5) / 10000;

		modeUp = generator_mode(rng);
		modeDown = generator_mode(rng);

		//robot.setParameters(maPointsS, maPointsM, maPointsL, slopePoints, slopeMin, stopLoss, modeUp, modeDown);
		robot.whiteStrategy(intialCash);
		robot.saveSimulation("simulations.csv");
		if ((i+1) % 100 == 0) {
			cout << "Simulation number: " << i+1<<endl;
		}
	}

	menuPause();
}



// Execute a series of random White Robots with parameters in closed intervals
void RobotMenu::FixedBrainRadomWhite() {

	int testNumber, modeUp, modeDown;
	int max_maPointsS, max_maPointsM, max_maPointsL, max_slopePoints;
	int min_maPointsS, min_maPointsM, min_maPointsL, min_slopePoints;
	double max_slopeMin, max_stopLoss;
	double min_slopeMin, min_stopLoss;
	double intialCash = 1000;

	clearConsole();
	cout << "****************************************************************************" << endl;
	cout << "			5. Random White Robots with Closed range and fixed brains (logic) " << endl;
	cout << "****************************************************************************" << endl << endl;
	cout << " Enter the parameters of the simulations:" << endl << endl;

	cout << "Please enter the minimum small window points size (Example:2) min 2: " << endl;
	cin >> min_maPointsS;
	cout << "Please enter the maximum small window points size (Example:20): " << endl;
	cin >> max_maPointsS;
	cout << "Please enter the minimum medium window points size (Example:10) min 2: " << endl;
	cin >> min_maPointsM;
	cout << "Please enter the maximum medium window points size (Example:40): " << endl;
	cin >> max_maPointsM;
	cout << "Please enter the minimum large window points size (Example:15) min 2: " << endl;
	cin >> min_maPointsL;
	cout << "Please enter the maximum large window points size (Example:60): " << endl;
	cin >> max_maPointsL;

	cout << "Please enter the minimum number of points to use for calculating the Slope (Example:30) min 2: " << endl;
	cin >> min_slopePoints;
	cout << "Please enter the maximum number of points to use for calculating the Slope (Example:3000): " << endl;
	cin >> max_slopePoints;
	cout << "Please enter the minimum slope to establish a trend (Example:0): " << endl;
	cin >> min_slopeMin;
	cout << "Please enter the maximum slope to establish a trend (Example:0.2): " << endl;
	cin >> max_slopeMin;

	cout << "Please enter the minimum Stop-loss parameter (Example:0): " << endl;
	cin >> min_stopLoss;
	cout << "Please enter the maximum Stop-loss parameter (Example:0.2): " << endl;
	cin >> max_stopLoss;

	cout << "Please enter the logic Mode for Long Trades [1-7]: " << endl;
	cin >> modeUp;
	cout << "Please enter the logic Mode for Short Trades [1-7]: " << endl;
	cin >> modeDown;


	cout << "Please enter the number of simulations to execute: " << endl;
	cin >> testNumber;

	cout << "All simulations are done with an initial cash invesment of 1000 " << endl;

	int maPointsS, maPointsM, maPointsL, slopePoints;
	double slopeMin, stopLoss;

	random_device rd;     // only used once to initialise (seed) engine
	mt19937 rng(rd());    // random-number engine used (Mersenne-Twister)

	uniform_int_distribution<int> generator_maPointsS(min_maPointsS, max_maPointsS);
	uniform_int_distribution<int> generator_maPointsM(min_maPointsM, max_maPointsM);
	uniform_int_distribution<int> generator_maPointsL(min_maPointsL, max_maPointsL);
	uniform_int_distribution<int> generator_slopePoints(min_slopePoints, max_slopePoints);
	uniform_real_distribution<double> generator_slopeMin(min_slopeMin, max_slopeMin);
	uniform_real_distribution<double> generator_stopLoss(min_stopLoss, max_stopLoss);
	
	WhiteRobot robot;
	robot.loadData("index_data.csv");

	for (int i = 0; i < testNumber; i++)
	{
		maPointsS = generator_maPointsS(rng);
		maPointsM = generator_maPointsM(rng);
		maPointsL = generator_maPointsL(rng);
		slopePoints = generator_slopePoints(rng);

		slopeMin = generator_slopeMin(rng);
		slopeMin = floor((slopeMin * 10000) + .5) / 10000;
		stopLoss = generator_stopLoss(rng);
		stopLoss = floor((stopLoss * 10000) + .5) / 10000;

		//robot.setParameters(maPointsS, maPointsM, maPointsL, slopePoints, slopeMin, stopLoss, modeUp, modeDown);
		robot.whiteStrategy(intialCash);
		robot.saveSimulation("simulations.csv");
		if ((i + 1) % 10 == 0) {
			cout << "Simulation number: " << i + 1 << endl;
		}
	}

	menuPause();
}

//Main menu for accesing White Robot program 
void RobotMenu::mainMenu() {

	int option = 9;

	while (option != 0) {
		clearConsole();
		cout << "****************************************************************************" << endl;
		cout << "	White Robot an algorimic trading backtesting program written in C++ " << endl << endl;
		cout << "		Version 3.0: Random generators + flexible dual brain " << endl << endl;
		cout << "Select an option by entering the given number:" << endl << endl;
		cout << "1. Test and print the data from the CSV File" << endl;
		cout << "2. Execute a single instance of the White Robot strategy" << endl;
		cout << "3. Simulate a series of random White Robots with open range" << endl;
		cout << "4. Series of random White Robots with Closed range" << endl;
		cout << "5. Random White Robots with Closed range and fixed brain (logic)" << endl;
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
		else if (option == 4) {
			closedRadomWhite();
		}
		else if (option == 5) {
			FixedBrainRadomWhite();
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
