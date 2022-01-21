//
//  ZeroOrderHoldInterp.cpp
//
//  Created by Fernando Mujica on 12/28/17.
//  Copyright © 2019 Stanford University. All rights reserved.
//

#include "ZeroOrderHoldInterp.hpp"

void ZeroOrderHoldInterp::filter(int16_t *outputData,
                          const int16_t *inputData,
                          int inputNumSamples,
                          int upSampleFactor,
                          int downSampleFactor) {
    
    // Starter code - Lab 2: copy input to output
    for(int n = 0; n < inputNumSamples; n++) {
        outputData[n] = inputData[n];
    }
    
    // Upsample input data and apply zero-order hold filter - Lab 2.1
    // Hint: use tempData array and check that is large enough to hold upsampled data
    
    for(int i = 0; i < inputNumSamples; i++) {
        if (sizeof(tempData) > inputNumSamples * upSampleFactor) {
            for (int j = 0; j < upSampleFactor; j++) {
                tempData[i * upSampleFactor + j] = inputData[i]    
            }
        }
           
    }

    // Downsample output of zero-order hold filter - Lab 2.3
    for (int i = 0; i < inputNumSamples * upSampleFactor / downSampleFactor;  i++) {
        tempData[i] = tempData[i*M]              
    }
    
    for(int n = 0; n < inputNumSamples * upSampleFactor / downSampleFactor; n++) {
        outputData[n] = tempData[n];
    }
}
