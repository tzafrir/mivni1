#ifndef _FESTIVAL_H
#define _FESTIVAL_H

#include "library1.h"
#include "avl.h"
#include "band.h"

class Festival {
	int budget;
	unsigned long discount;
	int min_price; // Post discount
	unsigned int num_of_bands;
	unsigned long sum_of_prices;
	AVL<Band, true> bands;
	AVL<BandByPrice, true> bands_by_price;
	AVL<BandByVotes, true> bands_by_votes;
	class GetBands : public AVL<BandByVotes,true>::Predicate {
		int** bandList;
		int i;
		int budget;
		int discount;
			public:
		GetBands(int** bandList, int budget, int discount) : bandList(bandList), i(0), budget(budget), discount(discount) {} ;
		bool DoWork(BandByVotes* b);
	};
	class CountBands : public AVL<BandByVotes,true>::Predicate {
		int budget;
		int discount;
			public:
		int count;
		CountBands(int budget, int discount) : budget(budget), discount(discount), count(0) {} ;
		bool DoWork(BandByVotes* b);
	};
	

		public:
	Festival(int budget) : budget(budget), discount(0), min_price(-1), 
		num_of_bands(0), sum_of_prices(0) {};
	StatusType ChangeBudget(int budget);
	StatusType AddBand(int bandID, int price);
	StatusType RemoveBand(int bandID);
	StatusType AddVotes(int bandID, int numVotes);
	StatusType ChangePrice(int bandID, int price);
	StatusType ChangeAllPrices(int discount);
	StatusType GetPrice(int bandID, int* price);
	StatusType MaxNeededBudget(int* maxBudget);
	StatusType BandList(int** bandList, int* size);
};

#endif
