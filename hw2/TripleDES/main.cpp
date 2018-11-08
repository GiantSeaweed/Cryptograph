// g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
// g++ -g -O2 -DNDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread

//#include "osrng.h"
#include <cryptopp/osrng.h>
using CryptoPP::AutoSeededRandomPool;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include <cryptopp/cryptlib.h>
using CryptoPP::Exception;

#include <cryptopp/hex.h>
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include <cryptopp/filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include <cryptopp/des.h>
using CryptoPP::DES_EDE2;

#include <cryptopp/modes.h>
using CryptoPP::CBC_Mode;

#include <cryptopp/secblock.h>
using CryptoPP::SecByteBlock;

#include<cryptopp/config.h>
using CryptoPP::byte;

#include <fstream>
using std::ifstream;
using std::ofstream;

#define BYTE_LENGTH 16
//byte key_byte[BYTE_LENGTH];
void str2byte(string str,byte* b) {
    int length = str.length();
    string tmp;
    for (int i = 0; i < length; i += 8) {
        tmp = str.substr(i, 8);
        b[i/8] = (byte) strtol(tmp.c_str(), NULL, 2);
 //       cout<<(int)b[i/8]<<" ";
        tmp = "";
//        for(int i=0;i<BYTE_LENGTH;i++){
//            cout<<(int)key_byte[i]<<" ";
//        }
//        cout<<endl;
    }
    //cout << endl;
}

string readfile(string filename){
    ifstream ifile;
    string str;
    ifile.open(filename);//,std::ofstream::in);
    if(!ifile){
        cerr << filename <<" open failed!" <<endl;
    }
    else{
        ifile >> str;
//        cout << str << endl;
        cout<<"Read "<<filename<<" successfully!"<<endl;
    }
    ifile.close();
    ifile.clear();
    return str;
}

void writefile(string str, string filename){
    ofstream ofile;
    ofile.open(filename);
    if(!ofile){
        cerr <<filename<< "open failed"<<endl;
    }
    else{
        string str_binary;
        int length=str.length();
        for(int i=0;i<length;i++){
            switch (str[i]){
                case '0': str_binary += "0000"; break;
                case '1': str_binary += "0001"; break;
                case '2': str_binary += "0010"; break;
                case '3': str_binary += "0011"; break;
                case '4': str_binary += "0100"; break;
                case '5': str_binary += "0101"; break;
                case '6': str_binary += "0110"; break;
                case '7': str_binary += "0111"; break;
                case '8': str_binary += "1000"; break;
                case '9': str_binary += "1001"; break;
                case 'A': str_binary += "1010"; break;
                case 'B': str_binary += "1011"; break;
                case 'C': str_binary += "1100"; break;
                case 'D': str_binary += "1101"; break;
                case 'E': str_binary += "1110"; break;
                case 'F': str_binary += "1111"; break;
                default: break;
            }
        }
        ofile << str_binary;
        cout<< filename << " has been written successfully !"<<endl;
    }
    ofile.close();

}
int main(int argc, char* argv[])
{
    string key_str = readfile("key.txt");
    byte key_byte[BYTE_LENGTH];
    str2byte(key_str, key_byte);

//    for(int i=0;i<BYTE_LENGTH;i++){
//        cout<<(int)key_byte[i]<<" ";
//    }
//    cout<<endl;


    string plain_str = readfile("plain.txt");
    byte plain_byte[BYTE_LENGTH]; //cout<<plain_str << endl << key_str <<endl;
    str2byte(plain_str,plain_byte);

//
//    for(int i=0;i<BYTE_LENGTH;i++){
//        cout<<(int)plain_byte[i]<<" ";
//    }
//    cout<<endl;

    AutoSeededRandomPool prng;


//    for(int i=0;i<BYTE_LENGTH;i++){
//        cout<<(int)key_byte[i]<<" ";
//    }
//    cout<<endl;

    SecByteBlock key(key_byte,BYTE_LENGTH);
//    prng.GenerateBlock(key, key.size());

    byte iv[DES_EDE2::BLOCKSIZE];
    prng.GenerateBlock(iv, sizeof(iv));

//    string plain = "CBC Mode Test";
    string plain = "0000000000000000";
    for(int i=0;i<BYTE_LENGTH;i++){
        plain[i] = (byte)plain_byte[i];
    }
    string cipher, encoded, recovered;

    /*********************************\
    \*********************************/

    // Pretty print key
    encoded.clear();
    StringSource(key, BYTE_LENGTH, true,
                 new HexEncoder(
                         new StringSink(encoded)
                 ) // HexEncoder
    ); // StringSource
    cout << "key: " << encoded << endl;

    // Pretty print iv
    encoded.clear();
    StringSource(iv, sizeof(iv), true,
                 new HexEncoder(
                         new StringSink(encoded)
                 ) // HexEncoder
    ); // StringSource
    cout << "iv: " << encoded << endl;

    /*********************************\
    \*********************************/

    try
    {
        //cout << "plain text: " << plain << endl;

        CBC_Mode< DES_EDE2 >::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter adds padding
        //  as required. ECB and CBC Mode must be padded
        //  to the block size of the cipher.
        StringSource(plain, true,
                     new StreamTransformationFilter(e,
                                                    new StringSink(cipher)
                     ) // StreamTransformationFilter
        ); // StringSource
    }
    catch(const CryptoPP::Exception& e)
    {
        cerr << e.what() << endl;
        exit(1);
    }

    /*********************************\
    \*********************************/

    // Pretty print
    encoded.clear();
    StringSource(cipher, true,
                 new HexEncoder(
                         new StringSink(encoded)
                 ) // HexEncoder
    ); // StringSource
    cout << "cipher text: " << encoded << endl;

    /*********************************\
    \*********************************/

    try
    {
        CBC_Mode< DES_EDE2 >::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv);

        // The StreamTransformationFilter removes
        //  padding as required.
        StringSource s(cipher, true,
                       new StreamTransformationFilter(d,
                                                      new StringSink(recovered)
                       ) // StreamTransformationFilter
        ); // StringSource

        //cout << "recovered text: " << recovered << endl;
    }
    catch(const CryptoPP::Exception& e)
    {
        cerr << e.what() << endl;
        exit(1);
    }

    writefile(encoded,"encrypted.txt");

    /*********************************\
    \*********************************/

    return 0;
}


