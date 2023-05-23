/* The OSX Cocoa stub to do window transparency... */

#include <FL/x.H>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#import <Cocoa/Cocoa.h>

void setWindowTransparency(Fl_Window *w, double alpha)
{
    [fl_xid(w) setAlphaValue:alpha];
}

