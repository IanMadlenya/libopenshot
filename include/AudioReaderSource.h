/**
 * @file
 * @brief Header file for AudioReaderSource class
 * @author Jonathan Thomas <jonathan@openshot.org>
 *
 * @section LICENSE
 *
 * Copyright (c) 2008-2013 OpenShot Studios, LLC
 * (http://www.openshotstudios.com). This file is part of
 * OpenShot Library (http://www.openshot.org), an open-source project
 * dedicated to delivering high quality video editing and animation solutions
 * to the world.
 *
 * OpenShot Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenShot Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenShot Library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OPENSHOT_AUDIOREADERSOURCE_H
#define OPENSHOT_AUDIOREADERSOURCE_H

/// Do not include the juce unittest headers, because it collides with unittest++
#define __JUCE_UNITTEST_JUCEHEADER__

#ifndef _NDEBUG
	/// Define NO debug for JUCE on mac os
	#define _NDEBUG
#endif

#include <iomanip>
#include "JuceLibraryCode/JuceHeader.h"
#include "ReaderBase.h"

using namespace std;

/// This namespace is the default namespace for all code in the openshot library
namespace openshot
{

	/**
	 * @brief This class is used to expose any ReaderBase derived class as an AudioSource in JUCE.
	 *
	 * This allows any reader to play audio through JUCE (our audio framework).
	 */
	class AudioReaderSource : public PositionableAudioSource
	{
	private:
		int position;
		int start;
		bool repeat;
		AudioSampleBuffer *buffer;

		int size; /// The size of the buffer
		ReaderBase *reader; /// The reader to pull samples from
		int64 frame_number; /// The current frame to read from
		tr1::shared_ptr<Frame> frame; /// The current frame object that is being read

		/// Get more samples from the reader
		void GetMoreSamplesFromReader();

	public:

		/// @brief Constructor that reads samples from a reader
		/// @param reader This reader provides constant samples from a ReaderBase derived class
		/// @param starting_frame_number This is the frame number to start reading samples from the reader.
		AudioReaderSource(ReaderBase *audio_reader, int64 starting_frame_number, int buffer_size);

		/// Destructor
		~AudioReaderSource();

		/// @brief Get the next block of audio samples
		/// @param info This struct informs us of which samples are needed next.
		void getNextAudioBlock (const AudioSourceChannelInfo& info);

		/// Prepare to play this audio source
		void prepareToPlay(int, double);

		/// Release all resources
		void releaseResources();

		/// @brief Set the next read position of this source
		/// @param newPosition The sample # to start reading from
		void setNextReadPosition (long long newPosition);

		/// Get the next read position of this source
		long long getNextReadPosition() const;

		/// Get the total length (in samples) of this audio source
		long long getTotalLength() const;

		/// Determines if this audio source should repeat when it reaches the end
		bool isLooping() const;

		/// @brief Set if this audio source should repeat when it reaches the end
		/// @param shouldLoop Determines if the audio source should repeat when it reaches the end
		void setLooping (bool shouldLoop);

		/// Update the internal buffer used by this source
		void setBuffer (AudioSampleBuffer *audio_buffer);
	};

}

#endif
