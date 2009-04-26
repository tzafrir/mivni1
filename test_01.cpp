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
		
}
