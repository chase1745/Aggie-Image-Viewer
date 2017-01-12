#include <iostream>
#include "NavButton.h"
#include "Viewer.h"
using namespace std;

NavButton::NavButton(string imageFilename, string label, int x, int y, int thumbnailsize, int imageIndex, const char *L) :
	Fl_Button(x, y, 1, 1, L), clickCount(0), label(label), thumbnailsize(thumbnailsize), imageLabel(nullptr) {
	setImage(imageFilename);
}

string NavButton::getLabel() const {
	return label;
}

void NavButton::setImage(string filename) {
	delete imageLabel;
	imageLabel = new Fl_JPEG_Image(filename.c_str());
	imageLabel->copy(thumbnailsize, thumbnailsize);
	image(imageLabel);
	this->resize(this->x(), this->y(), thumbnailsize + Viewer::borderSize, thumbnailsize + Viewer::borderSize);
}

// sets label for keyboard input
void NavButton::setLabel(string label) {
    this->label = label;
}

int NavButton::totalClicks = 0;

// handle function to handle keyboard input and also clicking on the buttons
int NavButton::handle(int e) {
    switch(e) {
        case FL_SHORTCUT:
            if ( Fl::event_key() == FL_Left || Fl::event_key() == 'p' ||  Fl::event_key() == FL_BackSpace) {
                this->setLabel("Previous Button");
                this->do_callback();
                return(1);
            } else if (Fl::event_key() == FL_Right|| Fl::event_key() == 'n' ||  Fl::event_key() == FL_Tab) {
                this->setLabel("Next Button");
                this->do_callback();
                return(1);
            } else {  // other keyboard output returns 0 because we do not use it
                return 0;
            }
        case FL_RELEASE:
            this->do_callback();
            return 1;
    }
    // default case. it shouldn't ever get to this return statement
    return Fl_Widget::handle(e);
}
