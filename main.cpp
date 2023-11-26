#include <iostream>
#include <string>

using namespace std;

string vigenere_encrypt(const string &message, const string &cle) {
    string ciphertext;
    int messageLen = message.length();
    int cleLen = cle.length();

    for (int i = 0; i < messageLen; ++i) {
        // Vérifie si le caractère est alphabétique
        if (isalpha(message[i])) {
            char base = isupper(message[i]) ? 'A' : 'a';
            int indexMessage = message[i] - base;
            int indexCle = cle[i % cleLen] - base;
            int new_index = (indexMessage + indexCle) % 26;
            char new_lettre = base + new_index;
            ciphertext += new_lettre;
        } else {
            // Si le caractère n'est pas alphabétique, le conserve tel quel
            ciphertext += message[i];
        }
    }

    return ciphertext;
}

int main() {
    string message = "Bonjour";
    string cle = "CLE";
    string ciphertext = vigenere_encrypt(message, cle);

    cout << "Message chiffré : " << ciphertext << endl;

    return 0;
}
