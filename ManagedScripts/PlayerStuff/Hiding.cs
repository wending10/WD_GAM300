/*!*************************************************************************
****
\file Hiding.cs
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: csd3450
\date 12-12-2023
\brief  Gameplay script for player hiding from the monster
****************************************************************************
***/
using System;
using System.Reflection.Emit;
using ScriptAPI;

public class Hiding : Script
{
    public bool interactable;
    public bool hiding;
    public Vector3 hidingPos;
    public Vector3 nonHidingPos;
    public float _RotationAngle;
    public GameObject player;
    public GameObject enemyPathfinding;
    public GameObject _flashlight;
    public GameObject _InteractUI;
    //public CheckGameState myGameState;
    public GameObject closet;
    /*[Header("AudioStuff")]
    public AudioSource playerVOSource;
    public AudioClip voClip;
    public Text subtitles;*/

    private float timer = 1.0f;

    public float turnSpeed = 0.01f;

    public override void Awake()
    {
    }

    public override void Start()
    {
        //_flashlight = player.GetComponent<Flashlight_Script>();
        hidingPos = closet.transform.GetPosition();
        _RotationAngle = 180.0f;
    }

    public override void Update()
    {
        
        if (interactable && gameObject.GetComponent<RigidBodyComponent>().IsRayHit())
        {
            _InteractUI.SetActive(true);
            if (Input.GetKeyDown(Keycode.E) && hiding == false)
            {
                hiding = true;
                interactable = false;
                nonHidingPos = player.transform.GetPosition();
                //player.transform.SetPosition(closet.transform.GetPosition());

                Vector3 rotation = new Vector3(0, 0, 0);
                //player.transform.SetRotation(rotation);

                Quaternion quat = new Quaternion(rotation);
                Vector3 newPosition = new Vector3(closet.transform.GetPosition().X, player.transform.GetPosition().Y, closet.transform.GetPosition().Z);
                player.GetComponent<RigidBodyComponent>().SetPositionRotationAndVelocity(newPosition, new Vector4(quat.X, quat.Y, quat.Z, quat.W), new Vector3(0, 0, 0), new Vector3(0, 0, 0));

                player.transform.SetRotation(new Vector3(0, -_RotationAngle, 0));

                player.GetComponent<FPS_Controller_Script>().playerCanMove = false;
                player.GetComponent<FPS_Controller_Script>().enableHeadBob = false;
                if (player.GetComponent<Flashlight_Script>().flashAudio.finished(player.GetComponent<Flashlight_Script>().flashAudiostr) && player.GetComponent<Flashlight_Script>().activateLight)
                {
                    player.GetComponent<Flashlight_Script>().flashAudio.play(player.GetComponent<Flashlight_Script>().flashAudiostr);
                }
                player.GetComponent<Flashlight_Script>().activateLight = false;
                _flashlight.SetActive(false);

                if (enemyPathfinding.GetComponent<GhostMovement>().hideEventDone == false)
                {
                    if (enemyPathfinding.GetComponent<GhostMovement>().hideEvent == false)
                    {
                        enemyPathfinding.transform.SetPosition(new Vector3(1790.0f, enemyPathfinding.transform.GetPosition().Y, -750.0f));
                        enemyPathfinding.GetComponent<GhostMovement>().hideEvent = true;
                    }
                    enemyPathfinding.GetComponent<GhostMovement>().isChasingPlayer = false;
                    enemyPathfinding.GetComponent<GhostMovement>().playSound = false;
                }
            }
        }
        else if (hiding)
        {
            _InteractUI.SetActive(false);
            if (Input.GetKeyDown(Keycode.E))
            {
                Console.WriteLine("There");
                hiding = false;
                interactable = true;
                //player.transform.SetPosition(nonHidingPos);

                Vector3 rotation = player.transform.GetRotation();
                Quaternion quat = new Quaternion(rotation);
                player.GetComponent<RigidBodyComponent>().SetPositionRotationAndVelocity(nonHidingPos, new Vector4(quat.X, quat.Y, quat.Z, quat.W), new Vector3(1, 1, 1).Normalize(), new Vector3(1, 1, 1).Normalize());

                // add if monster is finished
                player.GetComponent<FPS_Controller_Script>().playerCanMove = true;
                player.GetComponent<FPS_Controller_Script>().enableHeadBob = true;
                _flashlight.SetActive(true);
                //Input.KeyRelease(Keycode.E);
            }
        }
        else
        {
            _InteractUI.SetActive(false);
        }
        
    }

    /*private void OnTriggerEnter(GameObject other)
    {
        if (other.GetComponent<NameTagComponent>().GetName() == "Enemy" && hiding == true)
        {
            if (enemyPathfinding.isChasingPlayer && hiding == true)
            {
                player.transform.SetPosition(nonHidingPos);
                hiding = false;
                interactable = false;
                _flashlight.is_Enabled = true;
                //Debug.LogError("Pulled Out");
                //Play Attack Player Animation
            }
        }
    }*/
}
