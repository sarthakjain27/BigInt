//
// Created by Sarthak Jain on 10/17/19.
// GID: 22 (Twenty Two)
//

#include "BigInt.h"

BigInt::BigInt(const vector<int>& init_dig) {
    positive=true;
    int start=0;
    //skipping leading zeros
    while(start<init_dig.size() && init_dig[start]==0)
    {
        start++;
    }
    if(start==init_dig.size())
    {
        digits.push_back(0);
    }
    else{
        if(init_dig[start]<0){
            positive=false;
            digits.push_back(-1*init_dig[start]);
            start++;
        }
       for(int i=start;i<init_dig.size();i++)
           digits.push_back(init_dig[i]);
    }
}

BigInt::BigInt(const vector<char>& init_char) {
    int start=0;
    positive=true;

    //checking for negative sign or positive sign
    if(init_char[start]=='-'){
        positive=false;
        start++;
    }
    else if(init_char[start]=='+')
        start++;

    //Skipping leading zeros
    while(start<init_char.size() && init_char[start]=='0')
    {
        start++;
    }

    if(start==init_char.size())
    {
        digits.push_back(0);
    }
    else{
        for(int i=start;i<init_char.size();i++)
        {
            digits.push_back(init_char[i]-'0');
        }
    }
}

BigInt::BigInt(char* init_char, int n) {
    positive=true;
    int start=0;

    if(init_char[start]=='-'){
        positive=false;
        start++;
    }
    else if(init_char[start]=='+')
    {
        start++;
    }
    //Skipping leading zeros
    while(start<n && init_char[start]=='0')
    {
        start++;
    }

    if(start==n)
    {
        digits.push_back(0);
    }
    else{
        for(int i=start;i<n;i++)
        {
            digits.push_back(init_char[i]-'0');
        }
    }
}

BigInt::~BigInt() {
    cout<<"Destructor called for:  ";
    printBigInt();
}

BigInt operator+(const BigInt& f,const BigInt& s)
{
    BigInt first=f;
    BigInt second=s;

    //first number is positive and second is negative a + (-b)
    if(first.positive && !second.positive)
    {
        second.positive=true;
        // +a - (+b)
        return first-second;
    }
    //first negative and second positive -a + b
    else if(!first.positive && second.positive)
    {
        first.positive=true;
        // +b - (+a)
        return second-first;
    }

    //both negative condition then simple sum and result sign is negative -a + (-b)
    bool bothNegative=(!first.positive && !second.positive);

    int i=first.digits.size()-1;
    int j=second.digits.size()-1;
    int carry=0,sum=0;
    vector<int> res;
    while(i>=0 || j>=0)
    {
        int a=(i>=0)?first.digits[i]:0;
        int b=(j>=0)?second.digits[j]:0;
        sum=carry+a+b;
        carry=sum/10;
        sum%=10;
        res.insert(res.begin(),sum);
        i--;
        j--;
    }
    if(carry!=0)
        res.insert(res.begin(),carry);

    for(int k=0;k<res.size() && res[0]==0;k++)
    {
        res.erase(res.begin());
    }
    BigInt ans(res);
    if(bothNegative)
        ans.positive= false;
    return ans;
}

BigInt operator-(const BigInt& f,const BigInt& s)
{
    BigInt fcopy=f;
    BigInt scopy=s;

    // +a - (-b) = a + b
    if(fcopy.positive && !scopy.positive)
    {
        scopy.positive=true;
        // +a + (+b)
        return fcopy+scopy;
    }

    // -a - (+b) = -a -b
    else if(!fcopy.positive && scopy.positive){
        scopy.positive=false;
        //-a + (-b) = -a-b
        return fcopy+scopy;
    }

    // (-a) - (-b) => (+b) - (+a)
    else if(!fcopy.positive && !scopy.positive)
    {
        fcopy.positive=true;
        scopy.positive=true;
        return scopy-fcopy;
    }

    int n1=f.digits.size();
    int n2=s.digits.size();
    int i=n1-1,j=n2-1;
    bool negresult=false;

    //if second has more digits than first
    if(n2>n1)
    {
        negresult=true;
        i=n2-1;
        fcopy=s;
        scopy=f;
        j=n1-1;
    }
    //if both has same digits
    else if(n1==n2)
    {
        int a=0,b=0;
        while(a<n1 && b<n2 && fcopy.digits[a]==scopy.digits[b])
        {
            a++;
            b++;
        }
        //both are same
        if(a==n1)
        {
            vector<int> res;
            res.push_back(0);
            return BigInt(res);
        }
        else{
            //second number is greater
            if(scopy.digits[b]>fcopy.digits[a])
            {
                negresult=true;
                i=n2-1;
                fcopy=s;
                scopy=f;
                j=n1-1;
            }
        }
    }
    vector<int> res;
    while(i>=0 || j>=0)
    {
        int a=(i>=0)?fcopy.digits[i]:0;
        int b=(j>=0)?scopy.digits[j]:0;

        if(a>=b)
            res.insert(res.begin(),a-b);
        else
        {
                fcopy.digits[i-1]--;
                a+=10;
                res.insert(res.begin(),a-b);
        }
        i--;
        j--;
    }
    for(int k=0;k<res.size() && res[0]==0;k++)
    {
        res.erase(res.begin());
    }

    BigInt ans(res);
    ans.positive=!negresult;
    return ans;
}

void BigInt::printBigInt() {
    if(positive)
        cout<<"Number is positive and digits are: ";
    else
        cout<<"Number is negative and digits are: ";
    for(int & digit : digits)
    {
        cout<<digit;
    }
    cout<<endl;
}



