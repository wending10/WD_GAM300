using ScriptAPI;
using System;

public class LostScript : Script 
{ 
	public override void Awake()
	{
		Input.Lock(false);
	}
	public override void Update()
	{
		for (int i = 0; i < 256; i++)
		{
			if (Input.GetKeyDown((char)i))
			{
                SceneLoader.LoadEndGameCredits();
            }
		}
	}
 }