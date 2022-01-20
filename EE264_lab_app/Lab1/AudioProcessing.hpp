//
//  AudioProcessing.hpp
//  EE264_lab
//
//  Created by Fernando Mujica on 1/27/19.
//  Copyright © 2019 Fernando Mujica. All rights reserved.
//

#ifndef AudioProcessing_hpp
#define AudioProcessing_hpp

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>

#include "ZeroOrderHoldInterp.hpp"


class AudioProcessing {
    
    // Counter for the number of times the processAudio() function has been called
    int callCount = 0;
    
    int micNumSamples;         // N
    int fileUpSampleFactor;    // L
    int fileDownSampleFactor;  // M
    
    // Temporary array to store rate converted audio file data
    static const int maxDataArraySize = 8192;
    int16_t tempData[maxDataArraySize];
    
    // Number of samples to read from the audio file. See fileNumSamplesNeededFor().
    int fileNumSamplesNeeded = 0;
    
    // These properties are used to keep track of extra audio file samples produced
    int fileNumExtraSamples = 0;
    static const int maxFileExtraSamplesSize = 64;
    int16_t fileExtraSamples[maxFileExtraSamplesSize] = {0};
    
    // ---> Your code here! - Lab 2
    // Interpolation objects
    ZeroOrderHoldInterp zeroOrderHoldInterp;
    
public:
    
    /**
     The setup function is called once after the user interface Start switch is enabled.

     @param micNumSamplesParam N
     @param fileUpSampleFactorParam L
     @param fileDownSampleFactorParam M
     */
    void setup(int micNumSamplesParam,
               int fileUpSampleFactorParam,
               int fileDownSampleFactorParam);
    
    
    /**
     The cleanup function is called once after the user interface Start switch is disabled.
     */
    void cleanup();
    
    /**
     This function is called by the iOS audio interface when a block of output data
     is needed.  It provides inputs from the microphone interface (if enabled) and
     the audio file (if available).  It also passes the state of the application
     user interface elements.

     @param outputData Array to store output samples
     @param outputNumSamples Number of output samples
     @param micData Microphone input array
     @param micOn State of micOn user interface switch
     @param fileData Audio file input array
     @param fileNumSamples Number of samples in file array
     @param test State of test user interface button
     @param mode Value of mode user interface text field
     */
    void processAudio(int16_t *outputData,
                      int outputNumSamples,
                      const int16_t *micData,
                      bool micOn,
                      const int16_t *fileData,
                      int fileNumSamples,
                      bool test,
                      int mode);
    
    
    /**
     This function returns the number of samples to read from the audio file such that,
     after interpolation, the number of samples equals N, i.e.,
     N = fileNumSamplesNeeded * L / M
     Note that depending on the values of L and M and N, the above equality requires
     fileNumSamplesNeeded to be a fraction, however a fractional number of samples is only reasonable
     in the average sense, thus, the number of file samples requested must be jittered so that
     avg(fileNumSamplesNeeded) = N * M / L

     @param outputNumSamples Number of output samples needed
     @return Number of file samples needed
     */
    int fileNumSamplesNeededFor(int outputNumSamples);
    
    
};

#endif /* AudioProcessing_hpp */
