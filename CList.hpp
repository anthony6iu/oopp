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

template< class T>
class CList; // forward declaration.

class Cell{
private:
        friend class CList<Cell>; // use friend class.
        Player* plyr;
        Cell* next;
        Cell(Player* p){plyr = p;next = this;};
};

template< class T >
class CList{
private:
    int pnum;
    T* phead;
    T* ptail;
    T* pcurr;
    // additional one.
    T* pbefore;
public:
    CList(){
        pnum = 0;
        phead = NULL;
        ptail = NULL;
        pcurr = NULL;
        // additional one.
        pbefore = NULL;
    };
    ~CList(){
    };
    int count(){return pnum;};
    bool empty(){return pnum == 0;};
    //
    ostream& print(ostream& out){
        if(pnum == 0) return out<<"CList is empty."<<endl;
        // print 1st player.
        out<<*(first());
        // print follow players.
        for(;;){
            if(pcurr != ptail) out<<*(next());
            if(pcurr == ptail) break;
        }
        pbefore = ptail;
        pcurr = phead;
        return out;
    };
    void insertBack(Player* p){
        T* pT = new T(p);
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
    Player* first(){
        if( empty() ) fatal("CList is empty.");
        pcurr = phead;         // set pointer.
        return phead->plyr;    // return first player.
        
    };  
    Player* next(){
        if( empty() ) fatal("CList is empty.");

        pbefore = pcurr;       // save the last position.

        pcurr = pcurr->next;   // set pcurr to pcurr's pcell.
        return pcurr->plyr;    // return next player.
    };
    void remove(){
        // CList is empty.
        if( empty() ) fatal("CList is empty.");
        // remove the first Cell.
        if(pcurr == phead){
            phead = pcurr->next;
            pcurr = phead;
        }
        // remove Cell is not the first one.
        else{
            pbefore->next = pcurr->next;
            pcurr = pcurr->next;
        }
        // if # == 0, set all point NULL as a new start.
        if(--pnum == 0){phead = NULL;ptail = NULL;pcurr = NULL;pbefore = NULL;}
    };
//end
};

template< class T >
inline ostream& operator << (ostream& out, CList< T >& clist){ return clist.print(out); };
#endif /* CList_hpp */