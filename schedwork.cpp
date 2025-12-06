//pasted from vscode to run Tests

#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool fillSchedule(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, vector<int>& used, int day, int slot);


// Add your implementation of schedule() and other helper functions here

bool schedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched){
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();

    // Add your code below

    int n = avail.size();
    int k = avail[0].size();

    sched.resize(n, vector<Worker_T>(dailyNeed, INVALID_ID));
    vector<int> used(k, 0);

    return fillSchedule(avail, dailyNeed, maxShifts, sched, used, 0, 0);
}

bool fillSchedule(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts,
DailySchedule& sched, vector<int>& used, int day, int slot){
  int n = avail.size();
  int k = avail[0].size();

  if(day == n){
    return true;
  }

  if(slot == (int)dailyNeed){
    return fillSchedule(avail, dailyNeed, maxShifts, sched, used, day + 1, 0);
  }

  for(int w = 0; w < k; w++){
    if(avail[day][w] && used[w] < (int)maxShifts){
      
      bool already = false;

      for(int i = 0; i < slot; i++){
        if(sched[day][i] == (Worker_T)w){
          already = true;
        }
            }
        if(already == true){
          continue;
        }

        sched[day][slot] = w;
        used[w]++;

        if(fillSchedule(avail, dailyNeed, maxShifts, sched, used, day, slot + 1)){
          return true;
        }

        used[w]--;
        sched[day][slot] = INVALID_ID;
        }
    }

    return false;
}

