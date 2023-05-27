
#include <FL/x.H>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <CoreFoundation/CoreFoundation.h>
#include <iostream>
#include <objc/objc-runtime.h>
#include <objc/objc.h>
#import <Cocoa/Cocoa.h>

extern "C" void transparency(Fl_Window *w, double alpha)
{
    [fl_xid(w) setAlphaValue:alpha];
}

