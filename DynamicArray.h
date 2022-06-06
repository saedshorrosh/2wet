//
// Created by Saed Shorrosh on 02/06/2022.
//

#ifndef INC_2WET_DYNAMICARRAY_H
#define INC_2WET_DYNAMICARRAY_H
template<class T>
class DynamicArray{
public:
    T  * arr;
    int max;
    T& operator[](unsigned int i){
        return arr[i];
    }
    const T& operator[](unsigned int i)const{
        return arr[i];
    }
    ~DynamicArray()
    {
        delete[] arr;
    }
    DynamicArray(){
        max=2;
        T * newArr= new T [max];
        arr=newArr;
    };
    DynamicArray& operator=(const DynamicArray<T> & t)=default;

};
#endif //INC_2WET_DYNAMICARRAY_H
