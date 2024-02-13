/*!*************************************************************************
****
\file playButton.cs
\author Matthew Cheung
\par DP email: j.cheung@digipen.edu
\par Course: csd3450
\date 22-11-2023
\brief  Script for main menu play button
****************************************************************************
***/
using ScriptAPI;
using System;

public class PlayButton : Script
{
    public AudioComponent bgm;
    public string bgmName;
    private UISpriteComponent sprite;
    bool withinArea(float mouse, float min, float max)
    {
        bool within = false;
        if (mouse > min && mouse < max)
            within = true;
        return within;
    }

    public override void Awake()
    {
        GraphicsManagerWrapper.ToggleViewFrom2D(true);
        bgmName = "skyclad_sound_ambience_dark_loop_dynamic_tones_howling_moaning_mournful_eerie_105";
        bgm = gameObject.GetComponent<AudioComponent>();
        sprite = gameObject.GetComponent<UISpriteComponent>();
    }

    public override void Update()
    {
        bgm.play(bgmName);

        if (Input.GetMouseButtonDown(Keycode.M1) && sprite.IsMouseCollided())
        {
            //GraphicsManagerWrapper.ToggleViewFrom2D(false);
            bgm.stop(bgmName);
            SceneLoader.LoadStartingCutscene();
        }
    }

    public override void OnDestroy()
    {
        bgm.stopAll();
    }
}
