//
//  CList.hpp
//  P7-Hongchi
//
//  Created by Hongchi Liu on 3/22/18.
//  Copyright © 2018 hongchi liu. All rights reserved.
//

#ifndef CList_hpp
#define CList_hpp

#include <fstream>
#include "tools.hpp"
#include "Player.hpp"

// CList forward declaration.
template< class T >
class CList;

// Cell declaration.
template< class T >
class Cell{
private:
        friend class CList<T>; // use friend class.
        T* plyr;
        Cell* next;
        int cellcnt = 0;
        Cell(T* p){plyr = p;next = this;cellcnt++;};
        ~Cell(){cout<<"$$$FREE MEMORY$$$ Cell count: "<<--cellcnt<<endl;};
};

// CList follow declaration.
template< class T >
class CList{
private:
    int pnum;
    Cell<T>* phead;
    Cell<T>* ptail;
    Cell<T>* pcurr;
    // point to Cell before current position.
    Cell<T>* prior;
public:
    CList();
    ~CList();
    int count(){return pnum;};
    bool empty(){return pnum == 0;};
    
    ostream& print(ostream&);
    void insertBack(T*);
    T* first();  
    T* next();
    T* remove();
};

// CList implementation.
template<class T> 
CList<T>::
CList(){
    pnum = 0;
    phead = NULL;
    ptail = NULL;
    pcurr = NULL;
    // point to Cell before current position.
    prior = NULL;
};

template<class T> 
CList<T>::
~CList(){
    for(int c = pnum; c!=0;--c){
        delete next();
    }
};

template<class T>
ostream& CList<T>::
print(ostream& out){
    if(pnum == 0) return out<<"CList is empty."<<endl;
    // print 1st player.
    out<<*(first());
    // print follow players.
    for(;;){
        if(pcurr != ptail) out<<*(next());
        if(pcurr == ptail) break;
    }
    prior = ptail;
    pcurr = phead;
    return out;
};

template<class T>
void CList<T>::
insertBack(T* p){
    Cell<T>* pT = new Cell<T>(p);
    // first player.
    if(phead == NULL){
        phead = pT;        // phead point to first Cell.
        ptail = pT;        // ptail alse point to first Cell.
        pT->next = phead;  // point to head as a cycle.
    }
    // not the first player.
    else{
        ptail->next = pT;  // link to new Cell.
        ptail = pT;        // move ptail point new Cell
        pT->next =  phead; // point to head as a cycle.
    }
    ++pnum;                // add # of Cells.
};

template<class T>
T* CList<T>::
first(){
    if( empty() ) fatal("CList is empty.");
    pcurr = phead;         // set pointer.
    return pcurr->plyr;    // return first player.
};

template<class T>
T* CList<T>::
next(){
    if( empty() ) fatal("CList is empty.");
    prior = pcurr;         // save the last position.
    pcurr = pcurr->next;   // set pcurr to pcurr's pcell.
    return pcurr->plyr;    // return next player.
};

template<class T>
T* CList<T>::
remove(){
    // remove the first Cell.
    if(pcurr == phead){
        phead = pcurr->next;
        delete pcurr;
        pcurr = phead;
        ptail->next = phead;
    }
    // remove Cell is not the first one.
    else{
        prior->next = pcurr->next;
        delete pcurr;
        pcurr = pcurr->next;
    }
    --pnum;
    // CList is empty.
    if( empty() ) 
    {
        phead = NULL;
        ptail = NULL;
        pcurr = NULL;
        prior = NULL;
        return NULL;
    }
    else  return pcurr->plyr;
};

template< class T >
inline ostream& operator << (ostream& out, CList<T>& clist){ return clist.print(out); };
#endif /* CList_hpp */