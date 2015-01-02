
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


		- If times > bits, -1 will be returned.
	*/

	if (times > bits) return -1;

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

	int N = 24;
	vector<int> binary = Int2Binary(N, 8);
	int result = Binary2Int( Int2Binary( N, 8 ));

	printf("N: %d - Binary:", N); printVector( binary );
	printf("Back to Int -> %d\n", Binary2Int( binary ));
	printf("\n");
	
	int times = 5;
	int bits = 8;
	int mix1 = mixNumbers(N, N, bits, times);
	int mix2 = mixNumbers(N, N, bits, times);
	int mix3 = mixNumbers(N, N, bits, times);
	int mix4 = mixNumbers(N, N, bits, times);
	int mix5 = mixNumbers(N, N, bits, times);

	printf("N: %d\n - Mix 1: %d\n", N, mix1);
	printf("Binary of mix: "); printVector( Int2Binary(mix1, bits) );
	printf("\n - Mix 2: %d\n", mix2);
	printf("Binary of mix: "); printVector( Int2Binary(mix2, bits) );
	printf("\n - Mix 3: %d\n", mix3);
	printf("Binary of mix: "); printVector( Int2Binary(mix3, bits) );
	printf("\n - Mix 4: %d\n", mix4);
	printf("Binary of mix: "); printVector( Int2Binary(mix4, bits) );
	printf("\n - Mix 5: %d\n", mix5);
	printf("Binary of mix: "); printVector( Int2Binary(mix5, bits) );

	getchar();

}
