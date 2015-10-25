//
//  OccurrenceList.cpp
//  PCC
//
//  Created by Rafael Nunes G. da Silveira on 24/10/2015.
//  Copyright © 2015 Rafael Nunes. All rights reserved.
//

#include "OccurrenceList.h"
#include <string>

using namespace std;

OccurrenceListNode::OccurrenceListNode(string occurrence)
: occurrence(occurrence) {}

OccurrenceList::OccurrenceList() {
    this->head = NULL;
    this->tail = NULL;
}

void OccurrenceList::push_front(string newOccurrence) {
    OccurrenceListNode *newListHead = new OccurrenceListNode(newOccurrence);

    if(this->head != NULL)
        newListHead->next = this->head;

    this->head = newListHead;
}

void OccurrenceList::push_back(OccurrenceList *list) {
    if(this->tail != NULL)
        this->tail->next = list->head;
    else
        this->head = list->head;
    this->tail = list->tail;
}
