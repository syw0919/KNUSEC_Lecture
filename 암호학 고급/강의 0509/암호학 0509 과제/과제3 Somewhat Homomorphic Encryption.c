#include <stdio.h>

#define Enc(m) ((a*p+2*r+(m))%n)
#define Dec(c) (((c) % p) % 2)

int multiply(int a, int b, int n){
	int i, ret = 0;
	for(i=0;i<b;i++){
		ret += a;
		ret %= n;
	}
	return ret;
}

int main(){
	// 주어진 값 
	int p = 509;
	int q = 431;
	int n = p*q;
	// 임의로 설정한 값 
	int a = 10;
	int r = 3;
	int rand_m;
	
	printf("p = %d, q = %d, n = %d, a = %d, r = %d\n\n", p, q, n, a, r);
	
	for(rand_m=0;rand_m<8;rand_m++){
		int m1 = (rand_m>>2)%2;
		int m2 = (rand_m>>1)%2;
		int m3 = rand_m%2;
		printf("m1 = %d, m2 = %d, m3 = %d\n", m1, m2, m3);
		
		printf("Enc(m1) = %d, Enc(m2) = %d, ", Enc(m1), Enc(m2));
		printf("Enc(m1)+Enc(m2) = %d, Enc(m1+m2) = %d, ", (Enc(m1)+Enc(m2))%n, Enc(m1^m2));
		printf("Dec(Enc(m1)+Enc(m2)) = %d, Dec(Enc(m1+m2)) = %d\n", Dec((Enc(m1)+Enc(m2))%n), Dec(Enc(m1^m2)));
		
		printf("Enc(m1) = %d, Enc(m2) = %d, ", Enc(m1), Enc(m2));
		printf("Enc(m1)×Enc(m2) = %d, Enc(m1×m2) = %d, ", multiply(Enc(m1), Enc(m2), n), Enc(m1&m2));
		printf("Dec(Enc(m1)×Enc(m2)) = %d, Dec(Enc(m1×m2)) = %d\n", Dec(multiply(Enc(m1), Enc(m2), n)), Dec(Enc(m1&m2)));
		
		printf("Enc(m1) = %d, Enc(m2) = %d, Enc(m3) = %d, ", Enc(m1), Enc(m2), Enc(m3));
		printf("Enc(m1)×Enc(m2)×Enc(m3) = %d, Enc(m1×m2×m3) = %d, ", multiply(multiply(Enc(m1), Enc(m2), n), Enc(m3), n), Enc(m1&m2&m3));
		printf("Dec(Enc(m1)×Enc(m2)×Enc(m3)) = %d, Dec(Enc(m1×m2×m3)) = %d\n", Dec(multiply(multiply(Enc(m1), Enc(m2), n), Enc(m3), n)), Dec(Enc(m1&m2&m3)));
		
		puts("\n");
	}
	
	return 0;
}
