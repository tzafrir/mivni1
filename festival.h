#ifndef _FESTIVAL_H
#define _FESTIVAL_H

#define avl

#include <limits.h>

#include "library1.h"
#ifdef avl
#include "avl.h"
#else
#include "faketree.h"
#endif

#include "band.h"

class Festival {
	int budget;
	int discount;
	int min_price; // Post discount
	int num_of_bands;
	int sum_of_prices;
#ifdef avl
	AVL<Band, true> bands;
	AVL<BandByPrice, true> bands_by_price;
	AVL<BandByVotes, true> bands_by_votes;
#else
	FakeTree<Band> bands;
	FakeTree<BandByPrice> bands_by_price;
	FakeTree<BandByVotes> bands_by_votes;
#endif
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
};

#endif
