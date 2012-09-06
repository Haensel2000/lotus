/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LSTREAM_H
#define _HDR_LSTREAM_H

#include <system\lcontainer.h>
#include <system\lpointer.h>

#include <fstream>
#include <iostream>

using std::fstream;
using std::cout;

namespace Lotus
{

	class Serializable;
	class Stream;
	class Spatial;
	class Renderer;

	class Saver;

	/* class Stream
	 * A class to facilitate data reading and writing. */
	class Stream
	{
	private:
		HashTable<Serializable*, Ptr<Serializable> >* m_sharedLinks;

		char* m_buffer;
		unsigned int m_bufferSize;
		//unsigned int m_fileSize;
		unsigned int m_localBufferPos;
		

		FILE* m_fileHandle;

		void readBuffer();
		void writeBuffer();

		void writeToBuffer(const void* src, unsigned int bytes);
		void readFromBuffer(void* dst, unsigned int bytes);
	protected:
		unsigned int m_filePos;
	public:
		static const unsigned int BUFFER_SIZE = 1025;

		Stream(const string& filename, bool read = true, unsigned int bufferSize = BUFFER_SIZE);
		~Stream();

		//Serializable* readNext(int pos);

		//void load(const string& filename);
		//void save(const string& filename);

		bool endOfStream();


		// read and write functions:
		/* This function is applicable to all types that are native
		 * or consist only of native components without virtual functions */
		template <class T> void write(const T& value);
		template <class T> void write(const Ptr<T> value);
		template <class T> void write(const T* arr, int length);
		template <class T> void write(const List<T>& list);
		template <class T> void write(const Array<T>& arr);
		void write(const String& value);
		
		template <class T> void read(T& value);
		template <class T> void read(Ptr<T>& value);
		template <class T> void read(T* arr, int length);
		template <class T> void read(List<T>& list);
		template <class T> void read(Array<T>& arr);
		void read(String& value);

		template <class T> static unsigned int getDiskUsed(const T& obj = T());
		template <class T> static unsigned int getDiskUsed(const Ptr<T>& obj = Ptr<T>());

		friend Saver;
	};

#include "lstream.inl"

	/* Template Functions for the traversals */
	/*class DiskSpaceEstimator
	{
	private:
		int m_sum;
	public:
		DiskSpaceEstimator();
		bool operator()(Serializable* obj);
		int getSum();
	};

	class Saver
	{
	private:
		Spatial* m_tmpSpatial;
		Stream& m_stream;
	public:
		Saver(Stream& stream);
		bool operator()(Serializable* obj);
	};*/
}

#endif