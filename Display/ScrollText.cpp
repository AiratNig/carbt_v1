//scrolls text, what more could you want

#include "ScrollText.h"

ScrollText::ScrollText(TextLCD& lcdin) : lcd(lcdin) {

}

//used to scroll a section of text in a single row, needs the text to scroll, starting position, length of the display to scroll, and speed in ms
//text currently on there will be fine since this will only write to specific chars, not the whole row at once
//must be called continuously to ensure good fps
//I might make this a class to allow for multiple scrollers at once
void ScrollText::scroll(string textIn, int x, int y, int length, int speed, bool direction) {
	//set the cursor position

	//check the timer (for speed control) thread safe
	//if it's time to move the text up
		//subtract length from x, this is the max chars that can be shown at any time
		//get the length of textIn
		//for(int x = 0;textlength;x++)
			//get the current part of the text into a var
			//increase the var by 1
			//create a substring of textin, starting at the new var, and ending at the length
			//print it at the connect position
			//hopefully it works


}


//referenced from an older project
//void LCDControl::scrollTweet() {                                                //used to scroll the tweet text, must be continuously called
//    if(scroll) {
//        switch(section) {
//            case 0: {                                                           //beginning of tweet section
//                if(printedBegin) {                                              //if we already printed the beginning
//                    unsigned long currentMillis1 = millis();
//                    if(currentMillis1 - previousMillis > opt.getReadTime()) {   //wait for the user read time to elapse
//                        previousMillis = currentMillis1;
//                        section++;                                              //done waiting, allow the program to go to the next section
//                        lcdPos = 0;                                             //reset the lcdPos var, needs to start at 0 after the beginning
//                    }
//                }
//                else {                                                          //did not print the beginning yet
//                    if(currentTweet) {                                          //if we are on the current tweet
//                        printBegin(twt.getTweetBegin());                        //print the beginning
//                    }
//                    else {                                                      //if we are on the previous tweet
//                        printBegin(twt.getPrevBegin());                         //print the previous beginning
//                    }
//                }
//                break;
//            }
//            case 1:  {                                                          //scrolling section
//                if(opt.getScroll()) {
//                    unsigned long currentMillis2 = millis();
//                    if(currentMillis2 - previousMillis > textSpeed) {               //check if it's time to shift the text
//                        previousMillis = currentMillis2;
//                        shiftText();                                                //shift the text by one
//                    }
//                }
//                break;
//            }
//            case 2:   {                                                         //end of tweet section
//                unsigned long currentMillis3 = millis();
//                if(currentMillis3 - previousMillis > opt.getReadTime()) {       //wait for the user read time to elapse
//                    previousMillis = currentMillis3;
//                    section = 0;                                                //done waiting, go back to section 0
//                    printedBegin = false;
//                }
//                break;
//            }
//        }
//    }
//}
//
//void LCDControl::shiftText() {                                                  //used to shift the tweet text by one column
//    if(currentTweet) {                                                          //if we are on the current tweet
//        twtLength = twt.getTweetLength();                                       //save the tweet length
//    }
//    else {                                                                      //if we are on the previous tweet
//        twtLength = twt.getPrevLength();                                        //save the previous tweet length
//    }
//    if (lcdPos <= (twtLength - LCDWIDTH)) {
//        //(subtracted LCDWIDTH since we want the ending to use all of LCDWIDTH)
//        if(currentTweet) {                                                      //get the current tweet
//            subTweet = twt.getTweet();
//        }
//        else {                                                                  //or get the previous tweet
//            subTweet = twt.getPrevTweet();
//        }
//        subTweet = subTweet.substring(lcdPos, (lcdPos + LCDWIDTH));             //create a substring from the current position to LCDWIDTH chars ahead
//        lcdc.setCursor(0, 1);                                                   //make sure we print on the bottom row
//        lcdc.print(subTweet);                                                   //printed the shifted substring
//        lcdPos++;                                                               //increase lcdPos by one
//    }
//    if(lcdPos == ((twtLength - LCDWIDTH)+1)) {                                  //check if we are at the end of the text to be shifted
//        section++;                                                              //we are done here, go to the next section
//    }
//}
//
//void LCDControl::setSpeed(int in) {                                             //used to set the text shifting speed
//    textSpeed = in;
//}