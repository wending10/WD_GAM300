﻿/*!*************************************************************************
****
\file ReturnToMainMenuButton.cs
\author Matthew Cheung
\par DP email: j.cheung@digipen.edu
\par Course: csd3450
\date 20-1-2024
\brief  Script for pause menu main menu button
****************************************************************************
***/
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
            Console.WriteLine("Return to MM Button Pressed");
            AudioComponent audio = gameObject.GetComponent<AudioComponent>();
            audio.stopAll();
            PopupUI.isDisplayed = false;
            SceneLoader.LoadMainMenu();
        }
    }
}