using UnityEngine;
using System.Collections;

[RequireComponent(typeof(PlayerPhysics))]
public class PlayerController : Entities {

	public float walkSpeed = 8;
	public float runSpeed = 12;
	public float acceleration = 30;
	public float gravity = 20;
	public float jumpHeight = 12;
	public float slideDecel = 10;

	private float animationSpeed;
	private float currentSpeed;
	private float targetSpeed;

	public int damage = 2;



	private Vector2 amountToMove;
	//States
	private bool isJumping;
	private bool isSliding;

	private PlayerPhysics playerPhysics;
	private Animator animator;
	private GameManager manager;


	// Use this for initialization
	void Start () {
		transform.eulerAngles = Vector3.up * 90;
		playerPhysics = GetComponent<PlayerPhysics> ();
		animator = GetComponent<Animator> ();
		manager = Camera.main.GetComponent<GameManager>();
	}
	
	// Update is called once per frame
	void Update () {
		//When you hit a wall, stop trying to move.
		if (playerPhysics.movementStopped) {
			targetSpeed = 0; 
			currentSpeed = 0;
		}
		if (isJumping) {
			isJumping = false;
			animator.SetBool ("Jumping", false);
		}
		if (isSliding) {
			if (Mathf.Abs (currentSpeed) < .25f) {
				isSliding = false;
				animator.SetBool("Sliding", false);
				playerPhysics.ResetCollider();
			}
		}

		//When you hit the ground, stop trying to fall
		if (playerPhysics.grounded) {
			amountToMove.y = 0;
			if (Input.GetButtonDown ("Jump")) {
				amountToMove.y = jumpHeight;
				isJumping = true;
				animator.SetBool ("Jumping", true);
			}

			if (Input.GetButtonDown ("Slide")) {
				isSliding = true;
				animator.SetBool ("Sliding", true);
				targetSpeed = 0;
				playerPhysics.SetCollider (new Vector3(10.3f, 1.5f, 3f), new Vector3(.35f, .75f, 0));
			}
		}



		animationSpeed = IncrementTowards (animationSpeed, Mathf.Abs (targetSpeed), acceleration);
		animator.SetFloat ("Speed", animationSpeed); //Communicate with the Blend Tree, so as to pick what animation to use

		if (!isSliding) {
			float speed = (Input.GetButton ("Run") ? runSpeed : walkSpeed); //Depending on whether the RUN button is held or not, pick a speed.
			targetSpeed = Input.GetAxisRaw ("Horizontal") * speed;
			currentSpeed = IncrementTowards (currentSpeed, targetSpeed, acceleration);

			float moveDir = Input.GetAxisRaw ("Horizontal");
			if (moveDir != 0) { //Change direction if the model is moving
					transform.eulerAngles = (moveDir > 0) ? Vector3.up * 180 : Vector3.zero; //Turn left and right
					transform.eulerAngles -= Vector3.up * 90; //This model by default has his back facing to screen. So rotate him some more so it's properly left and right
			}
		} else {
			currentSpeed = IncrementTowards (currentSpeed, targetSpeed, slideDecel);

		}

		amountToMove.x = currentSpeed;
		amountToMove.y -= gravity * Time.deltaTime;
		animator.SetFloat ("DeltaY", amountToMove.y);
		playerPhysics.Move (amountToMove * Time.deltaTime);

	}

	void OnTriggerEnter(Collider c) {
		if (c.tag == "Checkpoint") {
			manager.SetCheckpoint (c.transform.position);
		}
		if (c.tag == "Finish") {
			manager.EndLevel();
		}
		if (c.tag == "Enemy") {
			//Inflict damage
			c.GetComponent<EnemyAI>().TakeDamage (damage);
		}
		if (c.tag == "Bottom") {
			Die ();
		}
	}

	//Tween the motion, work towards a speed.
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