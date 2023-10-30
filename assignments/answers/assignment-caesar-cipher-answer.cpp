// A solution for topic 2 assignments, assignment 6

#include <iostream>
#include <string>

std::string cipher(std::string msg, int shift, std::string alphabet) {
    std::string encryptedMsg;
    // loop through all letters in the message
    for (unsigned int i = 0; i < msg.size(); ++i) {
        // get current letter in the message
        char currentLetter = toupper(msg[i]);
        // find the index of that letter in the alphabet
        int currentLetterIndex = alphabet.find(currentLetter);
        // find the index in the alphabet for the encrypted letter
        int encryptedLetterIndex = currentLetterIndex + shift;
        // ensure the shifted letter stays within the limits of alphabet size
        while (encryptedLetterIndex >= (int)alphabet.size())
            encryptedLetterIndex -= alphabet.size();
        while (encryptedLetterIndex < 0)
            encryptedLetterIndex += alphabet.size();
        // find the encrypted letter for the current letter
        char encryptedLetter = alphabet[encryptedLetterIndex];
        encryptedMsg += encryptedLetter;
    }
    return encryptedMsg;
}

std::string decipher(std::string msg, int shift, std::string alphabet) {
    std::string decryptedMsg;
    decryptedMsg = cipher(msg, -shift, alphabet);
    return decryptedMsg;
}


int main()
{
    // define the alphabet we're using
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // the message we want to cipher
    std::string message = "ABCHELLOWORLDXYZ";
    // the shift parameter of Caesar cipher (note: if you want to shift the message "down" the alphabet, use a negative number)
    int shift = -52;

    std::string encrypted = cipher(message, shift, alphabet);
    std::string decrypted = decipher(encrypted, shift, alphabet);

    // encrypted message
    std::cout << encrypted << std::endl;
    // this should match the original message
    std::cout << decrypted << std::endl;

}
