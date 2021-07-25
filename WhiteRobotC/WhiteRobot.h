/****************************************************************************************
* Project		:	AlgoTrading Jorge, David, Camilo, Shanka
* File			:	WhiteRobot.h
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
*							#GUARDS #INCLUDES AND #CONSTANTS							*
****************************************************************************************/

#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <fstream>
#include <vector> 
#include <numeric>
#include <algorithm>
#include <chrono>
#include <ctime>

using namespace std;

/****************************************************************************************
*									CLASS DECLARATION									*
****************************************************************************************/

class WhiteRobot
{

public:

	//constructors
	WhiteRobot();

	//Getters and setters
	vector<double> getPrices();
	void printPrices();
	string getTimeStr();

	//public member functions	
	

	vector<string>  tokenize(string& str, char delim);

	void loadData(string fileName);
	
	double movingAverage(vector<double> prices, int windowSize);

	double movingSlope(const vector<double> prices, int windowSize);

	vector<double> generateSignals(vector<double> prices, int maPointsS, int maPointsM, int maPointsL, int slopePoints);

	
	int stateAnalyser(); 

	bool checkStopLoss(double stopLoss, double last_trade_investment);

	int whiteStateMachine(double slopeMin, double stopLoss, double last_trade_investment);
	
	double orderAnalyser(double& current_cash, double& last_trade_investment, double& cfd_units);

	void whiteStrategy(int maPointsS, int maPointsM, int maPointsL, int slopePoints, double slopeMin, double stopLoss, double intialCash);


	

	void printResults(int maPointsS, int maPointsM, int maPointsL, int slopePoints, double slopeMin, double stopLoss);
	
	void saveSimulation(string fileName, int maPointsS, int maPointsM, int maPointsL, int slopePoints, double slopeMin, double stopLoss);

	void saveSimulationData(string fileName);


	~WhiteRobot();

private:

	//private variable members
	vector<string> m_dates;
	vector<double> m_prices;
	vector<double> m_volume;

	vector<double> m_ma_small;
	vector<double> m_ma_medium;
	vector<double> m_ma_large;
	vector<double> m_slope;

	int m_point;
	int m_state;

	int m_long_trades;
	int m_short_trades;

	vector<int> m_order_signal;

	vector<double> m_portfolio_value;
	vector<int> m_stop_loss;

};

