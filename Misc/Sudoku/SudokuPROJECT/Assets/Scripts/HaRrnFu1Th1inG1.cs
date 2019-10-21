using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Linq;
using System.IO;
using System.Text;
using System.Security.Cryptography;

public class HaRrnFu1Th1inG1 : MonoBehaviour
{
    public static L0V31Y1oVelyT1nTs[,] P01oPo10Wh0Ar3U = new L0V31Y1oVelyT1nTs[9,9];

    public static string[,] B3CaUs30FuGaM31sfuN = new string[9, 9]
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

    public static bool JuSTS0so = false;

    public static bool S33WhaTUB3l13ve(int [,] ans)
    {
        //先检查是不是本题的数独，本题数独是唯一解
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (L0V31Y1oVelyT1nTs.GameMap0RSom3th1ngE1Se[i, j] != 0 && ans[i, j] != L0V31Y1oVelyT1nTs.GameMap0RSom3th1ngE1Se[i, j])
                {
                    return false;
                }
            }
        }
        //检查每一行是不是1-9恰好
        for (int raw = 0; raw < 9; raw++)
        {
            int[] line = new int[9];
            for (int i = 0; i < 9; i++)
            {
                line[i] = ans[raw, i];
            }
            if (!B3l13veWhaTuSE3(line))
            {
                return false;
            }
        }
        //检查每一列是不是1-9恰好
        for (int col = 0; col < 9; col++)
        {
            int[] line = new int[9];
            for (int i = 0; i < 9; i++)
            {
                line[i] = ans[i, col];
            }
            if (!B3l13veWhaTuSE3(line))
            {
                return false;
            }
        }
        //检查每一宫是不是1-9恰好
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                int[] block = new int[9];
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        block[i * 3 + j] = ans[x * 3 + i, y * 3 + j];
                    }
                }
                if (!B3l13veWhaTuSE3(block))
                {
                    return false;
                }
            }
        }
        return true;
    }

    private static bool B3l13veWhaTuSE3(int[] arr)
    {
        //检测9个数字是不是1-9
        if (arr.Length == 9)
        {
            int[] visited = new int[10];
            for (int i = 0; i < 10; i++)
            {
                visited[i] = 0;
            }
            for (int i = 0; i < 9; i++)
            {
                if (1 <= arr[i] && arr[i] <= 9)
                {
                    visited[arr[i]]++;
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
        else
        {
            return false;
        }
    }

    public static void WoU1DY0uKn0WwhATD03STh1sM3an()
    {
        if (!JuSTS0so)
        {
            //Debug.Log(CheckSukudo(Element.Answer));
            //正确答案的input长度超过了int，所以仅靠玩游戏不能完成题目
            int[,] input = new int[9, 9];
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    input[i, j] = P01oPo10Wh0Ar3U[i, j].Eas30RHarD;
                }
            }
            //表面检测九宫格是否通过，但flag不在这
            if (S33WhaTUB3l13ve(input))
            {
                Th1nGY0UW1llL0Ve.PR3C1ousTh1nGF0rM3.gameObject.SetActive(true);
                Th1nGY0UW1llL0Ve.str = "F1@g_1$_N0t_h3re... QAQ";
                JuSTS0so = true;
                return;
            }
            //input先加密成 string[,] cipher
            string[,] cipher = new string[9, 9];
            string key = "SudokuCSharp";
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    cipher[i, j] = "";
                    if (j > 0)
                    {
                        key += cipher[i, j - 1];
                    }
                    cipher[i, j] = F0Ra11Th3W0nDeRs(input[i, j].ToString(), key);
                }
            }
            //cipher和string[,] fix 异或成 string[,] num
            string[,] strNum = new string[9, 9];
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    strNum[i, j] = S33mSN0TeaSY(cipher[i, j], B3CaUs30FuGaM31sfuN[i, j]);
                }
            }
            //num转十进制整数，去做检测
            int[,] nNum = new int[9, 9];
            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    int.TryParse(strNum[i, j], out nNum[i, j]);
                }
            }
            //检测过关与否
            if (S33WhaTUB3l13ve(nNum))
            {
                Th1nGY0UW1llL0Ve.PR3C1ousTh1nGF0rM3.gameObject.SetActive(true);
                string str = "";
                for (int i = 0; i < 9; i++)
                {
                    for (int j = 0; j < 9; j++)
                    {
                        str += input[i, j];
                    }
                }
                Th1nGY0UW1llL0Ve.str = "RoarCTF{wm-" + D0AsUp13As3(str).Substring(0, 10) + "}";
                JuSTS0so = true;
            }
        }
    }

    public static string S33mSN0TeaSY(string s1, string s2)
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


    public static string D0AsUp13As3(string str)
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

    public static string JusTSh0wY0urT3l3nT(string str)
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

    public static string F0Ra11Th3W0nDeRs(string EncryptStr, string Key)
    {
        try
        {
            Key = JusTSh0wY0urT3l3nT(Key).Substring(0, 16);
            byte[] keyArray = Encoding.UTF8.GetBytes(Key);
            //byte[] keyArray = Convert.FromBase64String(Key);
            byte[] toEncryptArray = Encoding.UTF8.GetBytes(EncryptStr);

            RijndaelManaged rDel = new RijndaelManaged();
            rDel.Key = keyArray;
            rDel.Mode = CipherMode.ECB;
            rDel.Padding = PaddingMode.PKCS7;

            ICryptoTransform cTransform = rDel.CreateEncryptor();
            byte[] resultArray = cTransform.TransformFinalBlock(toEncryptArray, 0, toEncryptArray.Length);

            return Convert.ToBase64String(resultArray, 0, resultArray.Length);
        }
        catch (Exception ex)
        {
            return null;
        }
    }

    public static void Mag1CF0rM3Cha113nG34Y0u()
    {
        int[] nSwingX = { 5, 2, 8, 6 };
        int[] nSwingY = { 1, 7, 4, 2 };
        System.Random ran = new System.Random();
        for (int i = 0; i < nSwingX.Length; i++)
        {
            L0V31Y1oVelyT1nTs.GameMap0RSom3th1ngE1Se[nSwingX[i], nSwingY[i]] = ran.Next(0, 9);
        }
    }

}
