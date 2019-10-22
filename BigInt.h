
// Student Name: Sarthak Jain
// Student ID: 014508013
// GID: 22 (Twenty Two)

#ifndef ASSIGNMENT8_BIGINT_H
#define ASSIGNMENT8_BIGINT_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>
using namespace std;


class BigInt{

public:
    vector<int> digits;
    bool positive;

    BigInt();
    BigInt(const vector<int>& init_dig);
    BigInt(const vector<char>& init_char);
    BigInt(char* init_arr,int n);
    friend BigInt operator+(const BigInt& first, const BigInt& second);
    friend BigInt operator-(const BigInt& first, const BigInt& second);
    friend BigInt operator*(const BigInt& first, const BigInt& second);
    friend bool operator!(const BigInt& first);
    friend bool operator==(const BigInt& first,const BigInt& second);
    friend bool operator>=(const BigInt& first,const BigInt& second);
    friend bool operator>(const BigInt& first,const BigInt& second);
    friend bool operator<(const BigInt& first,const BigInt& second);
    friend bool operator<=(const BigInt& first,const BigInt& second);
    friend BigInt operator++(BigInt& first);
    friend BigInt operator--(BigInt& first);
    friend BigInt operator++(BigInt& first, int num);
    friend BigInt operator--(BigInt& first,int num);
    friend ostream &operator<<( ostream &output, const BigInt &first );
    friend istream &operator>>( istream &input, BigInt &first );

};

#endif //ASSIGNMENT8_BIGINT_H
