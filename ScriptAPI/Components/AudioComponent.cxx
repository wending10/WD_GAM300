#include "AudioComponent.hxx"

namespace ScriptAPI
{
	void AudioComponent::set3DCoords(float x, float y, float z)
	{
		position = Vector3({ x, y, z });
	}

	bool AudioComponent::isLoaded()
	{
		return (whatState == TDS::SOUND_LOADED);
	}

	bool AudioComponent::is3D()
	{
		return isit3D;
	}

	bool AudioComponent::isMuted()
	{
		return isitMuted;
	}

	bool AudioComponent::isPlaying()
	{
		return (whatState == TDS::SOUND_PLAYING);
	}

	bool AudioComponent::isPaused()
	{
		return (whatState == TDS::SOUND_PAUSE);
	}

	snd AudioComponent::getState()
	{
		return whatState;
	}

	unsigned int AudioComponent::getUniqueID()
	{
		return uniqueID;
	}

	unsigned int AudioComponent::getMSLength()
	{
		return MSLength;
	}

	std::string AudioComponent::getFilePath()
	{
		return filePath;
	}

	const char* AudioComponent::getFilePath_inChar()
	{
		return filePath.c_str();
	}

	float AudioComponent::getX()
	{
		return position.X;
	}

	float AudioComponent::getY()
	{
		return position.Y;
	}

	float AudioComponent::getZ()
	{
		return position.Z;
	}

	float AudioComponent::getReverbAmount()
	{
		return ReverbAmount;
	}

	float AudioComponent::getVolume()
	{
		return volume;
	}

	void AudioComponent::setVolume(float vol)
	{
		volume = vol;
	}

	void AudioComponent::setMSLength(unsigned int len)
	{
		MSLength = len;
	}

	void AudioComponent::setState(snd setting)
	{
		whatState = setting;
	}

	void AudioComponent::setLoop(bool condition)
	{
		isitLoop = condition;
	}

	void AudioComponent::set3D(bool condition)
	{
		isit3D = condition;
	}

	void AudioComponent::setMute(bool condition)
	{
		isitMuted = condition;
	}

	AudioComponent::AudioComponent(TDS::EntityID ID)
	{
		entityID = ID;
	}

	TDS::EntityID AudioComponent::GetEntityID()
	{
		return entityID;
	}

	//unique ID
	unsigned int AudioComponent::uniqueID::get()
	{
		return TDS::GetSoundInfo(entityID)->getUniqueID();
	}

	//MS Length
	unsigned int AudioComponent::MSLength::get()
	{
		return TDS::GetSoundInfo(entityID)->getMSLength();
	}
	void AudioComponent::MSLength::set(unsigned int value)
	{
		TDS::GetSoundInfo(entityID)->setMSLength(value);
	}

	//file path
	std::string AudioComponent::filePath::get()
	{
		return TDS::GetSoundInfo(entityID)->getFilePath();
	}

	//loop
	bool AudioComponent::isitLoop::get()
	{
		return TDS::GetSoundInfo(entityID)->isLoop();
	}
	void AudioComponent::isitLoop::set(bool value)
	{
		TDS::GetSoundInfo(entityID)->setLoop(value);
	}

	//3D boolean
	bool AudioComponent::isit3D::get()
	{
		return TDS::GetSoundInfo(entityID)->is3D();
	}
	void AudioComponent::isit3D::set(bool value)
	{
		TDS::GetSoundInfo(entityID)->set3D(value);
	}

	//muted
	bool AudioComponent::isitMuted::get()
	{
		return TDS::GetSoundInfo(entityID)->isMuted();
	}
	void AudioComponent::isitMuted::set(bool value)
	{
		TDS::GetSoundInfo(entityID)->setMute(value);
	}

	//state of sound info
	snd AudioComponent::whatState::get()
	{
		return TDS::GetSoundInfo(entityID)->getState();
	}
	void AudioComponent::whatState::set(snd value)
	{
		TDS::GetSoundInfo(entityID)->setState(value);
	}

	//3D position
	Vector3 AudioComponent::position::get()
	{
		auto[x, y, z] = TDS::GetSoundInfo(entityID)->getPosition();

		return Vector3(x, y, z);
	}
	void AudioComponent::position::set(Vector3 value)
	{
		float x = value.X, y = value.Y, z = value.Z;

		TDS::GetSoundInfo(entityID)->set3DCoords(x, y, z);
	}

	//volume
	float AudioComponent::volume::get()
	{
		return TDS::GetSoundInfo(entityID)->getVolume();
	}
	void AudioComponent::volume::set(float value)
	{
		TDS::GetSoundInfo(entityID)->setVolume(value);
	}

	//Reverb
	float AudioComponent::ReverbAmount::get()
	{
		return TDS::GetSoundInfo(entityID)->getReverbAmount();
	}
	void AudioComponent::ReverbAmount::set(float value)
	{
		TDS::GetSoundInfo(entityID)->setReverbAmount(value);
	}
}