#include<bits/stdc++.h>
using namespace std;

/*The solution is to find all possible ways through which the pattern in input-2 matches the words present in input-1
  The initial approach was String Matching through Recursion

  For Recursion,
  Base Case :
    Let len_s = Length of str, len_p = Length of pattern
    len_s < 0 implies str is exhausted, len_p < 0 implies pattern is exhausted
    1. if(len_s < 0 && len_p < 0) return true
    2. if(len_s >= 0 && len_p < 0) return false
    3. if(len_s < 0 && len_p >= 0)
        3.1. loop(i = 0; i < len_p; i++)
            3.1.1. if(pattern(i) != '*') return false
        3.2. end loop
        3.3. return true
    
  General Case (if(len_s >= 0 && len_p >= 0)) : 
    1. if(pattern[i] == str[j]) return function(i-1, j-1)
    2. else if(pattern[i] == '*') return function(i-1, j) | function(i, j-1)
    3. else return false.

  Time Complexity: O(2^N) (Exponential)
  Space Complexity: O(N+M)

  To improve complexity, the better approach is Dynamic Programming
  Here, Time Complexity: O(N*M)
  Space Complexity: O(N*M) + O(N+M)

  The auxiliary stack space can be reduced using Tabulation. So, new space complexity: O(N*M).
  As just the row above is needed each time, so the space complexity can be further reduced to O(N).
*/ 
bool autosuggest(string &str, string &pattern)
{
    //Initializing variables	
	int len_s = str.size();	
    int len_p = pattern.size();	

    //Creating a 2-D vector for dynamic programming
	vector<vector<int>> dp (2, vector<int>(len_p + 1, 0));

    //After Tabulation
    dp[0][0] = 1; //Base case where both str and pattern are exhausted

	int flag = 0; //Flag is set if * is not present in pattern

    //Base case when str is exhausted but pattern is not exhausted
	for(int j=1; j<=len_p; j++) {
		if(flag == 0 && pattern[j-1] == '*') {
			dp[0][j] = 1;			
		}
		else {
			flag = 1;
			dp[0][j] = 0;
		}		
	}

    //General Case
	for(int i=1; i<=len_s; i++) {
		for(int j=1; j<=len_p; j++) {
			if(pattern[j-1] == '*')
		        dp[1][j] = dp[0][j] | dp[1][j-1];
		    else if(pattern[j-1] == str[i-1])
		        dp[1][j] = dp[0][j-1];
		    else
		        dp[1][j] = 0;
		}
		dp[0] = dp[1]; //Copying the current result to previous result
	}
    
    //Returning the final result whether pattern is present or not
	return dp[0][len_p];
}

int main()
{
    //Declaring variables
	string input, pattern;
	vector<string> v;

	//Taking input for Input-1		
	cout << "Enter upto 5 words with similar spellings separated by commas (Input-1):" << endl;
	getline(cin, input);

    //Taking input for Input-2
	cout << "Enter a part of the words entered above (Input-2):" << endl;
	cin >> pattern;	

	//Cleaning the input
	string tmp = "";
	for(int i = 0; i < input.size(); i++) {
		if(input[i] == ',') {
			v.push_back(tmp);
			tmp = "";
		}
		else if(input[i] != ' ')
		    tmp += input[i];
	}
	v.push_back(tmp); //Now, vector v contains all the words in the input list

	//Modifying the pattern to achieve the desired result
	int flag = 0; //Flag is set if * is present in pattern
	for(auto x : pattern)
		if(x == '*')
            flag = 1;
    //Adding * to the start and end of pattern if not present in the entire string
	if(!flag) {
		pattern.insert (0, 1, '*');
		pattern.push_back('*');
	}

    //Displaying the output
    cout << "The words suggested from your Input-1 containing the part/phrase enered in Input-2 are:" << endl;
	for(auto str : v)
		if(autosuggest(str, pattern))
			cout << str << " ";
    cout << endl;
	return 0;
}