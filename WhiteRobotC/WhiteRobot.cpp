#include "WhiteRobot.h"



WhiteRobot::WhiteRobot()
{
}

vector<string> WhiteRobot::tokenize(string& str, char delim) {
	size_t start;
	size_t end = 0;
	vector<string> result;

	while ((start = str.find_first_not_of(delim, end)) != string::npos)
	{
		end = str.find(delim, start);
		result.push_back(str.substr(start, end - start));
	}

	return result;
}



void WhiteRobot::loadData(string fileName) {

	string line;
	ifstream myStream(fileName);
	if (myStream.is_open()) {

		getline(myStream, line);

		cout << "The first line is: " << line << endl;


		while (getline(myStream, line)) {

			//Parse the line 
			vector<string> fields = tokenize(line, ',');
			double price = stod(fields[1]);

			// Store the readed values
			if (price > 0) {
				m_dates.push_back(fields[0]);
				m_prices.push_back(price);
			}
		}
		myStream.close();
	}
	else
	{
		cout << "There was a problem opening the file: " << fileName << endl;
	}
}

vector<double> WhiteRobot::getPrices() {
	return this->m_prices;
}

void WhiteRobot::displayData() {
	cout << "Printing Data" << endl;
	for (auto& element : m_prices) {
		cout << element << endl;
	}
}

double WhiteRobot::movingAverage(vector<double> prices, int windowSize) {
	vector<double> window;
	window = vector < double > (prices.end() - windowSize, prices.end());
	auto n = window.size();
	double average = 0.0;
	if (n != 0) {
		average = accumulate(window.begin(), window.end(), 0.0) / n;
	}
	return average;
}

double WhiteRobot::movingSlope(const vector<double> prices, int windowSize) {
	//from https://stackoverflow.com/questions/18939869/how-to-get-the-slope-of-a-linear-regression-line-using-c
	
	vector<double> y;
	y = vector < double >(prices.end() - windowSize, prices.end());
	auto n = y.size();
	
	vector<double> x(n);
	iota(x.begin(), x.end(), 0); // x will become: [0..n]

	const auto s_x = std::accumulate(x.begin(), x.end(), 0.0);
	const auto s_y = std::accumulate(y.begin(), y.end(), 0.0);
	const auto s_xx = std::inner_product(x.begin(), x.end(), x.begin(), 0.0);
	const auto s_xy = std::inner_product(x.begin(), x.end(), y.begin(), 0.0);
	const auto slope = (n * s_xy - s_x * s_y) / (n * s_xx - s_x * s_x);
	return slope;
}


vector<double> WhiteRobot::generateSignals(vector<double> prices, int maPointsS, int maPointsM, int maPointsL, int slopePoints) {
	vector<double> signals;
	double maS, maM, maL, slope;
	maS = movingAverage(prices, maPointsS);
	signals.push_back(maS);
	maM = movingAverage(prices, maPointsM);
	signals.push_back(maM);
	maL = movingAverage(prices, maPointsL);
	signals.push_back(maL);
	slope = movingSlope(prices, slopePoints);
	signals.push_back(slope);
	return signals;
}

void WhiteRobot::whiteStrategy(int maPointsS, int maPointsM, int maPointsL, int slopePoints, int slopeMin, int intialCash) {
	cout << "White strategy" << endl;

	if (slopePoints > maPointsL && maPointsL > maPointsM && maPointsM > maPointsS) {

		// Loop over the first part of the dataset
		for (auto it = m_prices.begin(); it != m_prices.begin() + slopePoints; ++it) {
			m_ma_small.push_back(0.0);
			m_ma_medium.push_back(0.0);
			m_ma_large.push_back(0.0);
			m_slope.push_back(0.0);
		}

		// Loop over the tradable part of the dataset
		for (auto it = m_prices.begin() + slopePoints; it != m_prices.end(); ++it) {
			vector<double> window;
			window = vector < double >(it - slopePoints, it);
			vector<double> signals = generateSignals(window, maPointsS, maPointsM, maPointsL, slopePoints);
			m_ma_small.push_back(signals[0]);
			m_ma_medium.push_back(signals[1]);
			m_ma_large.push_back(signals[2]);
			m_slope.push_back(signals[3]);
		}
	}
	else
	{
		cout << " Window MA Small: " << maPointsS << endl;
		cout << " Window MA Medium: " << maPointsM << endl;
		cout << " Window MA Large: " << maPointsL << endl;
		cout << " Window Slope: " << slopePoints << endl;
		cout << " Strategy imposible to execute" << endl;
	}	
}


void WhiteRobot::saveSimulation(string fileName) {

	// Create an output filestream object
	ofstream outFile(fileName);

	// write the file headers
	outFile << "Date" << "," << "Price" << "," << "MA_Small" << "," << "MA_Medium" << "," << "MA_Large" << "," << "MA_Slope" << endl;

	// write data to the file
	for (int i = 0; i != m_prices.size(); i++) {

		//savedFile << m_dates[i] << "," << m_prices[i] << "," << m_ma_small[i] << "," << m_ma_medium[i] << "," << m_ma_large[i] << "," << m_slope[i] << "," << m_order_signal[i] << endl;
		outFile << m_dates[i] << "," << m_prices[i] << "," << m_ma_small[i] << "," << m_ma_medium[i] << "," << m_ma_large[i] << "," << m_slope[i] << endl;
	}

	// close the output file
	outFile.close();
	cout << "Simulation saved" << endl;
}

WhiteRobot::~WhiteRobot()
{
}

