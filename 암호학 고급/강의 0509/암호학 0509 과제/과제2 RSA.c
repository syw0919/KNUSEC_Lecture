#include <stdio.h>
#include <stdint.h>

int8_t bin[100];
int cnt;

void binary(int num){
	if(num>1) binary(num/2);
	else cnt = 0;
	bin[cnt++] = num%2;
}

int SquareAndMultiply(int base, int exponent, int mod){
	int64_t ret = 1;
	int i;
	
	binary(exponent);
	
	for(i=0;i<cnt;i++){
		ret *= ret;
		if(bin[i]) ret *= base;
		ret %= mod;
	}
	
	return (int)ret;
}

int main(){
	// 공개키 
	int N = 219379;
	int e = 7;
	//개인키 
	int d = 124823;
	//평문 
	int m = 31337;
	//암호문 
	int c;
	
	printf("N = %d\n", N);
	printf("e = %d\n", e);
	printf("d = %d\n", d);
	printf("m = %d\n", m);
	c = SquareAndMultiply(m, e, N); // m^e mod N
	printf("c = %d\n", c);
	printf("m' = %d\n", SquareAndMultiply(c, d, N)); // c^d mod N
	
	return 0;
}
