#include <string>
#define M 10000

using namespace std;

class Big_Integer
{
    string number;
    bool sign;
public:
    Big_Integer();
    Big_Integer(string s);
    Big_Integer(string s, bool sign);
    Big_Integer(int n);
    void set_number(string s);
    const string& get_number();
    void set_sign(bool s);
    const bool& get_sign();
    Big_Integer absolute();


    void operator=(Big_Integer b);
    bool operator==(Big_Integer b);
    bool operator!=(Big_Integer b);
    bool operator>(Big_Integer b);
    bool operator<(Big_Integer b);
    bool operator>=(Big_Integer b);
    bool operator<=(Big_Integer b);

    Big_Integer& operator++();
    Big_Integer operator++(int);
    Big_Integer& operator--();
    Big_Integer operator--(int);
    Big_Integer operator+(Big_Integer b);
    Big_Integer operator-(Big_Integer b);
    Big_Integer operator*(Big_Integer b);
    Big_Integer operator/(Big_Integer b);
    Big_Integer operator%(Big_Integer b);
    Big_Integer& operator+=(Big_Integer b);
    Big_Integer& operator-=(Big_Integer b);
    Big_Integer& operator*=(Big_Integer b);
    Big_Integer& operator/=(Big_Integer b);
    Big_Integer& operator%=(Big_Integer b);
    Big_Integer& operator[](int position);
    Big_Integer operator-();
    operator string();
private:
    bool equals(Big_Integer n1, Big_Integer n2);
    bool less(Big_Integer n1, Big_Integer n2);
    bool greater(Big_Integer n1, Big_Integer n2);
    string add(string num1, string num2);
    string subtract(string num1, string num2);
    string multiply(string num1, string num2);
    pair<string, long long> divide(string num, long long den);
    long long toInt(string s);
    string toString(long long n);
};