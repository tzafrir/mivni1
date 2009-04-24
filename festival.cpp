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
	if ((bandID < 0) || (price < 0)) {
		return INVALID_INPUT;
	}
	Band* new_band = new Band(bandID, price);
	if (new_band == NULL) {
		return ALLOCATION_ERROR;
	}
	BandByPrice* new_band_by_price = new BandByPrice(new_band);
	if (new_band_by_price == NULL) {
		delete new_band; // Leak proof
		return ALLOCATION_ERROR;
	}
	BandByVotes* new_band_by_votes = new BandByVotes(new_band);
	if (new_band_by_votes == NULL) {
		delete new_band;
		delete new_band_by_price; // This function's length is O(num of new objects)
		return ALLOCATION_ERROR;
	}
	
	// Fa
		
	if (bands.insert(new_band) != SUCCESS) {
		delete new_band;
		delete new_band_by_price;
		delete new_band_by_votes;
		return FAILURE;
	}
	bands_by_price.insert(new_band_by_price);
	bands_by_votes.insert(new_band_by_votes);
	return SUCCESS;
}

StatusType Festival::RemoveBand(int bandID) {
	if (bandID < 0) {
		return INVALID_INPUT;
	}
	Band has_id(bandID, 0);
	BandByPrice has_id_bp(&has_id);
	BandByVotes has_id_bv(&has_id);
	
	if (bands_by_votes.remove(&has_id_bv) == SUCCESS) { 
		bands_by_price.remove(&has_id_bp);
		bands.remove(&has_id); // This must be done last,
							   // the other trees depend on it
		return SUCCESS;
	} else {
		return FAILURE;
	}
}

StatusType Festival::AddVotes(int bandID, int numVotes) {
	if ((bandID < 0) || (numVotes <= 0)) {
		return INVALID_INPUT;
	}
	Band key(bandID, 0);
	Band* the_band = bands.find(&key);
	if (the_band == NULL) {
		return FAILURE;
	}
	
	the_band->votes += numVotes;
	
	BandByVotes* the_band_bv = new BandByVotes(the_band);
	bands_by_votes.remove(the_band_bv); // Will never fail
	bands_by_votes.insert(the_band_bv);
	return SUCCESS;
}

