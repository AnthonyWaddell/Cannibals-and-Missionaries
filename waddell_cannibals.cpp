//----------------------------------------------------------------------------
// File:		waddell_cannibals.cpp
// 
// Description: Test Driver 
// 
// Programmer:	Anthony Waddell
//
// Functions:   main()
//				bool attempt(int e_lhs, int c_lhs, int e_rhs, int c_rhs,
//					int boat_pos);
//				bool isSolution(string move);
//				bool legal_Worldstate(int e_lhs, int c_lhs, int e_rhs, int 
//					c_rhs, int boat_pos);
//				void print(string state)
// 
// Environment: Hardware: PC, i7
//              Software: OS: Windows 10 
//              Compiles under Microsoft Visual C++ 2015
//---------------------------------------------------------------------------
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <sstream>

using namespace std;

//Vectors for attempted moves and solution path
vector<string> tried;
vector<string> solution_Path;

// Forward function declararions
bool attempt(int e_lhs, int c_lhs, int e_rhs, int c_rhs, int boat_pos);
bool isSolution(string move);
bool legal_Worldstate(int e_lhs, int c_lhs, int e_rhs, int c_rhs, int boat_pos);
void print(string state);

//-----------------------------------------------------------------------------
// Function:	main()
//
// Title:		Program entry point
//
// Description: This file contains function main() which solves the explorers
//					and cannibals problem recursively
//
// Programmer:	Anthony Waddell
// Date:		11-02-17
// Version:		1.0
//  
// Environment: Hardware: PC, i7
// Software:	OS: Windows 10 
//				Compiles under Microsoft Visual C++ 2015
// 
// Input:		N/A
// Output:		Screen display to the console of a the path of moves taken 
//					by three cannibals and three explorers to cross a river
// Calls:		bool attempt(int e_lhs, int c_lhs, int e_rhs, int c_rhs, 
//					int boat_pos);
//				void print(string state)
// Called By:	N/A
// Parameters:	void
// Returns:		EXIT_SUCCESS upon successful execution
// History Log:	11-03-17 AW Completed Project
//-----------------------------------------------------------------------------
int main(void)
{
	cout << "Cannibals and Explorers by Anthony Waddell" << endl << endl;
	bool solve = attempt(3, 3, 0, 0, 0);
	for (int i = 0; i < solution_Path.size(); i++)
	{
		print(solution_Path[i]);
	}
	system("pause");
	return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------
// Function:	bool attempt(int e_lhs, int c_lhs, int e_rhs, int c_rhs,
//					int boat_pos)
//
// Title:		Attempts to move the cannibals and exlorers across the river
//
// Description: Attempts to move cannibals and explorers across the river
//					recursively until all three cannibals and explorers move
//					from the left bank to the right bank. 
//
// Programmer:	Anthony Waddell
// Date:		11-02-17
// Version:		1.0
//  
// Environment: Hardware: PC, i7
// Software:	OS: Windows 10 
//				Compiles under Microsoft Visual C++ 2015
// 
// Input:		N/A
// Output:		Screen display to the console of a the path of moves taken 
//					by three cannibals and three explorers to cross a river
// Calls:		bool attempt(int e_lhs, int c_lhs, int e_rhs, int c_rhs, 
//					int boat_pos); recursively
//				bool isSolution(string move);
//				bool legal_Worldstate
// Called By:	int main(void)
//				bool attempt(int e_lhs, int c_lhs, int e_rhs, int c_rhs,
//					int boat_pos); recursively
// Parameters:	int e_lhs; the number of explorers on the left river bank
//				int c_lhs; the number of cannibals on the left river bank
//				int e_rhs; the number of explorers on the right river bank
//				int c_rhs; the number of cannibals on the right river bank
//				int boat_pos; the side of the river that the boat is on 
//					(0 = left, 1 = right)
// Returns:		true if solution if found, false if not
// History Log:	11-02-17 AW completed function
//-----------------------------------------------------------------------------
bool attempt(int e_lhs, int c_lhs, int e_rhs, int c_rhs, int boat_pos)
{
	bool temp = false;

	//Take the numerical starting values and place into string
	stringstream ss;
	ss << e_lhs << c_lhs << e_rhs << c_rhs << boat_pos;
	string str = ss.str();

	//Test for solution case
	if (isSolution(str))
	{
		tried.push_back(str);
		for (int i = 0; i < tried.size(); i++)
		{
			//Only add the solution steps
			if (find(solution_Path.begin(), solution_Path.end(), 
				str) == solution_Path.end()) 
			{
				solution_Path.push_back(tried[i]);
			}
		}
		return true;
	}

	//Test for repeated states
	else if (find(tried.begin(), tried.end(), (str)) != tried.end())
	{
		return false;
	}

	//Test for illegal state
	else if (!legal_Worldstate(e_lhs, c_lhs, e_rhs, c_rhs, boat_pos))
	{
		return false;
	}

	//Attempt to move
	else
	{
		tried.push_back(str);

		//If the boat is on the left bank
		if (boat_pos == 0)
		{
			//Move 2 cannibals from the left to the right
			temp = attempt(e_lhs, c_lhs - 2, e_rhs, c_rhs + 2, 1);
			//Move 1 cannibal from the left to the right
			temp = attempt(e_lhs, c_lhs - 1, e_rhs, c_rhs + 1, 1);
			//Move on cannibal and one explorer from the left to the right
			temp = attempt(e_lhs - 1, c_lhs - 1, e_rhs + 1, c_rhs + 1, 1);
			//Move 2 explorers from the left to the right
			temp = attempt(e_lhs - 2, c_lhs, e_rhs + 2, c_rhs, 1);
			//Move one explorer from the left to the right
			temp = attempt(e_lhs - 1, c_lhs, e_rhs + 1, c_rhs, 1);
		}

		//If the boat is on the right bank
		else
		{
			//Move one cannibal from the right to the left
			temp = attempt(e_lhs, c_lhs + 1, e_rhs, c_rhs - 1, 0);
			//Move 2 cannibals from the right to the left
			temp = attempt(e_lhs, c_lhs + 2, e_rhs, c_rhs - 2, 0);
			//Move one cannibal and one explorer from the right to the left
			temp = attempt(e_lhs + 1, c_lhs + 1, e_rhs - 1, c_rhs - 1, 0);
			//Move one explorer from the right to the left
			temp = attempt(e_lhs + 1, c_lhs, e_rhs - 1, c_rhs, 0);
			//Move two explorers from the right to the left
			temp = attempt(e_lhs + 2, c_lhs, e_rhs - 2, c_rhs, 0);
		}
	}
	return temp;
}

//-----------------------------------------------------------------------------
// Function:	bool legal_Worldstate(int e_lhs, int c_lhs, int e_rhs, 
//					int c_rhs, int boat_pos)
//
// Title:		Determines legality of move
//
// Description: Checks to see if a move would cause there to be more than 3 or 
//					less than 0 of either group on either side or if there
//					there would be more cannibals than explorers. 
//
// Programmer:	Anthony Waddell
// Date:		11-02-17
// Version:		1.0
//  
// Environment: Hardware: PC, i7
// Software:	OS: Windows 10 
//				Compiles under Microsoft Visual C++ 2015
// 
// Input:		N/A
// Output:		N/A
// Calls:		N/A
// Called By:	bool attempt()
// Parameters:	int e_lhs; the number of explorers on the left river bank
//				int c_lhs; the number of cannibals on the left river bank
//				int e_rhs; the number of explorers on the right river bank
//				int c_rhs; the number of cannibals on the right river bank
//				int boat_pos; the side of the river that the boat is on 
//					(0 = left, 1 = right)
// Returns:		true if solution if move is legal, false if not
//
// History Log:	11-02-17 AW completed function
//-----------------------------------------------------------------------------
bool legal_Worldstate(int e_lhs, int c_lhs, int e_rhs, int c_rhs, int boat_pos)
{
	return !((e_lhs < 0 || c_lhs < 0 || e_rhs < 0 || c_rhs < 0 || boat_pos < 0) ||
		(e_lhs > 3 || c_lhs > 3 || e_rhs > 3 || c_rhs > 3 || boat_pos > 1) ||
		((c_lhs > e_lhs && e_lhs != 0) || (c_rhs > e_rhs && e_rhs != 0)));
}

//-----------------------------------------------------------------------------
// Function:	bool isSolution(string move)
//
// Title:		Tests for solution
//
// Description: Tests string to see if all cannibals and explorers crossed the
//					river
//
// Programmer:	Anthony Waddell
// Date:		11-02-17
// Version:		1.0
//  
// Environment: Hardware: PC, i7
// Software:	OS: Windows 10 
//				Compiles under Microsoft Visual C++ 2015
// 
// Input:		N/A
// Output:		N/A
// Calls:		N/A
// Called By:	bool attempt()
// Parameters:	string move; the string representation of the world state
// Returns:		true if solution state found, false if not
//
// History Log:	11-02-17 AW completed function
//-----------------------------------------------------------------------------
bool isSolution(string move)
{
	string solution = "00331";
	if (move == solution)
		return true;
	else
		return false;
}

//-----------------------------------------------------------------------------
// Function:	void print(string state)
//
// Title:		prints out state
//
// Description: Prints any of the 15 possible states. Special cases for states
//					beginning with '0' or '00' since switch statements read past
//					the '0' or '00'
//
// Programmer:	Anthony Waddell
// Date:		11-02-17
// Version:		1.0
//  
// Environment: Hardware: PC, i7
// Software:	OS: Windows 10 
//				Compiles under Microsoft Visual C++ 2015
// 
// Input:		N/A
// Output:		N/A
// Calls:		N/A
// Called By:	int main(void)
// Parameters:	string state; the string representation of the world state
// Returns:		void
//
// History Log:	11-03-17 AW completed function
//-----------------------------------------------------------------------------
void print(string state)
{
	int s_int = atoi(state.c_str());
	switch (s_int)
	{
	case 33000:
		cout << "EEECCC [__]              " << endl;
		break;
	case 31021:
		cout << "EEEC          [__]    CC" << endl;
		break;
	case 32010:
		cout << "EEECC  [__]             C" << endl;
		break;
	case 30031:
		cout << "EEE           [__]    CCC" << endl;
		break;
	case 31020:
		cout << "EEEC   [__]          CC" << endl;
		break;
	case 11221:
		cout << "EC            [__]   EECC" << endl;;
		break;
	case 22110:
		cout << "EECC   [__]          EC" << endl;
		break;
	case 2311:
		cout << "CCC           [__]   EEEC" << endl;
		break;
	case 3300:
		cout << "CCC    [__]          EEE" << endl;
		break;
	case 1321:
		cout << "C             [__]  EEECC" << endl;
		break;
	case 2310:
		cout << "CC     [__]          EEEC" << endl;
		break;
	case 331:
		cout << "              [__] EEECCC" << endl;
		break;
	case 11220:
		cout << "EC     [__]          EECC" << endl;
		break;
	case 22111:
		cout << "EECC          [__] ME" << endl;
		break;
	case 32011:
		cout << "EEECC         [__]      C" << endl;
		break;
	default:
		cout << "Invalid state" << endl;
	}
}