using ScriptAPI;
using System;

public class Test : Script
{
    public override void start()
    {
        Console.WriteLine("Start Test");
    }

    public override void Update()
    {
        Console.WriteLine("Update");
    }

    public override void Exit() 
    {
        Console.WriteLine("Exit");
    }
}
