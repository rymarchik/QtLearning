#include <iostream>

using namespace std;

void bug() {
    int i = 5;
    int* in = &i;
    delete in;
}

int main()
{
    bug();
//    cout << "Hello World!" << endl;
    return 0;
}
