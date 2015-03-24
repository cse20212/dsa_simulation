#include "selectionsort.h"

SelectionSort::SelectionSort(int innerCounter, int outterCounter):Algorithm("SelectionSort", "Sorting"), innerCounter(innerCounter), outterCounter(outterCounter)
{

}

SelectionSort::~SelectionSort()
{

}

bool SelectionSort::inOrder() {
    DataSet* set = getDataSet();
    QList<DataItem*>* items = set->getItems();
    int n = items->size();
    for (int i=1; i<n; i++){
        if((items->at(i))->getSize() < (items->at(i-1))->getSize()){
            return false;
        }
    }
    return true;
}

void SelectionSort::resetCounter() {
    innerCounter=1;
    outterCounter=0;
}

void SelectionSort::advanceAlg(){
    DataSet* set = getDataSet();
    //pure virtual; set dataset to the state after next state
    if(outterCounter != (set->getSize() -1) | innerCounter!= set->getSize()){
        //if the data processing is not done
        set->removeAllPointed(); //clean up and make all data items not pointed at
        QList<DataItem*>* items = set->getItems();
        //algorithm finished
        if(outterCounter > set->getSize() - 1){
            //reset counters
            resetCounter();
            set->removeAllPointed();
            emit updateGraphics();
            return;
        }


        DataItem* outer = (*items).at(outterCounter);
        DataItem* inner = (*items).at(innerCounter);

        Min=outer->getSize();
        iMin=outterCounter;

        //manipulate data items
        if(inner->getSize() < outer->getSize()){
            Min = inner->getSize();
            iMin = innerCounter;
        }

        if(innerCounter == (set->getSize()-1)){
            if(iMin!=outterCounter){
                items->swap(iMin, outterCounter);
                outer->setIndex(iMin);
                inner->setIndex(outterCounter);
            }
        }

        //set data items that are being processed
        (*items).at(innerCounter) ->setpointed(1);
        (*items).at(outterCounter)->setpointed(1);

        //advance two items
        emit updateGraphics();

        //advance the counter
        if(innerCounter == (set->getSize()-1)){
            outterCounter++;
            innerCounter=outterCounter+1;
        }else{
            innerCounter++;
        }
    }else {
        //already in order
        //reset counters
        resetCounter();
        set->removeAllPointed();
        emit updateGraphics();
    }
}

void SelectionSort::backAlg(){
        QString name1 = "Algorithm::name";
}
