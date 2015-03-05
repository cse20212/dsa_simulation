#include "insertionsort.h"
#include "dataset.h"

InsertionSort::InsertionSort(int innerCounter, int outterCounter): Algorithm("InsertionSort", "Sorting"), innerCounter(innerCounter),
    outterCounter(outterCounter)
{

}

InsertionSort::~InsertionSort()
{

}

bool InsertionSort::inOrder() {
    DataSet* set = getDataSet();
    QList<DataItem*>* items = set->getItems();
    int n = items->size();
    for (int i = 1; i < n; i++) {
        // if item at i is smaller than i-1
        if ((items->at(i))->getSize() < (items->at(i-1))->getSize()) {
            return false;
        }
    }
    return true;
}

void InsertionSort::advanceAlg(){
    // pure virtual; set dataset to the state after next step
    if (!inOrder()) {
        DataSet* set = getDataSet();
        QList<DataItem*>* items = set->getItems();
        // algorithm finished
         if (outterCounter > set->getSize() - 1) {
            //reset counters
            innerCounter = 1;
            outterCounter = 1;
            return;
        }
        // manipulate dataitems
        if ((*items)[innerCounter]->getSize() < (*items)[innerCounter-1]->getSize()){
            // swap
            items->swap(innerCounter, innerCounter-1);
            (*items)[innerCounter]->setIndex(innerCounter);
            (*items)[innerCounter - 1]->setIndex(innerCounter - 1);
            // advance two items
            emit updateGraphics();
        }
        // advance the counter
        if (innerCounter == 1) {
            outterCounter++;
            innerCounter = outterCounter;
        } else {
            innerCounter--;
        }
    }
}
void InsertionSort::back(){
    QString name1 = "Algorithm::name";
}
