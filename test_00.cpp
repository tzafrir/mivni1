#include "festival.h"
#include <iostream>
#include <string>
#include "library1.h"
#include <limits.h>
#include "tests.h"

using namespace std;

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
	
	cout << endl << "AddVotes" << endl;
	
	expect(
		"bandID = -682",
		INVALID_INPUT,
		fest->AddVotes(-682, 1)
	);
	expect(
		"bandID = -1, numVotes = 0",
		INVALID_INPUT,
		fest->AddVotes(-1, 0)
	);
	expect(
		"bandID = 747, numVotes = 0",
		INVALID_INPUT,
		fest->AddVotes(747, 0)
	);
	expect(
		"numVotes = -1",
		INVALID_INPUT,
		fest->AddVotes(1, -1)
	);
	expect(
		"bandID = 747",
		FAILURE,
		fest->AddVotes(747, 1)
	);
	expect(
		"bandID = 0",
		SUCCESS,
		fest->AddVotes(0, 1)
	);
	
	cout << endl << "ChangePrice" << endl;
	
	expect(
		"bandID = -1",
		INVALID_INPUT,
		fest->ChangePrice(-1, 12)
	);
	expect(
		"price = -1",
		INVALID_INPUT,
		fest->ChangePrice(2, -1)
	);
	expect(
		"bandID = 509",
		FAILURE,
		fest->ChangePrice(509,12)
	);
	expect(
		"bandID = 42",
		FAILURE,
		fest->ChangePrice(42, 12)
	);
	expect(
		"bandID = 0, price = 500",
		SUCCESS,
		fest->ChangePrice(0, 500)
	);
	
	
	delete fest;
	
	return 0;
}

