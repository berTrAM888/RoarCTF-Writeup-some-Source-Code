using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Explosion : MonoBehaviour {

	// Use this for initialization
	void Start () {
        Destroy(gameObject, 0.167f);
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
