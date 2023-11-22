//#pragma once
//
//#include "../IncludeFromEngine.hxx"
//#include "../Vector3.hxx"
//
//namespace ScriptAPI
//{
//	using snd = TDS::SOUND_STATE;
//	
//	public value class AudioComponent
//	{
//	public:
//		void set3DCoords(float x, float y, float z);
//
//		bool isLoaded();
//		bool is3D();
//		bool isLoop();
//		bool isMuted();
//		bool isPlaying();
//		bool isPaused();
//
//		snd getState();
//		unsigned int getUniqueID();
//		std::string getFilePath();
//		const char* getFilePath_inChar();
//
//		float getX();
//		float getY();
//		float getZ();
//		float getReverbAmount();
//		float getVolume();
//
//		void setVolume(float vol);
//		void setMSLength(unsigned int len);
//		void setState(snd setting);
//		void setLoop(bool condition);
//		void set3D(bool condition);
//		void setMute(bool condition);
//
//	internal:
//		AudioComponent(TDS::EntityID ID);
//		TDS::EntityID GetEntityID();
//
//	private:
//		property unsigned int uniqueID
//		{
//			unsigned int get();
//			void set(unsigned int value);
//		}
//
//		property unsigned int MSLength
//		{
//			unsigned int get();
//			void set(unsigned int value);
//		}
//	};
//}