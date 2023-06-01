//
// Created by kanade on 2023/5/27.
//

#include "Sprite.h"

#include <utility>

Sprite::Sprite(const QString&  filePath, const QString& name, int speed) :
filePath(filePath), name(name), speed(speed){
    QList<QString> files;
    //检索一遍 获取数量
    QString file;
    for (int i = 0; ; ++i) {
        file = this->filePath;
        file.replace("*", QString::number(i));
        if(QFile::exists(file))
            files << file;
        else{
            this->count = i;
            break;
        }
    }
    //加载到内存
    this->pixmaps = new QPixmap*[files.count()];
    for (int i = 0; i < files.count(); ++i) {
        this->pixmaps[i] = new QPixmap(files.at(i));
    }
}

int Sprite::getCount() const{
    return this->count;
}

QString Sprite::getName() const {
    return this->name;
}

QString Sprite::getFilePath() const {
    return this->filePath;
}

QPixmap **Sprite::getPixmaps() const {
    return this->pixmaps;
}
