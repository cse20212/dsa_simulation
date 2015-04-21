#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTextEdit>
#include <QRadioButton>
#include <QList>
#include <QMap>
#include <QTextBrowser>
#include "genealgorithm.h"
#include "algorithm.h"
#include "dataset.h"
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QGroupBox *createAlgorithmGroup();
    QGroupBox *createDataGroup();
    QGraphicsView *createGraphicsWindow();
    QTextEdit *createStateTextBox();
    QTextBrowser *createPsuedoTextBox();

    void initGraphicsItem();    // add items in currentDataSet to scene
    void createActions();
    void createToolBars();

private slots:
    void on_data_radio_checked();
    void on_alg_radio_checked();
    void go_back();
    void go_forward();
    void to_start();
    void to_end();

private:
    Ui::MainWindow *ui;
    GeneAlgorithm currentGenAlg;   // default constructor get sorting
    QList<QString> currentAlgList;
    QList<DataSet *> currentDataList;
    QMap< QRadioButton*, DataSet *> currentDataMap;
    QMap< QRadioButton*, QString> currentAlgMap;

     // active dataset and algorithm
    DataSet *currentDataSet;
    QString currentAlgorithm;

    QGraphicsView *graphicsView;
    QGraphicsScene *graphicsScene;
    QTextEdit *algStateTextBox;

    // toolbars and menus
    QToolBar *animationToolBar;
    QAction *nextFrame;
    QAction *previousFrame;
    QAction *toEnd;
    QAction *toBegin;

    //to display psuedocode
    QTextBrowser *psuedoTextBox;

    QString localDataPath;

    QTimer *timer;
};

#endif // MAINWINDOW_H
