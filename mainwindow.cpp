#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRadioButton>
#include <QDebug>
#include <QTextBrowser>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QTimer>

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

    grid->addWidget(createAlgorithmGroup(), 0, 0, 2, 1);
    grid->addWidget(createDataGroup(), 2, 0, 2, 1);
    grid->addWidget(createGraphicsWindow(), 0, 1, 3, 5);
    grid->addWidget(createStateTextBox(), 3, 1, 1, 5);
    grid->addWidget(createPsuedoTextBox(), 0, 6, 4, 1);

    createActions();
    createToolBars();

    setWindowTitle(tr("Algorithm Animation"));
    resize(800, 400);

    timer = new QTimer(this);

    localDataPath = "/Users/cindywang/simulator/";
    QFile psuedoFile(localDataPath + "pseudocode/sorting/InsertionSort.txt");
    psuedoFile.open(QIODevice::ReadOnly);
    QTextStream stream(&psuedoFile);
    QString content = stream.readAll();
    psuedoFile.close();
    psuedoTextBox->setPlainText(content);


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::createActions() {
    nextFrame = new QAction(QIcon("next.png"), tr("Next"),this);
    nextFrame->setStatusTip(tr("Next Step"));
    connect(nextFrame, SIGNAL(triggered()), this, SLOT(go_forward()) );

    previousFrame = new QAction(tr("Back"),this);
    previousFrame->setStatusTip(tr("Previous Step"));
    connect(previousFrame, SIGNAL(triggered()), this, SLOT(go_back()) );

    toEnd = new QAction(tr("End"),this);
    toEnd->setStatusTip(tr("Continue to the end"));
    connect(toEnd, SIGNAL(triggered()), this, SLOT(to_end()) );

    toBegin = new QAction(tr("Begin"),this);
    toBegin->setStatusTip(tr("Continue to the start"));
    connect(toBegin, SIGNAL(triggered()), this, SLOT(to_start()) );

}

void MainWindow::to_end(){
    timer->stop();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(go_back()));

    connect(timer, SIGNAL(timeout()), this, SLOT(go_forward()));
    timer->start(500);
    //timer->singleShot(200, this, SLOT(go_forward()));
}

void MainWindow::to_start(){
    timer->stop();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(go_forward()));

    connect(timer, SIGNAL(timeout()), this, SLOT(go_back()));
    //timer->singleShot(200, this, SLOT(go_back()));
    timer->start(500);
}


void MainWindow::go_forward(){
    algStateTextBox->clear();
    QString stateString = currentDataSet->go_forward();
    algStateTextBox->setPlainText(stateString);
    graphicsScene->advance();

    // stop animation on finish
    if (stateString.contains("End")) {
        timer->stop();
    }
}

void MainWindow::go_back(){
    algStateTextBox->clear();
    QString stateString = currentDataSet->go_back();
    algStateTextBox->setPlainText(stateString);
    graphicsScene->advance();

    // stop animation on finish
    if (stateString.contains("Start")) {
        timer->stop();
    }
}

void MainWindow::createToolBars() {
    animationToolBar = addToolBar(tr("Next"));
    animationToolBar->addAction(nextFrame);
   // animationToolBar = addToolBar(tr("Back"));
    animationToolBar->addAction(previousFrame);
   // animationToolBar = addToolBar(tr("End"));
    animationToolBar->addAction(toEnd);
   // animationToolBar = addToolBar(tr("Start"));
    animationToolBar->addAction(toBegin);
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

QTextEdit *MainWindow::createStateTextBox() {
    algStateTextBox = new QTextEdit();
    algStateTextBox->setReadOnly(true);
    return algStateTextBox;
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
            //set->generateRand();
            currentDataSet = set;
            currentDataSet->setAlgName(currentAlgorithm);
            currentDataSet->generateRand();
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
             QString codeFilePath = localDataPath + "/pseudocode/" + currentGenAlg.getName() + "/" + alg + ".txt";
             QFile psuedoFile(codeFilePath);
             qDebug() << codeFilePath;
             psuedoFile.open(QIODevice::ReadOnly);
             QTextStream stream(&psuedoFile);
             QString content = stream.readAll();
             psuedoFile.close();
             psuedoTextBox->setPlainText(content);
             currentAlgorithm = alg;
             // warning:: must set alg name before init state
             currentDataSet->initState(alg);
             initGraphicsItem();

         } else {
             qDebug() << "Error in on_alg_raio_checked";
             return;
         }

  }

  QTextBrowser *MainWindow::createPsuedoTextBox() {
      psuedoTextBox = new QTextBrowser();
      psuedoTextBox->setReadOnly(true);
      return psuedoTextBox;
  }



