#ifndef _FESTIVAL_H
#define _FESTIVAL_H

#include "library1.h"
#include "faketree.h"

#include "band.h"

class Festival {
	int budget;
	int discount;
	int min_price;
	int num_of_bands;
	int sum_of_prices;
	FakeTree<Band*> bands;
	FakeTree<BandByPrice*> bands_by_price;
	FakeTree<BandByVotes*> bands_by_votes;
		public:
	Festival(int budget) : budget(budget) {};
	StatusType ChangeBudget(int budget);
	StatusType AddBand(int bandID, int price);
	StatusType RemoveBand(int bandID);
	StatusType AddVotes(int bandID, int numVotes);
};

#endif
