using ScriptAPI;
using System;

public class Test : Script
{
    public override void Start()
    {
        Console.WriteLine("Start Test");
    }

    public override void Update()
    {
        Console.WriteLine("Update");
    }

    public override void OnDestroy() 
    {
        Console.WriteLine("Exit");
    }
}
