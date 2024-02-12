using System;
using ScriptAPI;

public class ReturnToMainMenuButton : Script
{
    UISpriteComponent returntoMMButtonSprite;
    public override void Awake()
    {
    }

    public override void Start()
    {
        returntoMMButtonSprite = gameObject.GetComponent<UISpriteComponent>();
    }

    public override void Update()
    {
        if (PopupUI.isDisplayed)
        {
            returntoMMButtonSprite.SetEnabled(true);
        }
        else
        {
            returntoMMButtonSprite.SetEnabled(false);
        }

        if (Input.GetMouseButtonDown(Keycode.M1) && returntoMMButtonSprite.IsMouseCollided() && PopupUI.isDisplayed == true)
        {
            //Console.WriteLine("Return to MM Button Pressed");
            PopupUI.isDisplayed = false;
            SceneLoader.LoadMainMenu();
        }
    }
}