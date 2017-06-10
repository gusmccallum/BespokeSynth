/*
  ==============================================================================

    RadioSequencer.h
    Created: 10 Jun 2017 4:53:13pm
    Author:  Ryan Challinor

  ==============================================================================
*/

#pragma once

#include <iostream>
#include "IDrawableModule.h"
#include "Grid.h"
#include "ClickButton.h"
#include "Checkbox.h"
#include "Transport.h"
#include "DropdownList.h"

class PatchCableSource;

class RadioSequencer : public IDrawableModule, public ITimeListener, public IDropdownListener, public GridListener
{
public:
   RadioSequencer();
   ~RadioSequencer();
   static IDrawableModule* Create() { return new RadioSequencer(); }
   
   string GetTitleLabel() override { return "radio sequencer"; }
   void CreateUIControls() override;
   
   //IGridListener
   void GridUpdated(Grid* grid, int col, int row, float value, float oldValue) override;
   
   //IDrawableModule
   void Init() override;
   void Poll() override;
   bool IsResizable() const override { return true; }
   void Resize(float w, float h) override;
   void SetEnabled(bool enabled) override { mEnabled = enabled; }
   
   //ITimeListener
   void OnTimeEvent(int samplesTo) override;
   
   void CheckboxUpdated(Checkbox* checkbox) override {}
   void DropdownUpdated(DropdownList* list, int oldVal) override;
   
   void LoadLayout(const ofxJSONElement& moduleInfo) override;
   void SaveLayout(ofxJSONElement& moduleInfo) override;
   void SetUpFromSaveData() override;
   
   void SaveState(FileStreamOut& out) override;
   void LoadState(FileStreamIn& in) override;
   
   //IPatchable
   void PostRepatch(PatchCableSource* cableSource) override;
   
private:
   void SetGridSize(float w, float h);
   void SetNumSteps(int numSteps, bool stretch);
   void SyncControlCablesToGrid();
   
   //IDrawableModule
   void DrawModule() override;
   bool Enabled() const override { return mEnabled; }
   void GetModuleDimensions(int& w, int& h) override;
   void OnClicked(int x, int y, bool right) override;
   bool MouseMoved(float x, float y) override;
   void MouseReleased() override;
   
   Grid* mGrid;
   NoteInterval mInterval;
   DropdownList* mIntervalSelector;
   int mLength;
   DropdownList* mLengthSelector;
   vector<PatchCableSource*> mControlCables;
};
