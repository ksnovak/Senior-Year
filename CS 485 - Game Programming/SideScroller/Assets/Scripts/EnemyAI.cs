using UnityEngine;
using System.Collections;

public class EnemyAI : MonoBehaviour {

	public GameObject corpse;
	public float startLocX;
	public float endPosX;
	public int rangeX = 3;

	public int moveSpeed = 1;

	public bool movingRight = true;

	public int health = 3;
	public int damage = 1;
	// Use this for initialization
	void Start () {
		startLocX = transform.position.x;
		endPosX = startLocX + rangeX;
	}
	
	// Update is called once per frame
	void Update () {
		if (health >0)
		{
			//If wandering to right
			if (movingRight)
			{
				transform.eulerAngles = new Vector3(0f, 90f, 0f);
				rigidbody.position += Vector3.right * moveSpeed * Time.deltaTime;
				animation.Play ("walk");
			}
			if (rigidbody.position.x >= endPosX) {
				movingRight = false;
			}

			//If wandering to left
			if (!movingRight)
			{
				transform.eulerAngles = new Vector3(0f, 270f, 0f);
				rigidbody.position -= Vector3.right * moveSpeed * Time.deltaTime;
				animation.Play ("walk");
			}
			if (rigidbody.position.x <= startLocX) {
				movingRight = true;
			}
		}
	}

	void OnTriggerEnter(Collider c) {
		if (c.tag == "Player") {
			//Inflict damage
			Debug.Log ("Die!");
			c.GetComponent<Entities>().TakeDamage (damage);
		}
	}


	public void TakeDamage(int damage)
	{
		if (health > 0)
			health -= damage;

		if (health <= 0)
		{
			Die ();
		}
	}

	public void Die() {
		Debug.Log ("I am now dead.");
		collider.enabled = false;
		startLocX = endPosX =  transform.position.x;
		damage = 0;
		animation.Stop();
		transform.eulerAngles = new Vector3(0f, transform.rotation.y, -90f);
	}


}
