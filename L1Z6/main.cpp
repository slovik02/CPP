/**
* @author Julia Słowińska
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// reversing the string -- https://www.geeksforgeeks.org/reverse-a-string-in-c-cpp-different-methods/
// for understanding i used this graphic -- https://pl.khanacademy.org/science/ap-biology/gene-expression-and-regulation/transcription-and-rna-processing/a/overview-of-transcription
using namespace std;

/**
 * Generates the complementary DNA strand (3' → 5' converted to 5' → 3').
 *
 * @param complimentary The input DNA strand (5' → 3').
 * @return The complementary strand in 5' → 3' order.
 * @throws invalid_argument If the sequence is empty or contains invalid characters.
 */
string komplement(string complimentary) {  // this function will return string

    if (complimentary.empty()) {
        throw invalid_argument("Sequence cannot be empty");
    }

    string matrix = ""; // matrix sequence


    for (char nucleotide : complimentary) {
      if (nucleotide == 'G'){
            matrix.push_back('C');
      }
      else if (nucleotide == 'C'){
            matrix.push_back('G');
      }
      else if (nucleotide == 'A'){
            matrix.push_back('T');
      }
      else if (nucleotide == 'T'){
            matrix.push_back('A');
      }
      else {
          throw invalid_argument("Sequence has invalid nucleotides");  // it there is sth other than GCAT
      }
    }

    // now we have string 3' 5'
    reverse(matrix.begin(), matrix.end()); // then we will have 5' 3'

    return matrix;
}

/**
 * Transcribes a DNA sequence into RNA (5' → 3').
 *
 * @param matrix The DNA sequence in 5' → 3' order.
 * @return The corresponding RNA sequence in 5' → 3' order.
 * @throws invalid_argument If the sequence is empty or contains invalid characters.
 */
string transkrybuj (string matrix) {

    if (matrix.empty()) {
        throw invalid_argument("Sequence cannot be empty");
    }

    string RNA = ""; // RNA sequence


    for (char nucleotide : matrix) {
        if (nucleotide == 'G'){
            RNA.push_back('C');
        }
        else if (nucleotide == 'C'){
            RNA.push_back('G');
        }
        else if (nucleotide == 'A'){    // in RNA A is U
            RNA.push_back('U');
        }
        else if (nucleotide == 'T'){
            RNA.push_back('A');
        }
        else {
            throw invalid_argument("Sequence has invalid nucleotides");  // it there is sth other than GCAT
        }
    }

    return RNA;  // it is already 5' 3'
}


/**
 * Tests the DNA complementary strand and transcription functions.
 *
 * - Checks valid conversions for typical cases.
 * - Handles single-character sequences.
 * - Verifies that invalid input cases throw exceptions.
 */
void test_functions() {

    // komplement function
    assert(komplement("ATGC") == "GCAT");
    cout << "Test passed for typical sequence" << endl;
    assert(komplement("A") == "T");
    cout << "Test passed for singe character" << endl;

    try {
        komplement("");
        cout << "This shouldn't work for empty string. Test not passed" << endl;
    } catch (const invalid_argument& e) {
        cout << "Test passed for empty string. Exception works" << endl;
    }

    try {
        komplement("HDCWC");
        cout << "This shouldn't work for invalid characters. Test not passed" << endl;
    } catch (const invalid_argument& e) {
        cout << "Test passed for invalid characters. Exception works"<< endl;
    }

    cout << "Testing transkrybuj"<< endl;

    // transkrybuj
    assert(transkrybuj("TACG") == "AUGC");
    cout << "Test passed for typical sequence" << endl;
    assert(transkrybuj("T") == "A");
    cout << "Test passed for singe character" << endl;

    try {
        transkrybuj("");
        cout << "This shouldn't work for empty string. Test not passed" << endl;
    } catch (const invalid_argument& e) {
        cout << "Test passed for empty string. Exception works" << endl;
    }

    try {
        transkrybuj("HDCWC");
        cout << "This shouldn't work for invalid characters. Test not passed" << endl;
    } catch (const invalid_argument& e) {
        cout << "Test passed for invalid characters. Exception works"<< endl;
    }
}



int main() {
    test_functions();
    return 0;
}