#include <iostream>

using namespace std;

//std::hex std::oct ...的实现机制
ostream& addX(ostream & os) {
    os << "X";
    return os;
}

ostream& addY(ostream & os) {
    os << "Y";
    return os;
}

istream& getX(istream &is, char &x) {
    is >> x;
    return is;
}

istream& getY(istream & is, char &y) {
    is >> y;
    return is;
}

istream& readChar(istream & is) {
    char c;
    is >> c;
    cout<<"c="<<c;
    return is;
}

int main()
{
    cout<<addX<<addY<<endl;
    cin >> readChar;
    return 0;
}
