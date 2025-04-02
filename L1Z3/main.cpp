/**
* @author Julia Słowińska and
* @author chat GPT
*/

// i am terrible at combinatorics and i didn't know how to do it more mathematical way but i tried (the window i talked about on the course)
// i paste the task and add 'write this function in c++ for me nad explain step by step'

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;


/**
 * Generates all subsets of the given input set
 *
 * @param inputSet A vector of characters representing the original set.
 * @return A vector of vectors, where each inner vector represents a subset.
 *
 */
vector<vector<char>> podzbiory(vector<char> inputSet) {
    int n = inputSet.size();    // the size of the input set
    int totalSubsets = pow(2, n);   // the number of options, 2^n
    vector<vector<char>> subsets;   // vector containing vectors

    for (int i = 0; i < totalSubsets; ++i) {    // for each combination
        vector<char> subset;    // single subset
        for (int j = 0; j < n; ++j) {
            if (i & (1 << j)) { // we got here and operator, we check bit by bit
                subset.push_back(inputSet[j]);  // put the letter into subset
            }
        }
        subsets.push_back(subset);
    }
    return subsets;
}


/**
*  Tests the podzbiory function using assert
 *
* - Empty set test
* - Handles typical cases
* - Checks the single letter case
*/
void test() {

    vector<vector<char>> expected1 = {{}};
    assert(podzbiory({}) == expected1);
    cout << "Test passed for empty vector" << endl;

    vector<vector<char>> expected2 = {{}, {'a'}};
    assert(podzbiory({'a'}) == expected2);
    cout << "Test passed for one letter" << endl;

    vector<vector<char>> expected3 = {{}, {'a'}, {'b'}, {'a', 'b'}};
    assert(podzbiory({'a', 'b'}) == expected3);
    cout << "Test passed for typical case" << endl;
}


int main() {
    test();
    return 0;
}
