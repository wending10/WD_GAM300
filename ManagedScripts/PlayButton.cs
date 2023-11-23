using ScriptAPI;
using System;

public class PlayButton : Script
{
    
    public override void Awake()
    {
        // Initialization code if any
    }

    public override void Update()
    {
        
        var entityID = gameObject.GetEntityID();
        if (Input.GetMouseButtonDown(Keycode.M1) && entityID == GraphicsManagerWrapper.GetPickedObject())
        {
            SceneLoader.LoadMainGame();
        }
    }
}
