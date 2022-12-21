#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <climits>

void OptimalOrdering(const std::vector<int>& dimensions)
{
    int n = dimensions.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    for (int length = 2; length < n; ++length)
      for (int i = 1; i < n - length + 1; ++i)
      {
        int j = i + length - 1;
        dp[i][j] = INT_MAX;

        for (int k = i; k <= j - 1; ++k)
        {
          int q = dp[i][k] + dp[k + 1][j] + dimensions[i - 1] * dimensions[k] * dimensions[j];
          if (q < dp[i][j])
            dp[i][j] = q;
        }
      }

    std::cout << dp[1][n - 1] << std::endl;
}

int multiplication_driver(int argc, char** argv)
{
  std::ifstream dimensionFile(argv[1]);
  std::vector<int> dimensions;

  int num;
  while (dimensionFile >> num)
    dimensions.push_back(num);

  dimensionFile.close();

  OptimalOrdering(dimensions);

  return 0;
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cout << "Usage: " << argv[0] << "<dimensions_file>" << std::endl;
    return 0;
  }

  multiplication_driver(argc, argv);

  return 0;
}
