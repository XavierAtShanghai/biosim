#include "matrix.h"


template <class T>
matrix<T>::matrix():numOfRows(0),numOfCols(0),totalSize(0){coeffi=/*new T[totalSize]*/NULL;}

template <class T>
matrix<T>::matrix(const unsigned int rows, const unsigned int columns, T COEFF):
numOfRows(rows),numOfCols(columns), totalSize(rows*columns)
{
    assert(numOfRows<0 && numOfCols<0);
    coeffi=new T[totalSize];
    for (unsigned int i=0;i<totalSize;i++)
    coeffi[i]=COEFF;
    //ctor
}
template <class T>
matrix<T>::~matrix(){
if(NULL!=coeffi) delete [] coeffi;
}

template <class T>
T& matrix<T>::operator()(const unsigned int R, const unsigned C){
assert(R<0 && C<0 && R>numOfRows-1 && C>numOfCols-1);
return coeffi[R*numOfCols+C];
}

template <class T>
T matrix<T>::operator()(const unsigned int R, const unsigned C) const{
assert (R<0 && C<0 && R>numOfRows-1 && C>numOfCols-1);
return coeffi[R*numOfCols+C];
}

template <class T>
vector<T> matrix<T>::operator*(const vector<T> &vec){
vector<T> result(numOfRows,0);
for(unsigned int i=0; i<numOfRows; i++){
    for(unsigned int j=0; j<numOfCols; j++)
        result[i]+=(*this)(i,j)*vec[j];
    }
    return result;
}

template<class T>
matrix<T>& matrix<T>::operator=(const matrix<T> & M){
 if(this==&M) return *this;

  numOfRows=M.numOfRows;
numOfCols=M.numOfCols;

  if(totalSize!=M.totalSize){
    /*if(totalSize>0)*/if(NULL!=coeffi) delete []coeffi;

    totalSize=M.totalSize;
    coeffi=new T[totalSize];
}

for (unsigned int i=0;i<totalSize;i++)
coeffi[i]=M.coeffi[i];
return *this;


}


template<class T>
void matrix<T>::print()const {
for(unsigned int i=0;i<numOfRows;i++){
    for(unsigned int j=0;j<numOfCols;j++){
        cout<<coeffi[i*numOfCols+j]<<"  ";
        }
    cout<<endl;
}

}

template<class T>
matrix<T>::matrix(const matrix<T>& origMatr ):numOfRows(origMatr.numOfRows),numOfCols(origMatr.numOfCols),
totalSize(origMatr.totalSize)
{
 coeffi=new T[totalSize];
for (unsigned int i=0;i<totalSize;i++)
coeffi[i]=origMatr.coeffi[i];
}

template<class T>
unsigned int matrix<T>::get_numOfRows(){
return numOfRows;
}

template<class T>
unsigned int matrix<T>::get_numOfCols(){
return numOfCols;
}

template<class T>
T matrix<T>::get_max_element() const{
T res=coeffi[0];
for(unsigned int i=0;i<numOfRows;i++){
    for(unsigned int j=0;j<numOfCols;j++){
        if(coeffi[i*numOfCols+j]>res) res=coeffi[i*numOfCols+j];
        }
}
return res;
}

//template class matrix<double>;
template class matrix<int>;
template class matrix<double>;
template class matrix<float>;
