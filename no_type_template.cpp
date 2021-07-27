#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename T, T val = T{}>
T addVal(T rhs)
{
    return rhs + val;
}

template <char const *T>
struct P
{
    P()
    {
        cout << T << endl;
    }
};

template <int I, bool B>
void pt()
{
    cout << I << " " << B << endl;
}

template <decltype(auto) N>
class C
{
public:
    void change()
    {
        cout<<N<<endl;
    }
};

char const s[] = "123";
int main()
{
    int i = 5;
    C<(i)>a;
    a.change();
    // cout << i << endl;
}