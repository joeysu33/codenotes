/*!
  刽子手游戏，刽子手游戏是一款猜单词游戏，
  游戏规则：
  计算机假象一个单词让你猜，你每次可以猜一个字母，如果单词里面有那个字母
  则所有该字母的单词都显示，如果没有刽子手会在一副刽子手图上填上一笔。这幅
  画需要7笔才能完成，因此最多只能错6次,猜一个已经出现的字母也算出错
  编写一个裁判程序，输入单词和玩家的猜测，判断玩家赢了、输了、还是放弃了，
  You win.
  You lose.
  You chickend out.
  每组数据包含3行，
  第1行是游戏编号（-1表示结束标记），
  第2行是计算机想的单词，
  第3行是玩家的猜测

  根据题意
  1.不区分单词的顺序
  2.相同单词一个和多个的意思相同（计算机假象的单词)
  3.只有6次机会
  4.因为猜一个已经出现的字母也算出错，所以不合适用set
*/
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

struct Input {
    int m_no;
    string m_predict;
    string m_real;
};

void showAnswer(int n, int result) {
    const char *s ;
    if(result == 0) {
        s = "You win.";
    } else if(result == 1) {
        s = "You chickend out.";
    } else {
        s = "You lose.";
    }
    printf("Round %d\n%s\n", n, s);
}

void game(const Input & i) {
    int *record = new int[i.m_predict.size()];
    memset(record, 0, i.m_predict.size() * sizeof(int));
    int chance = 0;
    bool cont ,succ;
    bool ok;
    for(const char *x = i.m_real.data(), *x0 = x; *x; ++x) {
        cont = false;
        for(const char *x1 = x0; x1 < x; ++x1) {
            if(*x1 == *x) {chance++; cont = true; break;}
        }
        if(chance == 6) break;
        if(cont) continue;

        succ = false;
        ok = true;
        for(int y = 0, z = i.m_predict.size(); y < z ; ++y) {
            if(record[y]) continue;
            if(*x == i.m_predict[y])
            {
                record[y]=1;
                succ = true;
            } else
                ok = false;
        }
        if(ok) break;
        if(!succ) {
            ++chance; if(chance==6) break;
        }
    }

    delete []record;
    if(chance >= 6)
        showAnswer(i.m_no, 2);
    else if(ok)
        showAnswer(i.m_no, 0);
    else
        showAnswer(i.m_no, 1);
}

int main()
{
    Input i;
    vector<Input> is;
    do {
       cin >> i.m_no;
       if(i.m_no < 0) break;

       cin >> i.m_predict;
       cin >> i.m_real;

       is.push_back(i);
    } while(true);

    for(unsigned j=0; j<is.size(); ++j) {
        game(is[j]);
    }

    return 0;
}
