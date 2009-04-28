#ifndef _FESTIVAL_H
#define _FESTIVAL_H

#define avl

#include <limits.h>

#include "library1.h"
#include "avl.h"
#include "band.h"

class Festival {
	int budget;
	int discount;
	int min_price; // Post discount
	int num_of_bands;
	int sum_of_prices;
	AVL<Band, true> bands;
	AVL<BandByPrice, true> bands_by_price;
	AVL<BandByVotes, true> bands_by_votes;
	StatusType ConvertStatus(AVLReturnCodes code) { // Helper function to receive statuses
		switch (code) {
			case Success : return SUCCESS;
			case Item_already_exist : return FAILURE;
			case Item_doesnt_exist : return FAILURE;
		}
		return FAILURE;
	}
	
		public:
	int _min_price() { return min_price; } // FIXME this shouldn't be here TODO
	Festival(int budget) : budget(budget), discount(0), min_price(INT_MAX), //FIXME
		num_of_bands(0), sum_of_prices() {};
	StatusType ChangeBudget(int budget);
	StatusType AddBand(int bandID, int price);
	StatusType RemoveBand(int bandID);
	StatusType AddVotes(int bandID, int numVotes);
	StatusType ChangePrice(int bandID, int price);
	StatusType ChangeAllPrices(int discount);
	StatusType GetPrice(int bandID, int* price);
	StatusType BandList(int** bandList, int* size);
	StatusType MaxNeededBudget(int* maxBudget);
};

#endif
