//
//  wrapper.cpp
//  pass_data_from_swift_C
//
//  Created by Prateek Murgai on 10/25/17.
//  Copyright © 2017 Prateek Murgai. All rights reserved.
//

#include "test_class.hpp"
#include <iostream>


extern "C" float* levelController(float*z, float level, int sample_count) {
    
    test_class test;
    
    
//    std::cout<<sizeof(z)/sizeof(z[0]);
//    std::cout<<sample_count;
//    std::cout<<"\n";
    return test.processAudio(z,level,sample_count);
    
    
}
