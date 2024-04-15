using ScriptAPI;
using System;

public class BasementDoorActivate : Script 
{
	public GameObject gallerySwitch;
	public override void Awake()
	{

	}
	public override void Update()
	{
		if (GallerySwitch.isActivated)
		{
			gameObject.GetComponent<Door_Script>().forcedLocked = false;
		}
	}
 }