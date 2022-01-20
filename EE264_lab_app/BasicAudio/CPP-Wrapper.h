//
//  CPP-Wrapper.h
//
//  Created by Prateek Murgai on 12/7/17.
//  Copyright © 2017 Stanford University. All rights reserved.
//


#import <Foundation/Foundation.h>

@interface AudioProcessingWrapper : NSObject
- (void)processAudio: (int16_t*) outputData numOutputFrames:(int) numOutputFrames inputData:(int16_t*) inputData micOn:(bool) micOn fileData:(int16_t*) fileData numFileFrames:(int) numFileFrames test:(bool) test mode:(int) mode;
@end

@interface AudioProcessingSetupWrapper : NSObject
- (void)setup: (int) numInputFrames upSampleFactor:(int) upSampleFactor downSampleFactor:(int) downSampleFactor;
@end

@interface AudioProcessingCleanupWrapper : NSObject
- (void)cleanup;
@end

@interface AudioProcessingNumFileSamplesNeededForWrapper : NSObject
- (int)numFileSamplesNeededFor: (int) numInputFrames;
@end

