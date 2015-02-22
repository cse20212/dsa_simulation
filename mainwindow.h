#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGroupBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QRadioButton>
#include <QList>
#include <QMap>
#include "genealgorithm.h"
#include "algorithm.h"
#include "dataset.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_data_radio_checked();

private:
    Ui::MainWindow *ui;
    GeneAlgorithm currentGenAlg;   // default constructor get sorting
    QList<Algorithm *> currentAlgList;
    QList<DataSet *> currentDataList;
    QMap< QRadioButton*, DataSet *> currentDataMap;
    QMap< QRadioButton*, Algorithm *> currentAlgMap;

     // active dataset and algorithm
    DataSet *currentDataSet;
    Algorithm *currentAlgorithm;

    QGroupBox *createAlgorithmGroup();
    QGroupBox *createDataGroup();
    QGraphicsView *createGraphicsWindow();

    QGraphicsView *graphicsView;
    QGraphicsScene *graphicsScene;

    void initGraphicsItem();    // add items in currentDataSet to scene

};

#endif // MAINWINDOW_H
