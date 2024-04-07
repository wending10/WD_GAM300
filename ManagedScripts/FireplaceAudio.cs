using ScriptAPI;
using System;

public class FireplaceAudio : Script
{
    String[] ClosetVO;
    AudioComponent audioComponent;

    public override void Awake()
    {
        ClosetVO = new string[17];

        audioComponent = new AudioComponent();
    }

    public override void Update()
    {
        audioComponent.set3DCoords(new Vector3(934.28f, 49.1388f, -995.61f), "fireplace");
        audioComponent.play("fireplace");
    }
}