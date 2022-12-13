#include "morsecodealg.h"

MorseCodeAlg::MorseCodeAlg()
    : re("\\s+")
{
    //initialize en2morseQMap ordered map
    initializeEn2MorseQMap();

    //initialize en2morseQHash unordered map from en2morseQMap
    initializeEn2MorseQHash();

    //initialize morse2enQHash unordered map from en2morseQHash
    initializeMorse2EnQHash();
}

void MorseCodeAlg::initializeEn2MorseQMap()
{
    //Letters
    en2morseQMap["a"] = ".-";
    en2morseQMap["b"] = "-...";
    en2morseQMap["c"] = "-.-.";
    en2morseQMap["d"] = "-..";
    en2morseQMap["e"] = ".";
    en2morseQMap["f"] = "..-.";
    en2morseQMap["g"] = "--.";
    en2morseQMap["h"] = "....";
    en2morseQMap["i"] = "..";
    en2morseQMap["j"] = ".---";
    en2morseQMap["k"] = "-.-";
    en2morseQMap["l"] = ".-..";
    en2morseQMap["m"] = "--";
    en2morseQMap["n"] = "-.";
    en2morseQMap["o"] = "---";
    en2morseQMap["p"] = ".--.";
    en2morseQMap["q"] = "--.-";
    en2morseQMap["r"] = ".-.";
    en2morseQMap["s"] = "...";
    en2morseQMap["t"] = "-";
    en2morseQMap["u"] = "..-";
    en2morseQMap["v"] = "...-";
    en2morseQMap["w"] = ".--";
    en2morseQMap["x"] = "-..-";
    en2morseQMap["y"] = "-.--";
    en2morseQMap["z"] = "--..";

    //Numbers
    en2morseQMap["0"] = "-----";
    en2morseQMap["1"] = ".----";
    en2morseQMap["2"] = "..---";
    en2morseQMap["3"] = "...--";
    en2morseQMap["4"] = "....-";
    en2morseQMap["5"] = ".....";
    en2morseQMap["6"] = "-....";
    en2morseQMap["7"] = "--...";
    en2morseQMap["8"] = "---..";
    en2morseQMap["9"] = "----.";
}

void MorseCodeAlg::initializeEn2MorseQHash()
{
    for(QMap<QString, QString>::iterator it = en2morseQMap.begin(); it != en2morseQMap.end(); it++)
        en2morseQHash.insert(it.key(), it.value());
}

void MorseCodeAlg::initializeMorse2EnQHash()
{
    for(QHash<QString, QString>::iterator it = en2morseQHash.begin(); it != en2morseQHash.end(); it++)
        morse2enQHash.insert(it.value(), it.key());
}

QString MorseCodeAlg::morseEncodeSingleChar(const QString& str)
{
    if(en2morseQHash.find(str) == en2morseQHash.end())
        return ERROR_MSG;
    return en2morseQHash[str];
}

QString MorseCodeAlg::morseDecodeSingleChar(const QString& str)
{
    if(morse2enQHash.find(str) == morse2enQHash.end())
        return ERROR_MSG;
    return morse2enQHash[str];
}

void MorseCodeAlg::morseEncodeText(const QString& inStr, QString& outStr)
{
    QStringList resultStrList;
    QStringList wordStrList;
    QString     tmpStr;
    QStringList inStrList   = inStr.split(re, Qt::SkipEmptyParts);

    //Iterate over words (seperated by " ") of the given text
    for (int wordtIt = 0; wordtIt < inStrList.size(); wordtIt++)
    {
        tmpStr = inStrList[wordtIt];

        //Iterate over the characters of each words
        for(int charIt = 0; charIt < tmpStr.size(); charIt++)
            wordStrList << morseEncodeSingleChar(tmpStr[charIt]);

        //concatenate characters
        resultStrList << wordStrList.join(" ");
        wordStrList.clear();
    }

    //concatenate words
    outStr = resultStrList.join(" / ");
}

void MorseCodeAlg::morseDecodeText(const QString& inStr, QString& outStr)
{
    QStringList resultStrList;
    QStringList wordStrList;
    QString     tmpStr;
    QStringList inStrList   = inStr.split("/", Qt::SkipEmptyParts);

    //Iterate over morse words (seperated by "/") of the given text
    for (int wordtIt = 0; wordtIt < inStrList.size(); wordtIt++)
    {
        tmpStr = inStrList[wordtIt];
        QStringList charList = tmpStr.split(re, Qt::SkipEmptyParts);

        //Iterate over morse code (seperated by " ")
        for(int charIt = 0; charIt < charList.size(); charIt++)
            wordStrList << morseDecodeSingleChar(charList[charIt]);

        //concatenate characters
        resultStrList << wordStrList.join("");
        wordStrList.clear();
    }

    //concatenate words
    outStr = resultStrList.join(" ");
}
