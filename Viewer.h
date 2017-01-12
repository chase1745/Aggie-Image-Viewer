    #ifndef VIEWER_H
    #define VIEWER_H

    #include <vector>
    #include <string>
    #include <FL/Fl_Window.H>
    #include <FL/Fl_Box.H>
    #include "NavButton.h"

    class Viewer : public Fl_Window {
        std::vector<std::string> imageFilenames;
        Fl_Box *imageBox;   // Holds image being shown
        Fl_JPEG_Image *pic; // Image being shown
        NavButton* prev;    // Button to go to previous item
                            //   Image is thumbnail of previous image
        NavButton* next;    // Button to go to next item
                            //   Image is thumbnail of next image
        int currentIndex;   // Index of the image currently shown
        int nextIndex;      // Index of next image
        int prevIndex;      // Index of previous image
        
        // private helper functions
        std::string imageFolder;
        std::string getPathFilename(std::string filename, bool thumb=false);

    public:
        static const int thumbnailSize = 50; // size of NavButton
        static const int borderSize = 10; // size of border between window edge and widgets

        void navPressed(Fl_Widget* widget);
        
        // constructor
        Viewer(std::string, std::vector<std::string>, int, int);
        
        //virtual int handle(int e);
        //int key_handle(int e, int key);
        //int mouse_handle(int e);
        
        void changeAllInds(bool increase);
        
        //NavButton::operator=(const NavButton& source) {
    };

    #endif
