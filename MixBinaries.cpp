
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>       
using namespace std;

static vector<int> Int2Binary( int N, int S ) {
	/* 
	  Returns a vector of size S with the binary value of n. 
	  The vector comes reversed, read from right to left.
	   V: 4		Size 32			Size 16			Size 8			Size 4		Size 2
				00100000...		00100000...		00100000		0010		00
	*/

	vector<int> binary(S);
		
	for ( int i = 0; i < S; i++ ) {
		binary[i] = N & (1 << i) ? 1 : 0;
	}

	return binary;
}

static int Binary2Int( vector<int> B ) {
	/*
	  Returns the number represented in binary by the vector B.
	  Vector B must be reversed, so the binary values are read from right to left.
	  Example: 0010 -> 4
	*/

	int value = 0;

	for( int i = 0; i < B.size(); i++ ) {
		if (B.at(i) == 1)
			value = value + pow (2.0, (float) i);
	}

	return value;
}

static void printVector( vector<int> V ) {
	for ( int i = 0; i < V.size(); i++)
		printf("%d", V.at(i));
	printf("\n");
}


static int mixNumbers( int P, int Q, int bits, int times ) {
	/* 
		Mixes binary values of P and Q to get a new random number, R.
		P's and Q's binary arrays are of the size of "bits". To be
		mixed, they are cut in "times" pieces, which are then mixed.
		
		The way of mixing them is:
		A number (P or Q) is chosen, then a subvector of its binary value.
		This subvector is added to R, the result. And so on as many times
		as "times" value.

		- If times > bits, bits == 0 or times <= 1, NULL will be returned.
	*/

	if ( (bits == 0) || (times <= 1) || (times > bits) ) return NULL;

	vector<int> P_bin = Int2Binary( P, bits );		// Holds P's binary value
	vector<int> Q_bin = Int2Binary( Q, bits );		// Holds Q's binary value
	vector<int> R, aux;		// R for result, aux as an auxiliar value to hold P_bin or Q_bin

	int whichNumber, whichSubvector;	
	int chunk = bits/times;		// size of the subvector to be taken

	for ( int i = 1; i <= times; i++ ) {
		whichNumber = rand() % 2 + 1;			// decides randomly which number (P or Q) will provide de subvector
		whichSubvector = rand() % (times-1);	// decides randomly which subvector will be provided

		if (whichNumber == 1) {	aux = P_bin;	// aux holds P or Q depending on whichNumber. 
		} else {				aux = Q_bin;	// 1: P		2: P
		}
		
		// Inserts in R (the result) the chosen subvector. 
		// whichSubvector*chunk points to the first value of the subvector, which ends in (whichSubvector+1)*chunk
		R.insert(R.end(), aux.begin() + whichSubvector*chunk, aux.begin()+(whichSubvector+1)*chunk);
	}

	return Binary2Int( R );
}

static int getDigitNumber( int N ) {
	// Returns number of digits of N
	int result = 0;
	do {
		int digit = N % 10;
		result++;
		N /= 10;
	} while (N > 0);
	return result;
}

int main(int argc, char* argv[]) {

	srand(time(NULL));	// Must be called once in order to get true semi-random mixes.

	int P, Q, R, times, bits, mix;
	
	printf("========================================================================\n\n");
	printf("Testing Int2Binary. REMEMBER! Binary values will be displayed reversed:\n");
	printf("N = 5 \t  4 bits:  "); printVector( Int2Binary(5, 4) );
	printf("N = 6 \t  8 bits:  "); printVector( Int2Binary(6, 8) );
	printf("N = 7 \t 16 bits:  "); printVector( Int2Binary(7, 16) );
	printf("N = 8 \t 32 bits:  "); printVector( Int2Binary(8, 32) );	
	printf("\n========================================================================\n\n");
	printf("Testing Binary2Int:\n");
	printf("N = 5 \t  4 bits: %d\n", Binary2Int(Int2Binary(5, 4)) ); 
	printf("N = 6 \t  8 bits: %d\n", Binary2Int(Int2Binary(6, 8)) );
	printf("N = 7 \t 16 bits: %d\n", Binary2Int(Int2Binary(7, 16)) ); 
	printf("N = 8 \t 32 bits: %d\n", Binary2Int(Int2Binary(8, 32)) ); 
	printf("\n========================================================================\n");
	printf("========================================================================\n\n");
	P = 9;
	Q = 18;
	printf("Mixing numbers %d and %d:\n\n", P, Q);
	printf("-> ERROR inputs:\n");

	bits = 0;	times = 1;		mix = mixNumbers(P, Q, bits, times);
	printf("%d bits, %d times: %d\n", bits, times, mix);

	bits = 1;	times = 0;		mix = mixNumbers(P, Q, bits, times);
	printf("%d bits, %d times: %d\n", bits, times, mix);

	bits = 4;	times = 5;		mix = mixNumbers(P, Q, bits, times);
	printf("%d bits, %d times: %d\n", bits, times, mix);

	bits = 1;	times = 1;		mix = mixNumbers(P, Q, bits, times);
	printf("%d bits, %d times: %d\n", bits, times, mix);


	int testBits[5] = {4, 8, 16, 32, 64};

	for ( int i = 0; i < 5; i++ ) {
		bits = testBits[i];
		printf("\n-> %d bits:\n", bits);

		for ( int j = 0; j < 4; j++ ) {
			times = (testBits[i]/4) + j;
			mix = mixNumbers(P, Q, bits, times);
			printf("%d bits, %d times: %d\n", bits, times, mix);
		}
	}

	printf("========================================================================\n");

	
	getchar();

}
