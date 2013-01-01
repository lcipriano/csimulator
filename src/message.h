/*
 * message.h
 *
 *  Created on: Dec 29, 2012
 *      Author: lcipriano
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <stdio.h>

#define MAX_MSG_LEN 128

typedef struct {
	char str[MAX_MSG_LEN];
} Message;

void sendMsg(Message m);

void sendMsgTo(FILE *f, Message m);

#endif /* MESSAGE_H_ */
