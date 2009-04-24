#include "festival.h"
#include "band.h"

#define NULL 0

StatusType Festival::ChangeBudget(int budget) {
	if (budget < 0) {
		return INVALID_INPUT;
	}
	this->budget = budget;
	return SUCCESS;
}

StatusType Festival::AddBand(int bandID, int price){
	if (bandID < 0) {
		return INVALID_INPUT;
	}
	if (price < 0) {
		return INVALID_INPUT;
	}
	Band* new_band = new Band(bandID, price);
	if (new_band == NULL) {
		return ALLOCATION_ERROR;
	}
		// Inputs OK, continue:
		
	return bands.insert(new_band);
}

StatusType Festival::RemoveBand(int bandID) {
	if (bandID < 0) {
		return INVALID_INPUT;
	}

//	bands.start();
//	while (!bands.end()) {
//		if ((*bands.getCurrent())->band_id == bandID) {
//			delete *bands.getCurrent();
//			bands.removeCurrent();
//			return SUCCESS;
//		}
//		bands.next();
//	}
	return FAILURE;
}
