#include "library1.h"
#include "festival.h"

void* Init(int budget) {
	if (budget < 0) {
		return NULL;
	}
	try {
		Festival* DS = new Festival(budget);
		return (void*)DS;
	}
	catch (std::bad_alloc&) {
		return NULL;
	}
}

StatusType ChangeBudget(void* DS, int budget) {
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((Festival*)DS)->ChangeBudget(budget);
}

StatusType AddBand(void* DS, int bandID, int price) {
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((Festival*)DS)->AddBand(bandID, price);
}

StatusType RemoveBand(void* DS, int bandID) {
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((Festival*)DS)->RemoveBand(bandID);
}

StatusType AddVotes(void* DS, int bandID, int votes) {
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((Festival*)DS)->AddVotes(bandID, votes);
}

StatusType ChangePrice(void* DS, int bandID, int price) {
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((Festival*)DS)->ChangePrice(bandID, price);
}

StatusType ChangeAllPrices(void* DS, int discount) {
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((Festival*)DS)->ChangeAllPrices(discount);
}

StatusType GetPrice(void* DS, int bandID, int* price) {
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((Festival*)DS)->GetPrice(bandID, price);
}

StatusType MaxNeededBudget(void* DS, int* maxBudget) {
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((Festival*)DS)->MaxNeededBudget(maxBudget);
}

StatusType BandList(void* DS, int** bandList, int* size) {
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((Festival*)DS)->BandList(bandList, size);
}

void Quit(void** DS) {
	delete (Festival*)*DS;
	*DS = NULL;
}
