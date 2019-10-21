MISC





## 坦克大战

思路：
逆向后，发现游戏原地图存储于MapState二维数组，初始值为
{
{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, },
{8, 8, 4, 5, 8, 1, 1, 1, 1, 1, 1, 8, 8, 8, 8, 4, 8, },
{8, 2, 8, 1, 8, 8, 5, 1, 8, 8, 8, 1, 8, 1, 8, 4, 8, },
{8, 5, 8, 2, 8, 8, 8, 8, 1, 8, 8, 4, 8, 1, 1, 5, 8, },
{8, 8, 8, 8, 2, 4, 8, 1, 1, 8, 8, 1, 8, 5, 1, 5, 8, },
{8, 8, 8, 8, 5, 8, 8, 1, 5, 1, 8, 8, 8, 1, 8, 8, 8, },
{8, 8, 8, 1, 8, 8, 8, 8, 8, 8, 8, 8, 1, 8, 1, 5, 8, },
{8, 1, 8, 8, 1, 8, 8, 1, 1, 4, 8, 8, 8, 8, 8, 1, 8, },
{8, 4, 1, 8, 8, 5, 1, 8, 8, 8, 8, 8, 4, 2, 8, 8, 8, },
{1, 1, 8, 5, 8, 2, 8, 5, 1, 4, 8, 8, 8, 1, 5, 1, 8, },
{0, 1, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, },
{1, 1, 8, 1, 8, 8, 2, 1, 8, 8, 5, 2, 1, 8, 8, 8, 8, },
{8, 8, 8, 8, 4, 8, 8, 2, 1, 1, 8, 2, 1, 8, 1, 8, 8, },
{8, 1, 1, 8, 8, 4, 4, 1, 8, 4, 2, 4, 8, 4, 8, 8, 8, },
{8, 4, 8, 8, 1, 2, 8, 8, 8, 8, 1, 8, 8, 1, 8, 1, 8, },
{8, 1, 1, 5, 8, 8, 8, 8, 8, 8, 8, 8, 1, 8, 8, 8, 8, },
{8, 8, 1, 1, 5, 2, 8, 8, 8, 8, 8, 8, 8, 8, 2, 8, 8, },
{8, 8, 4, 8, 1, 8, 2, 8, 1, 5, 8, 8, 4, 8, 8, 8, 8, },
{8, 8, 2, 8, 1, 8, 8, 1, 8, 8, 1, 8, 2, 2, 5, 8, 8, },
{8, 2, 1, 8, 8, 8, 8, 2, 8, 4, 5, 8, 1, 1, 2, 5, 8, },
{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, },
};
结合游戏观察发现对应关系为
0.老家 1.墙（可摧毁） 2.障碍（不可摧毁） 3.出生效果 4.河流 5.草 6.游戏边界 8.空地 9.被打爆的老家

逆向游戏逻辑后发现：
1. 墙和老家可以被攻击，攻击后墙由1变为8，老家由0变为9，且nDestroyNum都会+1。
2. 在每帧进行时会进入一个检测函数WinGame，首先保证nDestroyNum == 4 或 nDestroyNum==5，即摧毁4墙/1家3墙/5墙/1家4墙，然后加了一个前缀，将当前地图的数值遍历，转成字符串str，计算str的Sha1，如果等于预设值，则给出flag，flag为str的md5的前十位。

由这个思路，解题思路为：每次爆破，把 4墙/1家3墙/5墙/1家4墙 的组合全部爆破一遍，完成

爆破脚本
```C#
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography;


namespace TankGameMISCExp
{
    class Exp
    {
        const int w = 21;

        const int h = 17;

        static int[,] map = new int[w, h]
        {
            {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, },
            {8, 8, 4, 5, 8, 1, 1, 1, 1, 1, 1, 8, 8, 8, 8, 4, 8, },
            {8, 2, 8, 1, 8, 8, 5, 1, 8, 8, 8, 1, 8, 1, 8, 4, 8, },
            {8, 5, 8, 2, 8, 8, 8, 8, 1, 8, 8, 4, 8, 1, 1, 5, 8, },
            {8, 8, 8, 8, 2, 4, 8, 1, 1, 8, 8, 1, 8, 5, 1, 5, 8, },
            {8, 8, 8, 8, 5, 8, 8, 1, 5, 1, 8, 8, 8, 1, 8, 8, 8, },
            {8, 8, 8, 1, 8, 8, 8, 8, 8, 8, 8, 8, 1, 8, 1, 5, 8, },
            {8, 1, 8, 8, 1, 8, 8, 1, 1, 4, 8, 8, 8, 8, 8, 1, 8, },
            {8, 4, 1, 8, 8, 5, 1, 8, 8, 8, 8, 8, 4, 2, 8, 8, 8, },
            {1, 1, 8, 5, 8, 2, 8, 5, 1, 4, 8, 8, 8, 1, 5, 1, 8, },
            {0, 1, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, },
            {1, 1, 8, 1, 8, 8, 2, 1, 8, 8, 5, 2, 1, 8, 8, 8, 8, },
            {8, 8, 8, 8, 4, 8, 8, 2, 1, 1, 8, 2, 1, 8, 1, 8, 8, },
            {8, 1, 1, 8, 8, 4, 4, 1, 8, 4, 2, 4, 8, 4, 8, 8, 8, },
            {8, 4, 8, 8, 1, 2, 8, 8, 8, 8, 1, 8, 8, 1, 8, 1, 8, },
            {8, 1, 1, 5, 8, 8, 8, 8, 8, 8, 8, 8, 1, 8, 8, 8, 8, },
            {8, 8, 1, 1, 5, 2, 8, 8, 8, 8, 8, 8, 8, 8, 2, 8, 8, },
            {8, 8, 4, 8, 1, 8, 2, 8, 1, 5, 8, 8, 4, 8, 8, 8, 8, },
            {8, 8, 2, 8, 1, 8, 8, 1, 8, 8, 1, 8, 2, 2, 5, 8, 8, },
            {8, 2, 1, 8, 8, 8, 8, 2, 8, 4, 5, 8, 1, 1, 2, 5, 8, },
            {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, },
        };

        //存储所有墙体的位置
        static List<Tuple<int, int>> Walls = new List<Tuple<int, int>>();

        static Tuple<int, int> Heart;
        static void Func1()
        {
            //存储所有墙体的位置和老家的位置
            for (int i = 0; i < w; i++)
            {
                for (int j = 0; j < h; j++)
                {
                    if (map[i, j] == 1)
                    {
                        Walls.Add(new Tuple<int, int>(i, j));
                    }
                    if (map[i, j] == 0)
                    {
                        Heart = new Tuple<int, int>(i, j);
                    }
                }
            }
            
        }

        static void Func2(int pos, int cnt, int n, int k, bool[] visited)
        {
            //取所有4个墙体的组合进行爆破
            //已标记了k个数，计算
            if (cnt == k)
            {
                int [,] oneMap = new int[w, h];
                for (int i = 0; i < w; i++)
                {
                    for (int j = 0; j < h; j++)
                    {
                        oneMap[i, j] = map[i, j];
                    }
                }
                for (int i = 0; i < n; i++)
                {
                    if (visited[i])
                    {
                        oneMap[Walls[i].Item1, Walls[i].Item2] = 8;
                    }
                }

                string str = Once(oneMap);
                if (str.Length > 1)
                {
                    //爆破成功，输出结果
                    Console.WriteLine(str);
                }
                return;
            }

            if (pos == n) return;

            if (!visited[pos])
            {
                visited[pos] = true;
                Func2(pos + 1, cnt + 1, n, k, visited);
                visited[pos] = false;
            }
            Func2(pos + 1, cnt, n, k, visited);
        }

        static void Func3(int pos, int cnt, int n, int k, bool[] visited)
        {
            //取1老家，3墙体的组合进行爆破
            //已标记了k个数，计算
            if (cnt == k)
            {
                int[,] oneMap = new int[w, h];
                for (int i = 0; i < w; i++)
                {
                    for (int j = 0; j < h; j++)
                    {
                        oneMap[i, j] = map[i, j];
                    }
                }
                oneMap[Heart.Item1, Heart.Item2] = 9;
                for (int i = 0; i < n; i++)
                {
                    if (visited[i])
                    {
                        oneMap[Walls[i].Item1, Walls[i].Item2] = 8;
                    }
                }
                string str = Once(oneMap);
                
                if (str.Length > 1)
                {
                    //爆破成功，输出结果
                    Console.WriteLine(str);
                }
                return;
            }

            if (pos == n) return;

            if (!visited[pos])
            {
                visited[pos] = true;
                Func3(pos + 1, cnt + 1, n, k, visited);
                visited[pos] = false;
            }
            Func3(pos + 1, cnt, n, k, visited);
        }

        static string Once(int[,] MapState)
        {
            string str = "clearlove9";

            for (int i = 0; i < w; i++)
            {
                for (int j = 0; j < h; j++)
                {
                    str += MapState[i, j].ToString();
                }
            }

            string enc = Sha1(str);

            if (enc == "3F649F708AAFA7A0A94138DC3022F6EA611E8D01")
            {
                return "RoarCTF{wm-" + Md5(str) + "}";
            }
            else
            {
                return "";
            }
        }

        static string Md5(string str)
        {
            var buffer = Encoding.UTF8.GetBytes(str);
            var data = MD5.Create().ComputeHash(buffer);
            var sb = new StringBuilder();
            foreach (var t in data)
            {
                sb.Append(t.ToString("X2"));
            }
            return sb.ToString().Substring(0, 10);
        }

        static string Sha1(string str)
        {
            var buffer = Encoding.UTF8.GetBytes(str);
            var data = SHA1.Create().ComputeHash(buffer);
            var sb = new StringBuilder();
            foreach (var t in data)
            {
                sb.Append(t.ToString("X2"));
            }
            return sb.ToString();
        }

        static void Main()
        {
            Console.WriteLine("begin");
            Func1();
            Func2(0, 0, Walls.Count(), 4, new bool[Walls.Count()]);
            Func3(0, 0, Walls.Count(), 3, new bool[Walls.Count()]);
            Console.WriteLine("end");
        }
    }
}

```
运行得到flag：RoarCTF{wm-805CEC3545}