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
	
	// Try to insert into each one of the three trees.
		
	if ((bands.insert(new_band) != SUCCESS) || 
			(bands_by_price.insert(new_band_by_price) != SUCCESS) ||
			(bands_by_votes.insert(new_band_by_votes) != SUCCESS)) {
		delete new_band;
		delete new_band_by_price;
		delete new_band_by_votes;
		return FAILURE;
	}
	return SUCCESS;
}

StatusType Festival::RemoveBand(int bandID) {
	if (bandID < 0) {
		return INVALID_INPUT;
	}
	Band has_id(bandID, 0);
	BandByPrice has_id_bp(&has_id);
	BandByVotes has_id_bv(&has_id);
	
	// Leap of faith: I strongly believe that if a band is in one tree,
	// it is in all of them. It must be. I will make it so.
	
	if (bands_by_votes.remove(&has_id_bv) == SUCCESS) { 
		bands_by_price.remove(&has_id_bp);
		bands.remove(&has_id); // This must be done last,
							   // the other trees depend on it
		return SUCCESS;
	} else {
		return FAILURE;
	}
}

