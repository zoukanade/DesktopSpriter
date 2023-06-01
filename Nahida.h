//
// Created by kanade on 2023/5/28.
//

#ifndef DESKTOPSPRITER_NAHIDA_H
#define DESKTOPSPRITER_NAHIDA_H
#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>
#include <QTime>
#include <QMenu>
#include <QAction>
#include "box2d.h"
#include "Spriter.h"

class Nahida : public QWidget{
public:
    Nahida();
public:
private:
    void box2d_step();
    void getWidgetSpeed();

    void quit();
    void customContextMenu(const QPoint &pos);
private:
    Spriter *spriteNahida;

    //拖拽窗口
    bool m_bDrag;//鼠标是否按下
    QPoint mouseStartPoint;//鼠标起始位置
    QPoint windowTopLeftPoint;//窗口起始位置
    //Box2d
    QTimer *timer_box2d_step;
    b2World *world;
    b2Body *spriteNahidaBody;
    QTimer *timer_getWidgetSpeed;
    QPoint startWidgetPoint;
    b2Vec2 *widgetSpeed = new b2Vec2(0, 0);


protected:
    void mousePressEvent(QMouseEvent *event) override;//鼠标按下
    void mouseMoveEvent(QMouseEvent *event) override;//鼠标移动
    void mouseReleaseEvent(QMouseEvent *event) override;//鼠标释放
};


#endif //DESKTOPSPRITER_NAHIDA_H
