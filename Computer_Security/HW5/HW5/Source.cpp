#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <iomanip>

using namespace std;

const vector<double> ENGLISH_FREQS = {
    0.127, // A
    0.091, // B
    0.082, // C
    0.075, // D
    0.150, // E (higher weight)
    0.067, // F
    0.063, // G
    0.061, // H
    0.090, // I (higher weight)
    0.043, // J
    0.040, // K
    0.028, // L
    0.028, // M
    0.024, // N
    0.100, // O (higher weight)
    0.022, // P
    0.020, // Q
    0.060, // R
    0.070, // S (higher weight)
    0.080, // T (higher weight)
    0.010, // U
    0.008, // V
    0.0015, // W
    0.0015, // X
    0.001,  // Y
    0.0007  // Z
};



// Count letter frequencies in ciphertext
vector<double> countFrequencies(const string& ciphertext) {
    vector<double> freqs(26, 0.0);
    int totalLetters = 0;

    // Count letter frequencies
    for (char c : ciphertext) {
        if (isalpha(c)) {
            freqs[c - 'A']++;
            totalLetters++;
        }
    }

    // Normalize frequencies
    for (double& freq : freqs) {
        if (totalLetters > 0) {
            freq /= totalLetters;
        }
    }

    return freqs;
}


// Compute Phi(i) table
vector<double> computePhiTable(const vector<double>& cipherFreqs) {
    vector<double> phi(26, 0.0);

    for (int shift = 0; shift < 26; shift++) {
        double correlation = 0.0;
        for (int j = 0; j < 26; j++) {
            int shiftIndex = (j + shift) % 26;
            correlation += ENGLISH_FREQS[j] * cipherFreqs[shiftIndex];
        }
        phi[shift] = correlation;
    }

    return phi;
}

string decryptCaesar(const string& ciphertext, int key) {
    string plaintext = "";

    for (char c : ciphertext) {
        if (isupper(c)) {
            // Decrypt uppercase letters
            plaintext += (c - 'A' - key + 26) % 26 + 'A';
        }
        else if (isdigit(c)) {
            // Decrypt digits
            plaintext += (c - '0' - key + 10) % 10 + '0';
        }
        else {
            // Leave other characters unchanged
            plaintext += c;
        }
    }

    return plaintext;
}

int findBestKey(const vector<double>& phiTable) {
    int bestKey = 0;
    double maxCorrelation = phiTable[0];

    for (int i = 1; i < 26; i++) {
        if (phiTable[i] > maxCorrelation) {
            maxCorrelation = phiTable[i];
            bestKey = i;
        }
    }

    return bestKey;
}


int main() {
    string ciphertext = "TEBKFKQEBZLROPBLCERJXKBSBKQP";

    // Step 1: Count frequencies
    vector<double> cipherFreqs = countFrequencies(ciphertext);

    // Step 2: Compute Phi(i) table
    vector<double> phiTable = computePhiTable(cipherFreqs);

    // Output Phi(i) table
    cout << "Shift | Correlation" << endl;
    cout << "--------------------" << endl;
    int key = findBestKey(phiTable);

    for (int shift = 0; shift < 26; shift++) 
    {
        cout << setw(5) << shift << " | " << fixed << setprecision(5) << phiTable[shift] << endl;
    }

    cout << "Best Key: " << key << endl;

    //for (int i = 0; i < 26; i++)
    //{
    //    string plaintext = decryptCaesar(ciphertext, i);
    //    cout << "Decrypted Text key " << i << ": " << plaintext << endl;
    //}

    string plaintext = decryptCaesar(ciphertext, key);
    cout << "Decrypted Text key " << key << ": " << plaintext << endl;

    return 0;
}
