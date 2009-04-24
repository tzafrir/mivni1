#include "festival.h"
#include <iostream>
#include <string>
#include "library1.h"
#include <limits.h>

using namespace std;

string stat2str(StatusType stat) {
	switch ( stat ) {
		case ALLOCATION_ERROR	:	return "ALLOCATION_ERROR";
		case INVALID_INPUT		:	return "INVALID_INPUT";
		case SUCCESS			:	return "SUCCESS";
		case FAILURE			:	return "FAILURE";
		default					:	return "\033[31mUNDEFINED\033[0m";
	}
}

void expect(string message, StatusType exp, StatusType result) {
	const unsigned int len = 40;
	message += ":";
	while(message.length() < len) {
		message += " ";
	}
	if (result == exp) cout << "\t" << message << "\033[32mOK\033[0m\t\t" + stat2str(result) << endl;
	else cout << "\t" << message << "\033[31mFAIL\033[0m\t\t" + stat2str(result) << endl;
}

int main(int argc, char** argv) {
	
	Festival* fest = new Festival(1024);
	
	cout << endl << "ChangeBudget" << endl;
	
	expect(
		"Budget = 3",
		SUCCESS,
		fest->ChangeBudget(3)
	);
	expect(
		"Budget = INT_MAX",
		SUCCESS,
		fest->ChangeBudget(INT_MAX)
	);
	expect(
		"Budget = -1",
		INVALID_INPUT,
		fest->ChangeBudget(-1)
	);
	expect(
		"Budget = INT_MIN",
		INVALID_INPUT,
		fest->ChangeBudget(INT_MIN)
	);
	expect(
		"Budget = 0",
		SUCCESS,
		fest->ChangeBudget(0)
	);
	
	cout << endl << "AddBand" << endl;
	
	expect(
		"bandID = 0",
		SUCCESS,
		fest->AddBand(0, 1)
	);
	expect(
		"bandID = 42",
		SUCCESS,
		fest->AddBand(42, 96)
	);
	
	expect(
		"bandID = 2048",
		SUCCESS,
		fest->AddBand(2048, 1)
	);
	expect(
		"bandID = -1",
		INVALID_INPUT,
		fest->AddBand(-1, 1)
	);
	expect(
		"bandID = 0 (again)",
		FAILURE,
		fest->AddBand(0, 1)
	);
	expect(
		"bandID = 42 (again)",
		FAILURE,
		fest->AddBand(42, 960)
	);
	expect(
		"bandID = 42 (again)",
		FAILURE,
		fest->AddBand(42, 960)
	);
	
	expect(
		"bandID = 2048 (again), price = -1023",
		INVALID_INPUT,
		fest->AddBand(2048, -1023)
	);
	expect(
		"bandID = 2048 (again)",
		FAILURE,
		fest->AddBand(2048, 10)
	);
	
	expect(
		"price = -1",
		INVALID_INPUT,
		fest->AddBand(4096, -1)
	);
	
	cout << endl << "RemoveBand" << endl;
	
	expect(
		"bandID = -1",
		INVALID_INPUT,
		fest->RemoveBand(-1)
	);
	expect(
		"bandID = 1 (not in)",
		FAILURE,
		fest->RemoveBand(1)
	);
	expect(
		"bandID = 42",
		SUCCESS,
		fest->RemoveBand(42)
	);
//	
//	cout << endl << "AddVotes" << endl;
//	
//	expect(
//		"bandID = -682",
//		INVALID_INPUT,
//		fest->AddVotes(-682, 1)
//	);

	
	
	
	
	delete fest;
	
	return 0;
}

