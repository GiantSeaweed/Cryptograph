#include <iostream>
#include <sstream>
#include <iomanip>
#include <cryptopp/osrng.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>

using namespace std;
using namespace CryptoPP;

void printOTP();
void char2num(string str, short* p, int length);
void num2char(short* p  ,char* str, int length);
int main() {
    printOTP();
    cout << "Please input your plaintext:\n";
    string str_plaintext;
    getline(cin, str_plaintext);
    int length = str_plaintext.size();
    cout << "Length: " << length << endl;

    SecByteBlock seed(length); // Secure memory block
    OS_GenerateRandomBlock(false, seed, length);//Generate random array of bytes
    //OS_GenerateRandomBlock() uses the underlying operating system's random number generator.

    string hex_key;
    HexEncoder hexEncoder(new StringSink(hex_key));
    hexEncoder.Put(seed, length);
    hexEncoder.MessageEnd(); //signal the end of a message.

    /*** convert plaintext(string) to hex format ***/
    stringstream ss;
    for (int i = 0; i < length; i++) {
        ss << hex << (int) str_plaintext[i];
    }
    string hex_plaintext = ss.str();
    cout << "PlainText : " << hex_plaintext << endl;
    cout << "Key       : " << hex_key <<endl;

    short* num_key = new short[length * 2];
    short* num_pt  = new short[length * 2];
    short* num_ct_tmp  = new short[length * 2];
    short* num_ct  = new short[length];

    char2num(hex_plaintext, num_pt, length * 2);
    char2num(hex_key,      num_key, length * 2);

    /** XOR Operations **/
    for(int i=0;i < length*2; i++){
        num_ct_tmp[i] = num_pt[i] ^ num_key[i];
    }
    for(int i=0;i < length; i++){
        num_ct[i] = num_ct_tmp[2*i]*16+num_ct_tmp[2*i+1];
    }

    /** Convert num_ct_tmp(hex) to string format **/
    char hex_ciphertext[length];
    num2char(num_ct_tmp, hex_ciphertext,length*2);

    cout<<"CipherText: "<<hex_ciphertext<<endl;

    return 0;
}

void char2num(string str, short* p, int length){
    for(int i=0;i<length;i++){
        if(str[i]>='A' && str[i]<='F'){
            p[i] = str[i] - 'A' + 10;
        }
        else if(str[i]>='a' && str[i]<='f'){
            p[i] = str[i] - 'a' + 10;
        }
        else if(str[i]>='0' && str[i]<='9'){
            p[i] = str[i] - '0';
        }
    }
}
void num2char(short* p  ,char* str, int length){
    for(int i=0;i<length;i++){
        if(p[i]>=0 && p[i]<=9){
            str[i] = p[i] + '0';
        }
        else if(p[i] >=10 && p[i]<=15){
            str[i] = p[i] - 10 + 'a';
        }
    }
}

void printOTP(){
    cout<<"   ____                _______                   ____            __\n"
          "  / __ \\____  ___     /_  __(_)___ ___  ___     / __ \\____ _____/ /\n"
          " / / / / __ \\/ _ \\     / / / / __ `__ \\/ _ \\   / /_/ / __ `/ __  / \n"
          "/ /_/ / / / /  __/    / / / / / / / / /  __/  / ____/ /_/ / /_/ /  \n"
          "\\____/_/ /_/\\___/    /_/ /_/_/ /_/ /_/\\___/  /_/    \\__,_/\\__,_/   \n"
          "                                                                   \n";
}