﻿using UnityEngine;
using System.Collections;

public class Platform : MonoBehaviour {
	public float speed = 2;
	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		transform.Translate (Vector3.right * speed * Time.deltaTime);
	}
}
