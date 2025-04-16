#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>

// info about classes -- https://www.w3schools.com/cpp/cpp_encapsulation.asp
// i checked my old python code i did for this task so i tried to do sth similar
// overloading an operator -- https://www.programiz.com/cpp-programming/operator-overloading
// i got a problem with getting the specific polynomial (*this) so my friend explain me what is *this and how to use it

using namespace std;

class Wielomian {
private:
    vector<int> coef; // coefficients

public:
    /**
    * Constructor for Wielomian.
    *
    * @param coefficients Vector of coefficients, highest degree first.
    * @throws invalid_argument if the polynomial is empty.
    */
    Wielomian(vector<int> coefficients) { // constructor
        if (coefficients.empty()) {
            throw invalid_argument("Polynomial can't be empty!");
        }
        coef = coefficients;
        while (coef.size() > 1 && coef[0] == 0) { // delete 0 from the beginning
            coef.erase(coef.begin());
        }
    }

public:
    /**
    * Returns the degree of the polynomial.
    *
    * @return The degree (highest exponent).
    */
    int degree() const {
        return coef.size() - 1;
    }

public:
    /**
  * Converts the polynomial to a readable string.
  *
  * @return A string representation of the polynomial.
  */
    string to_string() const {
        string result = "W(x) = ";
        bool first = true;
        int deg = degree();

        for (int i = 0; i < coef.size(); ++i) {
            int c = coef[i];
            int power = deg - i;
            if (c == 0) continue;

            // Sign
            if (!first) {
                result += (c > 0 ? "+" : "-");
            } else if (c < 0) {
                result += "-";
            }

            // Coefficient (absolute value)
            if (abs(c) != 1 || power == 0) {
                result += std::to_string(abs(c));
            } else if (first) {
                // For -1x or 1x at beginning, we've already printed "-"
                result += "1";
            }

            // x and power
            if (power > 0) {
                result += "x";
                if (power > 1) {
                    result += "^" + std::to_string(power);
                }
            }

            first = false;
        }

        if (first) {
            result += "0";
        }

        return result;
    }

public:
    /**
     * Evaluates the polynomial at a given x value.
     *
     * @param x The value at which to evaluate the polynomial.
     * @return The result of the polynomial evaluated at x.
     */
    int call(int x) const {
        int result = 0;
        int degree = coef.size() - 1;
        for (int i = 0; i < coef.size(); ++i) {
            result += coef[i] * pow(x, degree - i);
        }
        return result;
    }

public:
    /**
     * Adds two polynomials.
     *
     * @param other The other polynomial to add.
     * @return A new polynomial which is the sum of this and other.
     */
    Wielomian operator+ (Wielomian other)  { // i overload +, so + means this
        vector<int> a = coef; // my two polynomials
        vector<int> b = other.coef;
        // so the polynomials will be the same size
        if (a.size() < b.size()) {
            a.insert(a.begin(), b.size() - a.size(), 0); // add 0 to make vector bigger
        }
        else if (b.size() < a.size()) {
            b.insert(b.begin(), a.size() - b.size(), 0);
        }

        vector<int> result;

        for (int i = 0; i < a.size(); ++i)
            result.push_back(a[i] + b[i]); // add the numbers with the same x degree
        return Wielomian(result);   // i return a new object
    }

public:
    /**
    * Subtracts another polynomial from this one.
    *
    * @param other The polynomial to subtract.
    * @return A new polynomial which is the result of subtraction.
    */
    Wielomian operator-(Wielomian other)  {  // this is done almost the same
        vector<int> a = coef;
        vector<int> b = other.coef;
        if (a.size() < b.size()) a.insert(a.begin(), b.size() - a.size(), 0);
        else if (b.size() < a.size()) b.insert(b.begin(), a.size() - b.size(), 0);

        vector<int> result;
        for (int i = 0; i < a.size(); ++i)
            result.push_back(a[i] - b[i]);
        return Wielomian(result);
    }


    /**
     * Multiplies this polynomial by another.
     *
     * @param other The other polynomial to multiply.
     * @return A new polynomial which is the product of this and other.
     */
    Wielomian operator*(Wielomian other) { // degree a and b, the result degree is a + b
        vector<int> result(coef.size() + other.coef.size() - 1, 0);
        for (int i = 0; i < coef.size(); ++i) // i multiply everything
            for (int j = 0; j < other.coef.size(); ++j)
                result[i + j] += coef[i] * other.coef[j]; // multiply and add to specific place in result
        return Wielomian(result);               // (to get the degree right)
    }


    /**
   * Adds another polynomial to this one in place.
   *
   * @param other The polynomial to add.
   * @return Reference to the modified polynomial.
   */
    Wielomian operator+=( Wielomian other) { // now i want to keep the same object just add sth to it
        *this = *this + other; // i refer to the specific object i am currently working with
        return *this; // add this extra polynomial to my object
    }

    /**
   * Subtracts another polynomial from this one in place.
   *
   * @param other The polynomial to subtract.
   * @return Reference to the modified polynomial.
   */
    Wielomian& operator-=(Wielomian other) {  // the same for += and *=
        *this = *this - other;
        return *this;
    }

    /**
     * Multiplies this polynomial with another in place.
     *
     * @param other The polynomial to multiply.
     * @return Reference to the modified polynomial.
     */
    Wielomian& operator*=(Wielomian other) {
        *this = *this * other;
        return *this;
    }
};

/**
 * Tests the all functionalities for Wielomian class.
 *
 */
void test_wielomian() {
    // typical
    Wielomian w1({5, -3, 2});
    assert(w1.degree() == 2);
    cout << "Degree of typical case works" << endl;

    // polynomial value
    assert(w1.call(1) == 4);
    assert(w1.call(0) == 2);
    assert(w1.call(-1) == 10);
    cout << "Calculation of typical case polynomial works" << endl;

    // string representation
    string str = w1.to_string();
    assert(str == "W(x) = 5x^2-3x+2");
    cout << "Getting string of typical case works"<< endl;

    try {
        Wielomian w_empty({});
        cout << "Test fails for empty polynomial" << endl;
    } catch (const invalid_argument& e) {
        cout << "Empty polynomial correctly throws exception" << endl;
    }

    Wielomian w_zero({0, 0, 0});
    assert(w_zero.degree() == 0);
    assert(w_zero.call(3) == 0);
    assert(w_zero.to_string() == "W(x) = 0");
    cout << "Zero polynomial case works" << endl;

    Wielomian w_const({7});
    assert(w_const.degree() == 0);
    assert(w_const.call(100) == 7);
    assert(w_const.to_string() == "W(x) = 7");
    cout << "Constant polynomial case works" << endl;


    // add
    Wielomian w2({1, 2, 3});
    Wielomian sum = w1 + w2;
    Wielomian sum_zero = w1 + w_zero;
    assert(sum.to_string() == "W(x) = 6x^2-x+5");
    assert(sum_zero.to_string() == "W(x) = 5x^2-3x+2"); // this way bc i couldn't compare 2 polynomials
    cout << "Adding works" << endl;

    // subtraction
    Wielomian sub = w1 - w2;
    Wielomian sub_zero = w1 - w_zero;
    assert(sub.to_string() == "W(x) = 4x^2-5x-1");
    assert(sum_zero.to_string() == "W(x) = 5x^2-3x+2");
    cout << "Subtraction works" << endl;

    // multiply
    Wielomian mul = w1 * w2;
    Wielomian mul_zero = w1 * w_zero;
    assert(mul.to_string() == "W(x) = 5x^4+7x^3+11x^2-5x+6");
    assert(mul_zero.to_string() == "W(x) = 0");
    cout << "Multiplication works" << endl;

    // +=
    Wielomian w3({1, 2, 3});
    w3 += w1;
    assert(w3.to_string() == "W(x) = 6x^2-x+5");
    cout << "+= works" << endl;

    // -=
    Wielomian w4({10, 9, 8});
    w4 -= w1; // (10−5)x^2 + (9−3)x + (8−2)
    assert(w4.to_string() == "W(x) = 5x^2+12x+6");
    cout << "-= works" << endl;

    // *=
    Wielomian w5({1, 1});
    w5 *= w5;
    assert(w5.to_string() == "W(x) = 1x^2+2x+1");
    cout << "-= works" << endl;

    Wielomian zeroFront({0, 0, 4, 1});
    assert(zeroFront.call(0) == 1);
    assert(zeroFront.degree() == 1);
    assert(zeroFront.to_string() == "W(x) = 4x+1");
    cout << "Everything for zeros at the front works" << endl;

    Wielomian zeroMiddle({3, 0, 2});
    assert(zeroMiddle.call(2) == 14);
    assert(zeroMiddle.degree() == 2);
    assert(zeroMiddle.to_string() == "W(x) = 3x^2+2");
    cout << "Everything for zeros in the middle works" << endl;

    Wielomian zeroEnd({2, 3, 0, 0});
    assert(zeroEnd.call(1) == 5);
    assert(zeroEnd.degree() == 3);
    assert(zeroEnd.to_string() == "W(x) = 2x^3+3x^2");
    cout << "Everything for zeros at the end works" << endl;
}



int main() {
    test_wielomian();
    return 0;
}
