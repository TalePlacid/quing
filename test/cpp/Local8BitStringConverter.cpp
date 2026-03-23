#include <QString>
#include "Local8BitStringConverter.h"

#pragma warning(disable:4996)

Local8BitStringConverter::Local8BitStringConverter(){

}

Local8BitStringConverter::~Local8BitStringConverter(){

}

string Local8BitStringConverter::Convert(string source){
    QString unicodeString = QString::fromStdString(source);
    QByteArray local8BitBytes = unicodeString.toLocal8Bit();

    return string(local8BitBytes.constData(), local8BitBytes.length());
}
