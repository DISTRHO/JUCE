/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2017 - ROLI Ltd.

   JUCE is an open source library subject to commercial or open-source
   licensing.

   By using JUCE, you agree to the terms of both the JUCE 5 End-User License
   Agreement and JUCE 5 Privacy Policy (both updated and effective as of the
   27th April 2017).

   End User License Agreement: www.juce.com/juce-5-licence
   Privacy Policy: www.juce.com/juce-5-privacy-policy

   Or: You may also use this code under the terms of the GPL v3 (see
   www.gnu.org/licenses).

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

#pragma once


//==============================================================================
#define FILE_EXT .h

#define EXPAND(x) x
#define CREATE_FILEPATH(DemoName, category) JUCE_STRINGIFY(EXPAND(category)/EXPAND(DemoName)EXPAND(FILE_EXT))

#define REGISTER_DEMO(DemoName, category, heavyweight) JUCEDemos::registerDemo ([] { return new DemoName(); }, CREATE_FILEPATH(DemoName, category), JUCE_STRINGIFY (category), heavyweight);
#define REGISTER_DEMO_WITH_FILENAME(DemoName, category, fileName, heavyweight) JUCEDemos::registerDemo ([] { return new DemoName(); }, CREATE_FILEPATH(fileName, category), JUCE_STRINGIFY (category), heavyweight);


//==============================================================================
struct JUCEDemos
{
    struct FileAndCallback
    {
        File demoFile;
        std::function<Component*()> callback;
        bool isHeavyweight;
    };

    struct DemoCategory
    {
        String name;
        std::vector<FileAndCallback> demos;
    };

    static std::vector<DemoCategory>& getCategories();
    static DemoCategory& getCategory (const String& name);

    static void registerDemo (std::function<Component*()> constructorCallback, const String& filePath, const String& category, bool isHeavyweight);
    static File findExamplesDirectoryFromExecutable (File exec);
};

//==============================================================================
// used by child-process demo
bool invokeChildProcessDemo (const String& commandLine);
void registerAllDemos() noexcept;

Component* createIntroDemo();
bool isComponentIntroDemo (Component*) noexcept;

CodeEditorComponent::ColourScheme getDarkColourScheme();
CodeEditorComponent::ColourScheme getLightColourScheme();

//==============================================================================
extern ScopedPointer<AudioDeviceManager> sharedAudioDeviceManager;

AudioDeviceManager& getSharedAudioDeviceManager (int numInputChannels = -1, int numOutputChannels = -1);
