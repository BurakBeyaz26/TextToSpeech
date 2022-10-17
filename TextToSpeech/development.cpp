#include "development.h"

Development::Development(QObject *parent) : QObject(parent)
{

}

void Development::startSpeech(QString text, QString language, float speed,QString filename,QString filetype)
{
    gts = new gtts::GoogleTTS(text.toStdString(), language.toStdString(), QString::number(speed).toStdString(),filename.toStdString(),filetype.toStdString());
    gts->execute();
}
