#include "BigInt.h"

int main() {
    vector<int> a={-9,9,9};
    vector<char> b={'-','9','9','9'};
    vector<char> c={'1','2','3'};
    char d[]="-1";
    char e[]="123456";
    BigInt aa(a);
    cout<<aa<<endl;
    BigInt bb(b);
    cout<<bb<<endl;
    BigInt cc(c);
    cout<<cc<<endl;
    BigInt dd(d,2);
    cout<<dd<<endl;
    BigInt ee(e,6);
    cout<<ee<<endl;

    cout<<"Doing addition"<<endl;
    cout<<aa<<" + "<<aa<<" : "<<(aa+aa)<<endl;

    cout<<"Doing Subtraction"<<endl;
    cout<<aa<<" - "<<aa<<" : "<<(aa-aa)<<endl;

    cout<<"Doing multiplication"<<endl;
    cout<<dd<<" * "<<aa<<" : "<<(dd*aa)<<endl;

    cout<<"Doing == "<<endl;
    cout<<cc<<" == "<<bb<<" : "<<(cc==bb)<<endl;

    cout<<"Doing > "<<endl;

    cout<<aa<<" > "<<aa<<" : "<<(aa>aa)<<endl;

    cout<<"Doing >= "<<endl;
    cout<<aa<<" >= "<<aa<<" : "<<(aa==aa)<<endl;

    cout<<"Doing < "<<endl;
    cout<<dd<<" < "<<cc<<" : "<<(dd<cc)<<endl;

    cout<<"Doing <= "<<endl;
    cout<<cc<<" <= "<<dd<<" : "<<(cc<=dd)<<endl;

    cout<<"Doing prefix ++"<<endl;
    cout<<aa<<" Prefix ++: "<<(++aa)<<endl;

    cout<<"Doing prefix --" <<endl;
    cout<<aa<<" Prefix --: "<<(--aa)<<endl;

    cout<<"Doing postfix ++"<<endl;
    cout<<aa<<" Postfix ++: "<<(aa++)<<endl;
    cout<<"After postfix ++: "<<aa<<endl;

    cout<<"Doing postfix --" <<endl;
    cout<<aa<<" Postfix --: "<<(aa--)<<endl;
    cout<<"After postfix --: "<<aa<<endl;

    cout<<"Overloaded >> operator"<<endl;
    cin>>aa;
}