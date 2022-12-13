/*
 * A class that peroforms basic morse coding and encoding
*/

#ifndef MORSECODEALG_H
#define MORSECODEALG_H
#define ERROR_MSG "#"

#include <QHash>
#include <QMap>
#include <QString>
#include <QRegularExpression>

class MorseCodeAlg
{
public:
    //constructor
    MorseCodeAlg();

    //function that encode a single english letter to corresponding morse code
    QString morseEncodeSingleChar(const QString& str);

    //function that decode a morse code to corresponding english letter
    QString morseDecodeSingleChar(const QString& str);

    //function that encode an english paragraph/text to corresponding morse code
    void morseEncodeText(const QString& inStr, QString& outStr);

    //function that decode a morse code to corresponding english paragraph/text
    void morseDecodeText(const QString& inStr, QString& outStr);

    //function that retreives a read only en2morseQMap ordered map
    const QMap<QString, QString>& getMorseCodeQMap() const { return en2morseQMap; }

private:
    //initialize en2morseQMap ordered map
    void initializeEn2MorseQMap();

    //initialize en2morseQHash unordered map
    void initializeEn2MorseQHash();

    //initialize morse2enQHash unordered map
    void initializeMorse2EnQHash();

    //en2morseQMap is an ordered map with a key being as an english letter and a value as being a morse code
    QMap<QString, QString>  en2morseQMap;

    //en2morseQMap is an unordered map with a key being as a morse code and a value as being an english letter
    QHash<QString, QString> en2morseQHash;

    //en2morseQMap is an unordered map with a key being as an english letter and a value as being a morse code
    QHash<QString, QString> morse2enQHash;

    QRegularExpression re;
};

#endif // MORSECODEALG_H
