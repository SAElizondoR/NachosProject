#ifdef CHANGED

PageProvider::PageProvider()
{
    bitmap = new BitMap(NumPhysPages);
}

PageProvider::~PageProvider()
{
    delete bitmap;
}

unsigned PageProvider::GetEmptyPage()
{
    int pageNumber = bitmap->Find();
    if (pageNumber == -1) {
        return 0;
    }
    /* A implementer */
    return 0;
}

#endif //CHANGED