﻿///*!*************************************************************************
//****
//\file QuitConfirmationNo.cs
//\author Matthew Cheung
//\par DP email: j.cheung@digipen.edu
//\par Course: csd3450
//\date 23-3-2024
//\brief  Script for pressing no in quit confirmation menu
//****************************************************************************
//***/

using ScriptAPI;
using System;

public class QuitConfirmationNo : Script
{
    private AudioComponent buttonSfx;
    private string buttonSfxName = "button_press";
    private UISpriteComponent sprite;
    private bool firstHover = true;
    
    GameObject QuitObject;

    public override void Awake()
    {
        buttonSfx = gameObject.GetComponent<AudioComponent>();
        sprite = gameObject.GetComponent<UISpriteComponent>();
    }

    public override void Start()
    {
        QuitObject = GameObjectScriptFind("QuitConfirmation");
    }
    public override void Update()
    {
        if (sprite.IsMouseCollided() && firstHover)
        {
            //set scale logic here
            firstHover = false;
            buttonSfx.play("buttonhover");
        }
        if (!sprite.IsMouseCollided())
        {
            firstHover = true;
        }
        if (Input.GetMouseButtonDown(Keycode.M1) && sprite.IsMouseCollided())
        {
            buttonSfx.play(buttonSfxName);
            QuitObject.SetActive(false);
        }

    }
}