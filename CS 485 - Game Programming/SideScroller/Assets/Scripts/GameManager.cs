using UnityEngine;
using System.Collections;

//Handle instantiating the player spawn
public class GameManager : MonoBehaviour {

	public GameObject player;
	private GameCamera cam;
	private GameObject currentPlayer; 
	private Vector3 checkpoint;
	private bool showMessage = false;
	public static int levelCount = 3; //statics will not get reset between scenes
	public static int currentLevel = 1;

	// Use this for initialization
	void Start () {
		cam = GetComponent<GameCamera> ();
		if (GameObject.FindGameObjectWithTag("Spawn")) {
			checkpoint = GameObject.FindGameObjectWithTag("Spawn").transform.position;
		}
		spawnPlayer (checkpoint);
	}

	void Update () {
		if (!currentPlayer) {
			if (Input.GetButtonDown ("Respawn"))
				spawnPlayer (checkpoint);
		}
	}

	void OnGUI () {
		if (showMessage)
		{
			GUI.Label(new Rect(Screen.height * .6f, Screen.height * .5f , 100,100), "YOU WON!");
		}
	}
	
	private void spawnPlayer(Vector3 spawnLocation) {
		currentPlayer = Instantiate (player, spawnLocation, Quaternion.identity) as GameObject;
		cam.setTarget (currentPlayer.transform); //Spawn at location 0, with 0 rotation
	}

	public void SetCheckpoint(Vector3 check) {
		checkpoint = check;
	}

	public void EndLevel() {
		if (currentLevel < levelCount) {
			currentLevel++;
			Application.LoadLevel ("Level_" + currentLevel);
		}
		else {
			showMessage = true;
		}
	}
}
