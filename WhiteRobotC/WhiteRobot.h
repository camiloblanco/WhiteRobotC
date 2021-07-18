#pragma once
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

	void whiteStrategy(int maPointsS, int maPointsM, int maPointsL, int slopePoints, int slopeMin, int intialCash);
	void saveSimulation(string fileName);

	~WhiteRobot();

private:
	vector<string> m_dates;
	vector<double> m_prices;
	vector<double> m_volume;

	vector<double> m_ma_small;
	vector<double> m_ma_medium;
	vector<double> m_ma_large;
	vector<double> m_slope;

	vector<double> m_order_signal;


};

