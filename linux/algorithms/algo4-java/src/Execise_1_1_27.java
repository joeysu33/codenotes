import java.lang.*;

class Execise_1_1_27 {
	private static int count = 0;
	
	public static void init() {
		count = 0;
	}

	public static double binomial(int n, int k , double p) {
		if(n == 0 && k == 0) return 1.0;
		if(n < 0 || k < 0) return 0.0;
		count++;
		return (1.0-p)*binomial(n-1, k, p) + p*binomial(n-1, k-1,p);
	}

	public static void show() {
		
		System.out.println("counter=" + count);
	}
}
