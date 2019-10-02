#include <QApplication>
#include "qwindow.h"
#include "qscreen.h"
#include "qwidget.h"
#include "mainscreen.h"
#include "qdebug.h"
#include "QPushButton"



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
    std::vector<unsigned int> vpWidths,vpHeights,vpXs,vpYs;


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
     ||(vpYs.size()!=videoCount))
    {
        qDebug()<<"Video count ERROR, closing APP";
        exit(0);
    }



    mainScreen * ms = new mainScreen(NULL,PATH,vpWidths,vpHeights,vpXs,vpYs);

    uint screenNumber = 1;

    if(screenNumber>a.screens().size()-1)
        screenNumber = a.screens().size()-1;


    ms->setGeometry(a.screens()[screenNumber]->geometry().x(),a.screens()[screenNumber]->geometry().y(),1080,1920);
    ms->show();






    return a.exec();

}
