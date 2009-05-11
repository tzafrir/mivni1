#ifndef _BAND_H
#define _BAND_H

/*
 *
 *	band.h
 *
 */

class Band {
		public:
	int band_id;
	int price;
	int votes;
	
	Band(int bandID, int price, int votes=0)
		: band_id(bandID), price(price), votes(votes) {};
	bool operator<= (Band b) const {
		return (this->band_id <= b.band_id);
	}
};

class BandByPrice {
		public:
	Band* band;
	BandByPrice(Band* new_band) : band(new_band) {};
	bool operator<= (BandByPrice b) const {		
		if (this->band->price < b.band->price) {
			return true;
		} else if (this->band->price == b.band->price) {
			if (this->band->band_id < b.band->band_id) {
				return true;
			} else if (this->band->band_id == b.band->band_id) {			
				return true;
			}
		}
		return false;
	}
};

class BandByVotes {
		public:
	Band* band;
	BandByVotes(Band* new_band) : band(new_band) {};

	bool operator<= (BandByVotes b) const {
		// Order is defined so that the first is the one with most votes
		if (this->band->votes > b.band->votes) {
			return true;
		} else if (this->band->votes == b.band->votes) {
			// Then cheapest
			if (this->band->price < b.band->price) {
				return true;
			} else if (this->band->price == b.band->price) {
				// Then larger bandID
				return (this->band->band_id >= b.band->band_id);
			}
		}
		return false;
	}
};

#endif
