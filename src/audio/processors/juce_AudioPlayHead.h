/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-11 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#ifndef __JUCE_AUDIOPLAYHEAD_JUCEHEADER__
#define __JUCE_AUDIOPLAYHEAD_JUCEHEADER__


//==============================================================================
/**
    A subclass of AudioPlayHead can supply information about the position and
    status of a moving play head during audio playback.

    One of these can be supplied to an AudioProcessor object so that it can find
    out about the position of the audio that it is rendering.

    @see AudioProcessor::setPlayHead, AudioProcessor::getPlayHead
*/
class JUCE_API  AudioPlayHead
{
protected:
    //==============================================================================
    AudioPlayHead() {}

public:
    virtual ~AudioPlayHead() {}

    //==============================================================================
    /** Frame rate types. */
    enum FrameRateType
    {
        fps24           = 0,
        fps25           = 1,
        fps2997         = 2,
        fps30           = 3,
        fps2997drop     = 4,
        fps30drop       = 5,
        fpsUnknown      = 99
    };

    //==============================================================================
    /** This structure is filled-in by the AudioPlayHead::getCurrentPosition() method.
    */
    struct CurrentPositionInfo
    {
        /** The tempo in BPM */
        double bpm;

        /** Time signature numerator, e.g. the 3 of a 3/4 time sig */
        int timeSigNumerator;
        /** Time signature denominator, e.g. the 4 of a 3/4 time sig */
        int timeSigDenominator;

        /** The current play position, in seconds from the start of the edit. */
        double timeInSeconds;

        /** For timecode, the position of the start of the edit, in seconds from 00:00:00:00. */
        double editOriginTime;

        /** The current play position in pulses-per-quarter-note.

            This is the number of quarter notes since the edit start.
        */
        double ppqPosition;

        /** The position of the start of the last bar, in pulses-per-quarter-note.

            This is the number of quarter notes from the start of the edit to the
            start of the current bar.

            Note - this value may be unavailable on some hosts, e.g. Pro-Tools. If
            it's not available, the value will be 0.
        */
        double ppqPositionOfLastBarStart;

        /** The video frame rate, if applicable. */
        FrameRateType frameRate;

        /** True if the transport is currently playing. */
        bool isPlaying;

        /** True if the transport is currently recording.

            (When isRecording is true, then isPlaying will also be true).
        */
        bool isRecording;

        //==============================================================================
        bool operator== (const CurrentPositionInfo& other) const throw();
        bool operator!= (const CurrentPositionInfo& other) const throw();

        void resetToDefault();
    };

    //==============================================================================
    /** Fills-in the given structure with details about the transport's
        position at the start of the current processing block.
    */
    virtual bool getCurrentPosition (CurrentPositionInfo& result) = 0;
};


#endif   // __JUCE_AUDIOPLAYHEAD_JUCEHEADER__
