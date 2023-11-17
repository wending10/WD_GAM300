#ifndef SOUND
#define SOUND

#include <string>
#include <array>
#include <time.h>

#include "components/iComponent.h"
#include "Vector3.h"

namespace TDS
{
    static unsigned int ID_Count{ 0 };

    enum SOUND_STATE
    {
        SOUND_ERR = 0,
        SOUND_LOADED,
        SOUND_UNLOAD,
        SOUND_PLAYING
    };

    struct SoundInfo : public IComponent
    {

        unsigned int uniqueID, MSLength;
        std::string filePath;
        bool isitLoop, isit3D;
        SOUND_STATE whatState;
        Vec3 position;
        float volume, ReverbAmount;

        /**
         * @brief Loading info from a file into SOUNDINFO.
         * @param obj 
         * @return true when success.
        */
        virtual bool Deserialize(const rapidjson::Value& obj)
        {
            position = { obj["PositionX"].GetFloat(), obj["PositionY"].GetFloat(), obj["PositionZ"].GetFloat() };
            filePath = { obj["file"].GetString() };
            isitLoop = { obj["Loop"].GetBool() };
            isit3D = { obj["3D"].GetBool() };
            

            return true; //Change this to return based of whether it's really successful or not
        }

        /**
         * @brief Storing info from SOUNDINFO into a file
         * @param writer 
         * @return true when success.
        */
        virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
        {
            writer->Key("PositionX");
            writer->Double(static_cast<float>(position[0]));

            return true; //Change this to return based of whether it's really successful or not
        }

        // convenience method to set the 3D coordinates of the sound.
        void set3DCoords(float x, float y, float z)
        {
            position.Set(x, y, z);
        }

        bool isLoaded()
        {
            return (whatState == SOUND_LOADED);
        }

        bool is3D()
        {
            return isit3D;
        }

        bool isLoop()
        {
            return isitLoop;
        }

        bool isPlaying()
        {
            return (whatState == SOUND_PLAYING);
        }

        unsigned int getUniqueID()
        {
            return uniqueID;
        }

        std::string getFilePath()
        {
            return filePath;
        }

        const char* getFilePath_inChar()
        {
            const char* name = filePath.c_str();

            return name;
        }

        float getX()
        {
            return position[0]; //!!!!!!!To be replaced when vec container is used
        }

        float getY()
        {
            return position[1]; //!!!!!!!To be replaced when vec container is used
        }

        float getZ()
        {
            return position[2]; //!!!!!!!To be replaced when vec container is used
        }

        float getReverbAmount()
        {
            return ReverbAmount;
        }

        float getVolume()
        {
            return volume;
        }

        /**
        * Parameter takes in Volume values (0 - 100)
        */
        void setVolume(float vol)
        {
            volume = 20.0f * log10f(vol);

            if (volume > 150.f)
            {
                volume = 149.f;
            }
        }

        void setMSLength(unsigned int len)
        {
            MSLength = len;
        }

        void setState(SOUND_STATE setting)
        {
            whatState = setting;
        }

        void setLoop(bool condition)
        {
            isitLoop = condition;
        }

        void set3D(bool condition)
        {
            isit3D = condition;
        }

        SoundInfo(std::string _filePath = "", bool _isLoop = false, bool _is3D = false, SOUND_STATE _theState = SOUND_UNLOAD, float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _volume = 50.f, float _reverbamount = 0.f)
            : filePath(_filePath), isitLoop(_isLoop), isit3D(_is3D), whatState(_theState), volume(_volume), ReverbAmount(_reverbamount)  //!!!!!!!To be replaced when vec container is used
        {
            if (filePath != "")
            {
                whatState = SOUND_LOADED;
            }
            
            position.Set(_x, _y, _z);
            MSLength = 0;
            uniqueID = ID_Count++; //Change UID to include time when added
        }

        // TODO  implement sound instancing
        // int instanceID = -1; 
        void operator=(const SoundInfo& rhs)
        {
            uniqueID = rhs.uniqueID;
            MSLength = rhs.MSLength;
            filePath = rhs.filePath;
            isitLoop = rhs.isitLoop;
            isit3D = rhs.isit3D;
            whatState = rhs.whatState;
            position = rhs.position;
            volume = rhs.volume;
            ReverbAmount = rhs.ReverbAmount;
        }

    };
}

#endif