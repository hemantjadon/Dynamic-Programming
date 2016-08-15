//
//  main.cpp
//  Counting To 1
//
//  Created by Hemant Jadon on 15/08/16.
//  Copyright (c) 2016 Hemant Jadon. All rights reserved.
//

/*
 Problem Statement: On a positive integer, you can perform any one of the following 3 steps. 
 1.) Subtract 1 from it. ( n = n - 1 ),
 2.) If its divisible by 2, divide by 2. ( if n % 2 == 0 , then n = n / 2  ),
 3.) If its divisible by 3, divide by 3. ( if n % 3 == 0 , then n = n / 3  ). 
 
 Now the question is, given a positive integer n,
 find the minimum number of steps that takes n to 1
 
 eg: 1.)For n = 1 , output: 0       2.) For n = 4 , output: 2  ( 4  /2 = 2  /2 = 1 )    3.)  For n = 7 , output: 3  (  7  -1 = 6   /3 = 2   /2 = 1 )
 */

#include <iostream>
#include <vector>
using namespace std;

/**
 * Greedy Approach
 *
 * The main concept in greedy approach is that to choose the step 
 * which makes the number smallest.
 * But this is NOT CORRECT solution.
 * Eg. n=10 => Greedy: 10/2=5 -> 5-1=4 -> 4/2=2 -> 2/2 = 1 ==> 4 steps.
 * Optimal Solution : 10-1=9 -> 9/3=3 -> 3/3=1 ==> 3 steps.
 */
int greedyApproach(int n){
    int steps=1;
    if (n == 1) {
        return 0;
    }
    
    int x = n-1;
    int y = (n%2 == 0) ? n/2 : INT_MAX;
    int z = (n%3 == 0) ? n/3 : INT_MAX;
    
    int minimum = min(x,min(y,z));
    
    steps += greedyApproach(minimum);
    
    return steps;
}


/**
 * Recursive Approach
 *
 * Recurence relation is simple :
 * F(n) = 1 + min{ F(n-1) , F(n/2) , F(n/3) }
 */
int recursiveApproach(int n){
    if (n == 1) {
        return 0;
    }
    
    int r = recursiveApproach(n-1);
    (n%2 == 0) ? r = min(r,recursiveApproach(n/2)) : r = r;
    (n%3 == 0) ? r = min(r,recursiveApproach(n/3)) : r = r;
    
    return r+1;
}

/**
 * Memorization
 *
 * We memorize the results in an array and use these for future.
 */
int memorizationApproach(int n, vector<int> &memo){
    if (n == 1) {
        return 0;
    }
    if (memo[n-1] != -1) {
        return memo[n-1];
    }
    
    int r = memorizationApproach(n-1, memo);
    (n%2 == 0) ? r = min(r,memorizationApproach(n/2, memo)) : r = r;
    (n%3 == 0) ? r = min(r,memorizationApproach(n/3, memo)) : r = r;
    
    memo[n-1] = r+1;
    return r+1;
}

/**
 * Bottom Up : DP
 * 
 * We compute all the results till n and store them.
 * Here the cases which are not even used are getting computed.
 */
int bottom_upApproach(int n,vector<int> &memo){
    for (int i=2; i<n; i++) {
        int r = memo[i-1];
        (n%2 == 0) ? r = min(r, memo[i/2]) : r = r;
        (n%3 == 0) ? r = min(r, memo[i/3]) : r = r;
        
        memo[i] = r+1;
    }
    
    return memo[n-1];
}

int main(int argc, const char * argv[]) {
    int n;
    cin >> n;
    
    vector<int> memo(n,-1);
    memo[1] = 0;
    cout << bottom_upApproach(n, memo) << endl;
}
