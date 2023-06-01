//
// Created by kanade on 2023/5/27.
//

#ifndef DESKTOPSPRITER_SPRITE_H
#define DESKTOPSPRITER_SPRITE_H
#include <QPixmap>
#include <QFIle>
#include <QList>
class Sprite {
public:
    Sprite(const QString&  filePath, const QString& name, int speed);

    [[nodiscard]] int getCount() const;
    [[nodiscard]] QString getName() const;
    [[nodiscard]] QString getFilePath() const;
    [[nodiscard]] QPixmap ** getPixmaps() const;

public:
    int speed = 0;
    int now = 0;
private:

private:
    QPixmap **pixmaps;
    int count;
    const QString name;
    const QString filePath;
};


#endif //DESKTOPSPRITER_SPRITE_H
