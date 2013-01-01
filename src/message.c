/*
 * message.c
 *
 *  Created on: Dec 29, 2012
 *      Author: lcipriano
 */

#include "message.h"

void sendMsg(Message m) {
	printf("%s\n", m.str);
}

void sendMsgTo(FILE *f, Message m) {
	fprintf(f, "%s\n", m.str);
}
