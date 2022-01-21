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
    // size of the temp array is compared before upSample and is not performed if it cannot 
    // fit into the temp array. This means are samples are limited to lengths of 8192 samples. 
    
    if (sizeof(tempData) > inputNumSamples * upSampleFactor) { 
        for(int i = 0; i < inputNumSamples; i++) {
            for (int j = 0; j < upSampleFactor; j++) {
                tempData[i * upSampleFactor + j] = inputData[i]    
            }
        }  
    }
    

    // Downsample output of zero-order hold filter - Lab 2.3
    for (int i = 0; i < inputNumSamples * upSampleFactor / downSampleFactor;  i++) {
        tempData[i] = tempData[i*M]              
    }
    
    for(int i = 0; i < inputNumSamples * upSampleFactor / downSampleFactor; i++) {
        outputData[i] = tempData[i];
    }
}
