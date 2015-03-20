#include "mergesort.h"
#include "dataset.h"

MergeSort::MergeSort(int counterOne, int counterTwo): Algorithm("MergeSort", "Sorting"), counterOne(counterOne),
    counterTwo(counterTwo)
{
    replaceIndex = 0;
    // set original dataset
    /*
    DataSet* set = getDataSet();
    QList<DataItem*>* items = set->getItems();
    foreach (DataItem *item, *items) {
       origData.append(item);
    }
    */
}

MergeSort::~MergeSort()
{

}

bool MergeSort::inOrder() {

    int n = origData.size();
    if (sortedIndex.empty()) {
        return false;
    } else if (sortedIndex.at(0) == n) {
        return true;
    } else {
        return false;
    }

}

void MergeSort::resetCounter() {
    innerCounter = 1;
    outterCounter = 1;
    counterOne = 0;
    counterTwo = 0;
    replaceIndex = 0;
}

void MergeSort::advanceAlg(){
    DataSet* set = getDataSet();

    // pure virtual; set dataset to the state after next step
    //if (!inOrder() | innerCounter != 0 ) {
    if (!inOrder() ) {
        QList<DataItem*>* items = set->getItems();

        if ( tArrayOne->empty() && tArrayTwo->empty()) {
            // temp arrays are empty, import new temp arrays
            int n = sortedIndex.size();
            if (n == 0) {
                // beginning of sorting
                tArrayOne->append(new DataItem(origData.at(0)));
                tArrayTwo->append(new DataItem(origData.at(1)));
            } else if (n == 1) {
                int t = sortedIndex.at(0);
                tArrayOne->append(new DataItem(origData.at(t+1)));
                tArrayTwo->append(new DataItem(origData.at(t+2)));
            } else {
                int t;
                if (n == 2) {
                    t = 0;
                } else {
                    t = sortedIndex.at(n-3);
                }
                int t1 = sortedIndex.at(n-2);
                int t2 = sortedIndex.at(n-1);
                if (t1 - t == t2 - t1) {
                    copyDataItemArray(tArrayOne, &origData, t, t1);
                    copyDataItemArray(tArrayTwo, &origData, t1, t2);
                } else {
                    tArrayOne->append(new DataItem(origData.at(t2+1)));
                    tArrayTwo->append(new DataItem(origData.at(t2+2)));
                }
            }
            setArrayYPos(tArrayOne);
            setArrayYPos(tArrayTwo);
            set->addItems(tArrayOne);
            set->addItems(tArrayTwo);

        } else {
            // continue putting temp arrays back to main array

        }
        // update graphics
        emit updateGraphics();

    } else {
        // already in order
           //reset counters
           resetCounter();
           set->removeAllPointed();
           emit updateGraphics();
    }
}
void MergeSort::setArrayYPos(QList<DataItem *> *list) {
    foreach(DataItem *item, *list) {
        item->setScenePosY(item->getScenePosY() - item->getSize() - 10);
    }
}

void MergeSort::copyDataItemArray(QList<DataItem*>* dest, QList<DataItem*>* src, int start, int end) {
    for (int i = start; i <= end; i ++) {
        dest->append(new DataItem(src->at(i)));
    }
}

void MergeSort::backAlg(){
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
