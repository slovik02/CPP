/**
* @author Julia Słowińska
*/

#include <iostream>
#include <vector>  // library for vectors, vectors are resizable arrays
#include <bits/stdc++.h>

// podstawy składni języka -- https://www.w3schools.com/cpp/default.asp
// INT_MIN -- https://www.geeksforgeeks.org/int_max-int_min-cc-applications/
// sorting the vector -- https://www.geeksforgeeks.org/sorting-a-vector-in-c/

using namespace std;

/**
 * Finds the common elements between two vectors (multisets).
 *
 * @param x First input vector (multiset).
 * @param y Second input vector (multiset).
 * @return A vector containing the sorted common elements.
 * @throws invalid_argument If either of the input vectors is empty.
 */
vector<int> wspolne(vector<int> x, vector<int> y) { // multi set x and y are vectors, only int inside

    if (x.empty() || y.empty()) {
        throw invalid_argument("One of the vectors is empty");
    }

    vector<int> intersection;

    // i take the number from vector x
    for (size_t i = 0; i < x.size(); i++) {
        for (size_t j = 0; j < y.size(); j++) { // i check it with every number in y vector
            if (x[i] == y[j]) { // check if the number is in both vectors
                intersection.push_back(x[i]); // add the number at the end of intersection
                y[j] = INT_MIN; // instead of NaN or sth like that
                break; // in number is found, break
            }
        }
    }

    sort(intersection.begin(), intersection.end());
    return intersection;
}


/**
 * Tests the wspolne function with various cases.
 *
 * This function tests:
 * - A typical case where elements are common.
 * - A case where no elements are common.
 * - A case where one of the vectors is empty.
 * - A case where elements include negative numbers.
 * - A case where both vectors contain a single element.
 */
void test_wspolne() {

    vector<int> a = {5, 6, 1, 3, 3, 1};
    vector<int> b = {4, 4, 3, 1, 3, 5};
    vector<int> intersection = wspolne(a, b);
    assert((intersection == vector<int>{1, 3, 3, 5}));
    cout << "Passed for typical case"<< endl;

    vector<int> c = {1, 2, 3};
    vector<int> d = {4, 5, 6};
    intersection = wspolne(c, d);
    assert(intersection.empty());
    cout << "Passed for empty intersection vector"<< endl;

    try {
        vector<int> e = {};
        vector<int> f = {1, 2, 3};
        intersection = wspolne(e, f);
        cout << "One of the vector is empty! Test is not passed"<< endl;
    } catch (const invalid_argument &e) {
        cout << "Passed for empty vector"<< endl;
    }

    vector<int> g = {-5, 0, -2, 3, 3};
    vector<int> h = {0, 3, -5, -5};
    intersection = wspolne(g, h);
    assert((intersection == vector<int>{-5, 0, 3}));
    cout << "Passed for numbers below 0"<< endl;

    vector<int> i = {0};
    vector<int> j = {0};
    intersection = wspolne(i, j);
    assert((intersection == vector<int>{0}));
    cout << "Passed for vector with 1 element"<< endl;

}

int main() {
    test_wspolne();
    return 0;
}
