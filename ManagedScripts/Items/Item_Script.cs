using ScriptAPI;
using System;

public class Item_Script : Script
{
    private GameObject playerObject;
    //RigidBodyComponent rigidBodyComponent; //for raycast?

    AudioComponent audioPlayer;
    String[] voClip;

    [SerializeField]
    public string Item_Name;
    public string Item_Texture;

    public override void Awake()
    {
        audioPlayer = gameObject.GetComponent<AudioComponent>();
        voClip = new String[2];
        voClip[0]= "pc_shinelightbeforereceipt";
        voClip[1]= "pc_shinelightafterreceipt"; //This one should be items VO
    }

    public override void Start()
    {
        playerObject = GameObjectScriptFind("player");
        //rigidBodyComponent = gameObject.GetComponent<RigidBodyComponent>();
    }

    public override void Update()
    {
        if (Input.GetKeyDown(Keycode.E) && isWithinRange()/* && rigidBodyComponent.IsRayHit()*/) // Maybe add 1 more condition to check if its within player's view
        {
            Console.WriteLine("Picked up item");
            InventoryScript.addItemIntoInventory(Item_Name, Item_Texture);
            gameObject.SetActive(false);
            audioPlayer.play(voClip[0]);
        }
    }

    public bool isWithinRange()
    {
        Vector3 itemPos = gameObject.transform.GetPosition();
        Vector3 playerPos = playerObject.transform.GetPosition();
        float distance = Vector3.Distance(itemPos, playerPos);
        Console.WriteLine(distance);
        audioPlayer.play(voClip[1]);
        return distance < 100.0;
    }
}