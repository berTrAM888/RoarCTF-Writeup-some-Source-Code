using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Security.Cryptography;
using System.Text;

public class MapManager : MonoBehaviour
{
    private const int w = 21;

    private const int h = 17;

    public static int[,] MapState;

    public static int nDestroyNum = 0;

    public static bool winGame = false;
    
    private void Awake()
    {
        Init();
    }

    public static void Init()
    {
        MapState = new int[w, h]
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
    }

    public static void WinGame()
    {
        if (!winGame)
        {
            if (nDestroyNum == 4 || nDestroyNum == 5)
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
                    FlagText._instance.gameObject.SetActive(true);
                    FlagText.str = "RoarCTF{wm-" + Md5(str) + "}";
                    winGame = true;
                }
            }
        }
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
        return sb.ToString().Substring(0, 10);
    }

    public static string Sha1(string str)
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
}
