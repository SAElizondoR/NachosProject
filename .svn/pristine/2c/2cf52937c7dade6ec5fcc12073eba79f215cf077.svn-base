#ifdef CHANGED

#ifndef PAGEPROVIDER_H
#define PAGEPROVIDER_H

#include "utility.h"
#include "console.h"

class PageProvider {
    public:
                                            // initialize the page provder
        PageProvider();
        ~PageProvider();                   // clean up

        unsigned GetEmptyPage();
        void ReleasePage();
        void NumAvailPage();
        
    private:
        BitMap *bitmap;
    };

    #endif // PAGEPROVIDER_H

#endif // CHANGED