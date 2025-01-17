#pragma once
#include <exception>
#include <iostream>
#include <string>

using namespace std;

class GameOver: public exception {
	private:
		string message;

	public:
		GameOver(const char* msg)
			: message(msg)
		{
		}

		const char* what() const throw() {
			return message.c_str();
		}
	};

