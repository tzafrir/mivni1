#include "band.h"
#include "tests.h"
#include "library1.h"

#define OK "\033[32mOK\033[0m\n"
#define FAIL "\033[31mFAIL\033[0m\n"

int main(){
	const int num = 7;
	Band* B[num][num];
	BandByPrice* Bbp[num][num];
	for (int i=0;i<num;i++) {
		for (int j=0;j<num;j++) {
			B[i][j] = new Band(i,j);
			Bbp[i][j] = new BandByPrice(B[i][j]); 
		}
	}
	int res[num][num];
	for (int i=0;i<num;i++) {
		for (int j=0;j<num;j++) {
			res[i][j] = (*Bbp[i][j] <= *Bbp[num/2][num/2] ? 0 : 1);
		}
	}
	int notgood = 0;
	for (int j=0;j<num/2;j++) {
		for (int i=0;i<num;i++) {
			notgood += res[i][j];
		}
	}
	for (int j=(num/2)+1;j<num;j++) {
		for (int i=0;i<num;i++) {
			notgood -= res[i][j] - 1;
		}
	}
	for (int i=0;i<=num/2; i++) {
		notgood += res[i][num/2];
	}
	for (int i=(num/2)+1;i<num; i++) {
		notgood -= res[i][num/2] -1;
	}
	cout << "\tBandByPrice <=                          " << (notgood == 0 ? "\033[32mOK\033[0m\n" : "\033[31mFAIL\033[0m\n") << endl;
	
	Band B000(0,0,0);
	Band B010(0,1,0);
	Band B100(1,0,0);
	Band B201(2,0,1);
	BandByVotes B1(&B000);
	BandByVotes B2(&B010);
	BandByVotes B3(&B100);
	BandByVotes B4(&B201);
	
	cout << "\tB1 <= B2                            ";
	if (B1 <= B2) {
		cout << OK;
	} else {
		cout << FAIL;
	}
	cout << "\tB1 <= B3 ";
	if (B1 <= B3) {
		cout << OK;
	} else {
		cout << FAIL;
	}
	cout << "\tB1 <= B3 ";
	if (B1 <= B3) {
		cout << OK;
	} else {
		cout << FAIL;
	}
	cout << "\tB1 <= B4 ";
	if (B1 <= B4) {
		cout << OK;
	} else {
		cout << FAIL;
	}
	cout << "\t!B4 <= B2 ";
	if (!(B4 <= B2)) {
		cout << OK;
	} else {
		cout << FAIL;
	}
	cout << "\tB3 <= B2 ";
	if (B3 <= B2) {
		cout << OK;
	} else {
		cout << FAIL;
	}
		
}
