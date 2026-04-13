import math

def min_coins(coins, S):
    # DP array
    dp = [math.inf] * (S + 1)
    parent = [-1] * (S + 1)

    dp[0] = 0  # base case

    for i in range(1, S + 1):
        for coin in coins:
            if coin <= i and dp[i - coin] + 1 < dp[i]:
                dp[i] = dp[i - coin] + 1
                parent[i] = coin

    # reconstruct coins used
    result = []
    curr = S
    while curr > 0:
        result.append(parent[curr])
        curr -= parent[curr]

    return dp[S], result


if __name__ == "__main__":
    coins = [1, 3, 4, 5]
    S = 7

    min_count, used_coins = min_coins(coins, S)

    print("Minimum coins:", min_count)
    print("Coins used:", used_coins)