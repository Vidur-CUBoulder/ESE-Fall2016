/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Example RF Radio Ping Pair
 *
 * This is an example of how to use the RF24 class.  Write this sketch to two different nodes,
 * connect the role_pin to ground on one.  The ping node sends the current time to the nRF module,
 * which drives the LEDs.
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include "../nRF24L01.h"
 using namespace std;


#include "RF24.h"

// Hardware configuration

RF24 radio(115, 117);


// sets the role of this unit in hardware.  Connect to GND to be the 'pong' receiver
// Leave open to be the 'ping' transmitter
const int role_pin = 7;

// Topology

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

/*
 *  Role management
 *  Set up role.  This sketch uses the same software for all the nodes
 *  in this system.  Doing so greatly simplifies testing.  The hardware itself specifies
 *  which node it is.
 *  This is done through the role_pin
 *  The various roles supported by this sketch
 */

typedef enum { role_ping_out = 1, role_pong_back } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

// The role of the current running sketch
role_e role;

void setup(void)
{

  // Setup and configure rf radio
  radio.begin();

  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15,15);

  // optionally, reduce the payload size.  seems to
  // improve reliability
  radio.setChannel(0x4c);
  radio.setPALevel(RF24_PA_MAX);

  // Open pipes to other nodes for communication

  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.
  // Open 'our' pipe for writing
  // Open the 'other' pipe for reading, in position #1 (we can have up to 5 pipes open for reading)

  if ( role == role_ping_out )
  {
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
  }
  else
  {
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
  }

  // Start listening
  radio.startListening();

  // Dump the configuration of the rf unit for debugging
  radio.printDetails();
}

void rcv_loop(void)
{
	radio.write_register(CONFIG, _BV(MASK_RX_DR));
	
	if (radio.read_register(CONFIG) == 0x40)
	{
		 cout << "LED Flash Start" << endl;
		 FILE *Flash = NULL;
		 const char *pwdBright="/sys/class/leds/beaglebone:green:usr0/brightness";

		 for(int i=0; i<10; i++){
		    if((Flash = fopen(pwdBright, "r+")) != NULL){
		      fwrite("1", sizeof(char), 1, Flash);
		      fclose(Flash);
		    }
		    usleep(1000000);

		    if((Flash = fopen(pwdBright, "r+")) != NULL){
		      fwrite("0", sizeof(char), 1, Flash);
		      fclose(Flash);
		    }
		    usleep(1000000);
		  }
		  cout << "LED Flash End" << endl;
	}
}

int main(int argc, char** argv)
{
        setup();
        while(1)
                rcv_loop();

        return 0;
}
