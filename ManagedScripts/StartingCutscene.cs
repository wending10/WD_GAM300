using ScriptAPI;
using System;

public class StartingCutscene : Script
{
    
    public override void Awake()
    {
        GraphicsManagerWrapper.ToggleViewFrom2D(true);
    }

    public override void Update()
    {
        var audioEntity = GameObjectScriptFind("Audio");
        AudioComponent Narration = audioEntity.GetComponent<AudioComponent>();
                
        var EntityID = gameObject.GetEntityID();
        UISpriteComponent Sprite = gameObject.GetComponent<UISpriteComponent>();
        
        //if audio plays finish
        Sprite.SetTextureName("Scene1.dds");//change scene
        //change subtitle

    }
}
