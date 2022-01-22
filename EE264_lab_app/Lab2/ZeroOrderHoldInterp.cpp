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
    
    // Upsample input data and apply zero-order hold filter - Lab 2.1
    // Hint: use tempData array and check that is large enough to hold upsampled data
    // size of the temp array is compared before upSample and is not performed if it cannot 
    // fit into the temp array. This means are samples are limited to lengths of 8192 samples. 
    
    if (inputNumSamples * upSampleFactor <= maxDataArraySize) {
        for(int i = 0; i < inputNumSamples; i++) {
            for (int j = 0; j < upSampleFactor; j++) {
                tempData[i * upSampleFactor + j] = inputData[i];
            }
        }  
    }
    

    // Downsample output of zero-order hold filter - Lab 2.3
    // No need to worry about the bounds if the upsampled version fits so does the downsampled one 
    
    for (int k = 0; k < inputNumSamples * upSampleFactor / downSampleFactor;  k++) {
        outputData[k] = tempData[k * downSampleFactor];
    }
    
    
}
