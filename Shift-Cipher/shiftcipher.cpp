/*
Nama	    : Hanifan Ayusti Khairunnisa
NPM		    : 140810200065
Kelas	    : A
*/

#include <iostream>

namespace ShiftCipher {
    const int ASCII_CODE_LC=97;
    const int ASCII_CODE_UC=65;

    /**
     * @brief 
     * Check if character is in range of A(0) to Z(25)
     *  
     * @param karakter Character being checked
     * @param code Ascii code used
     * 
     * @return true or false 
     */
    bool inRangeOfAscii(char karakter, int code) {
        return (
            (karakter-code) >= 0
            &&
            (karakter-code) <= 25
        );
    }

    /**
     * @brief 
     * Encrypting a text using the formula below:
     * Formula = (x + K) mod 26
     * 
     * @param text Plaintext for encryption
     * @param key Key used in formula
     * 
     * @return Encrypted text
     */
    std::string encrypt(std::string text="abc", int key=1) {
        std::string ans="";

        for(char ch: text) {
            if(inRangeOfAscii(ch,ASCII_CODE_LC)) { // Handling for lower case
                ch = (((ch-ASCII_CODE_LC)+key)%26)+ASCII_CODE_LC;
            } else if(inRangeOfAscii(ch,ASCII_CODE_UC)) { // Handling for upper case
                ch = (((ch-ASCII_CODE_UC)+key)%26)+ASCII_CODE_UC;
            }
            ans.push_back(ch);
        }

        return ans;
    }

    /**
     * @brief
     * Decrypting a text using the formula below:
     * Formula = (x - K) mod 26
     * 
     * @param text Encrypted Text for decryption
     * @param key Key used in formula
     * 
     * @return Decrypted text
     */
    std::string decrypt(std::string text="abc", int key=1) {
        std::string ans="";

        for(char ch: text) {
            if(inRangeOfAscii(ch,ASCII_CODE_LC)) { // Handling for lower case
                ch -= (ASCII_CODE_LC + key);
                ch = (ch < 0) ? ch+26 : ch; // If char is below 0, then it adds 26 to the char value
                ch = (ch%26)+ASCII_CODE_LC;
            } else if(inRangeOfAscii(ch,ASCII_CODE_UC)) { // Handling for upper case
                ch -= (ASCII_CODE_UC + key);
                ch = (ch < 0) ? ch+26 : ch; // If char is below 0, then it adds 26 to the char value
                ch = (ch%26)+ASCII_CODE_UC;
            }
            ans.push_back(ch);
        }

        return ans;        
    }
};

int main() {
    system("cls");
    bool running=true; // While this is true, program will keep on running

    while(running) {
        int pilihan=1;

        // Menu UI
        printf("\n=== MAIN MENU ===\n");
        printf("| 1. Enkripsi   |\n");
        printf("| 2. Dekripsi   |\n");
        printf("| 3. Exit       |\n");
        printf("|---------------|\n");
        std::cout << "| Pilihan: "; std::cin >> pilihan; std::cin.ignore();

        std::string plaintext="";
        int key=1;

        switch(pilihan) {
            case 1: 
                std::cout << "|---------------|";
                std::cout << "\n| Text: "; std::getline(std::cin,plaintext);
                std::cout << "| Key: "; std::cin >> key;
                std::cout << "| Encryption = " << ShiftCipher::encrypt(plaintext,key) << "\n";
                break;
                
            case 2: 
                std::cout << "|---------------|";
                std::cout << "\n| Text: "; std::getline(std::cin,plaintext);
                std::cout << "| Key: "; std::cin >> key;
                std::cout << "| Decryption = " << ShiftCipher::decrypt(plaintext,key) << "\n";
                break;

            case 3: // Exit program
                system("cls");
                printf("Terimakasih!\n");
                system("pause");
                running=false;
                break;

            default: // Error handling
                printf("\nTerjadi kesalahan, silahkan coba lagi!\n");
                system("pause");
                break;
        }
    }
}