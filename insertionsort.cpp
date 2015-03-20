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
    //if (!inOrder() | innerCounter != 0 ) {
    if (outterCounter != set->getSize() | innerCounter != 0 ) {
        // if the data processing is not done
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

        }

        //set dataitems that are being processed
        (*items).at(innerCounter-1) ->setpointed(1);
        (*items).at(outterCounter) ->setpointed(1);
        // advance two items
        emit updateGraphics();

        // advance the counter
        if (innerCounter == 1) {
            outterCounter++;
            innerCounter = outterCounter;
        } else {
            innerCounter--;
        }
    } else {
        // already in order
           //reset counters
           resetCounter();
           set->removeAllPointed();
           emit updateGraphics();
    }
}
void InsertionSort::backAlg(){
    if (innerCounter == 1 && outterCounter == 1) {
        // initial step do nothing
    } else {
        DataSet *set = getDataSet();
        QList<DataItem*> *items = set->getItems();
        // remove the pointer at the current pointed items
        set->removeAllPointed();

        DataItem *currentPointed;
        DataItem *prevComparedItem; // item is previously compared
        DataItem *prevOutterItem;   // previous outter counter pointed item

        if (innerCounter == outterCounter) {
            // if last step updates the outterCounter
            innerCounter = 1;
            outterCounter --;
            currentPointed = (*items).at(0);
            prevComparedItem = (*items).at(1);
            if (prevComparedItem->getSize() > currentPointed->getSize()) {
                // swap back
                items->swap(0, 1);
                prevComparedItem->setIndex(0);
                currentPointed->setIndex(1);
            }
             (*items).at(0) ->setpointed(1);

        } else {
            currentPointed = (*items).at(innerCounter);
            prevComparedItem = (*items).at(innerCounter+1);
            prevOutterItem = (*items).at(outterCounter);
            if (prevComparedItem->getSize() > currentPointed->getSize()) {
                // swap back
                items->swap(innerCounter, innerCounter+1);
                prevComparedItem->setIndex(innerCounter);
                currentPointed->setIndex(innerCounter+1);
            }

            innerCounter = innerCounter + 1;
             (*items).at(innerCounter) ->setpointed(1);
        }

        // update graphics to previous step

        (*items).at(outterCounter) ->setpointed(1);
        emit updateGraphics();
    }
}
