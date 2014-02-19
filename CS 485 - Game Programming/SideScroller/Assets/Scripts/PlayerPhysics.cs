using UnityEngine;
using System.Collections;

[RequireComponent (typeof(BoxCollider))]
public class PlayerPhysics : MonoBehaviour {

	public LayerMask collisionMask; //Layer of objects with which to collide
	private BoxCollider collider; //The collision checker
	private Vector3 size;
	private Vector3 center;

	private Vector3 originalSize;
	private Vector3 originalCenter;
	private float colliderScale;

	private int collisionDivisionsX = 3;
	private int collisionDivisionsY = 10;

	private float skin = .005f; //Always leave a small amount of distance between player and ground, to avoid rays spawning below ground

	private Transform platform;
	private Vector3 platformPositionOld;
	private Vector3 deltaPlatformPosition;

	[HideInInspector] public bool grounded;
	[HideInInspector] public bool movementStopped;

	Ray ray;
	RaycastHit hit;

	void Start() {
		collider = GetComponent<BoxCollider> ();
		colliderScale = transform.localScale.x;
		originalSize = collider.size;
		originalCenter = collider.center;
		SetCollider (originalSize, originalCenter);
	}

	public void Move(Vector2 moveAmount) 
	{
		float deltaY = moveAmount.y;
		float deltaX = moveAmount.x;
		Vector2 pos = transform.position;

		if (platform) {
			deltaPlatformPosition = platform.position - platformPositionOld;
		}
		else {
			deltaPlatformPosition = Vector3.zero;
		}
		#region Vertical collisions
		grounded = false;
		for (int i = 0; i < collisionDivisionsX; i++) {
			float dir = Mathf.Sign (deltaY);
			float x = (pos.x + center.x - size.x/2) + size.x/(collisionDivisionsX-1) * i;
			float y = pos.y + center.y + size.y/2 * dir;

			ray = new Ray(new Vector2(x, y), new Vector2(0, dir));
			Debug.DrawRay (ray.origin, ray.direction);
			if (Physics.Raycast(ray, out hit, Mathf.Abs (deltaY) + skin, collisionMask))
			{
				platform = hit.transform;
				platformPositionOld = platform.position;
				float distance = Vector3.Distance (ray.origin, hit.point);
				if (distance > skin) {
					deltaY = distance * dir - skin * dir;
				}
				else 
				{
					deltaY = 0;
				}
				grounded = true;

				break;
			} else {
				platform = null;
			}
		}
		#endregion

		#region Sideways Collisions
		movementStopped = false;
		for (int i = 0; i < collisionDivisionsY; i++) {
			float dir = Mathf.Sign (deltaX);
			float x = pos.x + center.x + size.x/2 * dir;
			float y = pos.y + center.y - size.y/2 + size.y/(collisionDivisionsY-1) * i;
			
			ray = new Ray(new Vector2(x, y), new Vector2(dir, 0));
			Debug.DrawRay (ray.origin, ray.direction);
			if (Physics.Raycast(ray, out hit, Mathf.Abs (deltaX) + skin, collisionMask))
			{
				float distance = Vector3.Distance (ray.origin, hit.point);
				if (distance > skin) {
					deltaX = distance * dir - skin * dir;
				}
				else 
				{
					deltaX = 0;
				}
				movementStopped = true;
				break;
			}
		}
		#endregion

		if (!grounded && !movementStopped) {
			Vector3 playerDir = new Vector3 (deltaX, deltaY);
			Vector3 origin = new Vector3 (pos.x + center.x + size.x / 2 * Mathf.Sign (deltaX), pos.y + center.y + size.y / 2 * Mathf.Sign (deltaY));
			Debug.DrawRay (origin, playerDir.normalized);
			ray = new Ray (origin, playerDir.normalized);
			if (Physics.Raycast (ray, Mathf.Sqrt (deltaX * deltaX + deltaY * deltaY), collisionMask)) {
					grounded = true;
					deltaY = 0;
			}
		}
		Vector2 finalTransform = new Vector2 (deltaX + deltaPlatformPosition.x, deltaY);
		transform.Translate (finalTransform, Space.World);
	}

	public void SetCollider(Vector3 aSize, Vector3 aCenter) {
		collider.size = aSize;
		collider.center = aCenter;

		size = aSize * colliderScale;
		center = aCenter * colliderScale;

	}

	public void ResetCollider() {
		SetCollider (originalSize, originalCenter);
	}
}
