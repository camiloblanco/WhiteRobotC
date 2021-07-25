/****************************************************************************************
* Project		:	AlgoTrading Jorge, David, Camilo, Shanka
* Lenguaje		:	C++
* License		:	Apache License Ver 2.0, www.apache.org/licenses/LICENSE-2.0
* Description	:	Header file for the RobotMenu Class
*					Menus and sub-menus for using the Robot
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
using namespace std;
#include<iostream>
#include<string>
#include<stdlib.h>

#include "WhiteRobot.h"
/****************************************************************************************
*									CLASS DECLARATION									*
****************************************************************************************/
class RobotMenu
{
public:
	//constructors
	RobotMenu();

	// Console manipulation member functions
	void clearConsole();
	void menuPause();
	void readLine(string& description);

	//public member functions
	void testData();
	void executeWhite();
	void mainMenu();
	
};

