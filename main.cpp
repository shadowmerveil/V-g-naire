#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int mod_inverse(int a, int m) {
    int m0 = m, x0 = 0, x1 = 1;

    while (a > 1) {
        int q = a / m;
        int temp = m;
        m = a % m;
        a = temp;
        temp = x0;
        x0 = x1 - q * x0;
        x1 = temp;
    }

    return x1 + m0 * (x1 < 0 ? 1 : 0);
}

bool is_coprime(int a, int b) {
    return gcd(a, b) == 1;
}

std::pair<int, int> generate_keypair() {
    const int alphabet_size = 26;
    std::srand(std::time(0));

    int a, b;
    do {
        a = std::rand() % alphabet_size + 2;
        b = std::rand() % alphabet_size + 1;
    } while (!is_coprime(a, alphabet_size));

    return std::make_pair(a, b);
}

std::string encrypt(const std::string& plaintext, int a, int b) {
    const int alphabet_size = 26;
    std::string ciphertext;

    for (char c : plaintext) {
        if (std::isalpha(c)) {
            if (std::isupper(c)) {
                ciphertext += static_cast<char>((a * (c - 'A') + b) % alphabet_size + 'A');
            } else {
                ciphertext += static_cast<char>((a * (c - 'a') + b) % alphabet_size + 'a');
            }
        } else {
            ciphertext += c;
        }
    }

    return ciphertext;
}

std::string decrypt(const std::string& ciphertext, int a, int b) {
    const int alphabet_size = 26;
    int a_inv = mod_inverse(a, alphabet_size);
    std::string plaintext;

    for (char c : ciphertext) {
        if (std::isalpha(c)) {
            if (std::isupper(c)) {
                plaintext += static_cast<char>((a_inv * (c - 'A' - b) + alphabet_size) % alphabet_size + 'A');
            } else {
                plaintext += static_cast<char>((a_inv * (c - 'a' - b) + alphabet_size) % alphabet_size + 'a');
            }
        } else {
            plaintext += c;
        }
    }

    return plaintext;
}

int main() {
    auto[key_a, key_b] = generate_keypair();
    std::cout << "Clé publique (a, b): (" << key_a << ", " << key_b << ")\n";

    std::string message = "Hello, World!";
    std::cout << "Message d'origine: " << message << "\n";

    std::string encrypted_message = encrypt(message, key_a, key_b);
    std::cout << "Message chiffré: " << encrypted_message << "\n";

    std::string decrypted_message = decrypt(encrypted_message, key_a, key_b);
    std::cout << "Message déchiffré: " << decrypted_message << "\n";

    return 0;
}
