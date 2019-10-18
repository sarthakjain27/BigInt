//
// Created by Sarthak Jain on 10/17/19.
// GID: 22 (Twenty Two)
//

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

    BigInt(const vector<int>& init_dig);
    BigInt(const vector<char>& init_char);
    BigInt(char* init_arr,int n);
    ~BigInt();
    void printBigInt();
    friend BigInt operator+(const BigInt& first, const BigInt& second);
    friend BigInt operator-(const BigInt& first, const BigInt& second);
    friend BigInt operator*(const BigInt& first, const BigInt& second);
    friend bool operator!(const BigInt& first);
    friend bool operator==(const BigInt& first,const BigInt& second);
};

#endif //ASSIGNMENT8_BIGINT_H
