/* Zain Ul Mustafa 2017 */



//Rules:

/*

1. Check if connection with Arduino is made

2. If Arduino is connected then take input from user in a String

3. Make a char array of the size of string + 1

4. Copy the whole string into the char array

5. Add escape sequence \n because this represents the end of a line in Serial Comm port

6. Write the whole char array into the buffer (a buffer takes the info forward to the Serial Comm Port)

7. Read from the Arduino if data is received successfully or if the action is taken as per needed

*/



//Connect with me:

/*	Twitter: http://www.twitter.com/ZainsOfficial/

	Facebook: http://www.facebook.com/ZainsOfficial/

	Github: http://github.com/ZainUlMustafa/

*/



/* This software is allowed for any user to copy, modify, merge, and distribute in any of his/her project.

Complete repository for this project is available on github. If you find this project anywhere except github, it

is to be noted that it is not made by me and not distributed by me.

Please follow this link to get to the original repository of github for this project

Github shortened link (no spam and no ads): http://bit.ly/2vGkinQ

*/



/* PC 2 Arduino */



#include<iostream>

using namespace std;

#include <string>

#include <stdlib.h>

#include "SerialPort.h"



char output[MAX_DATA_LENGTH];

char incomingData[MAX_DATA_LENGTH];



// change the name of the port with the port name of your computer

// must remember that the backslashes are essential so do not remove them

char *port = "\\\\.\\COM3";



int main(){

	SerialPort arduino(port);

	if(arduino.isConnected()){

		cout<<"Connection made"<<endl<<endl;

	}

	else{

		cout<<"Error in port name"<<endl<<endl;

	}

	while (arduino.isConnected()) {

    arduino.readSerialPort(output, MAX_DATA_LENGTH);
    if(output[0] == '1' || output[0] == '2' || output[0] == '3' || output[0] == '4')
    {
        cout << output;
        output[0] = NULL;
        output[1] = NULL;
        //for(int i = 0; i < 10; i++)
        //{
          //  output[i] = NULL;

        //}
    }


    //delete[] charArray;

 }

	return 0;

}
