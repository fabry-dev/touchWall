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
    explicit mainScreen(QLabel *parent = nullptr, QString PATH="",bool DEBUG=false, std::vector<unsigned int> vpWidths=std::vector<unsigned int>(), std::vector<unsigned int> vpHeights=std::vector<unsigned int>(), std::vector<unsigned int> vpXs=std::vector<unsigned int>(), std::vector<unsigned int> vpYs=std::vector<unsigned int>(), std::vector<unsigned int> buttonXs=std::vector<unsigned int>(), std::vector<unsigned int> buttonYs = std::vector<unsigned int>(), unsigned int buttonDiameter=50);

private:
    QString PATH;
    std::vector<unsigned int> buttonXs,buttonYs;
    unsigned int buttonDiameter;
    std::vector<mpvWidget *> vps;
    void buttonClick(unsigned int buttonId);
    mpvWidget *savingScreenVp;
    std::vector<bool>videoPlayingStatus;
    QTimer *savingTimer;

private slots:
    void goSavingScreen(void);
    void stopSavingScreen(void);
    void onVideoOver(void);

protected:
    void mousePressEvent(QMouseEvent *event);

};

#endif // MAINSCREEN_H
