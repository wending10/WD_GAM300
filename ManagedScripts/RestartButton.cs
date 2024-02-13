/*!*************************************************************************
****
\file RestartButton.cs
\author Matthew Cheung
\par DP email: j.cheung@digipen.edu
\par Course: csd3450
\date 20-1-2024
\brief  Script for pause menu restart game button
****************************************************************************
***/
using System;
using ScriptAPI;

public class RestartButton : Script
{
    UISpriteComponent restartButtonSprite;
    public override void Awake()
    {
    }

    public override void Start()
    {
        restartButtonSprite = gameObject.GetComponent<UISpriteComponent>();
    }

    public override void Update()
    {
        if (PopupUI.isDisplayed)
        {
            restartButtonSprite.SetEnabled(true);
        }
        else
        {
            restartButtonSprite.SetEnabled(false);
        }

        if (Input.GetMouseButtonDown(Keycode.M1) && restartButtonSprite.IsMouseCollided())
        {
            Console.WriteLine("Restart Button Pressed");
            PopupUI.isDisplayed = false;
            SceneLoader.LoadMainGame();
        }
    }
}