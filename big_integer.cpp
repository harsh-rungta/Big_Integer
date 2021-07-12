#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "Big_Integer.h"
#define MAX 10000 // for strings

Big_Integer::Big_Integer()
{
    number = "0";
    sign = false;
}

Big_Integer::Big_Integer(string s)
{
    if(isdigit(s[0]))
    {
        set_number(s);
        sign = false;
    }
    else
    {
        set_number(s.substr(1));
        sign = (s[0] == '-');
    }
}

Big_Integer::Big_Integer(int n)
{
    stringstream ss;
	string s;
	ss << n;
	ss >> s;


	if( isdigit(s[0]) ) // if not signed
	{
		set_number( s );
		set_sign( false ); // +ve
	}
	else
	{
		set_number( s.substr(1) );
		set_sign( s[0] == '-' );
	}
}

void Big_Integer::set_number(string s)
{
    number = s;
}

const string& Big_Integer::get_number()
{
    return number;
}

void Big_Integer::set_sign(bool s)
{
    sign = s;
}

const bool& Big_Integer::get_sign()
{
    return sign;
}

Big_Integer Big_Integer::absolute()
{
    return Big_Integer(get_number());
}

void Big_Integer::operator=(Big_Integer b)
{
    set_number(b.get_number());
    set_sign(b.get_sign());
}

bool Big_Integer::operator==(Big_Integer b)
{
    return equals((*this), b);
}

bool Big_Integer::operator!=(Big_Integer b)
{
    return !equals((*this), b);
}

bool Big_Integer::operator>(Big_Integer b)
{
    return greater((*this), b);
}

bool Big_Integer::operator<(Big_Integer b)
{
    return less((*this), b);
}

bool Big_Integer::operator>=(Big_Integer b)
{
    return equals((*this), b)||greater((*this), b);
}

bool Big_Integer::operator<=(Big_Integer b)
{
    return equals((*this), b)||less((*this), b);
}

Big_Integer& Big_Integer::operator++()
{
    (*this) = (*this)+1;
    return (*this);
}

Big_Integer Big_Integer::operator++(int)
{
    Big_Integer temp = (*this);
    (*this) = (*this)+1;
    return temp;
}

Big_Integer& Big_Integer::operator--()
{
    (*this) = (*this)-1;
    return (*this);
}

Big_Integer Big_Integer::operator--(int)
{
    Big_Integer temp = (*this);
    (*this) = (*this)-1;
    return temp;
}

Big_Integer Big_Integer::operator+(Big_Integer b)
{
    Big_Integer res;
    if(get_sign() == b.get_sign())
    {
        res.set_number(add(get_number(), b.get_number()));
        res.set_sign(get_sign());
    }
    else
    {
        if(absolute()>b.absolute())
        {
            res.set_number(subtract(get_number(), b.get_number()));
            res.set_sign(get_sign());
        }
        else
        {
            res.set_number(subtract(b.get_number(), get_number()));
            res.set_sign(b.get_sign());
        }
    }
    if(res.get_number()=="0") res.set_sign(false);
    return res;
}

Big_Integer Big_Integer::operator-(Big_Integer b)
{
    b.set_sign(!b.get_sign());
    return (*this)+b;
}

Big_Integer Big_Integer::operator*(Big_Integer b)
{
    Big_Integer res;
    res.set_number(multiply(get_number(), b.get_number()));
    res.set_sign(get_sign()!=b.get_sign());
    if(res.get_number()=="0")
        res.set_sign(false);
    return res;
}

Big_Integer Big_Integer::operator/(Big_Integer b)
{
    long long den = toInt(b.get_number());
    Big_Integer div;
    div.set_number( divide(get_number(), den).first );
	div.set_sign( get_sign() != b.get_sign() );

	if(div.get_number() == "0")
		div.set_sign(false);

	return div;
}

Big_Integer Big_Integer::operator%(Big_Integer b)
{
	long long den = toInt( b.get_number() );

	Big_Integer rem;
	long long rem_int = divide(number, den).second;
	rem.set_number( toString(rem_int) );
	rem.set_sign( get_sign() != b.get_sign() );

	if(rem.get_number() == "0") // avoid (-0) problem
		rem.set_sign(false);

	return rem;
}

Big_Integer& Big_Integer::operator+=(Big_Integer b)
{
    (*this) = (*this)+b;
    return (*this);
}

Big_Integer& Big_Integer::operator-=(Big_Integer b)
{
    (*this) = (*this)-b;
    return (*this);
}

Big_Integer& Big_Integer::operator*=(Big_Integer b)
{
    (*this) = (*this)*b;
    return (*this);
}

Big_Integer& Big_Integer::operator/=(Big_Integer b)
{
    (*this) = (*this)/b;
    return (*this);
}

Big_Integer& Big_Integer::operator%=(Big_Integer b)
{
    (*this) = (*this)%b;
    return (*this);
}

Big_Integer& Big_Integer::operator[](int position)
{
	return *(this + (position*sizeof(Big_Integer)));
}

Big_Integer Big_Integer::operator -() // unary minus sign
{
	return (*this) * -1;
}

Big_Integer::operator string()
{
	string signedString = ( get_sign() ) ? "-" : "";
	signedString += number;
	return signedString;
}

bool Big_Integer::equals(Big_Integer n1, Big_Integer n2)
{
	return n1.get_number() == n2.get_number()
		&& n1.get_sign() == n2.get_sign();
}

bool Big_Integer::less(Big_Integer n1, Big_Integer n2)
{
	bool sign1 = n1.get_sign();
	bool sign2 = n2.get_sign();

	if(sign1 && ! sign2) // if n1 is -ve and n2 is +ve
		return true;

	else if(! sign1 && sign2)
		return false;

	else if(! sign1)
	{
		if(n1.get_number().length() < n2.get_number().length() )
			return true;
		if(n1.get_number().length() > n2.get_number().length() )
			return false;
		return n1.get_number() < n2.get_number();
	}
	else
	{
		if(n1.get_number().length() > n2.get_number().length())
			return true;
		if(n1.get_number().length() < n2.get_number().length())
			return false;
		return n1.get_number().compare( n2.get_number() ) > 0; // greater with -ve sign is LESS
	}
}

bool Big_Integer::greater(Big_Integer n1, Big_Integer n2)
{
	return ! equals(n1, n2) && ! less(n1, n2);
}


string Big_Integer::add(string number1, string number2)
{
	string add = (number1.length() > number2.length()) ?  number1 : number2;
	char carry = '0';
	int differenceInLength = abs( (int) (number1.size() - number2.size()) );

	if(number1.size() > number2.size())
		number2.insert(0, differenceInLength, '0'); // put zeros from left

	else// if(number1.size() < number2.size())
		number1.insert(0, differenceInLength, '0');

	for(int i=number1.size()-1; i>=0; --i)
	{
		add[i] = ((carry-'0')+(number1[i]-'0')+(number2[i]-'0')) + '0';

		if(i != 0)
		{
			if(add[i] > '9')
			{
				add[i] -= 10;
				carry = '1';
			}
			else
				carry = '0';
		}
	}
	if(add[0] > '9')
	{
		add[0]-= 10;
		add.insert(0,1,'1');
	}
	return add;
}


string Big_Integer::subtract(string number1, string number2)
{
	string sub = (number1.length()>number2.length())? number1 : number2;
	int differenceInLength = abs( (int)(number1.size() - number2.size()) );

	if(number1.size() > number2.size())
		number2.insert(0, differenceInLength, '0');

	else
		number1.insert(0, differenceInLength, '0');

	for(int i=number1.length()-1; i>=0; --i)
	{
		if(number1[i] < number2[i])
		{
			number1[i] += 10;
			number1[i-1]--;
		}
		sub[i] = ((number1[i]-'0')-(number2[i]-'0')) + '0';
	}

	while(sub[0]=='0' && sub.length()!=1) // erase leading zeros
		sub.erase(0,1);

	return sub;
}


string Big_Integer::multiply(string n1, string n2)
{
	if(n1.length() > n2.length())
		n1.swap(n2);

	string res = "0";
	for(int i=n1.length()-1; i>=0; --i)
	{
		string temp = n2;
		int currentDigit = n1[i]-'0';
		int carry = 0;

		for(int j=temp.length()-1; j>=0; --j)
		{
			temp[j] = ((temp[j]-'0') * currentDigit) + carry;

			if(temp[j] > 9)
			{
				carry = (temp[j]/10);
				temp[j] -= (carry*10);
			}
			else
				carry = 0;

			temp[j] += '0'; // back to string mood
		}

		if(carry > 0)
			temp.insert(0, 1, (carry+'0'));

		temp.append((n1.length()-i-1), '0'); // as like mult by 10, 100, 1000, 10000 and so on

		res = add(res, temp); // O(n)
	}

	while(res[0] == '0' && res.length()!=1) // erase leading zeros
		res.erase(0,1);

	return res;
}

//-------------------------------------------------------------
// divides string on long long, returns pair(qutiont, remainder)
pair<string, long long> Big_Integer::divide(string n, long long den)
{
	long long rem = 0;
	string result; result.resize(MAX);

	for(int indx=0, len = n.length(); indx<len; ++indx)
	{
		rem = (rem * 10) + (n[indx] - '0');
		result[indx] = rem / den + '0';
		rem %= den;
	}
	result.resize( n.length() );

	while( result[0] == '0' && result.length() != 1)
		result.erase(0,1);

	if(result.length() == 0)
		result = "0";

	return make_pair(result, rem);
}

//-------------------------------------------------------------
// converts long long to string
string Big_Integer::toString(long long n)
{
	stringstream ss;
	string temp;

	ss << n;
	ss >> temp;

	return temp;
}

//-------------------------------------------------------------
// converts string to long long
long long Big_Integer::toInt(string s)
{
	long long sum = 0;

	for(int i=0; i<s.length(); i++)
		sum = (sum*10) + (s[i] - '0');

	return sum;
}

#endif
