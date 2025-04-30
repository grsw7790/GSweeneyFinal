/*
 * Scheduler.h
 *
 *  Created on: Jan 28, 2025
 *      Author: griff
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#include "stdint.h"
 
#define	DROP_EVENT		(1 << 0)
 
uint32_t getScheduledEvents();
void addSchedulerEvent(uint32_t event);
void removeSchedulerEvent(uint32_t event);
 
#endif /* SCHEDULER_H_ */