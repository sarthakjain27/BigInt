//
// Created by Sarthak Jain on 10/17/19.
// GID: 22 (Twenty Two)
//

#include "BigInt.h"

BigInt::BigInt()
{
    positive=true;
}

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
    //cout<<"Destructor called for:  ";
    //printBigInt();
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

    BigInt ans(res);
    ans.positive=!negresult;
    return ans;
}

BigInt operator*(const BigInt& f,const BigInt& s)
{
    int n1=f.digits.size();
    int n2=s.digits.size();
    bool negResult=false;
    if((!f.positive && s.positive) || (f.positive && !s.positive))
        negResult=true;
    vector<int> res;
    for(int i=0;i<n1+n2;i++)
        res.push_back(0);

    for(int i=n1-1,count=0;i>=0;i--,count++)
    {
        vector<int> each;
        int carry=0;
        for(int k=0;k<count;k++)
        {
            each.insert(each.begin(),0);
        }
        for(int j=n2-1;j>=0;j--)
        {
            int sum=carry+s.digits[j]*f.digits[i];
            carry=sum/10;
            sum%=10;
            each.insert(each.begin(),sum);
        }
        if(carry!=0)
            each.insert(each.begin(),carry);

        int resp=n1+n2-1,eachp=each.size()-1;
        carry=0;
        while(resp>=0 || eachp>=0)
        {
            int a=resp>=0?res[resp]:0;
            int b=eachp>=0?each[eachp]:0;
            int sum=a+carry+b;
            carry=sum/10;
            sum%=10;
            res[resp]=sum;
            resp--;
            eachp--;
        }
    }

    BigInt ans(res);
    if(negResult)
        ans.positive=false;
    return ans;
}

bool operator!(const BigInt &f)
{
    return f.digits[0] != 0;
}

bool operator==(const BigInt& f,const BigInt& s)
{
    if(f.positive && !s.positive)
        return false;
    else if(!f.positive && s.positive)
        return false;
    else
    {
        int n1=f.digits.size()-1;
        int n2=s.digits.size()-1;
        if(n1!=n2)
            return false;
        while(n1>=0 && n2>=0)
        {
            if(f.digits[n1]!=s.digits[n2])
                return false;
            n1--;
            n2--;
        }
        return true;
    }
}

bool operator>(const BigInt& f,const BigInt& s)
{
    if(f.positive && !s.positive)
        return true;
    else if(!f.positive && s.positive)
        return false;
    else if(f.positive && s.positive)
    {
        int n1=f.digits.size()-1;
        int n2=s.digits.size()-1;
        if(n2>n1)
            return false;
        else if(n1>n2)
            return true;
        else{
            int i=0,j=0;
            while(i<=n1 && j<=n2)
            {
                if(f.digits[i]>s.digits[j])
                    return true;
                else if(f.digits[i]<s.digits[j])
                    return false;
                i++;
                j++;
            }
            return false;
        }
    }
    else
    {
        int n1=f.digits.size()-1;
        int n2=s.digits.size()-1;
        if(n2>n1)
            return true;
        else if(n1>n2)
            return false;
        else{
            int i=0,j=0;
            while(i<=n1 && j<=n2)
            {
                if(f.digits[i]>s.digits[j])
                    return false;
                else if(f.digits[i]<s.digits[j])
                    return true;
                i++;
                j++;
            }
            return false;
        }
    }
}


bool operator>=(const BigInt& f,const BigInt& s)
{
    return ((f==s) || (f>s));
}

bool operator<(const BigInt& f,const BigInt& s)
{
    return s>f;
}

bool operator<=(const BigInt& f,const BigInt& s)
{
    return ((f==s) || (s>f));
}

BigInt operator++(BigInt& f)
{
    vector<int> one={1};
    BigInt add_one(one);
    f=f+add_one;
    return f;
}

BigInt operator--(BigInt& f)
{
    vector<int> one={1};
    BigInt sub_one(one);
    f=f-sub_one;
    return f;
}

BigInt operator++(BigInt& f,int num)
{
    const BigInt temp=f;
    ++f;
    return temp;
}

BigInt operator--(BigInt& f,int num)
{
    const BigInt temp=f;
    --f;
    return temp;
}

ostream& operator<<( ostream& output, const BigInt &first )
{
    output<<"Number is positive(1)/negative(0)="<<first.positive<<" :";
    for(const int& digit:first.digits)
    {
        output<<digit;
    }
    output<<endl;
    return output;
}

istream& operator>>( istream& input, BigInt &first )
{
    cout<<"Enter the number"<<endl;
    char ch;
    vector<char> input_digits;
    while(!input.eof())
    {
        ch=input.get();
        if(ch==' '||ch=='\n'||ch=='\t')
            break;
        input_digits.push_back(ch);
    }
    first=BigInt(input_digits);
    return input;
}





