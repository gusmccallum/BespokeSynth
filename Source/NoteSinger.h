/**
    bespoke synth, a software modular synthesizer
    Copyright (C) 2021 Ryan Challinor (contact: awwbees@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
//
//  NoteSinger.h
//  modularSynth
//
//  Created by Ryan Challinor on 5/23/13.
//
//

#ifndef __modularSynth__NoteSinger__
#define __modularSynth__NoteSinger__

#include <iostream>
#include "IAudioReceiver.h"
#include "INoteSource.h"
#include "Slider.h"
#include "Checkbox.h"
#include "IDrawableModule.h"
#include "RadioButton.h"
#include "ClickButton.h"
#include "INoteReceiver.h"
#include "Transport.h"
#include "BiquadFilter.h"
#include "PeakTracker.h"
#include "Scale.h"

#define NOTESINGER_MAX_BUCKETS 40

class NoteSinger : public IAudioReceiver, public INoteSource, public IIntSliderListener, public IFloatSliderListener, public IDrawableModule, public IRadioButtonListener, public IButtonListener, public IAudioPoller, public IScaleListener
{
public:
   NoteSinger();
   ~NoteSinger();
   static IDrawableModule* Create() { return new NoteSinger(); }
   
   
   void CreateUIControls() override;
   void Init() override;

   //IAudioReceiver
   InputMode GetInputMode() override { return kInputMode_Mono; }

   //IAudioPoller
   void OnTransportAdvanced(float amount) override;
   
   //IScaleListener
   void OnScaleChanged() override;

   void SetEnabled(bool enabled) override { mEnabled = enabled; }
   
   void CheckboxUpdated(Checkbox* checkbox) override;
   //IIntSliderListener
   void IntSliderUpdated(IntSlider* slider, int oldVal) override {}
   //IFloatSliderListener
   void FloatSliderUpdated(FloatSlider* slider, float oldVal) override {}
   //IRadioButtonListener
   void RadioButtonUpdated(RadioButton* radio, int oldVal) override {}
   //IButtonListener
   void ButtonClicked(ClickButton* button) override;
   
   virtual void LoadLayout(const ofxJSONElement& moduleInfo) override;
   virtual void SetUpFromSaveData() override;
   
   
private:
   //IDrawableModule
   void DrawModule() override;
   void GetModuleDimensions(float& width, float& height) override { width=100; height=50; }
   bool Enabled() const override { return mEnabled; }
   
   int GetPitchForBucket(int bucket);

   int mOctave;
   IntSlider* mOctaveSlider;

   int mPitch;

   float* mWorkBuffer;

   int mNumBuckets;
   BiquadFilter mBands[NOTESINGER_MAX_BUCKETS];
   PeakTracker mPeaks[NOTESINGER_MAX_BUCKETS];
};


#endif /* defined(__modularSynth__NoteSinger__) */

