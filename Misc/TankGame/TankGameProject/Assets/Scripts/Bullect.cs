using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bullect : MonoBehaviour {

    public float moveSpeed = 10;

    public bool isPlayerBullect;


	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        transform.Translate(transform.up * moveSpeed * Time.deltaTime, Space.World);
	}


    private void OnTriggerEnter2D(Collider2D collision)
    {
        int x = (int)collision.gameObject.transform.position.x;
        int y = (int)collision.gameObject.transform.position.y;
        switch (collision.tag)
        {
            case "Tank":
                if (!isPlayerBullect)
                {
                    collision.SendMessage("Die");
                    Destroy(gameObject);
                }
                break;
            case "Heart":
                //销毁老家
                //毁灭数+1
                MapManager.MapState[x + 10, y + 8] = 9;
                MapManager.nDestroyNum++;

                collision.SendMessage("Die");
                Destroy(gameObject);
                break;
            case "Enemy":
                if (isPlayerBullect)
                {
                    collision.SendMessage("Die");
                    Destroy(gameObject);
                }
                
                break;
            case "Wall":
                //销毁墙体
                //毁灭数+1
                MapManager.MapState[x + 10, y + 8] = 8;
                MapManager.nDestroyNum++;

                Destroy(collision.gameObject);
                Destroy(gameObject);
                break;
            case "Barrier":
                if (isPlayerBullect)
                {
                    collision.SendMessage("PlayAudio");
                }
                Destroy(gameObject);
                break;
            default:
                break;
        }
    }

}
