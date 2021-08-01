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

	WhiteRobot(int maPointsS_long,	int maPointsM_long, int maPointsL_long, double slopeMin_long, int mode_long, int maPointsS_short, int maPointsM_short, int maPointsL_short, double slopeMin_short, int mode_short, int slopePoints,	double stopLoss);


	//Getters and setters

	void setParameters(int maPointsS_long, int maPointsM_long, int maPointsL_long, double slopeMin_long, int mode_long, int maPointsS_short, int maPointsM_short, int maPointsL_short, double slopeMin_short, int mode_short, int slopePoints, double stopLoss);

	vector<double> getPrices();
	void printPrices();
	string getTimeStr();


	//public member functions	

	vector<string>  tokenize(string& str, char delim);

	void loadData(string fileName);
	
	double movingAverage(vector<double> prices, int windowSize);

	double movingSlope(const vector<double> prices, int windowSize);

	void generateSignals(vector<double> prices_window);

	
	int stateAnalyser(); 

	bool checkStopLoss(double last_trade_investment);

	int whiteStateMachine(double last_trade_investment);
	
	double orderAnalyser(double& current_cash, double& last_trade_investment, double& cfd_units);

	void whiteStrategy(double intialCash);



	void printResults();
	
	void saveSimulation(string fileName);

	void saveSimulationData(string fileName);


	~WhiteRobot();

private:

	//private variable members

	int m_maPointsS_long;
	int m_maPointsM_long;
	int m_maPointsL_long;
	double m_slopeMin_long;
	int m_mode_long;

	int m_maPointsS_short;
	int m_maPointsM_short;
	int m_maPointsL_short;
	double m_slopeMin_short;
	int m_mode_short;

	int m_slopePoints;
	double m_stopLoss;


	vector<string> m_dates;
	vector<double> m_prices;
	vector<double> m_volume;


	vector<double> m_ma_small_long;
	vector<double> m_ma_medium_long;
	vector<double> m_ma_large_long;
	vector<double> m_ma_small_short;
	vector<double> m_ma_medium_short;
	vector<double> m_ma_large_short;

	vector<double> m_slope;

	int m_point;
	int m_state;
	int m_long_stop_loss;
	int m_short_stop_loss;

	int m_long_trades;
	int m_short_trades;
	int m_good_long_trades;
	int m_good_short_trades;
	double m_long_trades_profit;
	double m_short_trades_profit;

	vector<int> m_state_signal;
	vector<int> m_order_signal;

	vector<double> m_current_cash;
	vector<double> m_cfd_units;
	vector<double> m_last_trade_investment;
	vector<double> m_portfolio_value;
	vector<double> m_trade_profit;
	vector<int> m_stop_loss;

};

