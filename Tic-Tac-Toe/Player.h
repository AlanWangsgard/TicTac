#pragma once
#include<iostream>;
using namespace std;
	class Player
	{
	public:
		std::string playerName;
		int playerNumber;
		std::string playerSymbol;
		/*void setName();*/

		void setName(std::string);
		void setNumber(int);
		void setSymbol(std::string);
	};

