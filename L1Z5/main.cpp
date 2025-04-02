/**
* @author Julia Słowińska
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// i got help with the modulo from my boyfriend
// collatz -- https://pl.wikipedia.org/wiki/Problem_Collatza

using namespace std;

/**
 * Generates the Collatz sequence for a given starting number.
 *
 * @param c0 The starting natural number.
 * @return A vector containing the Collatz sequence before it enters the {4, 2, 1} cycle.
 * @throws invalid_argument If `c0` is not a positive integer.
 */
vector<int> collatz(int c0) {
    if (c0 <= 0) {
        throw invalid_argument("C0 has to be natural number"); // i didn't include 0
    }

    vector<int> sequence;

    while (c0 != 4) {   // before falling into a cycle, without 4 2 1
        sequence.push_back(c0); // put calculated number into the sequence
        if (c0 % 2 == 0) {  // % is a modulo, it returns the rest from the division
            c0 = c0*0.5;
        } else {
            c0 = 3 * c0 + 1;
        }
    }

    return sequence;
}


/**
 * Tests the collatz function with different values.
 *
 * This function checks:
 * - Standard cases (positive integers).
 * - Smallest values (1, 2, 3).
 * - Invalid cases (0 and negative numbers).
 */
void test_collatz() {

    assert((collatz(11) == vector<int>{11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8}));
    assert((collatz(15) == vector<int>{15, 46, 23, 70, 35, 106, 53, 160, 80, 40, 20, 10, 5, 16, 8}));
    assert((collatz(10) == vector<int>{10, 5, 16, 8}));
    cout << "Test passed for 11, 15 and 10" << endl;

    assert((collatz(1) == vector<int>{1}));
    assert((collatz(2) == vector<int>{2, 1}));
    assert((collatz(3) == vector<int>{3, 10, 5, 16, 8}));
    cout << "Test passed for 1, 2 and 3" << endl;

    try {
        collatz(0);
        cout << "This shouldn't work for number 0. Test not passed" << endl;
    } catch (const invalid_argument& e) {
        cout << "Passed for 0. Exception occurs" << endl;
    }

    try {
        collatz(-5);
        cout << "This shouldn't work for number -5. Test not passed" << endl;
    } catch (const invalid_argument& e) {
        cout << "Passed for -5. Exception occurs" << endl;
    }

}

/**
 * This function calculates the number of iterations needed to reach 4 (just before entering the cycle).
 *
 * @param c0 The starting natural number.
 * @return The number of steps before entering the cycle.
 * @throws invalid_argument If `c0` is not a positive integer.
 */
int collatz_length(int c0) { // it returns how many numbers are in the cycle
    if (c0 <= 0) {
        throw invalid_argument("C0 has to be a natural number");
    }

    int length = 0;
    while (c0 != 4) {
        length++;
        if (c0 % 2 == 0) {
            c0 = c0 / 2;
        } else {
            c0 = 3 * c0 + 1;
        }
    }
    return length;
}

/**
 * Main function to run tests and display Collatz sequence lengths.
 * @return 0 if the program executes successfully.
 */
int main() {
    test_collatz();

    cout << "Corelation between c0 and length before falling into a cycle" << endl;
    for (int i = 1; i <= 20; i++) {
        cout << "c0 = " << i << ", length: " << collatz_length(i) << endl;
    }

    cout << "The size of the number c0 does not affect the length of the sequence" << endl;
    return 0;
}