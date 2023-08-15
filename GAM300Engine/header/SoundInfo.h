#pragma once

#include <string>

struct SoundInfo {

    std::string uniqueID;

    const char* filePath;

    bool isLoop, is3D, isLoaded;

    float x, y, z;

    float volume, ReverbAmount;

    // convienience method to set the 3D coordinates of the sound.
    void set3DCoords(float x, float y, float z) {
        this->x = x, this->y = y, this->z = z;
    }

    bool isLoaded()
    {
        return isLoaded;
    }

    std::string getUniqueID()
    {
        return uniqueID;
    }

    const char* getFilePath()
    {
        return filePath;
    }

    float getX()
    {
        return x;
    }

    float getReverbAmount()
    {
        return ReverbAmount;
    }

    /**
    * Parameter takes in Volume values (0 - 100)
    */
    void setVolume(float vol)
    {
        volume = 20.0f * log10f(vol);
    }

    SoundInfo(const char* filePath = "", bool isLoop = false, bool is3D = false, float x = 0.0f, float y = 0.0f, float z = 0.0f)
        : filePath(filePath), isLoop(isLoop), is3D(is3D), x(x), y(y), z(z)
    {
        uniqueID = filePath;
    }

    // TODO  implement sound instancing
    // int instanceID = -1; 

};