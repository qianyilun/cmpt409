#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <string.h>

using namespace std;

long long  dp[45005];

vector<int> weights;

int people = 0, sum = 0, temp = 0;

int main(int argc, char const *argv[])
{
    /* code */
    int t;
    cin >> t;

    while (t--)
    {
        weights.clear();
        scanf("%d", &people);

        sum = 0;

        for (int i = 0; i < people; i++) {        
            cin >> temp;
            weights.push_back(temp);
            sum += weights[i];
        }

        memset(dp, 0, sizeof(dp));
        dp[0] = 1;

        for (int i = 0; i < people; i++) {
            for (int j = sum; j >= weights[i]; j--) {
                dp[j] |= dp[j - weights[i]] << 1; 
            }
        }

        int left = 0;
        int right = 0x3f3f3f3f;

        int middle_weight = (people+1) / 2;

        for (int i = 0; i < sum; i++) {
            for (int j = 0; j <= middle_weight; j++) {
                if (dp[i] & (1LL << j) && abs(2 * j - people) <= 1) {
                    if (abs(sum - 2 * i) < abs(left - right)) {
                        left = min(sum - i, i);
                        right = max(sum - i, i);
                    }
                }
            }
        }
        cout << left << " " << right << endl;   
        if (t) {
            cout << endl;
        }

    }

    return 0;
}