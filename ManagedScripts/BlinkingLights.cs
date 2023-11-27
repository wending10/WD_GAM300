using ScriptAPI;
using System;


public class BlinkingLights : Script
{
    [SerializeField]
    public bool IsOn;
    float counter;
    public override void Awake()
    {
        IsOn = true;
        counter = 0;
    }

    public override void Update()
    {
        //GameObjectScriptFind() use this to find the name of the sensor to turn of the light
        
        Console.WriteLine(gameObject.GetComponent<GraphicComponent>().getColourAlpha().ToString());
        //Console.WriteLine(gameObject.GetEntityID());
        
        counter += Time.deltaTime;
        if (counter > 5) {
            IsOn = !IsOn;
            counter = 0;
        }
        //if (!IsOn)
        //{
        //    gameObject.GetComponent<GraphicComponent>().SetColourAlpha(0);
        //}
        //if (IsOn) 
        //{
        //    gameObject.GetComponent<GraphicComponent>().SetColourAlpha(OriginalIntensity);
        //}
    }
}