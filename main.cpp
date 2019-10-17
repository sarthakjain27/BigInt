#include "BigInt.h"

int main() {
    vector<int> a={0,0,0,-1,2,3,4};
    vector<char> b={'-','1','2','3'};
    vector<char> c={'1','2','3'};
    char d[]="-1234";
    char e[]="123456";
    BigInt aa(a);
    aa.printBigInt();
    BigInt bb(b);
    bb.printBigInt();
    BigInt cc(c);
    cc.printBigInt();
    BigInt dd(d,5);
    dd.printBigInt();

    BigInt ee(e,6);
    //Copy Constructor called for 123456
    BigInt ff(ee);
    ee.printBigInt();
    ff.printBigInt();


    //BigInt res=aa+aa;
    //res.printBigInt();

    BigInt res2=aa-aa;
    res2.printBigInt();
}