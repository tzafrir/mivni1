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
		"bandID = 2048, price = 1",
		SUCCESS,
		fest->AddBand(2048, 1)
	);
	cout << "\t" << SPACES << (fest->_min_price() == 1 ? GREEN : RED) << fest->_min_price() << WHITE << endl;
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
		"bandID = 2048 (again), price = 10",
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
	
	cout << endl << "GetPrice" << endl;
	int price;
	
	expect(
		"bandID = -1",
		INVALID_INPUT,
		fest->GetPrice(-1, &price)
	);
	expect(
		"price = NULL",
		INVALID_INPUT,
		fest->GetPrice(0, NULL)
	);
	expect(
		"bandID = 93746",
		FAILURE,
		fest->GetPrice(93746, &price)
	);
	expect(
		"bandID = 0",
		SUCCESS,
		fest->GetPrice(0, &price)
	);
	cout << "\t" << SPACES << price << endl;
	expect(
		"bandID = 2048",
		SUCCESS,
		fest->GetPrice(2048, &price)
	);
	cout << "\t" << SPACES << price << endl;
	expect(
		"ChangePrice 2048 to INT_MAX",
		SUCCESS,
		fest->ChangePrice(2048, INT_MAX)
	);
	expect(
		"GetPrice 2048",
		SUCCESS,
		fest->GetPrice(2048, &price)
	);
	cout << "\t" << SPACES << price << endl;
	
	cout << endl << "ChangeAllPrices" << endl;
	cout << "\tExpecting min_price to be 500" << endl;
	cout << "\t" << SPACES << (fest->_min_price() == 500 ? GREEN : RED) << fest->_min_price() << WHITE << endl;
	expect(
		"discount = 0",
		INVALID_INPUT,
		fest->ChangeAllPrices(0)
	);
	expect(
		"discount = 501 (makes 0 illegal)",
		FAILURE,
		fest->ChangeAllPrices(501)
	);
	expect(
		"Change 2048 to have price 128",
		SUCCESS,
		fest->ChangePrice(2048, 128)
	);
	expect(
		"discount = 2",
		SUCCESS,
		fest->ChangeAllPrices(2)
	);
	expect(
		"GetPrice from 2048 should show 126",
		SUCCESS,
		fest->GetPrice(2048, &price)
	);
	cout << "\t" << SPACES << (price == 126 ? GREEN : RED) << price << WHITE << endl;
	cout << "\tExpecting min_price to be 126" << endl;
	cout << "\t" << SPACES << (fest->_min_price() == 126 ? GREEN : RED) << fest->_min_price() << WHITE << endl;
	expect(
		"discount = 127, should fail",
		FAILURE,
		fest->ChangeAllPrices(127)
	);
	expect(
		"Remove 2048, min_price should be 498",
		SUCCESS,
		fest->RemoveBand(2048)
	);
	cout << "\t" << SPACES << (fest->_min_price() == 498 ? GREEN : RED) << fest->_min_price() << WHITE << endl;
	expect(
		"Add 5 with price 1, should be min_price",
		SUCCESS,
		fest->AddBand(5,1)
	);
	cout << "\t" << SPACES << (fest->_min_price() == 1 ? GREEN : RED) << fest->_min_price() << WHITE << endl;
	
	cout << endl << "Clean slate: deleting fest and making a new one" << endl;	
	
	delete fest;
	
	fest = new Festival(400);
	expect(
		"Expecting FAILURE on ChangeAllPrices",
		FAILURE,
		fest->ChangeAllPrices(1)
	);
	expect(
		"and MaxNeededBudget",
		FAILURE,
		fest->MaxNeededBudget(&price)
	);
	int *i, j;
	expect(
		"and BandList.",
		FAILURE,
		fest->BandList(&i, &j)
	);
	

	cout << endl << "MaxNeededBudget" << endl;
	
	expect(
		"maxBudget = NULL",
		INVALID_INPUT,
		fest->MaxNeededBudget(NULL)
	);

	
	delete fest;
	fest = new Festival(300);
	expect(
		"Add 0, 100",
		SUCCESS,
		fest->AddBand(0, 100)
	);
	expect(
		"Add 1, 300",
		SUCCESS,
		fest->AddBand(1, 300)
	);
	expect(
		"Add 2, 200",
		SUCCESS,
		fest->AddBand(2, 200)
	);
	int maxbudget;
	expect(
		"MaxNeededBudget should be 600",
		SUCCESS,
		fest->MaxNeededBudget(&maxbudget)
	);
	cout << "\t" << SPACES << (maxbudget == 600 ? GREEN : RED) << maxbudget << WHITE << endl;
	expect(
		"Discounting 50",
		SUCCESS,
		fest->ChangeAllPrices(50)
	);
	expect(
		"Expecting MaxNeededBudget to be 450",
		SUCCESS,
		fest->MaxNeededBudget(&maxbudget)
	);
	cout << "\t" << SPACES << (maxbudget == 450 ? GREEN : RED) << maxbudget << WHITE << endl;
	expect(
		"Add 3, 100",
		SUCCESS,
		fest->AddBand(3, 100)
	);
	expect(
		"Expecting MaxNeededBudget to be 550",
		SUCCESS,
		fest->MaxNeededBudget(&maxbudget)
	);
	cout << "\t" << SPACES << (maxbudget == 550 ? GREEN : RED) << maxbudget << WHITE << endl;
	expect(
		"Discounting 50",
		SUCCESS,
		fest->ChangeAllPrices(50)
	);
	expect(
		"Expecting MaxNeededBudget to be 350",
		SUCCESS,
		fest->MaxNeededBudget(&maxbudget)
	);
	cout << "\t" << SPACES << (maxbudget == 350 ? GREEN : RED) << maxbudget << WHITE << endl;
	expect(
		"Remove 1",
		SUCCESS,
		fest->RemoveBand(1)
	);
	expect(
		"Expecting MaxNeededBudget to be 150",
		SUCCESS,
		fest->MaxNeededBudget(&maxbudget)
	);
	cout << "\t" << SPACES << (maxbudget == 150 ? GREEN : RED) << maxbudget << WHITE << endl;
	expect(
		"Add 1, 850",
		SUCCESS,
		fest->AddBand(1, 850)
	);
	expect(
		"Expecting MaxNeededBudget to be 1000",
		SUCCESS,
		fest->MaxNeededBudget(&maxbudget)
	);
	cout << "\t" << SPACES << (maxbudget == 1000 ? GREEN : RED) << maxbudget << WHITE << endl;
	expect(
		"ChangePrice 0 to 1000",
		SUCCESS,
		fest->ChangePrice(0, 1000)
	);
	expect(
		"Expecting MaxNeededBudget to be 2000",
		SUCCESS,
		fest->MaxNeededBudget(&maxbudget)
	);
	expect(
		"ChangePrice 0 to 2000",
		SUCCESS,
		fest->ChangePrice(0, 2000)
	);
	expect(
		"Expecting MaxNeededBudget to be 3000",
		SUCCESS,
		fest->MaxNeededBudget(&maxbudget)
	);

	cout << "\t" << SPACES << (maxbudget == 3000 ? GREEN : RED) << maxbudget << WHITE << endl;
	expect(
		"RemoveBand 0",
		SUCCESS,
		fest->RemoveBand(0)
	);
		expect(
		"Expecting MaxNeededBudget to be 1000",
		SUCCESS,
		fest->MaxNeededBudget(&maxbudget)
	);

	cout << "\t" << SPACES << (maxbudget == 1000 ? GREEN : RED) << maxbudget << WHITE << endl;

	cout << endl << "Clean slate: deleting fest and making a new one" << endl;	
	
	delete fest;	
	fest = new Festival(300);
	expect(
		"Add 0, 100",
		SUCCESS,
		fest->AddBand(0, 100)
	);
	expect(
		"20 votes for 0",
		SUCCESS,
		fest->AddVotes(0, 20)
	);
	expect(
		"Add 1, 300",
		SUCCESS,
		fest->AddBand(1, 300)
	);
	expect(
		"10 votes",
		SUCCESS,
		fest->AddVotes(1, 10)
	);
	expect(
		"Add 2, 200",
		SUCCESS,
		fest->AddBand(2, 200)
	);
	expect(
		"5 votes",
		SUCCESS,
		fest->AddVotes(2,5)
	);
	int* bandList;
	int size;
	expect(
		"bandList = NULL",
		INVALID_INPUT,
		fest->BandList(NULL, &size)
	);
	expect(
		"size = NULL",
		INVALID_INPUT,
		fest->BandList(&bandList, NULL)
	);
	expect(
		"BandList",
		SUCCESS,
		fest->BandList(&bandList, &size)
	);
	cout << "Expecting size = 2" << endl;
	cout << "\t" << SPACES << (size == 2 ? GREEN : RED)
		<< size << WHITE << endl;
	for (int i = 0; i < size; i++) {
		cout << bandList[i] << " ";
	}
	cout << endl;
	
	cout << endl << "Clean slate: deleting fest and making a new one" << endl;	
	
	delete fest;	
	fest = new Festival(300);
	
	expect(
		"Add 2, 200",
		SUCCESS,
		fest->AddBand(2, 200)
	);
	expect(
		"Remove 2",
		SUCCESS,
		fest->RemoveBand(2)
	);
	delete fest;
	delete bandList;
	return 0;
}

