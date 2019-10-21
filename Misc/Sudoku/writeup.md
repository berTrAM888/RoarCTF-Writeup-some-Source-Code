## 数独

### 解题思路

对游戏逻辑逆向后发现

* 游戏初始化时，根据内存中暴露的数组初始化游戏棋盘，有4个位置被随机化为0-9，这里暗示了爆破范围

* 游戏中每个格子的对应数值input[i, j]，每次鼠标点击格子都会触发如下检测

1. CheckSudoku(input); 这个是混淆的，检测当前的input如果满足本题数独条件，给出错误提示 F1@g_1$_N0t_h3re... QAQ"
2. cipher[i, j] = AesEncryptor_Base64(input[i, j].ToString(), key); 对input[i, j] 进行AES加密，密钥key的计算为
3. string key = "SudokuCSharp"; 以及 if (j > 0) key += cipher[i, j - 1];
4. strNum[i, j] = Xor(cipher[i, j], fix[i, j]); 是与固定字符串进行异或操作，Xor的两个参数首先要保证长度一样，否则返回"0"
5. int.TryParse(strNum[i, j], out nNum[i, j]); 将异或得到的字符串转为int，转换失败得到0
6. CheckSukudo(nNum) 检测转换后的数字是否是本题的数独，且符合数独达成的条件，如果满足，给出flag



由此，解题分为如下几步：

1. 确定内存中一开始暴露的数组是不是可解的，因为思路6需要最后转换出来的数独还是本题的数独，那么要是本题一开始随机化完的数独根本是不可解的，就说明运气很差没有被随机到可解的数独
2. 算出本题的4个随机位应该时什么值，这4个值应该保证本题一个可解的数独，这里需要跑一个程序爆破10 * 10 * 10 * 10种情况，找出正确的题目
3. 根据本题的数独情况解出数独，得到nNum[i, j]和strNum[i, j]
4. 解出cipher[i, j]，公式 cipher[i, j] = Xor(strNum[i, j], fix[i, j])
5. 倒推input[i, j]，需要根据自定义AES加密函数的逻辑倒推写解密脚本
6. 根据input计算flag

RoarCTF{wm-74953174BB}

#### exp1：从一万个数独题目中找出可解的数独并解出来

```C++
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

```

根据解数独结果发现，这一万种初始情况中只有1种可解，即四个摇摆位分别为

map[5, 1] = 5

map[2, 7] = 5

map[8, 4] = 4

map[6, 2] = 5

可解的数独题目为

```C++
int sudoku[9][9] =    
{
	{0,0,3,0,7,9,6,1,0 },
	{6,0,0,1,0,0,3,0,0 },
	{0,1,0,3,4,6,0,0,8 },
	{2,3,0,0,9,0,5,6,1 },
	{9,6,1,0,0,0,7,0,3 },
	{0,0,7,6,3,1,0,2,0 },
	{0,4,0,0,1,3,0,0,6 },
	{3,0,0,5,6,0,1,0,0 },
	{1,0,6,0,2,8,0,3,0 },
};
```



解也是唯一的

```C++
int answer[9][9] = 
{
    {5,8,3,2,7,9,6,1,4 },
	{6,9,4,1,8,5,3,7,2 },
	{7,1,2,3,4,6,9,5,8 },
	{2,3,8,4,9,7,5,6,1 },
	{9,6,1,8,5,2,7,4,3 },
	{4,5,7,6,3,1,8,2,9 },
	{8,4,5,7,1,3,2,9,6 },
	{3,2,9,5,6,4,1,8,7 },
	{1,7,6,9,2,8,4,3,5 }
};
```



然后就可以写脚本倒推本题flag了，脚本如下

### exp2：倒推解密

```C#
using System;
using System.Text;
using System.Security.Cryptography;

namespace SukudoExp
{
    class Exp
    {
        public static int[,] nNum = new int[9, 9]
        {
            {5,8,3,2,7,9,6,1,4 },
            {6,9,4,1,8,5,3,7,2 },
            {7,1,2,3,4,6,9,5,8 },
            {2,3,8,4,9,7,5,6,1 },
            {9,6,1,8,5,2,7,4,3 },
            {4,5,7,6,3,1,8,2,9 },
            {8,4,5,7,1,3,2,9,6 },
            {3,2,9,5,6,4,1,8,7 },
            {1,7,6,9,2,8,4,3,5 }
        };

        public static string[,] Fix = new string[9, 9]
        {
            { "5t80rGPofpW4sV2KyAIDwQkgguqEXcN+NY9uSyGHq/g8", "WED/hGuf4CWz9laB87dzJOKG7wRg0nEzXHz0tdYtzqo5", "rGhuSt+5fG+w10o3WYM4v9dFvVG+S5uKo1UC6ZBZEVI>", "fFV0J0+r5l1wPHCRE5DoCfu8q70oFCO2C3Jv254Lcdo?", "k8kPz8CXyRVhKTrP3UjS2hO14fZuammD78MpSGseiAI:", "mE+lMGj6vzdIVPEK9mn/FrDeTTLsSwUqwIcf7sXb92E4", "RpVjvSK3TxvyQyTTxu6lHmVBI25V3SP37Edz6B32sa8;", "nbb7KHu8RNf+vqy6zj4coVu7mmCU8RvosU/kL4moGAA<", "4D2+cn5/aGiJmORYwoXkSIL7ikaKQwL9rpbvl/ts7MU9", },
            { "y9EtzJXxTNJkbqSfKbKilIL7ikaKQwL9rpbvl/ts7MU;", "2gV9Hf72AESV2NkkvPozr6DgyVViOnTr/lD6aHWuTRA4", "Xo/bG6EGFL52Y1esY4EaYt+7HeMsHWQ+mdJl0iI+oPA9", "T8nQ6qwtQEqJ96HItpw+AGec3nUuC+sKiAEjYwZzSL4<", "7mhUvR1FtyvorpF/goRKg8FFaHRhrU4CrEK7Pv4A/505", "mR+uuga8Z0j46LXEtuZB/0zQYV6Ri6ug7fzr45Khd6k8", "IXHNklLmSXRThaMmjcRag7w4O0fdR2VUEYRja/7lbiw>", "iZC5UWGE9R/sp65x+4vLdQzCL62UWWCJgwxXmuigb4E:", "pzHyw/uCkOx1NcgYs/ddkwhL8DGEZt8VjAa6VUEkWy4?", },
            { "WdihhswRm6U//BQCApboNQhL8DGEZt8VjAa6VUEkWy4:", "J8OAKnMNi/Vz3booS1xmMNH+MJ7aGVLO+LTiUQ/qVRI<", "YWUZVOKBPvuhA9rGhfF23c6ikS/eSN/1e6A8ARw4RRc?", "STAJHNg0ZRWzkDL9c/9KC/omC2ubNRSk9s5P+HxOOU8>", "RXxs5HiFKR6cS3b+BXz6eQYdP8IUytZBTIj86Z6LlxI9", "xIIMVXdXfIuYyoih5oO4knfqkpRsKuARrgRcs66yL6A;", "AufyhdM1IhdeJKZ+BuBhpciogh/BZCuMq3O+/Ih+lqE4", "+FCZJJ3D7DC6BiNuZ2iSfT/7z3qgVqoR79csChUTrcc8", "ZB2Zyltc8L5EOjv28RjPwSY8nBMOf2F8aZNjvLy1xE45", },
            { "Cji2FYVw9Mleq0ShvUw9vSY8nBMOf2F8aZNjvLy1xE4?", "BeXQqQNg/QrBzcAMOTzYqhQlYQ5zxe88stC2+X7CBPI>", "tbjBDtwwKZLwW3OzOwg1xCtvK2OC/o70VP1FBSUgUnw5", "T66lNpDcTSUu3CSbvCGn/JLAIAqAYBJcHyUiI6divgg9", "dCWMY3AeicCHf4nyxf2FEVxJBX1zOFMqFXkUmngwlWI4", "HmuJ91Uw8JLixubapXsAlchhAfxKDl/sjDRgo5oMscw:", "Ekl0NTcbCvw8w5KsD+zpTFw+rWHMLNMxKxsso+7Vh4Q8", "jUm1tYbR97nP+Dq8osTCoSCV/iIxi1mdAnepkSANHrg;", "L2p38fv1hLIShdXpC5bzC2e9nc435mXBJ3aEzA+v4rY<", },
            { "B7LisOPpyGsqiK3ElytKMme9nc435mXBJ3aEzA+v4rY4", "QY8cJmgdKuRgWqRaDtO/L40TdHbBC45/46aSqQZkf88;", "1IBwERDnA0dpfOse3fb9FlFHlVk5Rbn3mqlKrJ4Xovg<", "CXYugUeV9keOFFlza0hyORNva53pTV/X2zlox3gI/2k5", "aZmbRf41CBSW/RsVXEhNpYztXtt56JLDxUepAsZAX3Y8", "69ji+tZAg94PeoipHb9TbHQxJlosQNm87jthl07VoDY?", "aJzHBEOXp2wJwXf2vKUlGEVY8PXVevuwiQUXW1PbQMY:", "baI8Rqv6eXGMxEG6HJlYvuA0ZrDmuTqmJmmlNhlL1Bc9", "gMVq9Dcw9cVh4Tmu5bMRpW7USrN9pnqILRZNKg0zXiI>", },
            { "K0i61JnmL0/I58XN46Ehy27USrN9pnqILRZNKg0zXiI9", "NjaLlCL6Hz6+YBQ1C6rDU0wcjbLVy0bnu6cwNbWPZE08", "GjYz2jm0DGdcwk1mPC9tVOV/8L1kcdfDrMjfnHJVH+0:", "x2SP1Gy0pKH1jTe6gt/BVt7qwIj5vlklI61eoKIMmHE;", "LK8Wkq1J6ti6QoTjzFyOznFRIpVpKdyzziAPg9gT0Bc>", "dS04C9qGP5Z2kuMVJ6zbGjZ6XqK73sc0UqnuC7WM8/Y<", "xiRx7gVYg4wZDl5BbmHfVhrfnWXpLeqKUUXeTh4AaQ05", "MILCLO0Lz+2SWcURYJZtFItzXtRgfKBeyX+DFnZub+s?", "eZr847QNzK8BpmICkJGAQ6LwZ5N6thxUS7vfWeBmkms4", },
            { "t8XS/+Eel0MYDmNfUovnOqLwZ5N6thxUS7vfWeBmkms5", "5kDaAQ4c5o2/MnGay2iHsYBEKkHdChsJf/EN2jehBPw9", "C30S0ZY7Y4gVvsBS9C58gfyuyKeHjC3f2Tv3dE29k+88", "oOx4RmAkgrOMKFHK9suCIEz+9Aq2tNOlwBdDmrFaVCM:", "4ZZvfrT0CJPik1+9B2Txh2Cl9yh+YIO9sPKh4iXcbwI<", "9NwQDfYFsMprTJwdqtHRnLtKrVE8PLh04iLLpGlIXRs>", "Wgv5CkVNEjHhIFyhuMbgYU2rgFTlHnWsbyU3ujYnR5I?", "qWN39muvJWnpGAnlOWSJ+z97nY273O4zFRciy7VabhA4", "NGMEX0CDkoXrwbLSlEEpWgVOrry82vvx9oos/7AuM5c;", },
            { "ZhojN2smN0un6sTRQzaUyAVOrry82vvx9oos/7AuM5c>", "TVvX2/RggplaE4GccD2wuQHeyTYG040FlBZ/WqSNPjA?", "iwUBMQBtjGZKfvmbEQcyTXyCA62p6yFtdQe0QlT0Wmc4", "xNLxcnFGliQ36kPbzSrnSFiC8m3JTaU13Y+Yc/XbQ+k8", "kPHAl6Osl4HqTijAuxeTbVxph7ilpBtVsrDYYNmQGNI;", "3ntIaZQ4yaUANENhzpB/qgiU9/5aOJhtBvxWZcf8+8U9", "cTBqLwtF++R6cLHXp1LpaL/iSHO94Qv6HtsKLbNJuJo<", "yFGLd7q9HqWauqRqYu2yQJRcZev8OFsdXOSL3qwD7Ww5", "gQqwm2/MgiA1LfUsdHVwsvdmCiE0o4UG/y7N08C8Z/0:", },
            { "AciSIzaBZhr3vgi7bxlEpPdmCiE0o4UG/y7N08C8Z/0<", "jvvyvXPGybvL20ZtAfhubNA7Wp+yFOFPGpknVC1pNew:", "SVK0mXLjNH59Ql2omKJzUWVupoIlygQp/ccoixE/vLg;", "L+T06UiHog0mv9H0/cCk98/rGSWcdhzQTZ46D5CTTMg4", "grB45b4mb3imMo1MEpjwhECOtxsbioqia825BMO8oPY?", "Am1jhNMNkb4GKM4KYCSJenOqC8xn+CD854v28qHl67c5", "0dWT5idBsTQwVStXsXekMbgLtuXFTkvE+D6CTUEZ2Yw9", "X8m15IAmpOlGCvCr86fVIW3xxSpRSrEH6yNfUtKUysY>", "GybGvMpIs4MaS3au7CxsWAOP7BUdNLiZdad3wXH2YuA8", },
        };

        public static string[,] Cipher = new string[9, 9];

        public static string[,] Input = new string[9, 9];


        public static void Main()
        {
            HackCipher();
            HackInput();
            string str = "";
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    str += Input[i, j];
                }
            }
            string flag = "RoarCTF{wm-" + Sha1(str).Substring(0, 10) + "}";
            Console.WriteLine(flag);
        }

        public static void HackInput()
        {
            string key = "SudokuCSharp";
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (j > 0)
                    {
                        key += Cipher[i, j - 1];
                    }
                    Input[i, j] = AesDecryptor_Base64(Cipher[i, j], key);
                }
            }
        }

        public static void HackCipher()
        {
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    Cipher[i, j] = "";
                    Cipher[i, j] = Fix[i, j].Substring(0, Fix[i, j].Length - 1);
                    Cipher[i, j] += (char)(Fix[i, j][Fix[i, j].Length - 1] ^ nNum[i, j]);
                }
            }
        }

        public static string Xor(string s1, string s2)
        {
            string res = "";
            if (s1.Length == s2.Length)
            {
                for (int i = 0; i < s1.Length; i++)
                {
                    res += (s1[i] ^ s2[i]).ToString();
                }
            }
            else
            {
                res = "0";
            }
            return res;
        }

        public static string Sha1(string str)
        {
            var buffer = Encoding.UTF8.GetBytes(str);
            var data = SHA1.Create().ComputeHash(buffer);

            StringBuilder sub = new StringBuilder();
            foreach (var t in data)
            {
                sub.Append(t.ToString("X2"));
            }

            return sub.ToString();
        }

        public static string Md5(string str)
        {
            var buffer = Encoding.UTF8.GetBytes(str);
            var data = MD5.Create().ComputeHash(buffer);
            var sb = new StringBuilder();
            foreach (var t in data)
            {
                sb.Append(t.ToString("X2"));
            }
            return sb.ToString();
        }

        public static string AesDecryptor_Base64(string DecryptStr, string Key)
        {
            try
            {
                Key = Md5(Key).Substring(0, 16);
                byte[] keyArray = Encoding.UTF8.GetBytes(Key);
                byte[] toEncryptArray = Convert.FromBase64String(DecryptStr);

                RijndaelManaged rDel = new RijndaelManaged();
                rDel.Key = keyArray;
                rDel.Mode = CipherMode.ECB;
                rDel.Padding = PaddingMode.PKCS7;

                ICryptoTransform cTransform = rDel.CreateDecryptor();
                byte[] resultArray = cTransform.TransformFinalBlock(toEncryptArray, 0, toEncryptArray.Length);

                return Encoding.UTF8.GetString(resultArray);
            }
            catch (Exception ex)
            {
                return null;
            }
        }
    }
}

```
和0ops交流过之后，发现他们直接把4个随机位当做了空格，用在线网站解数独，然后这样仍然是唯一解（这并不代表题目有问题，反而证明了题目设计逻辑是正确的，因为设计初衷就是要保证10000种可能的数独地图有且只有一解）
