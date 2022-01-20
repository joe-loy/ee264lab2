//
//  CPP-Wrapper.m
//
//  Created by Prateek Murgai on 12/7/17.
//  Copyright © 2017 Stanford University. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "CPP-Wrapper.h"
#include "AudioProcessing.hpp"

AudioProcessing audioProcessing;


@implementation AudioProcessingWrapper

- (void)processAudio: (int16_t*) outputData numOutputFrames:(int) numOutputFrames inputData:(int16_t*) inputData micOn:(bool) micOn fileData:(int16_t*) fileData numFileFrames:(int) numFileFrames test:(bool) test mode:(int) mode {
    
    audioProcessing.processAudio(outputData, numOutputFrames, inputData, micOn, fileData, numFileFrames, test, mode);
}
@end


@implementation AudioProcessingSetupWrapper

- (void)setup: (int) numInputFrames upSampleFactor:(int) upSampleFactor downSampleFactor:(int) downSampleFactor {
    
    audioProcessing.setup(numInputFrames, upSampleFactor, downSampleFactor);
}
@end


@implementation AudioProcessingCleanupWrapper

- (void)cleanup {
    
    audioProcessing.cleanup();
}
@end


@implementation AudioProcessingNumFileSamplesNeededForWrapper

- (int)numFileSamplesNeededFor: (int) numInputFrames {
    
    return(audioProcessing.fileNumSamplesNeededFor(numInputFrames));
}
@end


