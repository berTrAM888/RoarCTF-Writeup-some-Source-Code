using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class MapCreation : MonoBehaviour
{
    //用来装饰初始化地图所需物体的数组。
    //0.老家 1.墙 2.障碍 3.出生效果 4.河流 5.草 6.空气墙
    public GameObject[] item;

    //已经有东西的位置列表
    private List<Vector3> itemPositionList = new List<Vector3>();


    private void Awake()
    {
        InitMap();
    }

    private void InitMap()
    {
        //实例化外围墙
        for (int i = -11; i < 12; i++)
        {
            CreateItem(item[6], new Vector3(i, 9, 0), Quaternion.identity, 6);
        }
        for (int i = -11; i < 12; i++)
        {
            CreateItem(item[6], new Vector3(i, -9, 0), Quaternion.identity, 6);
        }
        for (int i = -8; i < 9; i++)
        {
            CreateItem(item[6], new Vector3(-11, i, 0), Quaternion.identity, 6);
        }
        for (int i = -8; i < 9; i++)
        {
            CreateItem(item[6], new Vector3(11, i, 0), Quaternion.identity, 6);
        }

        //初始化玩家
        GameObject go = Instantiate(item[3], new Vector3(-2, -8, 0), Quaternion.identity);
        go.GetComponent<Born>().createPlayer = true;

        //产生敌人
        CreateItem(item[3], new Vector3(-10, 8, 0), Quaternion.identity, 3);
        CreateItem(item[3], new Vector3(0, 8, 0), Quaternion.identity, 3);
        CreateItem(item[3], new Vector3(10, 8, 0), Quaternion.identity, 3);

        InvokeRepeating("CreateEnemy", 4, 5);

        //创建地形数组
        for (int i = 0; i < 21; i++)
        {
            for (int j = 0; j < 17; j++)
            {
                int x = MapManager.MapState[i, j];
                if (x != 8)
                {
                    CreateItem(item[x], new Vector3(i - 10, j - 8, 0), Quaternion.identity, x);
                }
            }
        }
    }

    private void CreateItem(GameObject createCameObject, Vector3 createPosition, Quaternion createRotation, int id)
    {
        GameObject itemGo = Instantiate(createCameObject, createPosition, createRotation);
        itemGo.transform.SetParent(gameObject.transform);
        itemPositionList.Add(createPosition);
    }

    //产生随机位置的方法
    private Vector3 CreateRandomPosition()
    {
        while (true)
        {
            Vector3 createPosition = new Vector3(Random.Range(-9, 10), Random.Range(-7, 8), 0);
            if (!HasThePosition(createPosition))
            {
                return createPosition;
            }
        }
    }

    //用来判断位置列表中是否有这个位置
    private bool HasThePosition(Vector3 createPos)
    {
        for (int i = 0; i < itemPositionList.Count; i++)
        {
            if (createPos == itemPositionList[i])
            {
                return true;
            }
        }
        return false;
    }

    //产生敌人的方法
    private void CreateEnemy()
    {
        int num = Random.Range(0, 3);
        Vector3 EnemyPos = new Vector3();
        if (num == 0)
        {
            EnemyPos = new Vector3(-10, 8, 0);
        }
        else if (num == 1)
        {
            EnemyPos = new Vector3(0, 8, 0);
        }
        else
        {
            EnemyPos = new Vector3(10, 8, 0);
        }
        CreateItem(item[3], EnemyPos, Quaternion.identity, 3);
    }

}
