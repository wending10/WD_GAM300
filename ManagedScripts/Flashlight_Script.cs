using ScriptAPI;
using System;

public class Flashlight_Script : Script
{
    //public Light lightSource;
    public float lightIntensity;
    public GameObject lightSourceObj;
    public GameObject player;
    public bool activateLight = false;
    public GameDataManager myGameDataManager;
    public string flashAudiostr = "temp_flashlight";
    public AudioComponent flashAudio;
    public float followSpeed;

    private float yaw = 0.0f;
    private float pitch = 0.0f;

    [SerializeField] private bool flicker = false;
    [SerializeField] private float flickerTimer;

    public override void Awake()
    {
        flashAudio = gameObject.GetComponent<AudioComponent>();
    }

    public override void Start()
    {
          
    }

    public override void Update()
    {
        if (Input.GetKeyDown(Keycode.F))
        {
            activateLight = !activateLight;
            if (flashAudio.finished(flashAudiostr))
            {
                flashAudio.play(flashAudiostr);
            }
            //Input.KeyRelease(Keycode.F);
        }

        if (flicker)
        {
            FlickeringLight();
        }

        if (activateLight)
        {
            lightSourceObj.SetActive(true);
        }
        else
        {
            lightSourceObj.SetActive(false);
        }

        //BatteryLife();
    }

    public override void LateUpdate()
    {
        flashAudio.stop(flashAudiostr);

        if (activateLight)
        {
            
            lightSourceObj.transform.SetPositionY((player.transform.GetPosition().Y + 10f));

            yaw = Input.GetAxisX() * Input.GetSensitivity() * player.GetComponent<FPS_Controller_Script>().mouseSensitivity;
            pitch -= Input.GetAxisY() * Input.GetSensitivity() * player.GetComponent<FPS_Controller_Script>().mouseSensitivity;

            lightSourceObj.transform.SetRotationX(pitch);
            lightSourceObj.transform.SetRotationY(player.transform.GetRotation().Y);

            lightSourceObj.transform.SetRotation(Vector3.Slerp(lightSourceObj.transform.GetRotation(), 
                player.GetComponent<FPS_Controller_Script>().playerCamera.transform.GetRotation()
                ,Time.deltaTime * followSpeed));

            Vector4 direction = new Vector4(lightSourceObj.transform.GetRotation().X,
                lightSourceObj.transform.GetRotation().Y, lightSourceObj.transform.GetRotation().Z, 0);

            lightSourceObj.GetComponent<SpotlightComponent>().SetDirection(direction);
        }
    }

    void BatteryLife()
    {
        if (lightIntensity <= 0)
        {
            activateLight = false;
            lightSourceObj.GetComponent<GraphicComponent>().SetColourAlpha(0.0f);
        }

        if (activateLight)
        {
            lightIntensity -= 0.0001f * Time.deltaTime;
        }
    }

    void FlickeringLight()
    {
        //This chunck of code is not right, by I like the result of the code so yea lul
        //if (flickerTimer >= 0)
        //{
        //    lightSource.enabled = true;
        //    flickerTimer -= 0.1f;
        //}
        //else if (flickerTimer <= 1)
        //{
        //    lightSource.enabled = false;
        //    flickerTimer += 0.1f;
        //}
    }
}
