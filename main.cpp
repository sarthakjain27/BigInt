#include "BigInt.h"

int main() {
    vector<int> a={0,0,0,-1,2,3,4};
    vector<char> b={'-','1','2','3'};
    vector<char> c={'1','2','3'};
    char d[]="-1";
    char e[]="123456";
    BigInt aa(a);
    cout<<aa;
    BigInt bb(b);
    cout<<bb;
    BigInt cc(c);
    cout<<cc;
    BigInt dd(d,2);
    cout<<dd;

    BigInt ee(e,6);
    //Copy Constructor called for 123456
    BigInt ff(ee);
    cout<<ee;
    cout<<ff;


    cout<<"Doing addition"<<endl;
    BigInt res=aa+aa;
    cout<<res;

    cout<<"Doing Subtraction"<<endl;
    BigInt res2=aa-aa;
    cout<<res2;

    cout<<"Doing multiplication"<<endl;
    BigInt res3=dd*cc;
    cout<<res3;

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

    cout<<"Doing prefix ++"<<endl;
    ++dd;
    cout<<dd;

    cout<<"Doing prefix --" <<endl;
    --dd;
    cout<<dd;

    cout<<"Doing postfix ++"<<endl;
    BigInt res9=dd++;
    cout<<res9;

    cout<<"Doing postfix --" <<endl;
    BigInt res10=dd--;
    cout<<res10;

    cout<<"Overloaded << operator"<<endl;
    cout<<aa;

    BigInt input;
    cout<<"Overloaded >> operator"<<endl;
    cin>>input;
    cout<<input;
}