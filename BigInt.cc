
//Student Name: Sarthak Jain
// Student ID: 014508013
// GID: 22 (Twenty Two)

/*
 *    Things left to do
 *
 * 1. Output of BigInt. Negative positive number representation with first dig sign '-' in case of negative.
 * 2. Remove of non-parameterised constructor and destructor
 * 3. Sanity Check
 * 4. need to remove cerr
 */

#include "BigInt.h"

BigInt::BigInt()
{
    positive=true;
}

BigInt::BigInt(const vector<int>& init_dig) {
    positive=true;
    int start=0;

    //leading zeros results to invalid input
    if(init_dig.size()>1 && init_dig[0]==0)
    {
        cerr<<"Please enter a valid number with no leading zeros"<<endl;
        exit(0);
    }

    if(init_dig[start]<0){
        positive=false;
        if(init_dig[start]<-9)
        {
            cerr << "Please enter a valid number. Only single digits are allowed" << endl;
            exit(0);
        }
        digits.push_back(-1*init_dig[start]);
        start++;
    }

   for(int i=start;i<init_dig.size();i++) {
       if (init_dig[i] < 0 && i != 0) {
           cerr << "Please enter a valid number. Negative number should only be as first element of vector" << endl;
           exit(0);
       } else if (init_dig[i] >= 10) {
           cerr << "Please provide each digit as a separate integer." << endl;
           exit(0);
       }
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
    if(start==init_char.size())
    {
        cerr<<"Enter a valid number with some digits"<<endl;
        exit(0);
    }

    if(start==0 && init_char[start]=='0' && init_char.size()>1)
    {
        cerr<<"Please enter input without leading zeros"<<endl;
        exit(0);
    }
    else if(start==1 && init_char[start]=='0')
    {
        cerr<<"Zero given with positive/negative symbol"<<endl;
        exit(0);
    }

    for(int i=start;i<init_char.size();i++)
    {
        if(!(init_char[i]>='0' && init_char[i]<='9'))
        {
            cerr<<"Enter a valid number with characters between 0 & 9 inclusive"<<endl;
            exit(0);
        }
        digits.push_back(init_char[i]-'0');
    }
    if(digits.empty())
    {
        cerr<<"Enter atleast one digit"<<endl;
        exit(0);
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
    if(start==n)
    {
        cerr<<"Enter a valid number with some digits"<<endl;
        exit(0);
    }
    if(start==0 && init_char[start]=='0' && n>1)
    {
        cerr<<"Please enter input without leading zeros"<<endl;
        exit(0);
    }
    else if(start==1 && init_char[start]=='0')
    {
        cerr<<"Zero given with positive/negative symbol"<<endl;
        exit(0);
    }

    for(int i=start;i<n;i++)
    {
        if(!(init_char[i]>='0' && init_char[i]<='9'))
        {
            cerr<<"Enter a valid number with characters between 0 & 9 inclusive"<<endl;
            exit(0);
        }
        digits.push_back(init_char[i]-'0');
    }
    if(digits.empty())
    {
        cerr<<"Enter atleast one digit"<<endl;
        exit(0);
    }

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

    for(int i=0;i<res.size() && res[0]==0;i++)
    {
        res.erase(res.begin());
    }
    if(res.size()==0)
        res.push_back(0);

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

    for(int i=0;i<res.size() && res[0]==0;i++)
    {
        res.erase(res.begin());
    }
    if(res.size()==0)
        res.push_back(0);
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

    for(int i=0;i<res.size() && res[0]==0;i++)
    {
        res.erase(res.begin());
    }
    if(res.size()==0)
        res.push_back(0);
    BigInt ans(res);
    if(negResult)
        ans.positive=false;
    return ans;
}

/*
 * ! (NOT) operator should return true if the value of BigInt is Zero (0). Since 0 is considered false, and thus ! of false is true
 * It will return false otherwise if the value of BigInt is non zero. Since non-zero is true and thus ! (NOT) of non-zero is false;
 */
bool operator!(const BigInt &f)
{
    return f.digits[0] == 0;
}

bool operator==(const BigInt& f,const BigInt& s)
{
    if(f.positive != s.positive)
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
    int i=0;
    if(!first.positive)
    {
        output<<(-1*first.digits[i]);
        i++;
    }
    for(;i<first.digits.size();i++)
    {
        output<<(first.digits[i]);
    }
    return output;
}

istream& operator>>( istream& input, BigInt &first )
{
    cout<<"Enter the number"<<endl;
    char ch;
    vector<char> input_digits;
    ch=input.get();
    if(ch!='-' && ch!='+' && !(ch>='0' && ch<='9'))
    {
        cerr<<"Please enter a valid number"<<endl;
        return input;
    }
    input_digits.push_back(ch);
    while(!input.eof())
    {
        ch=input.get();
        if(ch=='\n')
            break;
        if(!(ch>='0' && ch<='9'))
        {
            cerr<<"Please enter a valid number"<<endl;
            return input;
        }
        input_digits.push_back(ch);
    }
    if(input_digits.size()==0)
    {
        cerr<<"Please enter a valid number"<<endl;
        return input;
    }
    first=BigInt(input_digits);
    cout<<first;
    return input;
}





