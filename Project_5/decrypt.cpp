//
//  main.cpp
//  Project_Five
//
//  Created by Srishti Dhawan on 5/20/19.
//  Copyright © 2019 Srishti Dhawan. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <array>
#include <cstring>
#include <cctype>    // allows us to use isalpha()
using namespace std;





// Will find the array with the number of letters/ words in crib
// words is length so its 1->word not 0->word
void findArray (const char crib[], int arr[], int& words) {
    unsigned long total = strlen(crib);
    
    int arrayNum = 0;
    int numOfLetters = 0;
    for (int i = 0; i < total; i++) {
        for(int j = i; j<total; j++) {
            if (isalpha(crib[j])) {
                numOfLetters++;
                i++;
            }
            else {
                if (numOfLetters > 0) {
                    arr[arrayNum] = numOfLetters;
                    arrayNum++;
                    numOfLetters = 0;
                }
                break;
            }
        }
    }
    if (numOfLetters > 0) {
        arr[arrayNum] = numOfLetters;
        arrayNum++;
        numOfLetters = 0;
    }
    words = arrayNum;
}

//condenses a Phrase
void condensePhrase (const char mainArray[], int start, int end, char newArray[]) {
    int num = 0;
    for (int i = start; i <=end; i++) {
        if (isalpha(mainArray[i])) {
            newArray[num] = mainArray[i];
            num++;
        }
    }
    newArray[num] = '\0';
}



// Will find the starting and ending points of crib (if it A. Exists and B. does not
//have duplicate characters with different crib characters representing it
bool findCrib (const char ciphertext[], const char crib[], int cribDigits[], int wordsInCrib, int& start, int& end) {
    int totalLength = static_cast<int>(strlen(ciphertext));
    int current = 0;
    bool exist = false;
    int i= 0;
    while (i < totalLength) {
        start = i;
        int j = 0;
        //Attempts to find the crib c string within the ciphertext starting at
        //the given starting point
        while (j < wordsInCrib) {
            char c = ciphertext[i];
            if (isalpha(ciphertext[i])) {
                current++;
                i++;
            }
            else if(c == '\n' ){
                i++;
                if (current == cribDigits[j]) {
                    j++;
                    end = i;
                    current = 0;
                    exist = true;
                    return exist;
                }
                else {
                    current = 0;
                    break;
                }
            }
            else {
                if (current ==0) {
                    i++;
                    continue;
                }
                else if (current != cribDigits[j]) {
                    exist = false;
                    current = 0;
                    j=0;
                    i++;
                }
                else{
                    j++;
                    if (j == 1) {
                        start = i - cribDigits[0];
                    }
                    end = i-1;
                    current = 0;
                    i++;
                    exist = true;
                }
            }
            
            if (j == wordsInCrib) {
                break;
            }
        }
        //Confirms that the c string in the ciphertext does not have duplicate
        //characters that correspond to different characters in the crib
        if (j == wordsInCrib) {
            char cribInCipher [80];
            char cribAlone[80];
            condensePhrase(ciphertext, start, end, cribInCipher);
            condensePhrase(crib, 0, static_cast<int>(strlen(crib)), cribAlone);
            
            int length = static_cast<int>(strlen (cribAlone));
            
            int i = 0;
            int j = 0;
            for (i = 0; i < length; i++) {
                for (j = 1; j<length; j++) {
                    if (cribInCipher[i] == cribInCipher[j]) {
                        if (cribAlone[i] != cribAlone[j]) {
                            exist = false;
                            start = 0;
                            end = 0;
                            break;
                        }
                    }
                }
                if (cribInCipher[i] == cribInCipher[j]) {
                    if ((cribAlone[i] != cribAlone[j])) {
                        break;
                    }
                }
            }
            if (cribAlone[i] != cribAlone[j]) {
                exist = false;
                continue;
            }
            else {
                exist = true;
                return exist;
            }
        }
        else {
            start = 0;
            end = 0;
            i++;
            exist = false;
        }
    }
    return exist;
}

void decodeCipher (const char ciphertext[], char cribInCipher[], char cribAlone[], char newCipherText[] ) {
    
    int totalcipher = static_cast<int>(strlen(ciphertext));
    int totalcrib = static_cast<int>(strlen(cribAlone));
    
    
    for (int i =0; i <totalcipher; i++) {
        for (int j =0; j<totalcrib; j++) {
            if (ciphertext[i] == cribInCipher[j]) {
                newCipherText[i] = cribAlone[j];
                newCipherText[i] = toupper(newCipherText[i]);
                break;
            }
            else {
                newCipherText[i] = ciphertext[i];
                if (isalpha(newCipherText[i])) {
                    newCipherText[i] = tolower(newCipherText[i]);
                }
            }
        }
    }
    
}


//Project 5 Function!!!
bool decrypt(const char ciphertext[], const char crib[]) {
    
    int cribDigits[80];
    int wordsInCrib = 0;
    
    //Makes sure crib is less than 80 characters so it fits between 2 new line
    //statements
    if (strlen(crib) > 80) {
        return false;
    }
    
    findArray(crib, cribDigits, wordsInCrib);
    
    int start=0;
    int end=0;
    
    bool result = findCrib(ciphertext, crib, cribDigits, wordsInCrib, start, end);
    
    if (!result) {
        return false;
    }
    
    //Will contain condensed forms of the crib in the cipher and alone
    char cribInCipher [80];
    char cribAlone[80];
    
    
    condensePhrase(ciphertext, start, end, cribInCipher);
    condensePhrase(crib, 0, static_cast<int>(strlen(crib)), cribAlone);
    
        
    char newCipherText [4880];
    
    decodeCipher(ciphertext, cribInCipher, cribAlone, newCipherText);
    
    int totalCipherLength = static_cast<int>(strlen(ciphertext));
    
    for (int i = 0; i< totalCipherLength; i++) {
        cout << newCipherText[i];
    }
    
    return true;
}




void runtest(const char ciphertext[], const char crib[])
{
    cout << "====== " << crib << endl;
    bool result = decrypt(ciphertext, crib);
    cout << "Return value: " << result << endl;
}

int main()
{
    cout.setf(ios::boolalpha); // output bools as "true"/"false"

    runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "my secret");
    runtest("Hirdd ejsy zu drvtry od.\nO'z fodvtrry.\n", "shadow");


}

