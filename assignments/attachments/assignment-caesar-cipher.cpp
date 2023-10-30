
#include <iostream>
#include <string>

std::string cipher(std::string msg, int shift, std::string alphabet) {
    std::string encryptedMsg;
    /*
    * WRITE YOUR CODE HERE
    */
    return encryptedMsg;
}

std::string decipher(std::string msg, int shift, std::string alphabet) {
    std::string decryptedMsg;
    /* 
    * WRITE YOUR CODE HERE
    */
    return decryptedMsg;
}


int main()
{
    // define the alphabet we're using
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // the message we want to cipher
    std::string message = "HELLOWORLD";
    // the shift parameter of Caesar cipher
    int shift = 3;

    std::string encrypted = cipher(message, shift, alphabet);
    std::string decrypted = decipher(encrypted, shift, alphabet);

    // encrypted message
    std::cout << encrypted << std::endl;
    // this should match the original message
    std::cout << decrypted << std::endl;

}
