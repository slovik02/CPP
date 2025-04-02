/**
* @author Julia Słowińska
*/

#include <iostream>
#include <vector>
#include <cassert>

// ciąg -- https://pl.wikipedia.org/wiki/Ci%C4%85g_Fibonacciego
// printing a vector -- https://stackoverflow.com/questions/10750057/how-do-i-print-out-the-contents-of-a-vector

using namespace std;

/**
 * Generates the Fibonacci sequence iteratively.
 *
 * @param n The number of elements in the Fibonacci sequence.
 * @return A vector containing the first `n` Fibonacci numbers.
 * @throws invalid_argument If `n` is less than or equal to 0.
 */
vector<int> fibonacci_iter(int n) {
    if (n <= 0) {
        throw invalid_argument("The number must be grater than 0");
    }

    vector<int> fib; // vector for the fib
    fib.push_back(0); // if there is only 1 element it is 0, end
    if (n == 1) return fib;

    fib.push_back(1);

    // start the for loop if n is greater than 2
    for (int i = 2; i < n; i++) {
        fib.push_back(fib[i - 1] + fib[i - 2]); // just regular fibonacci
    }
    return fib;
}

/**
 * Generates the Fibonacci sequence recursively.
 *
 * @param n The number of elements in the Fibonacci sequence.
 * @return A vector containing the first `n` Fibonacci numbers.
 * @throws invalid_argument If `n` is less than or equal to 0.
 */
vector<int> fibonacci_rec(int n) {
    if (n <= 0) {
        throw invalid_argument("The number must be grater than 0");
    }

    if (n == 1) {
        return {0};
    }

    if (n == 2) {
        return {0, 1};
    }

    vector<int> prev = fibonacci_rec(n - 1); // getting inside until n == 2
    prev.push_back(prev[n - 2] + prev[n - 3]); // add new element and go 'outside'
    return prev;
}

/**
 * Tests the fibonacci_iter and fibonacci_rec functions with various cases.
 *
 * This function tests:
 * - The base cases (1st and 2nd Fibonacci numbers).
 * - A typical case (first 5 Fibonacci numbers).
 * - Edge cases (n = 0 and negative n values, which should throw exceptions).
 */
void test_fibonacci() {
    cout << "Starting Fibonacci function tests...\n";

    // Expected results
    vector<int> expected_1 = {0};
    vector<int> expected_2 = {0, 1};
    vector<int> expected_5 = {0, 1, 1, 2, 3};

    assert(fibonacci_iter(1) == expected_1);
    assert(fibonacci_rec(1) == expected_1);
    cout << "Test passed. 1st element is 0" << endl;

    assert(fibonacci_iter(2) == expected_2);
    assert(fibonacci_rec(2) == expected_2);
    cout << "Test passed. 2 first elements are 0 and 1" << endl;


    assert(fibonacci_iter(5) == expected_5);
    assert(fibonacci_rec(5) == expected_5);
    cout << "Test passed. Typical case of 5 elements" << endl;

    try {
        fibonacci_iter(0);
        fibonacci_rec(0);
        cout << "This shouldn't work. There are 0 elements in this sequence" << endl;
    } catch (const invalid_argument&) {
        cout << "Test passed. 0 elements is invalid" << endl;
    }

    try {
        fibonacci_iter(-1);
        fibonacci_rec(-1);
        cout << "This shouldn't work. The number of elements cannot be below 0" << endl;
    } catch (const invalid_argument&) {
        cout << "Test passed. Exception for numbers below 0 is working" << endl;
    }
}

int main() {
    test_fibonacci();
    return 0;
}
