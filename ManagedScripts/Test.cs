using ScriptAPI;

public class Test : ScriptAPI.Script
{
    public override void Update()
    {
        TransformComponent transform = GetTransformComponent();
        //Console.WriteLine("Test!");
        Console.WriteLine("x: " + transform.GetPosition().X + "\ty: " + transform.GetPosition().Y + "\tz: " + transform.GetPosition().Z);
        transform.SetPositionX(100.0f);
        transform.SetPositionY(100.0f);
        //Vector3 vec = new Vector3(70.0f, 0.0f, 0.0f);
        //transform.SetPosition(vec);
    }
}
