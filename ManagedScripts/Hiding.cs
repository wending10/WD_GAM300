using ScriptAPI;
using System;

public class Hiding : Script
{
    public bool interactable;
    public bool hiding;
    public Vector3 hidingPos;
    public Vector3 nonHidingPos;
    public float _RotationAngle;
    public GameObject player;
    //public Pathfinding enemyPathfinding;
    public Flashlight_Script _flashlight;
    public GameObject _InteractUI;
    public CheckGameState myGameState;

    [Header("AudioStuff")]
    //public AudioSource playerVOSource;
    //public AudioClip voClip;
    //public Text subtitles;

    bool playedAudio;

    private void Update()
    {
        if (interactable)
        {
            if (Input.GetKeyDown(Keycode.E) && hiding == false)
            {
                //enemyPathfinding._waiting = true;
                _InteractUI.SetActive(_InteractUI.GetEntityID(), false);
                hiding = true;
                interactable = false;
                player.transform.SetPosition(hidingPos);
                //player.transform.SetRotation(Quaternion.Euler(new Vector3(0, _RotationAngle, 0)));
                player.GetComponent<FPS_Controller_Script>().playerCanMove = false;
                player.GetComponent<FPS_Controller_Script>().enableHeadBob = false;
                //_flashlight.activateLight = false;
                //_flashlight.gameObject.SetActive(false);

                if (gameObject.GetComponent<NameTagComponent>().GetName() == "Bedroom_Body" /*&& myGameState._CurrentState == GameState.Gameplay*/)
                {
                    if (!playedAudio)
                    {
                        //playerVOSource.clip = voClip;
                        //playerVOSource.Play();
                        //subtitles.enabled = true;
                        //subtitles.text = "Martin (Internal): \"Nothing inside, but I could hide in here in case someone shows up.\"";
                        playedAudio = true;
                    }

                    //if (!playerVOSource.isPlaying() && playedAudio)
                    //{
                    //    subtitles.enabled = false;
                    //}
                }

                //if (enemyPathfinding._detected)
                //{

                //}
                //else
                //{

                //}
            }
        }
        else if (hiding)
        {
            if (Input.GetKeyDown(Keycode.E))
            {
                hiding = false;
                interactable = false;
                player.transform.SetPosition(nonHidingPos);
                player.GetComponent<FPS_Controller_Script>().playerCanMove = true;
                player.GetComponent<FPS_Controller_Script>().enableHeadBob = true;
                //_flashlight.gameObject.SetActive(true);
            }
        }
    }

    //private void OnTriggerEnter(Collider other)
    //{
    //    if (other.gameObject.name == "Enemy" && hiding == true)
    //    {
    //        if (enemyPathfinding._detected && hiding == true)
    //        {
    //            player.transform.position = nonHidingPos;
    //            hiding = false;
    //            interactable = false;
    //            _flashlight.gameObject.SetActive(true);
    //            //Debug.LogError("Pulled Out");
    //            //Play Attack Player Animation
    //        }
    //    }
    //}
}
