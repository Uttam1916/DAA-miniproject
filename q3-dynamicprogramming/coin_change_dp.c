/*
===============================================================================
Coin Change - Minimum Coins (Dynamic Programming)

TASKS COVERED:
1. Recurrence relation
2. Bottom-up DP implementation
3. DP table construction
4. Reconstruction of coins used
5. Greedy failure demonstration

Time Complexity: O(n * S)
Space Complexity: O(S)
===============================================================================
*/

#include <stdio.h>
#include <limits.h>

#define MAX 100

/*
Recurrence:
dp[i] = min(dp[i], dp[i - coin] + 1)
*/

void coinChange(int coins[], int n, int S) {
    int dp[MAX];
    int parent[MAX];   // to reconstruct solution

    // Initialize
    dp[0] = 0;
    parent[0] = -1;

    for (int i = 1; i <= S; i++) {
        dp[i] = INT_MAX;
        parent[i] = -1;
    }

    // Build DP table
    for (int i = 1; i <= S; i++) {
        for (int j = 0; j < n; j++) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                if (dp[i] > dp[i - coins[j]] + 1) {
                    dp[i] = dp[i - coins[j]] + 1;
                    parent[i] = coins[j];
                }
            }
        }
    }

    // Print DP table
    printf("Amount:     ");
    for (int i = 0; i <= S; i++) printf("%3d", i);
    printf("\n");

    printf("Min Coins:  ");
    for (int i = 0; i <= S; i++) {
        if (dp[i] == INT_MAX) printf("  X");
        else printf("%3d", dp[i]);
    }
    printf("\n");

    printf("Last Coin:  ");
    for (int i = 0; i <= S; i++) {
        if (parent[i] == -1) printf("  -");
        else printf("%3d", parent[i]);
    }
    printf("\n\n");

    // Reconstruction
    if (dp[S] == INT_MAX) {
        printf("No solution possible\n");
        return;
    }

    printf("Minimum coins needed: %d\n", dp[S]);
    printf("Coins used: ");

    int temp = S;
    while (temp > 0) {
        printf("%d ", parent[temp]);
        temp -= parent[temp];
    }
    printf("\n");
}

/*
Greedy approach (for comparison)
*/
void greedy(int coins[], int n, int S) {
    int count = 0;

    printf("\nGreedy solution:\n");

    for (int i = n - 1; i >= 0; i--) {
        while (S >= coins[i]) {
            S -= coins[i];
            printf("%d ", coins[i]);
            count++;
        }
    }

    printf("\nTotal coins (greedy): %d\n", count);
}

/*
Main
*/
int main() {
    int coins[] = {1, 3, 4, 5};
    int n = 4;
    int S = 7;

    printf("Coin denominations: {1, 3, 4, 5}\n");
    printf("Target = %d\n\n", S);

    coinChange(coins, n, S);

    greedy(coins, n, S);

    return 0;
}