/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <system\lstream.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class Stream :                                          */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
Stream::Stream(const string& filename, bool read, unsigned int bufferSize) 
: m_fileHandle(0), m_bufferSize(bufferSize), m_sharedLinks(0)
{
	m_buffer = new char[m_bufferSize];
	errno_t r = fopen_s(&m_fileHandle, filename.c_str(), (read) ? "rb" : "wb");
	if (read)
	{
		// fill the buffer:
		m_localBufferPos = m_bufferSize;
		m_filePos = 0;
		readBuffer();
	}
}
/* ------------------------------------------------------- */
Stream::~Stream()
{
	delete m_buffer;
	delete m_sharedLinks;
	fclose(m_fileHandle);
}
/* ------------------------------------------------------- */
/*Serializable* Stream::readNext(int pos)
{
	String className;
	bool topLevel;
	read(className);
	topLevel = (className == "$ROOT$");
	if (topLevel)
	{
		read(className);
		pos += String("$ROOT$").getDiskUsed();
	}

	FactoryFunction factory = s_factory.get(className);
	if (!factory)
		throw ClassNotFoundException("Class " + className.toString() + " is not registered");

	Serializable* object = factory(*this);
	unsigned int read = m_filePos - pos;
	assert(read == object->getDiskUsed());

	if (topLevel)
	{
		Spatial* tl = dynamic_cast<Spatial*>(object);
		assert(tl);
		m_topLevel.append(tl);
	}
	return object;
}
/* ------------------------------------------------------- */
/*void Stream::load(const string& filename)
{
	errno_t r = fopen_s(&m_input, filename.c_str(), "rb");
	if (r != 0)
	{
		throw Exception("Could not open file: " + filename + "for reading");
	}

	m_localBufferPos = m_bufferSize;
	m_filePos = 0;
	readBuffer();
	read(m_fileSize);
	int objectCount;
	read(objectCount);

	m_sharedLinks = new HashTable<Serializable*, Ptr<Serializable> >((int)(objectCount*1.3));

	
	Serializable* object;
	while (m_filePos < m_fileSize)
	{
		readNext(m_filePos);
	}

	HashTable<Serializable*, Serializable*>::Iterator i = m_objectLinks->begin();
	while (i)
	{
		i.getValue()->link(*this);
		i++;
	}
	
	fclose(m_input);
	m_input = 0;
	delete m_objectLinks;
	delete m_sharedLinks;
}
/* ------------------------------------------------------- */
/*void Stream::save(const string& filename)
{
	errno_t r = fopen_s(&m_output, filename.c_str(), "wb");
	if (r != 0)
	{
		throw IOException("Could not open file: " + filename + "for writing");
	}

	m_localBufferPos = 0;
	m_filePos = 0;
	m_fileSize = 0;
	
	GraphTraverser<DiskSpaceEstimator> dsTrav;
	int additionalSum = 0;
	for (Set<Serializable*>::Iterator i = m_topLevel.begin(); i != false; i++)
	{
		Spatial* tmpSpatial = dynamic_cast<Spatial*>(*i);
		if (tmpSpatial)
			dsTrav.apply(tmpSpatial);
		else
			additionalSum += (*i)->getDiskUsed();
	}

	m_fileSize = dsTrav.getOperation().getSum();
	m_fileSize += ROOT.getDiskUsed()*m_topLevel.size();
	m_fileSize += sizeof(int)*2; // the header size	
	
	write(m_fileSize);
	write(dsTrav.objectCount());

	Saver saver(*this);
	GraphTraverser<Saver> sTrav(saver);
	for (Set<Serializable*>::Iterator i = m_topLevel.begin(); i != false; i++)
	{
		Spatial* tmpSpatial = dynamic_cast<Spatial*>(*i);
		if (tmpSpatial)
			sTrav.apply(tmpSpatial);
		else
			saver(*i);
	}
	
	writeBuffer();

	fclose(m_output);
	m_output = 0;
}
/* ------------------------------------------------------- */
bool Stream::endOfStream()
{
	return (feof(m_fileHandle) != 0);
}
/* ------------------------------------------------------- */
void Stream::write(const String& value)
{
	write(value.length());
	write(value.toCharArray(), value.length());
}
/* ------------------------------------------------------- */
void Stream::read(String& value)
{
	int len;
	read(len);
	char* carr = new char[len+1];
	read(carr, len);
	carr[len] = '\0';
	value = String(carr);
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/*                      PRIVATE                            */
/* ------------------------------------------------------- */
void Stream::readBuffer()
{
	assert(m_fileHandle);
	// copy the part of the buffer that hasn't been read
	int rest = m_bufferSize - m_localBufferPos;
	assert(rest >= 0);
	if (rest > 0)
	{
		memcpy(m_buffer, m_buffer + m_localBufferPos, rest);		
	}
	m_localBufferPos = 0;
	
	// fill the rest of the buffer with new data from disk
	int diskRead = m_bufferSize - rest;
	fread(m_buffer + rest, sizeof(char), diskRead, m_fileHandle);
}
/* ------------------------------------------------------- */
void Stream::writeBuffer()
{
	assert(m_fileHandle);
	if (m_localBufferPos > 0)
	{
		fwrite(m_buffer, sizeof(char), m_localBufferPos, m_fileHandle);
		m_localBufferPos = 0;
	}
}
/* ------------------------------------------------------- */
void Stream::writeToBuffer(const void* src, unsigned int bytes)
{
	m_filePos += bytes;

	unsigned int bspace =  m_bufferSize - m_localBufferPos;
	unsigned int written = 0;
	const char* source = reinterpret_cast<const char*>(src);
	while (bytes > bspace)
	{
		memcpy(m_buffer + m_localBufferPos, source + written, bspace);
		m_localBufferPos = m_bufferSize;
		writeBuffer();
		bytes -= bspace;
		written += bspace;
		bspace = m_bufferSize;
	}
	memcpy(m_buffer + m_localBufferPos, source + written, bytes);
	m_localBufferPos += bytes;
	
}
/* ------------------------------------------------------- */
void Stream::readFromBuffer(void* dst, unsigned int bytes)
{
	m_filePos += bytes;
	unsigned int bspace =  m_bufferSize - m_localBufferPos;
	unsigned int read = 0;

	char* target = reinterpret_cast<char*>(dst);

	while (bytes > bspace)
	{
		memcpy(target + read, m_buffer + m_localBufferPos, bspace);
		m_localBufferPos = m_bufferSize;
		readBuffer();
		bytes -= bspace;
		read += bspace;
		bspace = m_bufferSize;
	}
	memcpy(target + read, m_buffer + m_localBufferPos, bytes);
	m_localBufferPos += bytes;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class DiskSpaceEstimator:                               */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
/*DiskSpaceEstimator::DiskSpaceEstimator()
: m_sum(0)
{
}
/* ------------------------------------------------------- */
/*bool DiskSpaceEstimator::operator()(Serializable* obj)
{
	m_sum += obj->getDiskUsed();	
	return true;
}
/* ------------------------------------------------------- */
/*int DiskSpaceEstimator::getSum()
{
	return m_sum;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class Saver:                                            */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
/*Saver::Saver(Stream& stream)
: m_stream(stream)
{
}
/* ------------------------------------------------------- */
/*bool Saver::operator()(Serializable* obj)
{
	m_tmpSpatial = dynamic_cast<Spatial*>(obj);
	if (m_tmpSpatial && m_stream.contains(m_tmpSpatial)) 
	{
		m_stream.write(Stream::ROOT);
	}		

	unsigned int begin = m_stream.m_filePos;
	obj->save(m_stream);
	unsigned int written = m_stream.m_filePos - begin;
	assert(written == obj->getDiskUsed());
	
	return true;
}
/* ------------------------------------------------------- */