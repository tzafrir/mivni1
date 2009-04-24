#ifndef _FESTIVAL_H
#define _FESTIVAL_H

#include "library1.h"
#include "sortedlist.h"

#include "band.h"

class Festival {
	int budget;
	int discount;
	int min_price;
	int num_of_bands;
	int sum_of_prices;
	SortedList<Band*> bands;
		public:
	Festival(int budget) : budget(budget) {};
	~Festival() {
		bands.start();
		while(!bands.end()){
			delete *bands.getCurrent();
			bands.next();
		}
	}
	StatusType ChangeBudget(int budget);
	StatusType AddBand(int bandID, int price);
	StatusType RemoveBand(int bandID);
};

#endif
