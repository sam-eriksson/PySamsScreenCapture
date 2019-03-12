//
//  ScreenCapture.h
//  SamScreenCapture
//
//  Created by Sam Eriksson on 2018-12-17.
//  Copyright © 2018 Sam Eriksson. All rights reserved.
//

#ifndef ScreenCapture_h
#define ScreenCapture_h

extern void takeScreenShotAllDisplays(char * path);
extern void takeScreenShot(char * path, int display);
extern void takeScreenShotToFile(char * path, int display, char * filename);

#endif /* ScreenCapture_h */
