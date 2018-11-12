#include <iostream>
#include <fstream>

using namespace std;

int 
main(int argc, char *argv[]) {
    if(argc != 3) return 0;

    ifstream ifs;
    ofstream ofs;

    ifs.open(argv[1], ios::binary);
    ofs.open(argv[2], ios::binary | ios::trunc);

    if(!ifs) return 1;
    if(!ofs) return 2;

    //wrong usage,超出文件之后才会设置上EOF的标志位，所以会导致
    //ofs.put(ifs.get())多执行一次
    //while(!ifs.eof()) {
    //    ofs.put(ifs.get());
    //}

    char c;
    while(ifs.get(c)) {
        ofs.put(c);
    }

    ifs.close();
    ofs.close();

    return 0;
}
