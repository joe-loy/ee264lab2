//
//  AudioProcessing.cpp
//  EE264_lab
//
//  Created by Fernando Mujica on 1/27/19.
//  Copyright © 2019 Fernando Mujica. All rights reserved.
//

#include "AudioProcessing.hpp"

using namespace std;


void AudioProcessing::setup(int micNumSamplesParam,
                            int fileUpSampleFactorParam,
                            int fileDownSampleFactorParam) {
    
    std::cout << "AudioProcessing::setup\n";
    std::cout << "micNumSamplesParam        = " << micNumSamplesParam << "\n";
    std::cout << "fileUpSampleFactorParam   = " << fileUpSampleFactorParam << "\n";
    std::cout << "fileDownSampleFactorParam = " << fileDownSampleFactorParam << "\n";
    
    callCount = 0;
    
    micNumSamples = micNumSamplesParam;
    fileUpSampleFactor = fileUpSampleFactorParam;
    fileDownSampleFactor = fileDownSampleFactorParam;
    
    fileNumExtraSamples = 0;
    
    // Clear internal buffers
    for(int n = 0; n < maxDataArraySize; n++) {
        tempData[n] = 0;
    }
    for(int n = 0; n < maxFileExtraSamplesSize; n++) {
        fileExtraSamples[n] = 0;
    }
}


void AudioProcessing::cleanup() {
    std::cout << "AudioProcessing::cleanup\n";
}


void AudioProcessing::processAudio(int16_t *outputData,
                                   int outputNumSamples,
                                   const int16_t *micData,
                                   bool micOn,
                                   const int16_t *fileData,
                                   int fileNumSamples,
                                   bool test,
                                   int mode) {

    // Zero output data array
    for (int n = 0; n < outputNumSamples; n++) {
        outputData[n] = 0;
    }
    
    // File data processing
    if (fileNumSamples > 0) {
        // ---> Your code here! - Lab 2
        // Copy extra samples to beginning of tempData array, if needed - Lab 2.2
        for (int n = 0; n < fileNumExtraSamples; n++) {
            tempData[n] = fileExtraSamples[n];
            fileExtraSamples[n] = 0;
        }
        
        // Zero-order hold interpolation filter - Lab 2.1
        zeroOrderHoldInterp.filter(&tempData[fileNumExtraSamples], fileData, fileNumSamples, fileUpSampleFactor, fileDownSampleFactor);
                
        // ---> Your code here! - Lab 2.2
        // Keep track of extra samples produced
        // Hint: update fileNumExtraSamples data member
        fileNumExtraSamples += (fileNumSamplesNeeded * fileUpSampleFactor / fileDownSampleFactor) - fileNumSamples; 
        
        // ---> Your code here! - Lab 2.1
        // Copy data from tempData to outputData array
        for (int i = 0; i < fileNumSamples; i++) {
            outputData[i] = tempData[i];  
        }
    }
    
    // Mic data processing
    if (micOn == true) {
        // Your code here! - Lab 1.2
        // Add the mic data to the output buffer (outputData)
        // Hint: Properly scale the data to avoid overflow
        for (int i = 0; i < fileNumSamples; i++) {
            outputData[i] = (micData[i] >> 2) + (outputData[i] >> 2);
        }
    }
    
    // Test button pressed
    if (test == true) {
        // Uncomment the line below (and cout.close() statement below) to send output to a file
        // std::ofstream cout("/tmp/test_data.txt");

        cout << "AudioProcessing::Test button pressed!\n";
        cout << "Mode = " << mode << "\n";
        
        // ---> Your code here! - Lab 1.3
        
        // Uncomment the line below (and "ofstream cout" statement above) to send output to a file
        // cout.close();
    }
    
    // Debug - Lab 1.3
    /*
        if ((callCount % 100) == 0)  {
            for (int n = 0; n < outputNumSamples; n++) {
                std::cout << callCount << "\t" << n << "\t" << outputData[n] << "\n";
            }
        }
    */
    
    callCount += 1; // count how many times the processAudio function has been called

}


int AudioProcessing::fileNumSamplesNeededFor(int outputNumSamples) {

    // Lab 2
    fileNumSamplesNeeded = 0;
    
    // In this case, there are no extra samples needed
    if ((outputNumSamples * fileDownSampleFactor) % fileUpSampleFactor == 0) {
        fileNumSamplesNeeded = outputNumSamples * fileDownSampleFactor / fileUpSampleFactor;  
    }
    // In this case, we must determine the number of extra samples to add
    else {
        if (fileUpSampleFactor * (outputNumSamples / fileUpSampleFactor) + fileNumExtraSamples >= outputNumSamples) {
            fileNumSamplesNeeded = outputNumSamples / fileUpSampleFactor * fileDownSampleFactor;  
        } 
        else {
            fileNumSamplesNeeded = outputNumSamples / fileUpSampleFactor * fileDownSampleFactor + fileDownSampleFactor;      
        }
    }
        
    return(fileNumSamplesNeeded);
}

// ---> Your code here! - Lab 1.3
