//#include "AudioComponent.hxx"
//
//namespace ScriptAPI
//{
//	void AudioComponent::set3DCoords(float x, float y, float z)
//	{
//		position = Vector3({ x, y, z });
//	}
//
//	bool AudioComponent::isLoaded()
//	{
//		return (whatState == TDS::SOUND_LOADED);
//	}
//
//	bool AudioComponent::is3D()
//	{
//		return isit3D;
//	}
//
//	bool AudioComponent::isMuted()
//	{
//		return isitMuted;
//	}
//
//	bool AudioComponent::isPlaying()
//	{
//		return (whatState == TDS::SOUND_PLAYING);
//	}
//
//	bool AudioComponent::isPaused()
//	{
//		return (whatState == TDS::SOUND_PAUSE);
//	}
//
//	snd AudioComponent::getState()
//	{
//		return whatState;
//	}
//
//	unsigned int AudioComponent::getUniqueID()
//	{
//		return uniqueID;
//	}
//
//	unsigned int AudioComponent::getMSLength()
//	{
//		return MSLength;
//	}
//
//	std::string AudioComponent::getFilePath()
//	{
//		return filePath;
//	}
//
//	const char* AudioComponent::getFilePath_inChar()
//	{
//		return filePath.c_str();
//	}
//
//	float AudioComponent::getX()
//	{
//		return position.X;
//	}
//
//	float AudioComponent::getY()
//	{
//		return position.Y;
//	}
//
//	float AudioComponent::getZ()
//	{
//		return position.Z;
//	}
//
//	float AudioComponent::getReverbAmount()
//	{
//		return ReverbAmount;
//	}
//
//	float AudioComponent::getVolume()
//	{
//		return volume;
//	}
//
//	void AudioComponent::setVolume(float vol)
//	{
//		volume = vol;
//	}
//
//	void AudioComponent::setMSLength(unsigned int len)
//	{
//		MSLength = len;
//	}
//
//	void AudioComponent::setState(snd setting)
//	{
//		whatState = setting;
//	}
//
//	void AudioComponent::setLoop(bool condition)
//	{
//		isitLoop = condition;
//	}
//
//	void AudioComponent::set3D(bool condition)
//	{
//		isit3D = condition;
//	}
//
//	void AudioComponent::setMute(bool condition)
//	{
//		isitMuted = condition;
//	}
//
//	AudioComponent::AudioComponent(TDS::EntityID ID)
//	{
//		entityID = ID;
//	}
//
//	TDS::EntityID AudioComponent::GetEntityID()
//	{
//		return entityID;
//	}
//
//	unsigned int AudioComponent::uniqueID::get()
//	{
//		return TDS::GetSoundInfo(entityID)->getUniqueID();
//	}
//
//	unsigned int AudioComponent::MSLength::get()
//	{
//		return TDS::GetSoundInfo(entityID)->getMSLength();
//	}
//	void AudioComponent::MSLength::set(unsigned int value)
//	{
//		TDS::GetSoundInfo(entityID)->setMSLength(value);
//	}
//
//	std::string AudioComponent::filePath::get()
//	{
//		return TDS::GetSoundInfo(entityID)->getFilePath();
//	}
//
//	bool AudioComponent::isitLoop::get()
//	{
//		return TDS::GetSoundInfo(entityID)->isLoop();
//	}
//	void AudioComponent::isitLoop::set(bool value)
//	{
//		TDS::GetSoundInfo(entityID)->setLoop(value);
//	}
//
//
//}