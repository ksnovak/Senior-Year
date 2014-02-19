using UnityEngine;
using System.Collections;

public class GameCamera : MonoBehaviour {

	private Transform target;
	private float trackSpeed = 10;

	public void setTarget(Transform t) {
		target = t;	
	}

	void LateUpdate() {
		if (target)
		{
			float x = IncrementTowards(transform.position.x, target.position.x, trackSpeed);
			float y = IncrementTowards(transform.position.y, target.position.y, trackSpeed);
			transform.position = new Vector3(x, y, transform.position.z);
		}
	}


	private float IncrementTowards (float n, float target, float accel) {
		if (n == target) {
			return n;
		}
		else {
			float dir = Mathf.Sign (target - n);
			n += accel * Time.deltaTime * dir;
			return (dir == Mathf.Sign(target-n))? n : target;
		}
	}
}
