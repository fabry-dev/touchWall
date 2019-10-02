#ifndef MAINSCREEN_H
#define MAINSCREEN_H


#include <QWidget>
#include <qobject.h>
#include "qlabel.h"
#include "mpvwidget.h"
#include "qtimer.h"

#define vpCount 7

class mainScreen : public QLabel
{
    Q_OBJECT
public:
    explicit mainScreen(QLabel *parent = nullptr, QString PATH="", std::vector<unsigned int> vpWidths=std::vector<unsigned int>(), std::vector<unsigned int> vpHeights=std::vector<unsigned int>(), std::vector<unsigned int> vpXs=std::vector<unsigned int>(), std::vector<unsigned int> vpYs=std::vector<unsigned int>());

private:
    QString PATH;
    std::vector<mpvWidget *> vps;


};

#endif // MAINSCREEN_H
