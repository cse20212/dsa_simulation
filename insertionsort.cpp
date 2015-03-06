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

void InsertionSort::resetCounter() {
    innerCounter = 1;
    outterCounter = 1;
}

void InsertionSort::advanceAlg(){
    DataSet* set = getDataSet();
    // pure virtual; set dataset to the state after next step
    if (!inOrder()) {      
        set->removeAllPointed();    // clean up and make all data items not pointed at
        QList<DataItem*>* items = set->getItems();
        // algorithm finished
         if (outterCounter > set->getSize() - 1) {
            //reset counters
            resetCounter();
            set->removeAllPointed();
            emit updateGraphics();
            return;
        }
         DataItem* itemOne = (*items).at(innerCounter);
         DataItem* itemTwo = (*items).at(innerCounter-1);

        // manipulate dataitems
        if (itemOne->getSize() < itemTwo->getSize()){
            // swap
            items->swap(innerCounter, innerCounter-1);
            itemTwo->setIndex(innerCounter);    // index has already swaped
            itemOne ->setIndex(innerCounter - 1);
            //set dataitems that are being processed
            (*items).at(innerCounter-1) ->setpointed(1);
            (*items).at(outterCounter) ->setpointed(1);
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
    } else {
        // already in order
        if (outterCounter > set->getSize() - 1) {
           //reset counters
           resetCounter();
           set->removeAllPointed();
           emit updateGraphics();
           return;
       }
    }
}
void InsertionSort::back(){
    QString name1 = "Algorithm::name";
}
