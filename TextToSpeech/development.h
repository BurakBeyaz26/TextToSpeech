#ifndef DEVELOPMENT_H
#define DEVELOPMENT_H

#include <QObject>
#include <iostream>
#include "gtts.h"

using namespace std;
using namespace gtts;

class Development : public QObject
{
    Q_OBJECT
public:
    explicit Development(QObject *parent = nullptr);
    Q_INVOKABLE void startSpeech(QString text, QString language, float speed,QString filename,QString filetype);
private:
    GoogleTTS *gts;

signals:

};

#endif // DEVELOPMENT_H
