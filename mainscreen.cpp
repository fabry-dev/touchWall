#include "mainscreen.h"
#include "math.h"



mainScreen::mainScreen(QLabel *parent, QString PATH,std::vector<unsigned int>vpWidths,std::vector<unsigned int>vpHeights,std::vector<unsigned int>vpXs,std::vector<unsigned int>vpYs) : QLabel(parent),PATH(PATH)
{
    showFullScreen();
    resize(1920,1080);
    setStyleSheet("QLabel { background-color : black; }");
    vps.resize(7);
    int i = 0;
    for(auto vp:vps)
    {
        vp = new mpvWidget(this);
        vp->resize(vpWidths[i],vpHeights[i]);
        vp->move(vpXs[i],vpYs[i]);
        vp->setLoop(true);
        vp->setProperty("pause", false);
        vp->setProperty("keep-open",false);
        vp->show();
        vp->loadFile(PATH+QString::number(i+1)+".mp4");
        i++;
    }


}

