#pragma
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

class WhiteRobot
{
public:
	WhiteRobot();

	vector<double> getPrices();

	void displayData();

	vector<string>  tokenize(string& str, char delim);

	void loadData(string fileName);
	
	double movingAverage(vector<double> prices, int windowSize);

	double movingSlope(const vector<double> prices, int windowSize);

	vector<double> generateSignals(vector<double> prices, int maPointsS, int maPointsM, int maPointsL, int slopePoints);

	
	int stateAnalyser(); 

	bool checkStopLoss(double stopLoss, double last_trade_investment);

	int whiteStateMachine(double slopeMin, double stopLoss, double last_trade_investment);
	
	double marketAnalyser(double& current_cash, double& last_trade_investment, double& cfd_units);

	void whiteStrategy(int maPointsS, int maPointsM, int maPointsL, int slopePoints, double slopeMin, double stopLoss, double intialCash);


	string getTimeStr();

	void printResults(int maPointsS, int maPointsM, int maPointsL, int slopePoints, double slopeMin, double stopLoss);
	
	void saveSimulation(string fileName, int maPointsS, int maPointsM, int maPointsL, int slopePoints, double slopeMin, double stopLoss);

	void saveSimulationData(string fileName);

	~WhiteRobot();

private:
	vector<string> m_dates;
	vector<double> m_prices;
	vector<double> m_volume;

	vector<double> m_ma_small;
	vector<double> m_ma_medium;
	vector<double> m_ma_large;
	vector<double> m_slope;

	int m_point;
	int m_state;
	vector<int> m_order_signal;

	vector<double> m_portfolio_value;
	vector<int> m_stop_loss;


};

