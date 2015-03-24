#include "mergesort.h"
#include "dataset.h"

MergeSort::MergeSort(int counterOne, int counterTwo): Algorithm("MergeSort", "Sorting"), counterOne(counterOne),
    counterTwo(counterTwo)
{
    replaceIndex = 0;


}

MergeSort::~MergeSort()
{

}
MergeSort::MergeSort(MergeSort& that){

}

MergeSort& MergeSort::operator=(const MergeSort& right){

}

bool MergeSort::inOrder() {

    int n = (getDataSet()->getItems())->size();
    if (sortedIndex.empty()) {
        return false;
    } else if (sortedIndex.at(0) == n) {
        return true;
    } else {
        return false;
    }

}

void MergeSort::resetCounter() {

    counterOne = 0;
    counterTwo = 0;
    replaceIndex = 0;
}

void MergeSort::advanceAlg(){
    DataSet* set = getDataSet();
    QList<DataItem*>* items = set->getItems();

    // pure virtual; set dataset to the state after next step
    //if (!inOrder() | innerCounter != 0 ) {

    if (!inOrder()) {
        if ( arrayOne.size()==0 && arrayTwo.size()==0) {
            // temp arrays are empty, import new temp arrays
            int n = sortedIndex.size();
            if (n == 0) {
                // beginning of sorting
                arrayOne.append(items->at(0));
                arrayTwo.append(items->at(1));
                markInTemp(items->at(0));
                markInTemp(items->at(1));
            } else if (n == 1) {
                int t = sortedIndex.at(0);
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
                } else {

                }
            }


        } else {
            // continue putting temp arrays back to main array
            if (arrayOne.size() > 0 && arrayTwo.size() > 0) {
                DataItem* left = arrayOne.at(0);
                DataItem* right = arrayOne.at(0);
                if (left->getSize() < right->getSize()) {
                    arrayOne.removeAt(0);
                    markInArray(left);
                    left->setIndex(replaceIndex);
                    replaceIndex++;
                } else {
                    arrayTwo.removeAt(0);
                    markInArray(right);
                    right->setIndex(replaceIndex);
                    replaceIndex++;
                }
            } else if (arrayOne.size() > 0 ){
                DataItem *item = arrayOne.at(0);
                markInArray(item);
                item->setIndex(replaceIndex);
                replaceIndex++;
            } else if (arrayTwo.size() > 0 ) {
                DataItem *item = arrayTwo.at(0);
                markInArray(item);
                item->setIndex(replaceIndex);
                replaceIndex++;
            }
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
void MergeSort::markInTemp(DataItem* item) {
    int yPos = item->getScenePosY();

    item->setScenePosY(yPos + 20);
}

void MergeSort::markInArray(DataItem* item) {
    int yPos = item->getScenePosY();

    item->setScenePosY(yPos - 20);
}


void MergeSort::backAlg(){
    int name = 4;

}


int MergeSort::getReplaceIndex(){
    return replaceIndex;
}
int MergeSort::getCounterOne(){
    return counterOne;
}
int MergeSort::getCounterTwo(){
    return counterTwo;
}

QList<int> MergeSort::getSortedIndex(){
    return sortedIndex;
}

void MergeSort::setReplaceIndex(int n){
    replaceIndex = n;
}

void MergeSort::setCounterOne(int n){
    counterOne = n;
}

void MergeSort::setCounterTwo(int n){
    counterTwo = n;
}

void MergeSort::setSortedIndex(QList<int>){

}
