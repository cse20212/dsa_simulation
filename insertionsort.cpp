#include "insertionsort.h"
#include "dataset.h"

InsertionSort::InsertionSort(int innerCounter, int outterCounter): Algorithm("InsertionSort", "Sorting"), innerCounter(innerCounter),
    outterCounter(outterCounter)
{

}

InsertionSort::~InsertionSort()
{

}

void InsertionSort::advanceAlg(){
    // pure virtual; set dataset to the state after next step
    QString name = "Algorithm::name";

    DataSet* set = getDataSet();
    QList<DataItem*>* items = set->getItems();
    // algorithm finished
    if (outterCounter > set->getSize() - 1)
        return;
    // manipulate dataitems
    if ((*items)[innerCounter]->getSize() < (*items)[innerCounter-1]->getSize()){
        // swap
        /*
        int temp = items[innerCounter]->getIndex();
        items[innerCounter]->setIndex(items[innerCounter-1]->getIndex());
        items[innerCounter-1]->setIndex(temp); */

        items->swap(innerCounter, innerCounter-1);
        (*items)[innerCounter]->setIndex(innerCounter);
        (*items)[innerCounter - 1]->setIndex(innerCounter - 1);
        // advance two items
        //items[innerCounter]->advance(1);
        //items[innerCounter-1]->advance(1);
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
void InsertionSort::back(){
    QString name1 = "Algorithm::name";
}
