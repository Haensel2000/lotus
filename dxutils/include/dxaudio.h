#pragma once

#include "dmutil.h"
#include "dxbasic.h"
#include "dxdisplay.h"
#include <vector>
#include <map>
#include <string>

namespace DX
{
	using std::vector;
	using std::map;
	using std::string;

	class AudioManager
	{
		private:
			CMusicManager* musicManager;
			unsigned maxSources;
			vector<IDirectMusicAudioPath*> audioPaths;
			vector<IDirectSound3DBuffer*> buffers;
			IDirectSound3DListener* listener;
			vector<DS3DBUFFER> bufferParams;
			DS3DLISTENER listenerParams;
			DisplayDevice* device;
			int current;
			map<string, CMusicSegment*> segments;
			void createObjects(int from, int to);
		public:
			AudioManager(HWND windowHandle, DisplayDevice* device, unsigned maxSources = 10);
			~AudioManager();
			void reserve(unsigned val);
			void resize(unsigned val);
			void set3DSoundParameters(float dopplerFactor, float rollOffFactor, 
				float minDistance, float maxDistance);
			void createFromFile(string id, wchar_t* fileName);
			void play(string id, bool repeat = false);
			void stop(string id);
			void setVolume(unsigned volume);
			void play3D(string id, D3DXVECTOR3 position, D3DXVECTOR3 velocity, bool repeat = false);
			void set3DSound(string id, D3DXVECTOR3 position, D3DXVECTOR3 velocity, bool repeat = false);
			//void doFrame();
	};
}