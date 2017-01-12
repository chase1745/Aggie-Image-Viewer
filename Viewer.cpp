#include <iostream>
#include "Viewer.h"

using namespace std;

// callback function
void buttonCallback(Fl_Widget* widget, void* viewerPtr) {
	cout << "Callback called" << endl;
	Viewer* viewer = static_cast<Viewer*>(viewerPtr);
    viewer->navPressed(widget);
    viewer->redraw();
}



Viewer::Viewer(string imageFolder, vector<string> imageFilenames, int width = 800, int height = 600) :
	Fl_Window(width, height, "Image Viewer"), imageFolder(imageFolder), imageFilenames(imageFilenames), currentIndex(0), nextIndex(1), prevIndex(imageFilenames.size()-1),
	prev(nullptr), next(nullptr), imageBox(nullptr), pic(nullptr) {
        
        
  	prev = new NavButton(getPathFilename(imageFilenames.at(prevIndex), true), "Previous Button", borderSize, this->h() - borderSize - thumbnailSize - borderSize, thumbnailSize, imageFilenames.size() - 1);
        
        
	next = new NavButton(getPathFilename(imageFilenames.at(nextIndex), true), "Next Button",
        this->w() - borderSize - thumbnailSize - borderSize, this->h() - borderSize - thumbnailSize - borderSize, thumbnailSize, imageFilenames.size()-1);
        
        
	imageBox = new Fl_Box(borderSize, borderSize, this->w() - (2*borderSize), this->h() - (2*borderSize) - thumbnailSize - 2*borderSize);
        
        
	//imageBox->box(FL_BORDER_BOX); // useful to see where the full size of the widget holding the images

	pic = new Fl_JPEG_Image(getPathFilename(imageFilenames.at(currentIndex)).c_str());
	imageBox->image(pic);
	this->end();
    prev->callback(buttonCallback, static_cast<void*>(this));
    next->callback(buttonCallback, static_cast<void*>(this));
}



string Viewer::getPathFilename(string filename, bool thumb) {
	string thumbPart = "";
	if (thumb) thumbPart = "t_";
	return imageFolder + "/" + thumbPart+ filename;
}



void Viewer::navPressed(Fl_Widget *widget) {
    NavButton* b = dynamic_cast<NavButton*>(widget);
    
    // determines which button is pressed
    if (b->getLabel() == "Next Button") {
        // increase indexes
        changeAllInds(true);
        
        // adds to the click counts to keep track of them
        next->addClickCount(); next->addTotalClicks();
        cout <<  next->getLabel() << " has been pressed " << next->getClickCount() << " times." << endl;
        cout << "All buttons have been pressed " << next->getTotClicks() << " times." << endl;
        
        // check to see if at end of list
        if ((nextIndex) > imageFilenames.size()-1) {
            nextIndex = 0;
        } else if (currentIndex > imageFilenames.size()-1) {
            currentIndex = 0;
        } else if (prevIndex > imageFilenames.size()-1) {
            prevIndex = 0;
        }
        
        // changes main image
        pic = new Fl_JPEG_Image(getPathFilename(imageFilenames.at(currentIndex)).c_str());
        imageBox->image(pic);
        
        // changes thumbnails
        prev->setImage(getPathFilename(imageFilenames.at(prevIndex), true).c_str());
        next->setImage(getPathFilename(imageFilenames.at(nextIndex), true).c_str());
        

    } else {
        // decrease indexes
        changeAllInds(false);
        
        
        // adds to the click counts to keep track of them
        prev->addClickCount(); prev->addTotalClicks();
        cout <<  prev->getLabel() << " has been pressed " << prev->getClickCount() << " times." << endl;
        cout << "All buttons have been pressed " << prev->getTotClicks() << " times." << endl;
        
        // check to see if at beginning of list
        if ((nextIndex) < 0) {
            nextIndex = imageFilenames.size()-1;
        } else if (currentIndex < 0) {
            currentIndex = imageFilenames.size()-1;
        } else if (prevIndex < 0) {
            prevIndex = imageFilenames.size()-1;
        }
        
        // changes main image
        pic = new Fl_JPEG_Image(getPathFilename(imageFilenames.at(currentIndex)).c_str());
        imageBox->image(pic);
        
        // changes thumbnails
        prev->setImage(getPathFilename(imageFilenames.at(prevIndex), true).c_str());
        next->setImage(getPathFilename(imageFilenames.at(nextIndex), true).c_str());

    }
    //cout << currentIndex << endl;
    cout << endl;
    
}


// update indices according to going forward or backwards (increase or decrease)
void Viewer::changeAllInds(bool increase) {
    if (increase) {
        currentIndex++; nextIndex++; prevIndex++;
    } else {
        currentIndex--; nextIndex--; prevIndex--;
    }
}

