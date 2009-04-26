#ifndef _BAND_H
#define _BAND_H



// FIXME TODO TODO FIXME clean up the operators

class Band {
		public:
	int band_id;
	int price;
	int votes;
	
	Band(int bandID, int price, int votes=0)
		: band_id(bandID), price(price), votes(votes) {};
	
	bool operator< (Band b) const {
		return (this->band_id < b.band_id);
	}
	bool operator<= (Band b) const {
		return (this->band_id <= b.band_id);
	}
	bool operator> (Band b) const {
		return (this->band_id > b.band_id);
	}
	friend bool operator== (Band a, Band b) {
		return (a.band_id == b.band_id);
	}
};

class BandByPrice {
	Band* band;
		public:
	BandByPrice(Band* new_band) : band(new_band) {};
	bool operator< (BandByPrice b) const {
		if (this->band->price < b.band->price) {
			return true;
		} else if (this->band->price == b.band->price) {
			return (this->band->band_id < b.band->band_id);
		}
		return false;
	}
	bool operator<= (BandByPrice b) const {
		if (this->band->price < b.band->price) {
			return true;
		} else if (this->band->price == b.band->price) {
			return (this->band->band_id < b.band->band_id);
		}
		return true;
	}
	bool operator> (BandByPrice b) const {
		if (this->band->price > b.band->price) {
			return true;
		} else if (this->band->price == b.band->price) {
			return (this->band->band_id > b.band->band_id);
		}
		return false;
	}
	friend bool operator== (BandByPrice a, BandByPrice b) {
		return (*a.band == *b.band);
	}
};

class BandByVotes {
	Band* band;
		public:
	BandByVotes(Band* new_band) : band(new_band) {};
	bool operator< (BandByVotes b) const {
		if (this->band->votes < b.band->votes) {
			return true;
		} else if (this->band->votes == b.band->votes) {
			if (this->band->price < b.band->price) {
				return true;
			} else if (this->band->price == b.band->price) {
				return (this->band->band_id < b.band->band_id);
			}
		}
		return false;
	}
	bool operator> (BandByVotes b) const {
		if (*this == b) {
			return false;
		} else {
			return !(*this < b);
		}
	}
	bool operator<= (BandByVotes b) const {
		if (this->band->votes < b.band->votes) {
			return true;
		} else if (this->band->votes == b.band->votes) {
			if (this->band->price < b.band->price) {
				return true;
			} 
		}

	}
	friend bool operator== (BandByVotes a, BandByVotes b) {
		return (*a.band == *b.band);
	}
};

#endif
