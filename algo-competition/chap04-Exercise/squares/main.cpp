/*!
  有n行n列(2<<n<<9)的小黑点，还有m条线段连接其中的一些黑点。统计这些线段连成了多少个正方形
  行从上到下是1-n，列从左到右是1-n。边用Hij和Vij表示，分别代表(i,j)-(i,j+1)和(i,j)-(i+1,j)。
  @---@   @---@
  |   |       |
  @---@---@---@
      |   |   |
  @   @---@   @
      |       |
  @   @---@---@

  图中示例包含两个边长为1的正方形和1个边长为2的正方形
*/
#include <iostream>
#include <memory>

using namespace std;

#define N 20

static int edges[N][N];
static int ndim;

enum LinkState {
    LS_N = 0x0,
    LS_H = 0x1,
    LS_V = 0x2,
};

bool isHorizonLink(int i, int j, int len) {
    for(int k=0; k<len; ++k) {
        if(!(edges[i][j+k] & LS_H)) return false;
    }
    return true;
}

bool isVerticalLink(int i, int j, int len) {
    for(int k=0; k<len; ++k) {
        if(!(edges[i+k][j] & LS_V)) return false;
    }
    return true;
}

bool isSquare(int i, int j, int len) {
    if(!isHorizonLink(i, j, len)) return false;
    if(!isHorizonLink(i+len, j, len)) return false;
    if(!isVerticalLink(i, j, len)) return false;
    if(!isVerticalLink(i, j+len, len)) return false;
    printf("(%d,%d,%d)\n",i,j,len);
    return true;
}

int searchSquare(int len) {
    int cnt = 0;
    for(int i=0; i<ndim-len; ++i) {
        for(int j=0; j<ndim-len; ++j) {
            if(!isSquare(i, j, len)) continue;
            cnt++;
        }
    }
    return cnt;
}

void allSquares() {
    //这里可以进行优化，如果边长为1的正方形不成立，则变成为1以上的正方形肯定也不成立
    //可以直接忽略这些点
    for(int i=1, j=0; i<ndim; ++i) {
        j = searchSquare(i);
        if(!j) continue;
        printf("边长是%d的正方形有:%d个\n", i, j);
    }
    fflush(stdout);
}

int main()
{
    char line[1024];
    ndim=4;
    //cin>>ndim;
    if(ndim < 1) return 0;
    //cin.getline(line, 1024);
    const char *s = "H11 H13 V11 V12 V14 H21 H22 H23 V22 V23 V24 H32 V32 H33 V33 V34 H42 H43";
    strcpy(line,s);
    int st=0;
    memset(edges, 0 , sizeof(edges));
    for(const char* i = line; *i; ++i){
        if(*i == 'H') {
           st=1;
           continue;
        }else if(*i == 'V') {
            st=2;
            continue;
        }

        if(st && isdigit(*i)) {
            int x=*i-'0';
            int y=*(i+1)-'0';
            ++i;
            if(x > ndim || y > ndim) return 0;

            if(st==1) {
                edges[x-1][y-1] |= LS_H;
            } else {
                edges[x-1][y-1] |= LS_V;
            }
        } else {
            st = 0;
        }
    }
    allSquares();
    return 0;
}
