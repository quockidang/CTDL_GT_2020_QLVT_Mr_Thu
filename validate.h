#pragma once

#include <cstdlib>

#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>

#include <windows.h>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <algorithm> 
#include <cctype>
#include <locale>


#include "constant.h"
#include "globalvariable.h"
#include "lib.h"
using namespace std;

int X = 110;
int Y = 6;

int ValidateDateHour(int condition)
{
	int result = 0;
	int count = 0;
	while (true)
		while (_kbhit())
		{
			int key = _getch();
			if (key >= 48 && key <= 57)
			{
				int f = key - 48;
				cout << f;
				result = result * 10 + (f);
				count++;
			}
			else if (key == ENTER)
			{
				if (result > condition)
					continue;
				return result;
			}
			else if (key == BACKSPACE && count >0)
			{
				cout << "\b" << " " << "\b";
				count--;
				result /= 10;
			}
		}
	return result;
}

unsigned int ValidateIdentityCard()
{
	unsigned int result = 0;
	int count = 0;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();

			if (key >= 48 && key <= 57 && count <9)
			{
				int f = key - 48;
				if (count == 0 && key == 48)
				{
					continue;
				}
				else
				{
					cout << f;
					result = result * 10 + (f);
					count++;
				}
			}
			else if (key == 13)
			{

				return result;

			}
			else if (key == 8 && count >0)
			{
				cout << "\b" << " " << "\b";
				count--;
				result /= 10;
			}

		}
	}
	return result;
}

string ValidateName()
{
	string result = "";
	int count = 0;
	bool isSpaced = false;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();

			//if ( (key >= 65 && key <= 90) || (key >= 97 && key <= 142) || key = 32)
			if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || key == 32)
			{
				count++;
				if (!isSpaced && key == 32)
				{
					cout << (char)key;
					result += (char)key;
					isSpaced = true;
				}
				else if (key != 32)
				{
					cout << (char)key;
					result += (char)key;
					isSpaced = false;
				}

			}
			else if (key == 13)
			{

				return result;

			}
			else if (key == 8 && count >0)
			{
				cout << "\b" << " " << "\b";
				result.erase(1, result.length());

			}
			else if (key == 72)
			{

				return result;
			}
			else if (key == 80)
			{

				return result;
			}
		}
	}
	return result;
}


//only number and char
string ValidateID(bool &isMoveUp)
{
	string result = "";
	int count = 0;

	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();

			//if ( (key >= 65 && key <= 90) || (key >= 97 && key <= 142) || key = 32)
			if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || (key >= 48 && key <= 57))
			{
				count++;
				cout << (char)key;
				result += (char)key;
			}
			else if (key == 13)
			{
				isMoveUp = false;
				return result;

			}
			else if (key == 8 && count >0)
			{
				cout << "\b" << " " << "\b";
				result.erase(1, result.length());

			}
			else if (key == 72)
			{
				isMoveUp = true;
			}
			else if (key == 80)
			{
				isMoveUp = false;
				return result;
			}
		}
	}
	return result;
}






void CheckMoveAndValidateIdentityCard(unsigned int &result, bool &isMove, int &thuTu, bool &isSave, int distance)
{
	int lengh;
	if (result != 0)
		lengh = (int)log10(result) + 1;
	else lengh = 0;
	Gotoxy(X_ADD + distance, thuTu * 3 + Y_ADD);
	if (result != 0)
		cout << result;
	int count = lengh;
	bool isSpaced = false;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();
			if (key != 224 && key != SPACE && key != 0)
			{
				if (key >= 48 && key <= 57 && count <9)
				{
					int f = key - 48;
					if (count == 0 && key == 48)
						continue;
					else
					{
						cout << f;
						result = result * 10 + (f);
						count++;
					}
				}
				else if (key == ENTER)
					return;
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					count--;
					result /= 10;
				}
			}
			else if (key == 224)
			{
				key = _getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = _getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}//while kbhit
	} // while true

}

void CheckMoveAndValidateName_1(string &result, bool &isMove, int &thuTu, bool &isSave, int distance, int condition)
{
	int lengh = result.length();
	Gotoxy(X_ADD + distance, thuTu * 3 + Y_ADD);
	cout << result;
	int count = lengh;
	bool isSpaced = false;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();
			if (key != 224  && key != 0)
			{
				if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || key == SPACE || (key >= 48 && key <= 57) || key == 46 || key == 38)
				{
					if (count < condition)
					{
						count++;
						if (!isSpaced && key == SPACE)
						{
							cout << (char)key;
							result += (char)key;
							isSpaced = true;
						}
						else
						{
							cout << (char)key;
							result += (char)key;
							isSpaced = false;
						}
					}
				}
				else if (key == ENTER)
					return;
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					result.erase(result.length() - 1, 1);
					count--;
				}
			}
			else if (key == 224)
			{
				key = _getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = _getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}//kbhit
	}//true
}

void CheckMoveAndValdateIdPassenger(int &result, int distance)
{
	int lengh;
	if (result != 0)
		lengh = (int)log10(result)+1;
	else lengh = 0;
	Gotoxy(X_ADD + distance, Y_ADD);
	if (result != 0)
	cout << result;
	int count = lengh;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();
			if (key != 224 && key != SPACE && key != 0)
			{
				if (key >= 48 && key <= 57)
				{
					if (count < 9)
					{
						count++;
						cout << (char)key;
						result += (char)key;
					}
					
				}
				else if (key == ENTER)
					return;
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					
					count--;
					result = result / 10;

				}
			}
		
		}//kbhit
	}//while true
}


void CheckMoveAndValidateString(string &result, bool &isMove, int &ordinal, bool &isSave, int distance, int condition)
{
	int lengh = result.length();
	Gotoxy(X_ADD + distance, ordinal * 3 + Y_ADD);
	cout << result;
	int count = lengh;
	bool isSpaced = false;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();
			if (key != 224  && key != 0)
			{
				if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || key == SPACE || (key >= 48 && key <= 57) || key == 46 || key == 38)
				{
					if (count < condition)
					{
						count++;
						if (!isSpaced && key == SPACE)
						{
							cout << (char)key;
							result += (char)key;
							isSpaced = true;
						}
						else
						{
							cout << (char)key;
							result += (char)key;
							isSpaced = false;
						}
					}
				}
				else if (key == ENTER)
					return;
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					result.erase(result.length() - 1, 1);
					count--;
				}
			}
			else if (key == 224)
			{
				key = _getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = _getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}//kbhit
	}//true
}


//only char and number
void CheckMoveAndValidateID(string &result, bool &isMove, int &ordinal, bool &isSave, int distance, int condition)
{
	int lengh = result.length();
	Gotoxy(X_ADD + distance , ordinal * 3 + Y_ADD);
	cout << result;
	int count = lengh;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();
			if (key != 224 && key != SPACE && key != 0)
			{
				if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122)  || (key >= 48 && key <= 57))
				{
					if (count < condition)
					{
						count++;
						cout << (char)key;
						result += (char)key;
					}
					
				}
				else if (key == ENTER)
					return;
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					result.erase(result.length() - 1,1);
					count--;

				}
			}
			else if (key == 224)
			{
				key = _getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = _getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}//kbhit
	}//while true

}

void CheckMoveAndValidateNumber(int &result, bool &isMove, int &thuTu, bool &isSave,int distance, int condition)
{
	int lengh;
	if (result != 0)
		lengh = (int)log10(result)+1;
	else lengh = 0;
	Gotoxy(X_ADD + distance, thuTu * 3 + Y_ADD);
	if (result != 0)
	cout << result;
	int count = lengh;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();
			if (key != 224 && key != SPACE && key!= 0 )
			{
				if (key >= 48 && key <= 57)
				{
					int f = key - 48;
					if (count == 0 && key == 48)
						continue;
					else if (result * 10 + (f) <= condition)
						{
							cout << f;
							result = result * 10 + (f);
							count++;
						}
				}
				else if (key == ENTER)
				{
					if (result > condition)
						continue;
					return;
					
				}
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					count--;
					result /= 10;
				}
			}
			else if (key == 224)
			{
				key = _getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = _getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}//kbhit
	}//while tru

}


void CheckMoveAndValidateDateTime(int &result, bool &isMove, int &thuTu, bool &isSave, int condition, int distance)
{
	int lengh;
	if (result != 0)
		lengh = (int)log10(result) + 1;
	else lengh = 0;
	Gotoxy(X_ADD + distance + thuTu * 3, 3 * 2 + Y_ADD);
	if (result !=0)
	cout << result;
	int count = lengh;
	bool isSpaced = false;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();
			if (key != 224 && key != SPACE && key != 0)
			{
				if (key >= 48 && key <= 57)
				{
					int f = key - 48;
					if (count == 0 && key == SPACE)
						continue;
					else
					{
						if (result * 10 + (f) <= condition)
						{
							cout << f;
							result = result * 10 + (f);
							count++;
						}
						
						
					}
				}
				else if (key == ENTER)
				{
					if (result > condition)
						continue;
					return;
				}
				else if (key == 8 && count >0)
				{
					cout << "\b" << " " << "\b";

					count--;
					result /= 10;

				}
			}
			else if (key == 224)
			{
				key = _getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = _getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}
	}

}
void StandarString(string &result)
{

	for (size_t i = 1; i < result.length(); i++)
	{
		if (result[0] == ' ')
		{
			result.erase(0, 1);
			i--;
		}
		else if (result[i - 1] == ' ' && result[i] == ' ')
		{
			result.erase(i - 1, 1);
			i--;
		}
		else if (result[result.length() - 1] == ' ')
		{
			result.erase(result.length() - 1, 1);

		}
	}
	
}

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

void CheckMoveAndValidateTypeBill(string &result, bool &isMove, int &thuTu, bool &isSave, int distance, int condition)
{
	int lengh = result.length();
	Gotoxy(X_ADD + distance, thuTu * 3 + Y_ADD);
	cout << result;
	int count = lengh;
	bool isSpaced = false;
	while (true)
	{
		while (_kbhit())
		{
			int key = _getch();
			if (key != 224  && key != 0)
			{
				if (key == 78 || key == 88)
				{
					if (count < condition)
					{
						count++;
						if (!isSpaced && key == SPACE)
						{
							cout << (char)key;
							result += (char)key;
							isSpaced = true;
						}
						else
						{
							cout << (char)key;
							result += (char)key;
							isSpaced = false;
						}
					}
				}
				else if (key == ENTER)
					return;
				else if (key == BACKSPACE && count >0)
				{
					cout << "\b" << " " << "\b";
					result.erase(result.length() - 1, 1);
					count--;
				}
			}
			else if (key == 224)
			{
				key = _getch();
				if (key == KEY_UP)
				{
					isMove = true;
					return;
				}
				else
				{
					isMove = false;
					return;
				}
			}
			else if (key == 0)
			{
				key = _getch();
				if (key == KEY_F10)
				{
					isSave = true;
					return;
				}
			}
		}//kbhit
	}//true
}

