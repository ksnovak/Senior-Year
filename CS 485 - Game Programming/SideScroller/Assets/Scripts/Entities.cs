using UnityEngine;
using System.Collections;

public class Entities : MonoBehaviour {
	
	public float health;
	public GameObject ragdoll;

	public void TakeDamage(float damage) {
		health -= damage;

		if (health <= 0)
		{
			Die();
		}
	}

	public void Die() {
		Debug.Log ("I am now dead.");
		Ragdoll r = (Instantiate (ragdoll, transform.position, transform.rotation) as GameObject).GetComponent<Ragdoll>();
		r.CopyPose (transform);
		Destroy(this.gameObject);
	}


}
