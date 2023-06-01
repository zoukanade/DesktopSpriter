//
// Created by kanade on 2023/5/27.
//

#ifndef DESKTOPSPRITER_SPRITER_H
#define DESKTOPSPRITER_SPRITER_H
#include <QWidget>
#include <QList>
#include <QTimer>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include "Sprite.h"

class Spriter : public QWidget{
    Q_OBJECT
public:
    enum Status{
        Run,
        Stop,
        Pause
    };
public:
    explicit Spriter(QWidget* parent);

    bool load(const QString& filePath, const QString& name, int speed);
    bool play(const QString& name);
    bool run();
    void stop();
    void pause();

    int getSpriteIdOfName(const QString& name);
    Sprite *getNowSprite();
    void move(int x, int y);
public:
private:
    void updateEvent();
private:
    QTimer *timer_spriteUpdate;
    QList<Sprite*> sprites;
    Sprite *nowPlay = nullptr;
    Status status = Stop;
    QRect rect;
protected:
    void paintEvent(QPaintEvent *event) override;

};


#endif //DESKTOPSPRITER_SPRITER_H
