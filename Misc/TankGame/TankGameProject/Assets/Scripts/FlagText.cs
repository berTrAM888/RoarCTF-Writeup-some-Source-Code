using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FlagText : MonoBehaviour
{
    public static FlagText _instance;

    public static string str = "";

    private void Awake()
    {
        _instance = this;
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
