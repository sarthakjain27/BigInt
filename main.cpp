#include "BigInt.h"

int main() {
    vector<int> a={0,0,0,-1,2,3,4};
    vector<char> b={'-','1','2','3'};
    vector<char> c={'1','2','3'};
    char d[]="345";
    char e[]="123456";
    BigInt aa(a);
    aa.printBigInt();
    BigInt bb(b);
    bb.printBigInt();
    BigInt cc(c);
    cc.printBigInt();
    BigInt dd(d,3);
    dd.printBigInt();

    BigInt ee(e,6);
    //Copy Constructor called for 123456
    BigInt ff(ee);
    ee.printBigInt();
    ff.printBigInt();


    cout<<"Doing addition"<<endl;
    BigInt res=aa+aa;
    res.printBigInt();

    cout<<"Doing Subtraction"<<endl;
    BigInt res2=aa-aa;
    res2.printBigInt();

    cout<<"Doing multiplication"<<endl;
    BigInt res3=dd*cc;
    res3.printBigInt();

    cout<<"Doing == "<<endl;
    bool res4=(cc==bb);
    cout<<res4<<endl;

    cout<<"Doing > "<<endl;
    bool res5=(aa>aa);
    cout<<res5<<endl;

    cout<<"Doing >= "<<endl;
    bool res6=(aa>=aa);
    cout<<res6<<endl;

    cout<<"Doing < "<<endl;
    bool res7=(dd<cc);
    cout<<res7<<endl;

    cout<<"Doing <= "<<endl;
    bool res8=(cc<=dd);
    cout<<res8<<endl;
}