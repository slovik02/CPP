#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cassert>

// most methods are identical for each class and normally they will be repeated unnecessary
// so this common things are in the class sequence and the rest just inherit it

// cutting string -- https://cplusplus.com/reference/string/string/substr/
// finding sth in string -- https://www.digitalocean.com/community/tutorials/string-find-c-plus-plus
// not found in string -- https://medium.com/lightning-strikes-a-developers-journey/breaking-down-std-string-npos-understanding-the-not-found-constant-a785b58313d7

using namespace std;

class Sequence {
protected: // bc of the inheritance
    string identifier; // tells about sequence
    string data;    // actual sequence

public:
    /**
     * Constructs a Sequence object with a given identifier and data string
     *
     * @param id Id of the sequence
     * @param seq Aminoacid sequence
     */
    Sequence(string id, string seq) {
        identifier = id;
        data = seq;
    }

    /**
   * Returns the sequence in FASTA-like format
   * @return A string starting with '>' followed by ID and the sequence
   */
    string toString() const {
        return ">" + identifier + "\n" + data; // \n ends the line
    }

    /**
     * Mutates the sequence at a given position with a new character.
     * @param position Index to mutate.
     * @param value New character to insert.
     * @throws out_of_range if the position is invalid.
     */
    void mutate(int position, char value) {
        if (position < 0 || position >= data.size()) {
            throw out_of_range("Invalid mutation position");
        }
        data[position] = value;
    }

    /**
   * Finds all positions of a given motif in the sequence.
   * @param motif The subsequence to search for.
   * @return A vector of starting indices where the motif is found.
   */
    vector<int> findMotif(string motif) {  // find some small string in big string
        vector<int> positions;
        for (int i = 0; i <= data.size() - motif.size(); ++i) { // so the size of the window do not go outside the data
            if (data.substr(i, motif.size()) == motif) { // take the substring and compare it
                positions.push_back(i); // save the starting index
            }
        }
        return positions; // positions of the match
    }

    /**
   * Returns the length of the sequence.
   * @return Length of the data string.
   */
    int length() {
        return data.size();
    }

    /**
     * Getter for the sequence data.
     * @return The sequence string.
     */
    string getData() { return data; }
};


class ProteinSequence : public Sequence {
private:
    string VALID_CHARS = "ACDEFGHIKLMNPQRSTVWY"; // 1 letter shortcut

public:
    /**
   * Constructs a ProteinSequence and validates characters.
   * @throws invalid_argument if any character is not a valid amino acid.
   */
    ProteinSequence(string id, string seq) : Sequence(id, seq) {
        for (char aa : seq) {
            if (VALID_CHARS.find(aa) == string::npos) {
                throw invalid_argument("Invalid amino acid in protein sequence");
            }
        }
    }
};

class RNASequence : public Sequence { // it has to be above DNA class so i can call it
private:
    string VALID_CHARS = "AUGC";

public:
    /**
   * Constructs an RNASequence and validates characters.
   * @throws invalid_argument if any character is not a valid RNA nucleotide.
   */
    RNASequence(string id, string seq) : Sequence(id, seq) {
        for (char i : seq) {
            if (VALID_CHARS.find(i) == string::npos) {
                throw invalid_argument("Invalid character in RNA");
            }
        }
    }

    /**
     * Translates the RNA sequence into a protein sequence.
     * Translation starts at the first "AUG" codon and stops at a stop codon.
     * @return A ProteinSequence object representing the translated protein.
     */
    ProteinSequence transcribe() {
        // map of RNA codons
        map<string, char> codonTable = {
                {"AUG", 'M'}, // Start codon and methionine

                // Phenylalanine
                {"UUU", 'F'}, {"UUC", 'F'},
                // Leucine
                {"UUA", 'L'}, {"UUG", 'L'}, {"CUU", 'L'}, {"CUC", 'L'}, {"CUA", 'L'}, {"CUG", 'L'},
                // Isoleucine
                {"AUU", 'I'}, {"AUC", 'I'}, {"AUA", 'I'},
                // Valine
                {"GUU", 'V'}, {"GUC", 'V'}, {"GUA", 'V'}, {"GUG", 'V'},
                // Serine
                {"UCU", 'S'}, {"UCC", 'S'}, {"UCA", 'S'}, {"UCG", 'S'}, {"AGU", 'S'}, {"AGC", 'S'},
                // Proline
                {"CCU", 'P'}, {"CCC", 'P'}, {"CCA", 'P'}, {"CCG", 'P'},
                // Threonine
                {"ACU", 'T'}, {"ACC", 'T'}, {"ACA", 'T'}, {"ACG", 'T'},
                // Alanine
                {"GCU", 'A'}, {"GCC", 'A'}, {"GCA", 'A'}, {"GCG", 'A'},
                // Tyrosine
                {"UAU", 'Y'}, {"UAC", 'Y'},
                // Histidine
                {"CAU", 'H'}, {"CAC", 'H'},
                // Glutamine
                {"CAA", 'Q'}, {"CAG", 'Q'},
                // Asparagine
                {"AAU", 'N'}, {"AAC", 'N'},
                // Lysine
                {"AAA", 'K'}, {"AAG", 'K'},
                // Aspartic Acid
                {"GAU", 'D'}, {"GAC", 'D'},
                // Glutamic Acid
                {"GAA", 'E'}, {"GAG", 'E'},
                // Cysteine
                {"UGU", 'C'}, {"UGC", 'C'},
                // Tryptophan
                {"UGG", 'W'},
                // Arginine
                {"CGU", 'R'}, {"CGC", 'R'}, {"CGA", 'R'}, {"CGG", 'R'}, {"AGA", 'R'}, {"AGG", 'R'},
                // Glycine
                {"GGU", 'G'}, {"GGC", 'G'}, {"GGA", 'G'}, {"GGG", 'G'},

                // Stop codons
                {"UAA", '-'}, {"UAG", '-'}, {"UGA", '-'}
        };

        string protein = ""; // sequence of protein
        bool started = false; // to see if we already started

        for (int i = 0; i + 2 < data.size(); i += 3) { // check every 3 nucleotides
            string codon = data.substr(i, 3); // take 3 of them

            if (!started) { // look for start
                if (codon == "AUG") {
                    started = true;
                    protein += 'M'; // start with Methionine
                }
            }
            else {
                char aminoAcid = codonTable[codon];

                if (aminoAcid == '-') break; // stop codon
                if (aminoAcid) protein += aminoAcid;
            }
        }

        return ProteinSequence(identifier, protein);
    }
};


class DNASequence : public Sequence { // inherit from sequence, we have left valid chars, complement and transcribe
private:
    string VALID_CHARS = "ATGC"; // valid chars for DNA

public:
    /**
      * Constructs a DNASequence and validates characters.
      * @throws invalid_argument if any character is not a valid DNA nucleotide.
      */
    DNASequence(string id, string seq) : Sequence(id, seq) { // i need to 'call' the parent

        for (char i : seq) { // for each character in sequence
            if (VALID_CHARS.find(i) == string::npos) { // find this char in valid chars, if not found
                throw invalid_argument("Invalid character in DNA");
            }
        }
    }

    /**
     * Computes the reverse complement of a given DNA string.
     * @param complimentary DNA string to complement.
     * @return The reverse complement string.
     * @throws invalid_argument if the input is empty.
     */
    string complement(string complimentary) {  // i just used the function from L1Z6

        if (complimentary.empty()) {
            throw invalid_argument("Sequence can't be empty");
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
        }

        // now we have string 3' 5'
        reverse(matrix.begin(), matrix.end()); // then we will have 5' 3'

        return matrix;
    }

    /**
      * Transcribes the DNA sequence into its RNA complement.
      * @return An RNASequence object.
      * @throws invalid_argument if the sequence is empty or contains invalid characters.
      */
    RNASequence transcribe() { // again i used method from earlier
        if (data.empty()) {
            throw invalid_argument("Sequence cannot be empty");
        }

        string RNA = "";

        for (char nucleotide : data) {
            if (nucleotide == 'G') {
                RNA.push_back('C');
            }
            else if (nucleotide == 'C') {
                RNA.push_back('G');
            }
            else if (nucleotide == 'A') {
                RNA.push_back('U');
            }
            else if (nucleotide == 'T') {
                RNA.push_back('A');
            }
            else {
                throw invalid_argument("Sequence has invalid nucleotides");
            }
        }

        return RNASequence(identifier, RNA); // return the object
    }

};

/**
 * Tests the all functionalities from the classes.
 *
 */
void test_sequences() {
    // sequence class
    Sequence s1("seq1", "ATGCGT");
    assert(s1.toString() == ">seq1\nATGCGT");
    assert(s1.length() == 6);
    s1.mutate(1, 'A');
    assert(s1.getData() == "AAGCGT");
    vector<int> motif_positions = s1.findMotif("CG");
    assert(motif_positions[0] == 3);
    cout << "Sequence class passed all tests" << endl;

    try {
        s1.mutate(10, 'A');
        cout << "Mutate should have thrown an exception (invalid position)" << endl;
    } catch (const out_of_range& e) {
        cout << "Correctly caught mutation" << endl;
    }

    // DNA
    DNASequence d1("dna1", "ATGC");
    assert(d1.complement("ATGC") == "GCAT");
    RNASequence rna = d1.transcribe();
    assert(rna.getData() == "UACG");
    cout << "DNASequence passed tests" << endl;

    try {
        DNASequence d_invalid("badDNA", "ATXG");
        cout << "Invalid character should not have passed" << endl;
    } catch (const invalid_argument& e) {
        cout << "Correctly caught exception" << endl;
    }

    // RNA
    RNASequence r1("rna1", "AUGGCCUAA");
    ProteinSequence protein = r1.transcribe();
    assert(protein.getData() == "MA");
    cout << "RNA transcription to Protein passed" << endl;

    try {
        RNASequence r_invalid("badRNA", "AUZCC");
        cout << "Invalid RNA character not caught" << endl;
    } catch (const invalid_argument& e) {
        cout << "Correctly caught invalid RNA sequence" << endl;
    }

    // protein
    try {
        ProteinSequence p_invalid("badProtein", "MAZK");
        cout << "Invalid protein character not caught!" << endl;
    } catch (const invalid_argument& e) {
        cout << "Correctly caught invalid protein sequence" << endl;
    }
}


int main() {
    test_sequences();
    return 0;
}