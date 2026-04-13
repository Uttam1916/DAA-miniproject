import math

coins = [1, 3, 4, 5]
S = 7

dp = [math.inf] * (S + 1)
dp[0] = 0

for i in range(1, S + 1):
    for coin in coins:
        if coin <= i:
            dp[i] = min(dp[i], dp[i - coin] + 1)

print("DP table:", dp)