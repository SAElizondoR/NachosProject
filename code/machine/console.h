// console.h
//	Data structures to simulate the behavior of a terminal
//	I/O device.  A terminal has two parts -- a keyboard input,
//	and a display output, each of which produces/accepts
//	characters sequentially.
//
//	The console hardware device is asynchronous.  When a character is
//	written to the device, the routine returns immediately, and an
//	interrupt handler is called later when the I/O completes.
//	For reads, an interrupt handler is called when a character arrives.
//
//	The user of the device can specify the routines to be called when
//	the read/write interrupts occur.  There is a separate interrupt
//	for read and write, and the device is "duplex" -- a character
//	can be outgoing and incoming at the same time.
//
//  DO NOT CHANGE -- part of the machine emulation
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#ifndef CONSOLE_H
#define CONSOLE_H

#include "copyright.h"
#include "utility.h"
#include "synch.h"
#include <stdio.h>

// The following class defines a hardware console device.
// Input and output to the device is simulated by reading
// and writing to UNIX files ("readFile" and "writeFile").
//
// Since the device is asynchronous, the interrupt handler "readAvailHandler"
// is called when a character has arrived, ready to be read by calling
// RX().
// The interrupt handler "writeDone" is called when an output character written
// by calling TX() has been "put", so that the next character can be
// written.

class Console:public dontcopythis {
  public:
    Console(const char *readFile, const char *writeFile, VoidFunctionPtr readAvailHandler,
        VoidFunctionPtr writeDoneHandler, void *callArg);
                                // initialize the hardware console device,
                                // registers the readAvailHandler and writeDoneHandler
                                // callbacks

    ~Console();                 // clean up console emulation

// external interface -- Nachos kernel code can call these
    void TX(int ch);            // Write "ch" to the console display,
                                // and return immediately.  "writeDone"
                                // is called when the I/O completes.

    int RX(void);               // Poll the console input.  If a char is
                                // available, return it.  Otherwise, crash.
                                // EOF is returned if the end of the input
                                // file was reached.
                                // "readDone" is called whenever there is
                                // a char to be gotten

// internal emulation routines -- DO NOT call these.
    void WriteDone(void);	// internal routines to signal I/O completion
    void CheckCharAvail(void);
    Semaphore *mutex;

  private:
    int readFileNo;                     // UNIX file emulating the keyboard
    int writeFileNo;                    // UNIX file emulating the display
    VoidFunctionPtr writeHandler;       // Interrupt handler to call when
                                        // the TX I/O completes
    VoidFunctionPtr readHandler;        // Interrupt handler to call when
                                        // a character arrives from the keyboard
    void *handlerArg;                   // argument to be passed to the
                                        // interrupt handlers
    bool putBusy;                       // Is a TX operation in progress?
                                        // If so, you can't do another one!
    int incoming;                       // Contains the character to be read,
                                        // if there is one available.
                                        // Otherwise contains EOF.
    static int stdin_busy;              // Whether stdin is already read from
                                        // by a console.
};

#endif // CONSOLE_H