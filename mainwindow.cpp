#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRadioButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentGenAlg()
{
    ui->setupUi(this);

    QGridLayout *grid = ui->gridLayout;
    //currentGenAlg.setDataList();
    currentAlgList = currentGenAlg.getAlgList();
    currentDataList = currentGenAlg.getDataList();

    if (currentDataList.size() >= 1)
        currentDataSet = currentDataList[0];
    if (currentAlgList.size() >= 1)
        currentAlgorithm = currentAlgList[0];
    //currentAlgorithm->setDataSet(currentDataSet);

    grid->addWidget(createAlgorithmGroup(), 0, 0);
    grid->addWidget(createDataGroup(), 1, 0);
    grid->addWidget(createGraphicsWindow(), 0, 1);

    createActions();
    createToolBars();

    setWindowTitle(tr("Algorithm Animation"));
    resize(480, 320);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createActions() {
    nextFrame = new QAction(tr("Next"),this);
    nextFrame->setStatusTip(tr("Next Step"));
    connect(nextFrame, SIGNAL(triggered()), this, SLOT(go_forward()) );

    previousFrame = new QAction(tr("Back"),this);
    previousFrame->setStatusTip(tr("Previous Step"));
    connect(previousFrame, SIGNAL(triggered()), this, SLOT(go_back()) );
}

void MainWindow::go_forward(){
    currentDataSet->go_forward();
    graphicsScene->advance();
}

void MainWindow::go_back(){
    currentDataSet->go_back();
    graphicsScene->advance();
}

void MainWindow::createToolBars() {
    animationToolBar = addToolBar(tr("Next"));
    animationToolBar->addAction(nextFrame);
    animationToolBar = addToolBar(tr("Back"));
    animationToolBar->addAction(previousFrame);
}

QGroupBox *MainWindow::createAlgorithmGroup() {
    QGroupBox *groupBox = new QGroupBox(tr("Algorithms"));
    QVBoxLayout *vbox = new QVBoxLayout;
    foreach (QString alg, currentAlgList){
        QRadioButton *radioData = new QRadioButton(alg);
        currentAlgMap[radioData] = alg;
        vbox->addWidget(radioData);


    }

    QMap<QRadioButton*, QString>::const_iterator kvp = currentAlgMap.constBegin();
    while (kvp != currentAlgMap.constEnd()) {
        if (kvp.value() == currentAlgorithm) {
            (kvp.key())->setChecked(true);
        }
        connect(kvp.key(), SIGNAL(clicked()), this, SLOT(on_alg_radio_checked()));
        ++kvp;
    }

    vbox->addStretch(1);
    groupBox->setLayout(vbox);
    return groupBox;
}

QGroupBox *MainWindow::createDataGroup() {
    QGroupBox *groupBox = new QGroupBox(tr("Data"));
    QVBoxLayout *vbox = new QVBoxLayout;
    foreach (DataSet* set, currentDataList){
        QRadioButton *radioData = new QRadioButton(set->getName());
        // put dataset and corresponding radiobutton in map
        currentDataMap[radioData] = set;
        vbox->addWidget(radioData);

    }

    QMap<QRadioButton*, DataSet*>::const_iterator kvp = currentDataMap.constBegin();
    while (kvp != currentDataMap.constEnd()) {
        if (kvp.value() == currentDataSet) {
            (kvp.key())->setChecked(true);
        }
        connect(kvp.key(), SIGNAL(clicked()), this, SLOT(on_data_radio_checked()));
        ++kvp;
    }
    //set data set algorithm name
    currentDataSet->setAlgName(currentAlgorithm);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);
    return groupBox;

}

QGraphicsView *MainWindow::createGraphicsWindow() {
    graphicsView = new QGraphicsView();
    graphicsScene = new QGraphicsScene();

    graphicsView->setScene(graphicsScene);
    initGraphicsItem();
    return graphicsView;
}

void MainWindow::initGraphicsItem() {

    foreach (QGraphicsItem *item, graphicsScene->items()) {
        if (!item->parentItem())
            //topLevels << item;
            graphicsScene->removeItem(item);
    }
    // update viewport
    (graphicsView->viewport())->update();

    graphicsScene->setSceneRect(QRect(QPoint(0,0), QPoint(graphicsView->width(), graphicsView->height())));
    graphicsScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    QList<DataItem *> dataItems = (currentDataSet)->getItems();
    for (int i = 0; i < dataItems.size(); ++i) {
           DataItem *dataItem = dataItems[i];
           double scenePosX = dataItem->getScenePosX();
           double scenePosY = dataItem->getScenePosY();
           dataItem->setPos( scenePosX, scenePosY);
           graphicsScene->addItem(dataItem);
       }

}

// slots to connect with data selection, set/update current data
 void MainWindow::on_data_radio_checked(){
     // e.g. check with member variable _foobarButton

        QRadioButton* button = dynamic_cast<QRadioButton*>(sender());
        QMap<QRadioButton*, DataSet*>::const_iterator i = currentDataMap.find(button);
        // just get the first match, as there can only be one
        if (i != currentDataMap.end() && i.key() == button) {
            DataSet* set = currentDataMap[button];
            // reset data to original

            currentDataSet = set;
            currentDataSet->initState(currentAlgorithm);

            initGraphicsItem();
        } else {
            qDebug() << "Error in on_data_radio_checked";
            return;
        }


 }

 // slots to connect with data selection, set/update current data
  void MainWindow::on_alg_radio_checked(){
      // e.g. check with member variable _foobarButton

         QRadioButton* button = dynamic_cast<QRadioButton*>(sender());
         QMap<QRadioButton*, QString>::const_iterator i = currentAlgMap.find(button);
         // just get the first match, as there can only be one
         if (i != currentAlgMap.end() && i.key() == button) {

             QString alg = currentAlgMap[button];

<<<<<<< HEAD
=======
             currentAlgorithm = alg;
             // warning:: must set alg name before init state
             currentDataSet->initState(alg);

>>>>>>> mergesortBranch
             initGraphicsItem();
         } else {
             qDebug() << "Error in on_alg_raio_checked";
             return;
         }

  }


