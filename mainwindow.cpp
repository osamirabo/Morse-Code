#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->textEditOutput->setReadOnly(true);
    ui->text2morseBtn->setChecked(true);
    initializeMorseCodeTable();

    //signals and slots connection
    connect(ui->textEditInput, SIGNAL(textChanged()), this,  SLOT(reactToInputTextValueChanged()));
    connect(this, SIGNAL(outputTextValueChanged(QString)), ui->textEditOutput,  SLOT(setPlainText(QString)));
    connect(ui->clearPushButton, SIGNAL(clicked(bool)), this,  SLOT(reactToClearBtn()));
    connect(ui->text2morseBtn, SIGNAL(toggled(bool)), this,  SLOT(reactToToggledText2MorsBtn()));
    connect(ui->morse2textBtn, SIGNAL(toggled(bool)), this,  SLOT(reactToToggledMors2TextBtn()));
}

void MainWindow::initializeMorseCodeTable()
{
    //set table configuration
    int maxRow = 8, maxCol = 10;
    ui->morseCodeTable->setRowCount(maxRow);
    ui->morseCodeTable->setColumnCount(maxCol);
    ui->morseCodeTable->horizontalHeader()->hide();
    ui->morseCodeTable->verticalHeader()->hide();
    ui->morseCodeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //fill the table with corresponding values
    int row = 0, col = 0;
    QTableWidgetItem *item;
    const QMap<QString, QString>& morseCodeMap = morseCodeAlg.getMorseCodeQMap();
    for(QMap<QString, QString>::const_iterator it = morseCodeMap.begin(); it != morseCodeMap.end(); it++)
    {
        item = new QTableWidgetItem(it.key());
        ui->morseCodeTable->setItem(row, col, item);
        item = new QTableWidgetItem(it.value());
        ui->morseCodeTable->setItem(row, col + 1, item);
        row = (row + 1) % maxRow;
        col = (row == 0) ? col + 2 : col;
    }
}

void MainWindow::reactToInputTextValueChanged()
{
    QString resultStr = "";
    strToOperate = ui->textEditInput->toPlainText();
    if(ui->text2morseBtn->isChecked())
        morseCodeAlg.morseEncodeText(strToOperate, resultStr);
    else
        morseCodeAlg.morseDecodeText(strToOperate, resultStr);
    emit outputTextValueChanged(resultStr);
}

void MainWindow::clear()
{
    ui->textEditInput->clear();
    ui->textEditOutput->clear();

    strToOperate = "";
}

void MainWindow::reactToClearBtn()
{
    clear();
}

void MainWindow::reactToToggledText2MorsBtn()
{
    clear();
}

void MainWindow::reactToToggledMors2TextBtn()
{
    clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}
