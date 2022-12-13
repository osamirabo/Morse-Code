#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "morsecodealg.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    //function to initialize morse code QWidgetTable
    void initializeMorseCodeTable();

    //function to clear both textEditInput and textEditOutput
    void clear();

    Ui::MainWindow *ui;
    QString strToOperate;
    MorseCodeAlg morseCodeAlg;

signals:
    //function to emit changes to textEditOutput
    void outputTextValueChanged(QString str);

private slots:
    //function that reacts to textEditInput changes
    void reactToInputTextValueChanged();

    //function that reacts to text2MorsBtn
    void reactToToggledText2MorsBtn();

    //function that reacts to mors2TextBtn
    void reactToToggledMors2TextBtn();

    //function that reacts to clear button
    void reactToClearBtn();
};
#endif // MAINWINDOW_H
