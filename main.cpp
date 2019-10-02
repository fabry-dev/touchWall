#include <QApplication>
#include "qwindow.h"
#include "qscreen.h"
#include "qwidget.h"
#include "mainscreen.h"
#include "qdebug.h"
#include "QPushButton"
#include "qmessagebox.h"


#define PATH_DEFAULT (QString)"/home/fred/Dropbox/Taf/Cassiopee/walls/files/"



int main(int argc, char *argv[])

{
    QApplication a(argc, argv);




    QString PATH;
    QStringList params = a.arguments();
    if(params.size()>1)
        PATH = params[1];
    else
        PATH=PATH_DEFAULT;

    bool HIDE_CURSOR=false;
    bool DEBUG=false;
    unsigned int videoCount= 0;
    unsigned int buttonDiameter = 50;
    std::vector<unsigned int> vpWidths,vpHeights,vpXs,vpYs,buttonXs,buttonYs;


    QFile file(PATH+"config.cfg");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"no config file";

    }
    else
    {

        QTextStream in(&file);

        QString  line;
        QString paramName,paramValue;
        QStringList params;


        while(!in.atEnd()) {
            line = in.readLine();
            line = (line.split("#"))[0];
            params = line.split("=");
            if(params.size()>=2)
            {
                paramName = params[0];
                paramValue = params[1];

                if (paramName.mid(0,6)=="CURSOR")
                    HIDE_CURSOR = (paramValue=="NO");
                else if (paramName.mid(0,5)=="DEBUG")
                    DEBUG = (paramValue=="YES");
                else if(paramName == "VIDEOCOUNT")
                {
                    videoCount = paramValue.toInt();

                }
                else if(paramName=="WIDTHS")
                {
                    QStringList buf = paramValue.split(",");
                    for(auto s:buf)
                        vpWidths.push_back(s.toInt());
                }
                else if(paramName=="HEIGHTS")
                {
                    QStringList buf = paramValue.split(",");
                    for(auto s:buf)
                        vpHeights.push_back(s.toInt());
                }
                else if(paramName=="XS")
                {
                    QStringList buf = paramValue.split(",");
                    for(auto s:buf)
                        vpXs.push_back(s.toInt());
                }
                else if(paramName=="YS")
                {
                    QStringList buf = paramValue.split(",");
                    for(auto s:buf)
                        vpYs.push_back(s.toInt());
                }
                else if(paramName=="buttonX")
                {
                    QStringList buf = paramValue.split(",");
                    for(auto s:buf)
                        buttonXs.push_back(s.toInt());
                }
                else if(paramName=="buttonY")
                {
                    QStringList buf = paramValue.split(",");
                    for(auto s:buf)
                        buttonYs.push_back(s.toInt());
                }
                else if(paramName == "buttonDiameter")
                {
                    buttonDiameter = paramValue.toInt();

                }

                else
                    qDebug()<<paramName<<" - "<<paramValue;
            }
        }
        file.close();

    }




    if (HIDE_CURSOR)
    {
        QCursor cursor(Qt::BlankCursor);
        a.setOverrideCursor(cursor);
        a.changeOverrideCursor(cursor);
    }






    qDebug()<<"Screens count: "<<a.screens().size();
    qDebug()<<"Video Count: "<<videoCount;
    qDebug()<<"Video widths: "<<vpWidths;
    qDebug()<<"Video heights: "<<vpHeights;
    qDebug()<<"Video Xs: "<<vpWidths;
    qDebug()<<"Video Ys: "<<vpHeights;



    if((vpWidths.size()!=videoCount)
     ||(vpHeights.size()!=videoCount)
     ||(vpXs.size()!=videoCount)
     ||(vpYs.size()!=videoCount)
     ||(buttonXs.size()!=videoCount)
     ||(buttonYs.size()!=videoCount))
    {
        qDebug()<<"Video & button parameters count mismatch. Check config.cfg. Closing APP";


        QMessageBox msgBox;
        msgBox.setText("Video & button parameters count mismatch. Check config.cfg. Closing APP now.");
        //msgBox.setInformativeText("Do you want to save your changes?");
        //msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        //msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

        exit(0);
    }



    mainScreen * ms = new mainScreen(NULL,PATH,DEBUG,vpWidths,vpHeights,vpXs,vpYs,buttonXs,buttonYs,buttonDiameter);

    uint screenNumber = 1;

    if(screenNumber>a.screens().size()-1)
        screenNumber = a.screens().size()-1;


    ms->setGeometry(a.screens()[screenNumber]->geometry().x(),a.screens()[screenNumber]->geometry().y(),1080,1920);
    ms->show();


    if(DEBUG)
    {
        QPushButton *pb0 = new QPushButton(ms);
        pb0->move(0,0);
        pb0->resize(200,200);
        pb0->setText("close app");
        a.connect(pb0,SIGNAL(clicked(bool)),&a,SLOT(closeAllWindows()));
        pb0->show();
        pb0->raise();
    }

    return a.exec();

}
