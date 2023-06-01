//
// Created by kanade on 2023/5/27.
//

#include "Spriter.h"
Spriter::Spriter(QWidget* parent) : QWidget(parent){
    this->QWidget::resize(parent->size());

    this->rect.setTopLeft(QPoint(0, 0));
    this->rect.setSize(this->QWidget::size());

    this->timer_spriteUpdate = new QTimer(this);
    this->timer_spriteUpdate->setTimerType(Qt::PreciseTimer);//使用精确定时器
    connect(this->timer_spriteUpdate, &QTimer::timeout, this, &Spriter::updateEvent);
    this->QWidget::show();
}

bool Spriter::load(const QString& filePath, const QString& name, int speed) {
    if(this->getSpriteIdOfName(name) > -1)
        return false;
    this->sprites << new Sprite(filePath, name, speed);
    return true;
}

bool Spriter::play(const QString& name) {
    if(nowPlay != nullptr && name == this->nowPlay->getName())
        return true;
    int i = this->getSpriteIdOfName(name);
    if(i < 0)
        return false;
    this->nowPlay = sprites.at(i);
    return this->run();
}

bool Spriter::run() {
    if(this->nowPlay == nullptr || this->status == Run)
        return false;
    this->status = Run;
    if(this->nowPlay->speed < 1)
        return true;
    this->timer_spriteUpdate->start(1000 / this->nowPlay->speed);
    return true;
}

void Spriter::stop() {
    if(this->nowPlay == nullptr || this->status == Stop)
        return;
    this->timer_spriteUpdate->stop();
    this->nowPlay->now = 0;
    this->nowPlay = nullptr;
    this->status = Stop;
}

void Spriter::pause() {
    if(this->nowPlay == nullptr || this->status == Pause)
        return;
    this->timer_spriteUpdate->stop();
    this->status = Pause;
}

int Spriter::getSpriteIdOfName(const QString& name) {
    for (int i = 0; i < this->sprites.count(); ++i) {
        if(this->sprites[i]->getName() == name)
            return i;
    }
    return -1;
}
Sprite *Spriter::getNowSprite() {
    return this->nowPlay;
}

void Spriter::move(int x, int y) {
    this->rect.moveTopLeft(QPoint(x, y));
}

void Spriter::updateEvent() {
    if(this->nowPlay->now < nowPlay->getCount() - 1)
        ++this->nowPlay->now;
    else
        this->nowPlay->now = 0;

    update();
}
void Spriter::paintEvent(QPaintEvent *event) {
    if(this->nowPlay == nullptr)
        return;
    QPainter painter(this);

#ifdef QT_DEBUG
    painter.setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap));
    painter.drawRect(0, 0, this->QWidget::width() - 1, this->QWidget::height() - 1);//QWidget边框
#endif
    painter.setClipRect(this->rect);
#ifdef QT_DEBUG
    painter.setPen(QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap));
    painter.drawRect(this->rect.x(), this->rect.y(), this->rect.width() - 1, this->rect.height() - 1);//Spriter边框
#endif
    painter.drawPixmap(this->rect.topLeft(),*this->nowPlay->getPixmaps()[this->nowPlay->now]);

}


