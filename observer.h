/* * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                   */
/*  Program:  MyTunes Music Player                   */
/*  Contributors: Alexander Kuhn (101023154)	     */
/*  Author:   Louis Nel                              */
/*  Date:     21-SEP-2017                            */
/*                                                   */
/*  (c) 2017 Louis Nel                               */
/*  All rights reserved.  Distribution and           */
/*  reposting, in part or in whole, requires         */
/*  written consent of the author.                   */
/*                                                   */
/*  COMP 2404 students may reuse this content for    */ 
/*  their course assignments without seeking consent */
/* * * * * * * * * * * * * * * * * * * * * * * * * * */
#ifndef _OBSERVER_H
#define _OBSERVER_H

#include <string.h> 
#include <iostream> 

#include "subject.h"
class Subject;
class Observer { 
  public:
  virtual ~Observer(void) {};
  virtual void update(Subject * subject){};
  virtual void update(Subject * subject, int deletion){}; //special update method only called when the subject is deleted: it makes sure the observer knows it is no longer observing
 

  int operator==(const Observer & obs) const { 
    return this == & obs; 
  }

}; 

#endif