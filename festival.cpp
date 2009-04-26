#include "festival.h"
#include "band.h"


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
	
	// Note: if we have a discount in effect, we add the band with a price
	//       that matches that discount.
	Band* new_band = new Band(bandID, price+discount);
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
		delete new_band_by_price;
		return ALLOCATION_ERROR;
	}
		
	if (ConvertStatus(bands.insert(new_band)) != SUCCESS) { // Band already exists, or other failure
		delete new_band;
		delete new_band_by_price;
		delete new_band_by_votes;
		return FAILURE;
	}
	bands_by_price.insert(new_band_by_price); // Must succeed
	bands_by_votes.insert(new_band_by_votes);
	
	if (price < min_price) {
		min_price = price;
	}
	
	return SUCCESS;
}

StatusType Festival::RemoveBand(int bandID) {
	if (bandID < 0) {
		return INVALID_INPUT;
	}
	Band has_id(bandID, 0);
	Band* the_band = bands.find(&has_id);
	if (the_band == NULL) {
		return FAILURE;
	}
	BandByPrice has_id_bp(the_band);
	BandByVotes has_id_bv(the_band);
	
	if (ConvertStatus(bands_by_votes.remove(&has_id_bv)) == SUCCESS) { 
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
	
	BandByVotes* bbv = new BandByVotes(the_band);
	if (bbv == NULL) {
		return ALLOCATION_ERROR;
	}
	bands_by_votes.remove(bbv); // Will never fail
	bands_by_votes.insert(bbv);
	return SUCCESS;
}

StatusType Festival::ChangePrice(int bandID, int price) {
	if ((bandID < 0) || (price <= 0)) {
		return INVALID_INPUT;
	}
	Band has_id(bandID, 0);
	Band* the_band = bands.find(&has_id);
	if (the_band == NULL) {
		return FAILURE;
	}
	BandByPrice* bbp = new BandByPrice(the_band);
	if (bbp == NULL) {
		return ALLOCATION_ERROR;
	}
	BandByVotes* bbv = new BandByVotes(the_band);
	if (bbv == NULL) {
		delete bbp;
		return ALLOCATION_ERROR;
	}
	// These are guaranteed to succeed:
	bands_by_price.remove(bbp);
	bands_by_votes.remove(bbv);
	
	// Include discount value when modifying the price
	the_band->price = price+discount;
	
	bands_by_price.insert(bbp);
	bands_by_votes.insert(bbv);
	
	min_price = bands_by_price.GetMin()->band->price - discount;
	
	return SUCCESS;
}

StatusType Festival::ChangeAllPrices(int discount) {
	if (discount <= 0) {
		return INVALID_INPUT;
	}
	
	if (discount > min_price) {
		return FAILURE;
	}
	
	this->discount += discount;
	min_price -= discount;
	return SUCCESS;
}

StatusType Festival::GetPrice(int bandID, int* price) {
	if ((bandID < 0) || (price == NULL)) {
		return INVALID_INPUT;
	}
	Band has_id(bandID, 0);
	Band* the_band = bands.find(&has_id);
	if (the_band == NULL) { // No cigar
		return FAILURE;
	}
	*price = the_band->price - discount;
	return SUCCESS;
}

