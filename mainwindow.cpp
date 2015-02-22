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
    currentAlgorithm->setDataSet(*currentDataSet);

    grid->addWidget(createAlgorithmGroup(), 0, 0);
    grid->addWidget(createDataGroup(), 1, 0);
    grid->addWidget(createGraphicsWindow(), 0, 1);

    setWindowTitle(tr("Algorithm Animation"));
    resize(480, 320);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QGroupBox *MainWindow::createAlgorithmGroup() {
    QGroupBox *groupBox = new QGroupBox(tr("Algorithms"));
    QVBoxLayout *vbox = new QVBoxLayout;
    foreach (Algorithm* alg, currentAlgList){
        QRadioButton *radioData = new QRadioButton(alg->getName());
        currentAlgMap[radioData] = alg;
        vbox->addWidget(radioData);
    }
    QList<QRadioButton *> buttons = currentAlgMap.keys();
    // check the first button
    buttons[0]->setChecked(true);
    //set signal slots

    vbox->addStretch(1);
    groupBox->setLayout(vbox);
    return groupBox;
    return groupBox;
}

QGroupBox *MainWindow::createDataGroup() {
    QGroupBox *groupBox = new QGroupBox(tr("Data"));
    QVBoxLayout *vbox = new QVBoxLayout;
    foreach (DataSet* set, currentDataList){
        QRadioButton *radioData = new QRadioButton(set->geName());
        // put dataset and corresponding radiobutton in map
        currentDataMap[radioData] = set;
        vbox->addWidget(radioData);

    }
    QList<QRadioButton *> buttons = currentDataMap.keys();
    // check the first button
    buttons[0]->setChecked(true);
    for (int i = 0; i < buttons.size(); ++i) {
     // set signal to init dataset graphics scene
        connect(buttons[i], SIGNAL(clicked()), this, SLOT(on_data_radio_checked()));
    }
    vbox->addStretch(1);
    groupBox->setLayout(vbox);
    return groupBox;

}

QGraphicsView *MainWindow::createGraphicsWindow() {
    graphicsView = new QGraphicsView();
    graphicsScene = new QGraphicsScene();

    initGraphicsItem();

    graphicsView->setScene(graphicsScene);
    return graphicsView;
}

void MainWindow::initGraphicsItem() {
    //graphicsScene->clear();
    //QList<QGraphicsItem *> topLevels;
    foreach (QGraphicsItem *item, graphicsScene->items()) {
        if (!item->parentItem())
            //topLevels << item;
            graphicsScene->removeItem(item);
    }
    //qDeleteAll(topLevels);

    graphicsScene->setSceneRect(-300, -300, 600, 600);
    graphicsScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    QList<DataItem *> dataItems = currentDataSet->getItems();
    for (int i = 0; i < dataItems.size(); ++i) {
           DataItem *dataItem = dataItems[i];
           dataItem->setPos(50 + 10*i, 50);
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
            currentDataSet = set;
            currentAlgorithm->setDataSet(*currentDataSet);
            initGraphicsItem();
        } else {
            qDebug() << "Error in on_data_radio_checked";
            return;
        }
     /*
        // e.g. casting to the class you know its connected with
        QPushButton* button = dynamic_cast<QPushButton*>(sender());
        if( button != NULL )
        {
           ...
        }*? */

 }
