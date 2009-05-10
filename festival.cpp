#include "festival.h"
#include "band.h"
#include <stdlib.h> 

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
	Band* new_band = NULL; //init to null, so we'll be able to call delete on them before the new
	BandByPrice* new_band_by_price = NULL;
	BandByVotes* new_band_by_votes = NULL;

	try
	{
		// Note: if we have a discount in effect, we add the band with a price
		//       that matches that discount.
		new_band = new Band(bandID, price+discount);
		new_band_by_price = new BandByPrice(new_band);
		new_band_by_votes = new BandByVotes(new_band);;

		if (bands.insert(new_band) != bands.Success) { // Band already exists, or other failure
			delete new_band;
			delete new_band_by_price;
			delete new_band_by_votes;
			return FAILURE;
		}

		new_band = NULL; //we dont want to free new_band in the catch block
						//if we already inserted it to the tree
	
		
		bands_by_price.insert(new_band_by_price); // Must succeed
		new_band_by_price = NULL; //we dont want to free new_band_by_price in the catch block
						//if we already inserted it to the tree
	
		bands_by_votes.insert(new_band_by_votes);// Must succeed

	}
	catch (std::bad_alloc&)
	{
		delete new_band;
		delete new_band_by_price;
		delete new_band_by_votes;
		return ALLOCATION_ERROR;
	}
	
	if ((price < min_price) || (num_of_bands == 0)) {
		min_price = price;
	}
	
	num_of_bands++;
	sum_of_prices += (price+discount); // Again, normalizing the previous discount value;
	
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
	
	if (bands_by_votes.remove(&has_id_bv) == bands_by_votes.Success) { 
		bands_by_price.remove(&has_id_bp);
		
		num_of_bands--;
		sum_of_prices -= the_band->price;
		if (num_of_bands > 0) {
			min_price = bands_by_price.GetMin()->band->price - discount;
		} else {
			min_price = -1;
		}
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

	BandByVotes* bbv = NULL;
	try
	{
		bbv = new BandByVotes(the_band);
		bands_by_votes.remove(bbv); // Will never fail
		the_band->votes += numVotes;
		bands_by_votes.insert(bbv);
	}
	catch (std::bad_alloc&)
	{
		delete bbv;
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

StatusType Festival::ChangePrice(int bandID, int price) {
	if ((bandID < 0) || (price < 0)) {
		return INVALID_INPUT;
	}
	Band has_id(bandID, 0);
	Band* the_band = bands.find(&has_id);
	if (the_band == NULL) {
		return FAILURE;
	}
	
	BandByPrice* bbp = NULL;
	BandByVotes* bbv = NULL;
		
	try
	{
		bbp = new BandByPrice(the_band);
		bbv = new BandByVotes(the_band);

		// These are guaranteed to succeed:
		bands_by_price.remove(bbp);
		bands_by_votes.remove(bbv);
		
		sum_of_prices += price + discount - ( the_band->price); // Reduce old price, add new price
		
		// Include discount value when modifying the price	
		the_band->price = price+discount;
		
		bands_by_price.insert(bbp);
		bbp = NULL;	//we dont want to free new_band_by_price in the catch block
						//if we already inserted it to the tree
		bands_by_votes.insert(bbv);
	}
	catch (std::bad_alloc&)
	{
		delete bbp;
		delete bbv;
		return ALLOCATION_ERROR;
	}
	
	if (num_of_bands == 1) {
		min_price = price;
	} else {
		min_price = bands_by_price.GetMin()->band->price - discount;
	}
	
	
	return SUCCESS;
}

StatusType Festival::ChangeAllPrices(int discount) {
	if (discount <= 0) {
		return INVALID_INPUT;
	}
	
	if (num_of_bands == 0) {
		return FAILURE;
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

StatusType Festival::MaxNeededBudget(int* maxBudget) {
	if (maxBudget == NULL) {
		return INVALID_INPUT;
	}
	
	if (num_of_bands == 0) {
		return FAILURE;
	}
	
	*maxBudget = (int)(sum_of_prices - ((long)num_of_bands * (long)discount));
	return SUCCESS;
}

StatusType Festival::BandList(int** bandList, int* size) {
	if ((bandList == NULL) || (size == NULL)) {
		return INVALID_INPUT;
	}
	if (num_of_bands == 0) {
		return FAILURE;
	}
	CountBands counter(budget, discount);
	bands_by_votes.inorder(&counter);
	
	
	*bandList = NULL; //in case size is zero, we dont do malloc 
	*size = counter.count;
	if (*size != 0) {
		*bandList = (int*)malloc(counter.count * sizeof(int));
	
		if (*bandList == NULL) {
			return ALLOCATION_ERROR;
		}

		GetBands getter(bandList, budget, discount);
		bands_by_votes.inorder(&getter);
	}
	return SUCCESS;
}

bool Festival::GetBands::DoWork(BandByVotes* b) {
	if ((b->band->price - discount) <= budget) {
		budget -= (b->band->price - discount);
		(*bandList)[i] = b->band->band_id;
		i++;
	}
	return false;
}

bool Festival::CountBands::DoWork(BandByVotes* b) {
	if ((b->band->price - discount) <= budget) {
		budget -= (b->band->price - discount);
		count++;
	}
	return false;
}
