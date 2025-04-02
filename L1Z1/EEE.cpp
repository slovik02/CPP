/**
* @author Julia Słowińska
*/

// źródła:
// wzór -- wikipedia https://pl.wikipedia.org/wiki/Wz%C3%B3r_Herona
// podstawy składni języka -- https://www.w3schools.com/cpp/default.asp
// invalid_argument exception -- https://stackoverflow.com/questions/25765188/best-practice-for-handling-invalid-function-arguments
// exception handling -- https://www.geeksforgeeks.org/exception-handling-c/
// assert -- https://www.geeksforgeeks.org/assertions-cc/

// mam nadzięję, że nie przeszkadza Panu duża ilość komentarzy, ale to jednocześnie moje notatki do nowego języka

#include <iostream> // input and output
#include <cmath>
#include <cassert>

using namespace std;


/**
 * Computes the area of a triangle using Heron's formula.
 *
 * @param a Length of the first side of the triangle.
 * @param b Length of the second side of the triangle.
 * @param c Length of the third side of the triangle.
 * @return The area of the triangle as a double.
 * @throws invalid_argument If any side is ≤ 0 or if the given sides do not form a valid triangle.
 */
double heron(int a, int b, int c) {
    // is the triangle valid?
    // standard || is or
    if (a <= 0 || b <= 0 || c <= 0) {
        throw invalid_argument("Side lengths must be higher than 0.");
    }

    if (a + b <= c || a + c <= b || b + c <= a) {
        throw invalid_argument("This is not a valid triangle.");
    }

    double p = (a + b + c) / 2.0;
    double S = sqrt(p * (p - a) * (p - b) * (p - c));

    return S;
}


/**
 * Tests the heron function with various cases.
 *
 * The function runs several test cases, including:
 * - A typical valid triangle.
 * - An equilateral triangle.
 * - Edge cases with invalid triangles (e.g., one side is too long).
 * - Cases where one or more sides are 0 or negative.
 */
void test_heron() {
    assert(heron(3, 4, 5) == 6);
    cout << "Surface of triangle (3,4,5) is 6. Test passed" << endl;

    assert(abs(heron(5, 5, 5) - 10.8253) < 1e-4); // == is wrong bc 10.8253 is just +/-
    cout << "Surface of triangle (5,5,5) is sth about 10.8253. Test passed" << endl;


    try {
        heron(4, 6, 10); // not a triangle
        cout << "This shouldn't work. Triangle (3, 6, 10) is not a valid triangle" << endl;
    } catch (...) {
        cout << "Triangle (3, 6, 10) is not a valid triangle. Test passed"<< endl;
    }

    try {
        heron(-2, 4, 5);
        cout << "One side is below 0. This shouldn't pass the test. " << endl;
    } catch (...) {
        cout << "One side is below 0. Test passed. " << endl;
    }

    try {
        heron(0, 4, 5); // one side is 0
        cout << " One side of triangle (0,4,5) is 0. This shouldn't pass" << endl;
    } catch (...) {
        cout << "One side of triangle (0,4,5) is 0. Test passed" << endl;
    }
}

/**
 * Main function to take user input and compute the area of a triangle.
 *
 * It prompts the user to enter the three sides of a triangle, then attempts to
 * calculate its area using Heron's formula. If the input is invalid, it catches
 * and displays an error message.
 *
 * @return 0 on successful execution.
 */
int main() {

    int a,b,c;

    cout << "Please enter the 3 sides of triangle." << endl; // endl means the end of the line
    cout << "1 side: "; // without endl this cout and cin are in the same line
    cin >> a;   // after enter in cin there is always new line

    cout << "2 side: ";
    cin >> b;

    cout << "3 side: ";
    cin >> c;

    try {
        double area = heron(a, b, c); // double bc the function return double, call the function
        cout << "The area of the triangle is: " << area << endl;
    }
    catch (const exception& e) {
        cout << "Exception: " << e.what() << endl;
    }

    test_heron();
    return 0; // end of main
}