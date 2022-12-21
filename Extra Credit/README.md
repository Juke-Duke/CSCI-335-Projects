# Dynamic Programming

## Longest Common Subsequence

### Problem:
Given two sequences $A = a_1,a_2,...a_n$ and $B = b_1,b_2,...b_m$ find the length, $k$, of the longest subsequence $C = c_1,c_2,...c_k$ such that $C$ is a subsequence (not necessarily contiguous) of both $A$ and $B$.

### Solution:
We can solve this problem using dynamic programming. Let $DP(i,j)$ be the length of the longest common subsequence of $A[0..n]$ and $B[0..m]$. Then we have the following recurrence:

$$DP(i,j) = \begin{cases} 0 & \text{if } i = 0 \text{ or } j = 0 \\ DP(i-1,j-1) + 1 & \text{if } a_i = b_j \\ \max(DP(i-1,j),DP(i,j-1)) & \text{otherwise} \end{cases}$$

What we are doing is comparing subsequences of $A$ and $B$ of length $n$ and $m$ respectively. If the last element of each subsequence is equal, then we can add one to the length of the longest common subsequence of the subsequences of length $n-1$ and $m-1$. Otherwise, we can take the maximum of the longest common subsequence of the subsequences of length $n-1$ and $m$ and the longest common subsequence of the subsequences of length $n$ and $m-1$. We can use a matrix to store the values of $DP(i,j)$ and then use it to find the longest common subsequence.

### Psuedocode:
    function LongestCommonSubsequence(A, B):
        if A and B are the same:
            return their length

        n <- Length of A
        m <- Length of B
        lcs <- Empty string
        DP <- Empty matrix of size (n+1) x (m+1)

        for i <- 0 to n:
            for j <- 0 to m:
                if i is 0 or j is 0:
                    DP[i][j] <- 0
                else if A[i] is equal to B[j]:
                    DP[i][j] <- DP[i-1][j-1] + 1
                else:
                    DP[i][j] <- max(DP[i-1][j], DP[i][j-1])

        while n is greater than 0 and m is greater than 0:
            if A[n - 1] is equal to B[m - 1]:
                lcs <- A[n - 1] + lcs
                n <- n - 1
                m <- m - 1
            else if DP[n - 1][m] is greater than or equal to DP[n][m - 1]:
                n <- n - 1
            else:
                m <- m - 1

        print length of lcs
        print lcs
        return length of lcs

### Sources:
* [Wikipedia](https://en.wikipedia.org/wiki/Longest_common_subsequence_problem)
* CSCI 335 UTA Devin Li

## Matrix Chain Multiplication

### Problem:
Given the sizes of several matrices, calculate the optimal multiplication ordering.

### Solution:
We can solve this problem using dynamic programming. Let $DP(i,j)$ be the minimum number of scalar multiplications needed to compute the product of matrices $A_i,...,A_j$. We can use a matrix to store the values of $DP(i,j)$ and then use it to find the optimal multiplication ordering.

The amount of operations it takes to multiply two matrices is row count of the first matrix times column count of the second matrix times column count of the first matrix. This is because we have to multiply each element in the first matrix by each element in the second matrix. We can use this to calculate the number of scalar multiplications needed to compute the product of matrices $A_i,...,A_j$.

### Psuedocode:
    function MatrixChainMultiplication(Dimensions)
        n <- Length of Dimensions
        DP <- Empty matrix of size n x n

        for l <- 2 to n:
            for i <- 1 to n - l + 1:
                j <- i + l - 1
                DP[i][j] <- INFINITY
                for k <- i to j - 1:
                    q <- DP[i][k] + DP[k + 1][j] + Dimensions[i - 1] * Dimensions[k] * Dimensions[j]
                    if q is less than DP[i][j]:
                        DP[i][j] <- q

        print DP[1][n]
        return DP[1][n]

### Sources:
* [Wikipedia](https://en.wikipedia.org/wiki/Matrix_chain_multiplication)
* [GeeksforGeeks](https://www.geeksforgeeks.org/matrix-chain-multiplication-dp-8/)
* [Abdul Bari](https://www.youtube.com/watch?v=prx1psByp7U)