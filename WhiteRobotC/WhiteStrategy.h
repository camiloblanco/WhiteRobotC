//
// Created by Shankar on 25/09/2021.
//

#ifndef WHITEROBOTC_WHITESTRATEGY_H
#define WHITEROBOTC_WHITESTRATEGY_H
#include "WhiteRobot.h"

class WhiteStrategy
{
private:
public:
    WhiteStrategy();
    int stateAnalyser();
    int whiteStateMachine(double last_trade_investment);
    double orderAnalyser(double& current_cash, double& last_trade_investment, double& cfd_units);
    bool checkStopLoss(double last_trade_investment);
};



#endif //WHITEROBOTC_WHITESTRATEGY_H
