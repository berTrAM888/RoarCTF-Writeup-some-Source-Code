#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

int countttt = 0;

int question[10][10]{};
int rowmark[10][10]{};
int colmark[10][10]{};
int blockmark[10][10]{};
int row[10]{}, col[10]{}, block[10]{};
clock_t start, finish;


class point
{
public:
    int r, c, n = 0;
    point() {};
    point(int _r, int _c, int _n = 0)
    {
        r = _r;
        c = _c;
        n = _n;
    }
    point(const point& p)
    {
        r = p.r;
        c = p.c;
        n = p.n;
    }
};
vector<point>tofill;
bool judge(int r, int c, int n);
bool dfs(int);
void setmark(int r, int c, int n, bool flag);
inline int getblocknum(int r, int c);
void printboard();
void Clear();
bool checknum9(int ans[10]);
bool mycheck(int ans[10][10]);

int main(int argc, const char* argv[])
{
    start = clock();
    int count;
    for (int a1 = 0; a1 < 9; a1++)
    {
        for (int a2 = 0; a2 < 9; a2++)
        {
            for (int a3 = 0; a3 < 9; a3++)
            {
                for (int a4 = 0; a4 < 9; a4++)
                {
                    int smap[10][10] = 
                    {
                        {},
                        {0,0,0,3,0,7,9,6,1,0 },
                        {0,6,0,0,1,0,0,3,0,0 },
                        {0,0,1,0,3,4,6,0,0,8 },
                        {0,2,3,0,0,9,0,5,6,1 },
                        {0,9,6,1,0,0,0,7,0,3 },
                        {0,0,0,7,6,3,1,0,2,0 },
                        {0,0,4,0,0,1,3,0,0,6 },
                        {0,3,0,0,5,6,0,1,0,0 },
                        {0,1,0,6,0,2,8,0,3,0 },
                    };
                    smap[5 + 1][1 + 1] = a1;
                    smap[2 + 1][7 + 1] = a2;
                    smap[8 + 1][6 + 1] = a3;
                    smap[6 + 1][2 + 1] = a4;
                    memcpy(question, smap, sizeof(smap));
                    {
                        for (int r = 1; r < 10; r++)//from 1 to 9
                        {
                            for (int c = 1; c < 10; c++)//from 1 to 9
                            {
                                if (question[r][c] == 0)
                                {
                                    tofill.push_back(point(r, c));
                                }
                                else
                                {
                                    setmark(r, c, question[r][c], 1);
                                    row[r]++;
                                    col[c]++;
                                    block[getblocknum(r, c)]++;
                                }
                            }
                        }
#if 1
                        for (int i = 0; i < tofill.size(); i++)
                        {
                            int r = tofill[i].r, c = tofill[i].c;
                            tofill[i].n = row[r] + col[c] + block[getblocknum(r, c)];
                        }
                        for (int i = 0; i < tofill.size(); i++)
                        {
                            int m = i;
                            for (int j = i; j < tofill.size() - 1; j++)
                            {

                                if (tofill[m].n < tofill[j + 1].n)
                                    m = j + 1;
                            }
                            swap(tofill[i], tofill[m]);
                        }
#endif
                        if (dfs(0))
                        {
                            if (!mycheck(question))
                            {
                                continue;
                            }
                            printboard();
                            countttt++;
                            cout << countttt << endl;
                            cout << a1 << " " << a2 << " " << a3 << " " << a4 << endl;
                        }
                        Clear();
                    }
                }
            }
        }
    }
    finish = clock();
    cout << (finish - start) << endl;
    return 0;

}
void setmark(int r, int c, int n, bool flag)
{
    rowmark[r][n] = flag;
    colmark[c][n] = flag;
    blockmark[getblocknum(r, c)][n] = flag;
}

inline int getblocknum(int r, int c)
{
    return ((r - 1) / 3) * 3 + ((c - 1) / 3);
}

bool judge(int r, int c, int n)
{
    return !rowmark[r][n] && !colmark[c][n] && !blockmark[getblocknum(r, c)][n];
}

void printboard()
{
    for (int r = 1; r < 10; r++)//from 1 to 9
    {
        for (int c = 1; c < 10; c++)//from 1 to 9
        {
            cout << question[r][c];
        }
        cout << endl;
    }
}
void Clear()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            rowmark[i][j] = 0;
            colmark[i][j] = 0;
            blockmark[i][j] = 0;
            question[i][j] = 0;
        }
        row[i] = 0;
        col[i] = 0;
        block[i] = 0;
    }
    tofill.clear();
    vector<point>().swap(tofill);
}

bool dfs(int step)
{
    if (step == tofill.size())
    {
        return true;
    }
#if 0
    int reverse = (int)tofill.size() - step - 1;
    int r = tofill[reverse].r, c = tofill[reverse].c;
#else
    int r = tofill[step].r, c = tofill[step].c;
#endif
    for (int i = 1; i < 10; i++)
    {
        if (judge(r, c, i))
        {
            question[r][c] = i;
            setmark(r, c, question[r][c], 1);
            if (dfs(step + 1))return true;
            setmark(r, c, question[r][c], 0);
            question[r][c] = 0;
        }
    }
    return false;
}


bool checknum9(int ans[10])
{
    int visited[10];
    for (int i = 0; i < 10; i++)
    {
        visited[i] = 0;
    }
    for (int i = 1; i < 10; i++)
    {
        if (1 <= ans[i] && ans[i] <= 9)
        {
            visited[ans[i]]++;
        }
        else
        {
            return false;
        }
    }
    for (int i = 1; i <= 9; i++)
    {
        if (visited[i] != 1)
        {
            return false;
        }
    }
    return true;
}

bool mycheck(int ans[10][10])
{
    for (int raw = 1; raw < 10; raw++)
    {
        int line[10];
        for (int i = 1; i < 10; i++)
        {
            line[i] = ans[raw][i];

        }if (!checknum9(line))
        {
            return false;
        }
    }

    for (int col = 1; col < 10; col++)
    {
        int line[10];
        for (int i = 1; i < 10; i++)
        {
            line[i] = ans[i][col];
        }
        if (!checknum9(line))
        {
            return false;
        }
    }
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            int block[10];
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    block[i * 3 + j + 1] = ans[x * 3 + i + 1][y * 3 + j + 1];
                }
            }
            if (!checknum9(block))
            {
                return false;
            }
        }
    }

    return true;
}
