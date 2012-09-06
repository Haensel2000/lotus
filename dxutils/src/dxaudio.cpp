#include "..\include\dxaudio.h"

using namespace DX;

void AudioManager::createObjects(int offset, int count)
{
	IDirectMusicPerformance8* performance = musicManager->GetPerformance();	
	for (int i = offset; i < offset+count; i++)
	{
		performance->CreateStandardAudioPath(DMUS_APATH_DYNAMIC_3D, 1, TRUE, &audioPaths[i]);
		
		audioPaths[i]->GetObjectInPath(0, DMUS_PATH_BUFFER, 0, GUID_NULL, 0, IID_IDirectSound3DBuffer,
			reinterpret_cast<void**>(&buffers[i]));
		bufferParams[i].dwSize = sizeof(DS3DBUFFER);
		buffers[i]->GetAllParameters(&bufferParams[i]);
		bufferParams[i].dwMode = DS3DMODE_NORMAL;
		buffers[i]->SetAllParameters(&bufferParams[i], DS3D_IMMEDIATE);

		audioPaths[i]->GetObjectInPath(0, DMUS_PATH_PRIMARY_BUFFER, 0, GUID_NULL, 0, 
			IID_IDirectSound3DListener, reinterpret_cast<void**>(&listener));
		listenerParams.vOrientTop = VERTICAL;
		listenerParams.vOrientFront = FRONT;
		listener->SetOrientation(listenerParams.vOrientFront.x, listenerParams.vOrientFront.y, 
			listenerParams.vOrientFront.z, listenerParams.vOrientTop.x, listenerParams.vOrientTop.y, 
			listenerParams.vOrientTop.z, DS3D_IMMEDIATE);
	}
}




AudioManager::AudioManager(HWND windowHandle, DisplayDevice* device, unsigned maxSources) : maxSources(maxSources), device(device)
{
	current = 0;	
	musicManager = new CMusicManager();
	musicManager->Initialize(windowHandle);
	audioPaths.resize(maxSources);
	buffers.resize(maxSources);
	bufferParams.resize(maxSources);
	createObjects(0, maxSources);	
}

AudioManager::~AudioManager()
{
	if (musicManager)
		musicManager->StopAll();

	if (listener)
		listener->Release();
	for (int i = 0; i < maxSources; i++)
	{
		if (buffers[i])
			buffers[i]->Release();
		if (audioPaths[i])
			audioPaths[i]->Release();
	}

	for (map<string, CMusicSegment*>::iterator iter = segments.begin(); iter != segments.end(); iter++)
	{
		delete iter->second;
	}

	if (musicManager)
		delete musicManager;
}

void AudioManager::reserve(unsigned val)
{	
	audioPaths.resize(maxSources+val);
	buffers.resize(maxSources+val);
	bufferParams.resize(maxSources+val);
	createObjects(maxSources, val);
	maxSources += val;
}

void AudioManager::resize(unsigned val)
{
	audioPaths.resize(val);
	buffers.resize(val);
	bufferParams.resize(val);
	createObjects(0, val);
	maxSources = val;
}

void AudioManager::set3DSoundParameters(float dopplerFactor, float rollOffFactor, float minDistance,
	float maxDistance)
{
	listenerParams.flDopplerFactor = dopplerFactor;
	listenerParams.flRolloffFactor = rollOffFactor;
	listenerParams.vPosition.x = 0;
	listenerParams.vPosition.y = 0;
	listenerParams.vPosition.z = 0;
	if (listener)
		listener->SetAllParameters(&listenerParams, DS3D_IMMEDIATE);
	for (int i = 0; i < maxSources; i++)
	{
		bufferParams[i].flMinDistance = minDistance;
		bufferParams[i].flMaxDistance = maxDistance;
		if (buffers[i])
			buffers[i]->SetAllParameters(&bufferParams[i], DS3D_IMMEDIATE);
	}
}

void AudioManager::createFromFile(string id, wchar_t* fileName)
{
	segments[id] = 0;
	CMusicSegment* tmp;
	musicManager->CreateSegmentFromFile(&tmp, fileName);
	segments[id] = tmp;
}

void AudioManager::play(string id, bool repeat)
{
	if (segments.find(id) != segments.end())
	{
		segments[id]->Stop(DMUS_SEGF_DEFAULT);
		segments[id]->SetRepeats((repeat) ? DMUS_SEG_REPEAT_INFINITE : 0);
		segments[id]->Play(DMUS_SEGF_DEFAULT);
	}
}

void AudioManager::stop(string id)
{
	if (segments.find(id) != segments.end())
		segments[id]->Stop();
}

void AudioManager::setVolume(unsigned volume)
{
	if (segments.begin() != segments.end())
		segments.begin()->second->SetVol(volume);
}

void AudioManager::play3D(string id, D3DXVECTOR3 position, D3DXVECTOR3 velocity, bool repeat)
{
	bufferParams[current].vPosition = position - device->getCamera()->getPosition();
	bufferParams[current].vVelocity = mul(device->getCamera()->getMatrix(), velocity);
	if (buffers[current])
	{
		buffers[current]->SetPosition(bufferParams[current].vPosition.x, 
			bufferParams[current].vPosition.y, bufferParams[current].vPosition.z, DS3D_IMMEDIATE);
		buffers[current]->SetVelocity(bufferParams[current].vVelocity.x, 
			bufferParams[current].vVelocity.y, bufferParams[current].vVelocity.z, DS3D_IMMEDIATE);
	}
	if (segments.find(id) != segments.end())
	{
		segments[id]->SetRepeats((repeat) ? DMUS_SEG_REPEAT_INFINITE : 0);
		segments[id]->Play(DMUS_SEGF_SECONDARY, audioPaths[current]);
		current = (current+1)%maxSources;
	}
}
