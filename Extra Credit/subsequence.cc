#include <iostream>
#include <string>
#include <vector>

int LongestCommonSubsequence(const std::string& s1, const std::string& s2)
{
  if (s1 == s2)
    return s1.size();

  int n = s1.size();
  int m = s2.size();

  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

  for (int i = 0; i <= n; ++i)
    for (int j = 0; j <= m; ++j)
      if (i == 0 || j == 0)
        dp[i][j] = 0;
      else if (s1[i - 1] == s2[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);

  std::string longestCommonSubsequence = "";

  while (n > 0 && m > 0)
    if (s1[n - 1] == s2[m - 1])
    {
      longestCommonSubsequence = s1[n - 1] + longestCommonSubsequence;
      --n;
      --m;
    }
    else if (dp[n - 1][m] > dp[n][m - 1])
      --n;
    else
      --m;

  std::cout << longestCommonSubsequence.size() << std::endl;
  std::cout << longestCommonSubsequence << std::endl;

  return longestCommonSubsequence.size();
}

int subsequence_driver(int argc, char** argv)
{
  LongestCommonSubsequence(argv[1], argv[2]);

  return 0;
}

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    std::cout << "Usage: " << argv[0] << "<word_a>" << "<word_b>" << std::endl;
    return 0;
  }

  subsequence_driver(argc, argv);

  return 0;
}
