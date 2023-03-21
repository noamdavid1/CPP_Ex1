#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AdptArray_
{
    PElement* element;
    size_t arrsize;
    COPY_FUNC cf;
    DEL_FUNC df;
    PRINT_FUNC pf;
}AdptArray;

//create a new adptive array and initialize the array. 
PAdptArray CreateAdptArray(COPY_FUNC cf, DEL_FUNC df,PRINT_FUNC pf){
PAdptArray adp= (PAdptArray)malloc(sizeof(AdptArray));
if(!adp){
    return NULL;
}else{
    adp->arrsize=0;
    adp->cf=cf;
    adp->df=df;
    adp->pf=pf;
    adp->element= NULL;
    return adp;
}
}

//freeing memory of the array
void DeleteAdptArray(PAdptArray adp){
if (adp==NULL){
    return;
}else{
    for (size_t i = 0; i < adp->arrsize; i++)
    {
        if (adp->element[i]!= NULL){ //checking whether the specific object at the given index is null.
            adp->df(adp->element[i]);
            adp->element[i]=NULL;
        }
    } free(adp);
}
}

//this function copies a given element to a given position in the array.
Result SetAdptArrayAt(PAdptArray adp, int index, PElement pelement){
if(index<0){ //the index cannot be a negetive number. 
    return FAIL;
}else{
if (index>=adp->arrsize){ //if the index is larger than the size of the array we will built a larger array. 
PElement new_element= (PElement*)calloc((index+1),sizeof(PElement));    
if(!new_element){
    return FAIL;
}memcpy(new_element,adp->element,(adp->arrsize*(sizeof(PElement))));//copies the old array to the new array that we build.
free(adp->element); //free the old array.
adp->element=new_element; //update the element array in the struct and the struct size. 
adp->arrsize=index+1;
}
if(adp->element[index]==NULL){ //if the requested position is null we will insert the given element.
    adp->element[index]=pelement;
    return SUCCESS;
}else{
    adp->df(adp->element[index]); //if the requested position is not null we will delete the current element and insert the given element.
    adp->element[index]=pelement;
    return SUCCESS;
}   
}
}
//this function returns a copy of a member at the given index.
PElement GetAdptArrayAt(PAdptArray adp, int index){
if (adp!=NULL && index< adp->arrsize){
    if(adp->element[index]!=NULL){
        return adp->cf(adp->element[index]);
    }return NULL;
}else 
return NULL;
}

//this function returns the size of the array.
int GetAdptArraySize(PAdptArray adp){
size_t temp= sizeof(adp);
if(adp!=NULL){
    return temp;
}else{
    return -1;//returns -1 if the array was not initialized succsessfully.
}
}
//this function prints the elements of the array.
void PrintDB(PAdptArray adp){
    if (adp!=NULL)
    {
       for (size_t i = 0; i < adp->arrsize; i++)
       {
        if (adp->element[i]!=NULL)
        {
             adp->pf(adp->element[i]);
        } else{continue;}
       }
    }else printf("there is no elements to print");   
}



