/*!
  有一个5*5的网格，其中恰好有一个格子是空的，其他格子各有一个字母。一共有4中指令
  A,B,L,R,分别表示上、下、左、右的相邻字母移到空格中。如果有非法指令，应输出
  "This puzzle has no final configuration.",
  初始网格
  T R G S J
  X D O K I
  M   V L N
  W P A B E
  U Q H C F
  例如ARRBBL0，0作为结束字符
*/
#include <iostream>

using namespace std;

#define N 5
#define MAX_LEN 1000

static char tbl[][N] = { {'T', 'R', 'G', 'S', 'J'},
                         {'X', 'D', 'O', 'K', 'I'},
                         {'M', ' ', 'V', 'L', 'N'},
                         {'W', 'P', 'A', 'B', 'E'},
                         {'U', 'Q', 'H', 'C', 'F'},
                       };

struct Position {
    bool isValid() const {
        if(m_x < 0 || m_x >=N) return false;
        if(m_y < 0 || m_y >=N) return false;
        return true;
    }
    int m_x, m_y;
};
static Position blank {2, 1};

char* cell(const Position & p) {
    if(!p.isValid()) return nullptr;
    return &tbl[p.m_x][p.m_y];
}

void _swap(char *a, char *b) {
    char c {*a};
    *a = *b;
    *b = c;
}

bool move(const char c) {
    if(!blank.isValid()) return false;

    Position pdest = blank;
    if(c == 'A') {
        pdest.m_x--;
    } else if(c == 'B') {
        pdest.m_x++;
    } else if(c == 'L') {
        pdest.m_y--;
    } else if(c == 'R') {
        pdest.m_y++;
    } else {
        return false;
    }

    if(!pdest.isValid()) return false;
    _swap(cell(blank), cell(pdest));
    blank = pdest;

    return true;
}

void showTable() {
    for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
            printf("%3c", tbl[i][j] != ' ' ? tbl[i][j] : '@');
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    char str[MAX_LEN];
    if(scanf("%s", str) != 1) return 0;
    char *s = &str[0];
    //char *s = "ARRBL0";
    showTable();
    while(*s && *s != '0') {
        if(!move(*s)) {
            printf("%s\n", "This puzzle has no final configuration.");
            return 0;
        }
        ++s;
    }
    showTable();
    return 0;
}
