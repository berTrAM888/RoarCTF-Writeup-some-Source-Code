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
            //取所有k个墙体的组合进行爆破
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
            //取1老家，k墙体的组合进行爆破
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
            Func2(0, 0, Walls.Count(), 4, new bool[Walls.Count()]); //4墙的组合
            Func3(0, 0, Walls.Count(), 3, new bool[Walls.Count()]); //1老家3墙的组合
            Func2(0, 0, Walls.Count(), 5, new bool[Walls.Count()]); //5墙的组合
            Func3(0, 0, Walls.Count(), 4, new bool[Walls.Count()]); //1老家4墙的组合
            Console.WriteLine("end");
        }
    }
}
