#include <iostream>
#include <vector>
#include <cassert>

int knapsack(int capacity, std::vector<int> values, std::vector<int> weights, std::vector<int> *itemsSelected = nullptr)
{
    if (weights.size() != values.size() || capacity < 0)
    {
        throw std::invalid_argument("Invalid inputs");
    }
    
    int n = weights.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));

    // Build DP table
    for (int i = 1; i <= n; i++)
    {
        int w = weights[i - 1], v = values[i - 1];
        for (int sz = 1; sz <= capacity; sz++)
        {
            dp[i][sz] = dp[i - 1][sz];
            if (sz >= w && dp[i - 1][sz - w] + v > dp[i][sz])
            {
                dp[i][sz] = dp[i - 1][sz - w] + v;
            }
        }
    }

    // Get selected items
    if (itemsSelected != nullptr)
    {
        int sz = capacity;
        for (int i = n; i > 0; i--)
        {
            if (dp[i][sz] != dp[i - 1][sz])
            {
                itemsSelected->emplace_back(i - 1);
                sz -= weights[i - 1];
            }
        }
    }
    std::cout << dp[n][capacity] << '\n';
    return dp[n][capacity];
}

int main()
{
    int capacity = 7;
    std::vector<int> V{2, 2, 4, 5, 3};
    std::vector<int> W{3, 1, 3, 4, 2};
    std::cout << "Test case #1: ";
    knapsack(capacity, V, W);

    return 0;
}
