using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class L0V31Y1oVelyT1nTs : MonoBehaviour
{
    //虚假的map
    public static int[,] GameMap0RSom3th1ngE1Se = new int[9, 9]
    {
        {0,0,3,0,7,9,6,1,0 },
        {6,0,0,1,0,0,3,0,0 },
        {0,1,0,3,4,6,0,7,8 },
        {2,3,0,0,9,0,5,6,1 },
        {9,6,1,0,0,0,7,0,3 },
        {0,8,7,6,3,1,0,2,0 },
        {0,4,0,0,1,3,0,0,6 },
        {3,0,0,5,6,0,1,0,0 },
        {1,0,6,0,5,8,0,3,0 },
    };

    //真实的map
    //public static int[,] Map = new int[9, 9]
    //{
    //    {0,0,3,0,7,9,6,1,0 },
    //    {6,0,0,1,0,0,3,0,0 },
    //    {0,1,0,3,4,6,0,0,8 },
    //    {2,3,0,0,9,0,5,6,1 },
    //    {9,6,1,0,0,0,7,0,3 },
    //    {0,0,7,6,3,1,0,2,0 },
    //    {0,4,0,0,1,3,0,0,6 },
    //    {3,0,0,5,6,0,1,0,0 },
    //    {1,0,6,0,2,8,0,3,0 },
    //};

    //答案map
    //public static int[,] Answer = new int[9, 9]
    //{
    //    {5,8,3,2,7,9,6,1,4 },
    //    {6,9,4,1,8,5,3,7,2 },
    //    {7,1,2,3,4,6,9,5,8 },
    //    {2,3,8,4,9,7,5,6,1 },
    //    {9,6,1,8,5,2,7,4,3 },
    //    {4,5,7,6,3,1,8,2,9 },
    //    {8,4,5,7,1,3,2,9,6 },
    //    {3,2,9,5,6,4,1,8,7 },
    //    {1,7,6,9,2,8,4,3,5 }
    //};

    public int Sud0ku1SEas3;
    public int Sud0ku1SHaRd;
    public int Eas30RHarD;

    private void Awake()
    {
        HaRrnFu1Th1inG1.Mag1CF0rM3Cha113nG34Y0u();
        Sud0ku1SEas3 = (int)(transform.position.x / 2);
        Sud0ku1SHaRd = (int)(transform.position.y / 2);
        Eas30RHarD = GameMap0RSom3th1ngE1Se[Sud0ku1SEas3, Sud0ku1SHaRd];
        if (Eas30RHarD != 0)
        {
            GetComponent<BoxCollider2D>().enabled = false;
            GetComponentInChildren<TextMesh>().color = Color.blue;
        }
        HaRrnFu1Th1inG1.P01oPo10Wh0Ar3U[Sud0ku1SEas3, Sud0ku1SHaRd] = this;
    }

    void Update()
    {
        int increaseKey = 0;
        int decreaseKey = 1;
        if (Input.GetMouseButtonDown(increaseKey) && !HaRrnFu1Th1inG1.JuSTS0so)
        {
            Vector3 mousepos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            Vector2 mouse2 = new Vector2(mousepos.x, mousepos.y);
            RaycastHit2D hit = Physics2D.Raycast(mouse2, Vector2.zero);
            if (hit.collider != null && hit.collider.gameObject == this.gameObject)
            {
                //Debug.Log(hit.collider.gameObject.transform.position);
                Eas30RHarD++;
                HaRrnFu1Th1inG1.WoU1DY0uKn0WwhATD03STh1sM3an();
            }
        }
        else if (Input.GetMouseButtonDown(decreaseKey) && !HaRrnFu1Th1inG1.JuSTS0so)
        {
            Vector3 mousepos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            Vector2 mouse2 = new Vector2(mousepos.x, mousepos.y);
            RaycastHit2D hit = Physics2D.Raycast(mouse2, Vector2.zero);
            if (hit.collider != null && hit.collider.gameObject == this.gameObject)
            {
                //Debug.Log(hit.collider.gameObject.transform.position);
                if (Eas30RHarD >= 1)
                    Eas30RHarD--;
                HaRrnFu1Th1inG1.WoU1DY0uKn0WwhATD03STh1sM3an();
            }
        }

        GetComponentInChildren<TextMesh>().text = Eas30RHarD.ToString();
        
    }
}
