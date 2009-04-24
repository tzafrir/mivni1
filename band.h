#ifndef _BAND_H
#define _BAND_H

class Band {
		public:
	int band_id;
	int price;
	int votes;
	
	Band(int bandID, int price)
		: band_id(bandID), price(price), votes(0) {};
	
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
		return (this->price < b.price);
	}
	bool operator> (BandByPrice b) {
		return (this->price > b.price);	
	}
	friend bool operator== (BandByPrice a, BandByPrice b) {
		return (*a.band == *b.band);
	}
}

#endif
