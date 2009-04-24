#ifndef _BAND_H
#define _BAND_H

class Band {
		public:
	int band_id;
	int price;
	int votes;
	
	Band(int bandID, int price)
		: band_id(bandID), price(price), votes(0) {};
	Band(int bandID, int price, int votes)
		: band_id(bandID), price(price), votes(votes) {};
	
	bool operator< (Band b) {
		return (this->band_id < b.band_id);
	}
	bool operator> (Band b) {
		return (this->band_id > b.band_id);
	}
	friend bool operator== (Band a, Band b) {
		return (a.band_id == b.band_id);
	}
};

class BandByPrice {
	Band* band;
		public:
	bool operator< (BandByPrice b) {
		return (this->band->price < b.band->price);
	}
	bool operator> (BandByPrice b) {
		return (this->band->price > b.band->price);	
	}
	friend bool operator== (BandByPrice a, BandByPrice b) {
		return (*a.band == *b.band);
	}
};

class BandByVotes {
	Band* band;
		public:
	bool operator< (BandByVotes b) {
		if (this->band->votes < b.band->votes) {
			return true;
		} else if (this->band->votes == b.band->votes) {
			if (this->band->price < b.band->price) {
				return true;
			} else {
				return (this->band->band_id < b.band->band_id);
			}
		}
	}
	bool operator> (BandByVotes b) {
		if (*this == b) {
			return false;
		} else {
			return !(*this < b);
		}
	}
	friend bool operator== (BandByVotes a, BandByVotes b) {
		return (*a.band == *b.band);
	}
};

#endif
