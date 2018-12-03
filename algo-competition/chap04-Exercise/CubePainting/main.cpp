/*
 骰子填色，输入两个骰子，判断两个骰子是否等价。每个骰子用6个字母表示
 🎲
 骰子的上方是1，正前方是2，自上而下观察，顺时针方向分别是3,5,4,下方是6
 即1-6 2-5 3-4
 例如用rbgggr和rggbgr分别表示两个骰子。通过沿着垂直方向90度旋转，二者是
 等价的。

 确定骰子能支持的操作，沿着垂直或者水平方向进行旋转,且旋转的次数不会超过3次。

 解法1
 因为骰子的顶部是可以任意的，也即是无序的，将两个骰子都化简为：有序的，如果相等
 则说明两个一定相等,不改变相对位置，仅通过旋转来进行排序。

 解法2
 旋转骰子得到所有的解6*4=24种，判断是否相等
*/
#include <iostream>
#include <vector>
#include <cstdio>
#include <utility>
#include <stdexcept>

using namespace std;

#define N 6
#define FACE 4

////0x1000作为判断是水平/垂直,最后一个字节表示step,因为step<6
//#define FLAG 0x100

//static int tbl[N][N];

void shiftN(vector<int*> &arr, int count) {
    if(arr.size() < 1 || count == 0) return ;

    if(count > 0) {
        count %= FACE;
        //认为顺时针是正数
        for(int i=0, j=arr.size()-1; i<count; ++i) {
            int tmp = *arr[j];
            for(int k=j-1; k>=0; --k) {
                *arr[k+1] = *arr[k];
            }
            *arr[0]=tmp;
        }
    } else {
        count = -count;
        count %= FACE;
        //认为逆时针是正数
        for(int i=0, j=0; i<count; ++i) {
            int tmp=*arr[j];
            for(int k=1; k<arr.size(); ++k) {
                *arr[k-1] = *arr[k];
            }
            *arr[arr.size()-1]=tmp;
        }
    }
}

//从上至下看<1-6为轴>
void rotateX(int *cube, int step) {
    vector<int*> vec;
    vec.push_back(&cube[1]);
    vec.push_back(&cube[2]);
    vec.push_back(&cube[4]);
    vec.push_back(&cube[3]);
    shiftN(vec, step);
}

//从左至右看<3-4为轴>
void rotateY(int *cube, int step) {
    vector<int*> vec;
    vec.push_back(&cube[0]);
    vec.push_back(&cube[1]);
    vec.push_back(&cube[5]);
    vec.push_back(&cube[4]);
    shiftN(vec, step);
}

//从前至后看<2-5为轴>
void rotateZ(int *cube, int step) {
    vector<int*> vec;
    vec.push_back(&cube[0]);
    vec.push_back(&cube[3]);
    vec.push_back(&cube[5]);
    vec.push_back(&cube[2]);
    shiftN(vec, step);
}


//将i位置的移动到j位置,i和j表示索引
void rotate(int *cube, int i, int j) {
    if(i < 0 || i>=N) return ;
    if(j < 0 || j>=N) return ;
    bool revert=1;
    if(i > j) {
        int t = i;
        i = j;
        j = t;
        revert=-1;
    }
    switch(i) {
    case 0: {
        switch(j) {
        case 1: return rotateY(cube, 1 *revert);
        case 2: return rotateZ(cube, -1*revert);
        case 3: return rotateZ(cube, 1*revert);
        case 4: return rotateY(cube, -1*revert);
        case 5: return rotateY(cube, 2*revert);
        }
        break;
    }
    case 1: {
        switch (j) {
        case 2: return rotateX(cube, 1*revert);
        case 3: return rotateX(cube, -1*revert);
        case 4: return rotateY(cube, 2*revert);
        case 5: return rotateY(cube, 1*revert);
        }
        break;
    }
    case 2: {
        switch(j) {
        case 3: return rotateX(cube, 2*revert);
        case 4: return rotateX(cube, 1*revert);
        case 5: return rotateZ(cube, -1*revert);
        }
    }
    case 3: {
        switch (j) {
        case 4: return rotateX(cube, -1*revert);
        case 5: return rotateZ(cube, 1 *revert);
        }
    }
    case 4: {
        switch(j) {
        case 5: return rotateY(cube, -1 *revert);
        }
    }
    }
}

void showCube(int *cube) {
    for(int i=0; i<N; ++i) {
        printf("%d", cube[i]);
    }
    printf("\n");
    fflush(stdout);
}

void showCharCube(int *cube) {
    for(int i=0; i<N; ++i) {
        printf("%c", cube[i]);
    }
    printf("\n");
    fflush(stdout);
}

//这方方法存在问题，如果存在多个相同元素，则存在问题----
//对cube的排序，仅对位置1和位置2进行，因为位置1和位置2就确定了cube
void sortCube(int *cube) {
    //确定位置1
    int min=0;
    for(int i=1; i<N; ++i) {
        if(cube[i] < cube[min]) {
            min = i;
        }
    }
    if(min != 0) {
        rotate(cube,0, min);
    }

    //确定位置2，可能存在多种?
}

void cmpCube(int *ca, int *cb) {

}

//void makeRotateTable() {
//    tbl[0][1] = FLAG & 1;
//    tbl[0][2] =
//}

int main()
{
//    int cb1[N] ,cb2[N];
//    for(int i=0; i<N; ++i) cb1[i]=i+1;

//    for(int i=0; i<N-1; ++i) {
//        for(int j=i+1;j<N; ++j) {
//            memcpy(cb2, cb1, sizeof(cb1));
//            rotate(cb2,i, j);
//            showCube(cb2);
//        }
//    }

    bool matche = false;
//    int cube1[N] = {'r','b','g','g','g','r'}, cube2[N] = {'r','g', 'g', 'b', 'g', 'r'};
    int cube1[N] = {'1','2','3','4','5','6'}, cube2[N] = {'3','2', '6', '1', '5', '4'};
    //便利cube中的所有种类
    for(int i=0; i<N; ++i) { //1位置的骰子
        //水平方向旋转
        int cube[N];
        memcpy(cube, cube1, sizeof(cube1));
        rotate(cube, i, 0);

        for(int j=0; j<4; ++j) {
            int tmp[N];
            memcpy(tmp, cube, sizeof(cube));
            rotateX(tmp, j);
            showCharCube(tmp);

            if(!memcmp(tmp, cube2, sizeof(cube2))) {
                matche = true;
                break;
            }
        }

        if(matche) break;
    }

    printf("%s\n", matche?"YES":"NO");

    return 0;
}
