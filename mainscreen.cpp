#include "mainscreen.h"
#include "math.h"
#include "qdebug.h"
#include "qpainter.h"


mainScreen::mainScreen(QLabel *parent, QString PATH,bool DEBUG,std::vector<unsigned int>vpWidths,std::vector<unsigned int>vpHeights,std::vector<unsigned int>vpXs,std::vector<unsigned int>vpYs,std::vector<unsigned int>buttonXs,std::vector<unsigned int>buttonYs,unsigned int buttonDiameter) : QLabel(parent),PATH(PATH),buttonXs(buttonXs),buttonYs(buttonYs),buttonDiameter(buttonDiameter)
{
    showFullScreen();
    resize(1920,1080);
    setStyleSheet("QLabel { background-color : black; }");





    int i = 0;


    savingTimer = new QTimer(this);
    savingTimer->setSingleShot(true);
    savingTimer->setInterval(10);
    connect(savingTimer,SIGNAL(timeout()),this,SLOT(goSavingScreen()));
    savingTimer->start();

    savingScreenVp = new mpvWidget(this);
    savingScreenVp->resize(size());
    savingScreenVp->move(0,0);
    savingScreenVp->setLoop(true);
    savingScreenVp->setProperty("keep-open",true);
    savingScreenVp->setAttribute(Qt::WA_TransparentForMouseEvents, true);




    for(int i = 0;i<vpWidths.size();i++)
    {
        mpvWidget * vp = new mpvWidget(this);
        vp->resize(vpWidths[i],vpHeights[i]);
        vp->move(vpXs[i],vpYs[i]);
        vp->setLoop(false);
        vp->setProperty("keep-open",false);
        vp->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        connect(vp,SIGNAL(videoOver()),this,SLOT(onVideoOver()));
        vp->setId(i);
        vps.push_back(vp);
        videoPlayingStatus.push_back(false);
    }



    if(DEBUG)
    {
        QLabel *circles = new QLabel(this);
        circles->resize(this->size());
        circles->show();
        circles->raise();

        //draw button
        QPixmap *circle = new QPixmap(size());
        circle->fill(Qt::transparent);
        QPainter *painter = new QPainter(circle);
        painter->setPen(QPen(QBrush("#600000"),5));

        for(int i = 0;i<buttonXs.size();i++)
            painter->drawEllipse(QPoint(buttonXs[i],buttonYs[i]),buttonDiameter/2,buttonDiameter/2);

        circles->setPixmap(*circle);
        circles->setAttribute(Qt::WA_TransparentForMouseEvents, true);
    }



}


void mainScreen::buttonClick(unsigned int buttonId)
{
    if(buttonId>vps.size())
        return;

    stopSavingScreen();

    mpvWidget *vp = vps[buttonId];

    vp->show();
    vp->setProperty("pause", false);
    vp->loadFile(PATH+QString::number(buttonId+1)+".mp4");
    vp->raise();

    videoPlayingStatus[buttonId] = true;

}

void mainScreen::onVideoOver()
{


    mpvWidget *vp = (mpvWidget*)QObject::sender();

    videoPlayingStatus[vp->getId()]=false;


    qDebug()<<videoPlayingStatus;

    for(auto b:videoPlayingStatus)
        if(b)
            return;


    //if we got here no video is playing anymore.
    //go saving in ten

    savingTimer->start();

}



void mainScreen::mousePressEvent(QMouseEvent *event)
{
    for(uint i = 0;i<buttonXs.size();i++)
    {
        QPoint dist = event->pos() - QPoint(buttonXs[i],buttonYs[i]);
        double d = std::sqrt(pow(dist.x(), 2) + std::pow(dist.y(), 2));
        if(d<buttonDiameter/2)
        {
            buttonClick(i);
        }
    }
}



void mainScreen::goSavingScreen(void)
{

    savingScreenVp->lower();
    savingScreenVp->show();
    savingScreenVp->setProperty("pause", false);
    savingScreenVp->loadFile(PATH+"savingscreen.mp4");
    savingScreenVp->raise();
}


void mainScreen::stopSavingScreen(void)
{

    savingTimer->stop();
    savingScreenVp->stop();
    savingScreenVp->hide();
}
