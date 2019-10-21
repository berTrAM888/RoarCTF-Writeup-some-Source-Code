using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Th1nGY0UW1llL0Ve : MonoBehaviour
{
    public static Th1nGY0UW1llL0Ve PR3C1ousTh1nGF0rM3;

    public static string str = "";

    private void Awake()
    {
        PR3C1ousTh1nGF0rM3 = this;
        gameObject.SetActive(false);
    }


    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        this.GetComponent<Text>().text = str;
    }
}
