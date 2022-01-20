//
//  ZeroOrderHoldInterp.hpp
//
//  Created by Fernando Mujica on 12/28/17.
//  Copyright © 2019 Stanford University. All rights reserved.
//

#ifndef ZeroOrderHoldFilter_hpp
#define ZeroOrderHoldFilter_hpp

#include <stdio.h>


class ZeroOrderHoldInterp {
    
    static const int maxDataArraySize = 8192;
    
    int16_t tempData[maxDataArraySize];
    
public:
    
    void filter(int16_t *outputData,
                const int16_t *inputData,
                int inputNumSamples,
                int upSampleFactor,
                int downSampleFactor = 1);

};

#endif /* ZeroOrderHoldFilter_hpp */
