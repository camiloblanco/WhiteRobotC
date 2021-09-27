//
// Created by Shankar on 25/09/2021.
//

#include "WhiteStrategy.h"



// Generates the order signal from the state of the State Machine
int WhiteStrategy::stateAnalyser()
{

    if (r.m_state == 3 || r.m_state == 4) {
        //Long position
        return 1;
    }
    else if (r.m_state == 6 || r.m_state == 7) {
        //Short position
        return -1;
    }
    else {
        //Not invested
        return 0;
    }
}

// State machine containing the brain (logic) of the robot
int WhiteStrategy::whiteStateMachine( double last_trade_investment) {

    if (checkStopLoss(last_trade_investment)) {
        // Slop loss limit reached in the previous point
        m_state = 1;
    } else if (m_state == 1) {
        if (m_slope[m_point] >= m_slopeMin_long && m_mode_long != 0) {
            //positive trend
            if ((m_ma_small_long[m_point] > m_ma_medium_long[m_point]) &&
            (m_ma_small_long[m_point - 1] < m_ma_medium_long[m_point - 1]) &&
            (m_mode_long == 1 || m_mode_long == 2 || m_mode_long == 3)) {
                //S>M  big cycle
                m_state = 2;
            }
            else if ((m_ma_small_long[m_point] > m_ma_large_long[m_point]) &&
            (m_ma_small_long[m_point - 1] < m_ma_large_long[m_point - 1]) &&
            (m_mode_long == 4 || m_mode_long == 5 )) {
                //S>L
                m_state = 3;
            }
            else if ((m_ma_small_long[m_point] > m_ma_medium_long[m_point]) &&
            (m_ma_small_long[m_point - 1] < m_ma_medium_long[m_point - 1]) &&
            (m_mode_long == 6 || m_mode_long == 7 )) {
                //S>M small cycle
                m_state = 4;
            }
        }
        else if (m_slope[m_point] < -m_slopeMin_short && m_mode_long != 0) {
            //negative trend
            if ((m_ma_small_short[m_point] < m_ma_medium_short[m_point]) &&
            (m_ma_small_short[m_point - 1] > m_ma_medium_short[m_point - 1]) &&
            (m_mode_short == 1 || m_mode_short == 2 || m_mode_short == 3)) {
                //S<M big cycle
                m_state = 5;
            }
            else if ((m_ma_small_short[m_point] < m_ma_large_short[m_point]) &&
            (m_ma_small_short[m_point - 1] > m_ma_large_short[m_point - 1]) &&
            (m_mode_short == 4 || m_mode_short == 5)) {
                //S<L
                m_state = 6;
            }
            else if ((m_ma_small_short[m_point] < m_ma_medium_short[m_point]) && (m_ma_small_short[m_point - 1] > m_ma_medium_short[m_point - 1]) && (m_mode_short == 6 || m_mode_short == 7)) {
                //S<M small cycle
                m_state = 7;
            }
        }
    }
    else if (m_state == 2) {
        if ((m_ma_small_long[m_point] > m_ma_large_long[m_point]) && (m_ma_small_long[m_point - 1] < m_ma_large_long[m_point - 1]) && (m_mode_long == 1 || m_mode_long == 2)) {
            //S>L big cycle
            m_state = 3;
        }
        else if ((m_ma_small_long[m_point] > m_ma_large_long[m_point]) && (m_ma_small_long[m_point - 1] < m_ma_large_long[m_point - 1]) && (m_mode_long == 3)) {
            //S>L medium cycle
            m_state = 4;
        }
    }
    else if (m_state == 3) {
        if ((m_ma_small_long[m_point] < m_ma_medium_long[m_point]) && (m_ma_small_long[m_point - 1] > m_ma_medium_long[m_point - 1]) && (m_mode_long == 1 || m_mode_long == 5)) {
            //S<M
            m_state = 4;
        }
        else if ((m_ma_small_long[m_point] < m_ma_large_long[m_point]) && (m_ma_small_long[m_point - 1] > m_ma_large_long[m_point - 1]) && (m_mode_long == 2 || m_mode_long == 4)) {
            //S<L
            m_state = 1;
        }
    }
    else if (m_state == 4) {
        if ((m_ma_small_long[m_point] < m_ma_large_long[m_point]) && (m_ma_small_long[m_point - 1] > m_ma_large_long[m_point - 1]) && (m_mode_long == 1 || m_mode_long == 3 || m_mode_long == 5 || m_mode_long == 6 )) {
            //S<L
            m_state = 1;
        }
        if ((m_ma_small_long[m_point] < m_ma_medium_long[m_point]) && (m_ma_small_long[m_point - 1] > m_ma_medium_long[m_point - 1]) && (m_mode_long == 7)) {
            //S<M
            m_state = 1;
        }
    }
    else if (m_state == 5) {
        if ((m_ma_small_short[m_point] < m_ma_large_short[m_point]) && (m_ma_small_short[m_point - 1] > m_ma_large_short[m_point - 1]) && (m_mode_short == 1 || m_mode_short == 2)) {
            //S<L big cycle
            m_state = 6;
        }
        else if ((m_ma_small_short[m_point] < m_ma_large_short[m_point]) && (m_ma_small_short[m_point - 1] > m_ma_large_short[m_point - 1]) && (m_mode_short == 3)) {
            //S<L medium cycle
            m_state = 7;
        }
    }
    else if (m_state == 6) {
        if ((m_ma_small_short[m_point] > m_ma_medium_short[m_point]) && (m_ma_small_short[m_point - 1] < m_ma_medium_short[m_point - 1]) && (m_mode_short == 1 || m_mode_short == 5)) {
            //S>M
            m_state = 7;
        }
        else if ((m_ma_small_short[m_point] > m_ma_large_short[m_point]) && (m_ma_small_short[m_point - 1] < m_ma_large_short[m_point - 1]) && (m_mode_short == 2 || m_mode_short == 4)) {
            //S>L
            m_state = 1;
        }
    }
    else if (m_state == 7) {
        if ((m_ma_small_short[m_point] > m_ma_large_short[m_point]) && (m_ma_small_short[m_point - 1] < m_ma_large_short[m_point - 1]) && (m_mode_short == 1 || m_mode_short == 3 || m_mode_short == 5 || m_mode_short == 6)) {
            //S>L
            m_state = 1;
        }
        else if ((m_ma_small_short[m_point] > m_ma_medium_short[m_point]) && (m_ma_small_short[m_point - 1] < m_ma_medium_short[m_point - 1]) && (m_mode_short == 7)) {
            //S>M
            m_state = 1;
        }
    }
    else {
        m_state = 1;
    }


    m_state_signal.push_back(m_state);
    // Return the order signal according to the state
    return stateAnalyser();
}

// Analyses the current and previous order signal to determine the current portfolio value
double WhiteStrategy::orderAnalyser(double& current_cash, double& last_trade_investment, double& cfd_units)
{

        double portfolio_value;

        // Evaluate order signals and update invesment position variables
        if (r.m_order_signal[r.m_point] == 1 && r.m_order_signal[r.m_point - 1] == 0) {
            //Start Long trade
            last_trade_investment = current_cash;
            current_cash = 0;
            cfd_units = last_trade_investment / r.m_prices[r.m_point];
            ++r.m_long_trades;
        }
        else if (r.m_order_signal[r.m_point] == 0 && r.m_order_signal[r.m_point - 1] == 1) {
            //Stop Long trade
            current_cash = cfd_units* r.m_prices[r.m_point];
            cfd_units = 0;
        }
        else if (r.m_order_signal[r.m_point] == -1 && r.m_order_signal[r.m_point - 1] == 0) {
            //Start short trade
            last_trade_investment = current_cash;
            current_cash = 0;
            cfd_units = last_trade_investment / r.m_prices[r.m_point];
            ++r.m_short_trades;
        }
        else if (r.m_order_signal[r.m_point] == 0 && r.m_order_signal[r.m_point - 1] == -1) {
            //Stop short trade
            current_cash = 2* last_trade_investment - cfd_units * r.m_prices[r.m_point];
            cfd_units = 0;
        }

        //Calculate the porfolio value
        if (r.m_order_signal[r.m_point] == 1) {
            portfolio_value = current_cash + cfd_units * r.m_prices[r.m_point];
        }
        else if (r.m_order_signal[r.m_point] == -1) {
            portfolio_value = current_cash + 2 * last_trade_investment - cfd_units * r.m_prices[r.m_point];
        }
        else {
            portfolio_value = current_cash;
        }

        // Calculate trade profit and performance
        if (r.m_order_signal[r.m_point] == 0 && r.m_order_signal[r.m_point - 1] == 1) {
            //Long trade detected
            r.m_long_trades_profit += portfolio_value - last_trade_investment;
            r.m_trade_profit.push_back(portfolio_value - last_trade_investment);
            if (portfolio_value > last_trade_investment) {
                //Succesfull long trade
                ++r.m_good_long_trades;
            }
        }
        else if (r.m_order_signal[r.m_point] == 0 && r.m_order_signal[r.m_point - 1] == -1) {
            //short trade detected
            r.m_short_trades_profit += portfolio_value - last_trade_investment;
            r.m_trade_profit.push_back(portfolio_value - last_trade_investment);
            if (portfolio_value > last_trade_investment) {
                ++r.m_good_short_trades;
            }
        }
        else {
            r.m_trade_profit.push_back(0);
        }

        r.m_current_cash.push_back(current_cash);
        r.m_cfd_units.push_back(cfd_units);
        r.m_last_trade_investment.push_back(last_trade_investment);

        //Return the current porfolio value
        return portfolio_value;
    }

// Analyses if the stop loss condition has been reached
bool WhiteStrategy::checkStopLoss(double last_trade_investment) {

    double curren_trade_profit = (r.m_portfolio_value[r.m_point-1] - last_trade_investment) / last_trade_investment;

    if ( (r.m_state == 3 || r.m_state == 4 ) &&  curren_trade_profit < - r.m_stopLoss) {
        r.m_stop_loss.push_back(1);
        r.m_long_stop_loss ++;
        return true;
    }
    else if ((r.m_state == 6 || r.m_state == 7) && curren_trade_profit < - r.m_stopLoss) {
        r.m_stop_loss.push_back(1);
        r.m_short_stop_loss ++;
        return true;
    }
    else if (r.m_point == r.m_prices.size()-1) {
        r.m_stop_loss.push_back(1);
        return true;
    }
    else {
        r.m_stop_loss.push_back(0);
        return false;
    }

}



