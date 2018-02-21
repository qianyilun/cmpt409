import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.math.BigInteger;

public class Main {
    static BigInteger dp[][];
    static int x, z;
    static String X, Z;

    static void initialize() {
        dp = new BigInteger[x+1][z+1];
        for (int i = 0; i < x + 1; i++) {
            for (int j = 0; j < z + 1; j++) {
                if (j == 0) {
                    dp[i][j] = BigInteger.ONE;
                } else {
                    dp[i][j] = BigInteger.ZERO;
                }
            }
        }
    }

    public static void main(String[] args) throws IOException{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        for (int i = 0; i < n; i++) {
            X = br.readLine();
            Z = br.readLine();
            x = X.length();
            z = Z.length();
            initialize();
            System.out.println(solve() + "\n");
        }
    }

    private static BigInteger solve() {
        for (int i = 1; i <= x; i++) {
            for (int j = 1; j <= z; j++) {
                if (X.charAt(i - 1) == Z.charAt(j - 1)) {
                    dp[i][j] = dp[i-1][j].add(dp[i-1][j-1]);
                } else {
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
        return dp[x][z];
    }
}
