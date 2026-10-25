
/*access navigation control
  Name: airline   Program
  Author: apocalypse coder0
  Date Started: 2018 /5/2
  Date Stop: 2018/5/2
  Version 1.0
  Description: C++ airline  Database System
*/
//TODO (#0#): Work on passenger_information
//TODO (#1#): Work on Reservation
//TODO (#2#): Work on Seat Assignment
//TODO (#3#): Work out the Bugs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <iostream>
#include <cctype>

struct flight;  //Forward Declaration of Flight structure

//Airline List Structure And Function Declarations

struct airline    //Structure for Airline node, includes strings for Airline name
{                //pointer locations to the next airline and also to the flight list for that airline
	char *airlinename;
	struct airline  *next;
	struct flight *node1;
} *start1 = NULL;

airline * create_airline_node(airline  *start1);  //Function Declarations
airline * enter_airline_info(airline  *node);
airline * delete_airline_node(airline  *start1);
void print_airline_list(airline  *start1);
airline * enter_flight_menu(airline  *start1);
void write_to_file(airline  *start1);
airline * read_from_file();
airline * airline_menu(airline  *start1);

//Flight List Structure And Function Declarations

struct passenger;  //Forward Declaration of passenger structure

struct flight   //Structure for flight node, includes strings for flightname, from, to and time with
{               //pointer locations to the next flight and also to the passenger list
	char *flightnumber;
	char *date_of_flight;
	char *departure_location;
	char *arrival_location;
	char *take_off_time;
	char *arrival_time;

	struct flight *next;
	struct passenger *node2;
	struct reservation *node3;
} *start2 = NULL;

struct reservation;  //forward declaration used by struct flight above

flight* create_flight_node(flight *start2);  //Function Declarations
flight* enter_flight_info(flight *node);
flight* delete_flight_node(flight *start2);
void print_flight_list(flight *start2);
flight* enter_passenger_menu(flight *start2);
flight* enter_reservation_menu(flight *start2);
flight* flight_menu(flight *start2);

//Passenger List Structure And Function Declarations

struct passenger  //Passenger Structure includes name of the passenger and the ponter to the next
{                 //passenger node, structure declaration also declares start as the first node
	char *name_suffix;  //Passenger Name Suffix
    char *name;  //Passenger Full Name
    char *passenger_id; //(unique key)
    char *address;  //Passenger Address
    char *city;  //Passenger City
    char *gender;  //Passenger Gender
    char *data_of_birth;  //Passenger Data of Birth
    char *weight;  //Passenger Weight
	struct passenger *next;     //and declares it NULL
} *start3 = NULL;

passenger* create_passenger_node(passenger *start3);  //Function Declarations
passenger* enter_passenger_info(passenger *node);
passenger* delete_passenger_node(passenger *start3);
passenger* passenger_menu(passenger *start3);
void print_passenger_list(passenger *node);

struct reservation  //Reservation Structure includes name of the reservation and the ponter to the next
{                 //Reservation node, structure declaration also declares start as the first node
    char *reservation_id; //(unique key)
    char *passenger_id;  //Passenger ID
    char *flight_number;  //Flight Number
    char *cost;  //cost
	struct reservation  *next;     // and declares it NULL
} *start4 = NULL;

reservation* create_reservation_node(reservation *start4);  //Function Declarations
reservation* enter_reservation_info(reservation *node);
reservation* delete_reservation_node(reservation *start4);
reservation* reservation_menu(reservation *start4);
void print_reservation_list(reservation *node);
 

 struct seat_assignment  //Seat Assignment Structure
{
   char seat_assignment[80];   //seat name/id
   char cost[80];
   int Available;

      struct seat_assignment  *next;
} *start5 = NULL;

seat_assignment* create_seat_assignment_node(seat_assignment *start5);
seat_assignment* enter_seat_assignment_info(seat_assignment *node);
seat_assignment* cancelled_seat_assignment_node(seat_assignment *start5);
seat_assignment* seat_assignment_menu(seat_assignment *start5);
void print_seat_assignment_list(seat_assignment *node);


//------------------------------------------------------------------------------

//Member Functions To Manipulate The Airline Linked List

airline  * create_airline_node(airline   *start1)  //Creates a sorted list of airlines (default entry sort condition by airline name)
{                                             //by entering the airline name in a node at the sorted position,
                                             //it calls the function "enter_airline_info() to ask the
	if (start1 == NULL)                     //user for its information
{
		start1 = (airline   *) malloc(sizeof(airline  ));
		start1 = enter_airline_info(start1);
		start1->next = NULL;
}
	else
{
		airline   *count_node1, *count_node2, *node;
		node = (airline   *) malloc(sizeof(airline  ));
		node = enter_airline_info(node);
		for (count_node1 = start1;
        (count_node1 != NULL) && (strcmp(count_node1->airlinename, node->airlinename) <= 0);
         count_node2 = count_node1, count_node1 = count_node1->next);
		if(count_node1 == start1)
{
		node->next = start1;
		start1 = node;
}
	else if (count_node1 == NULL)
{
    	count_node2->next = node;
		node->next = NULL;
}
		else
{
		count_node2->next = node;
		node->next = count_node1;
}
}
	return start1;
}


airline  * enter_airline_info(airline   *node)  //Function to enter the information about the airline, this function is
{                                           //called from the function create_airline_node(airline *start1)by itself.
	printf("\n");
	printf(" Welcome To  Name Airport\n");
	printf("Please enter the Airline Name\n");
	printf("\n");
	fflush(stdin);
	node->airlinename = new char [80];
	fgets(node->airlinename,80,stdin);
	node->airlinename[strcspn(node->airlinename,"\n")] = 0;
	node->node1 = NULL;
	return node;
}

airline  * delete_airline_node(airline   *start)  //Function to delete the name of a airline, function
{                                             //searches for the name and deletes if it is found.
	if(start1 == NULL)
	{
		printf("\n");
		printf("Sorry, this Airport is not operational at this moment\n");
}
	else
{
		char airlinename[80];
		printf("\n");
		printf("Please enter the  name of the Airline you want to delete\n");
		fflush(stdin);
		fgets(airlinename,80,stdin);
	airlinename[strcspn(airlinename,"\n")] = 0;
		airline   *count_node1, *count_node2;
		airline   *temp;
	for(count_node1 = start1;
    (count_node1 != NULL) && (strcmp(count_node1->airlinename, airlinename) != 0);
     count_node2 = count_node1, count_node1 = count_node1->next);
    	if(count_node1!= NULL)
{
		if (count_node1 == start1)
{
			temp = start1;
			start1 = start1->next;
			free(temp);
}
	else if(count_node1->next == NULL && count_node1 != start1)
{
			temp = count_node1;
			count_node2->next = NULL;
			free (temp);
	}
	else
	{
				temp = count_node1;
				count_node2->next = count_node1->next;
				free (temp);
}
}
	else
{
			printf("\n");
			printf("Sorry, this airline is currently not in service at this airport\n");
}
}
	return start1;
}


void print_airline_list(airline   *start) /*Function to print all the airlines operating on the airport*/
{
	if (start1 == NULL)
 {
		printf("\n");
		printf("Sorry, this Airport is not operational at this moment\n");
  }
	else
{
		printf("\n");
		airline   *count;
		for (count = start1; count != NULL; count = count->next)
		printf("%s\n", count->airlinename);
	}
}

airline  * enter_flight_menu(airline   *start1)  /*Function to search for the airline
                                             entered and enter its flight list menu*/
{
	char airlinename[80];
	printf("\n");
	printf("Welcome to the Flight List Menu\n");
	printf("Enter the Airline name you wish to check\n");
	fflush(stdin);
	fgets(airlinename,80,stdin);
	airlinename[strcspn(airlinename,"\n")] = 0;
	airline   *count;
	for(count = start1;
     (count != NULL) && (strcmp(count->airlinename, airlinename) != 0);
      count = count->next);
	if(count == NULL)
	{
		printf("\n");
		printf("Sorry, this airline does not operate in this airport\n");
		return start1;
	}
	else
	{
		printf("\n");
		count->node1 = flight_menu(count->node1);
		return start1;
	}
}

void write_to_file(airline   *start1)  //Write to file airline.txt
{
	FILE *fp;
	airline   *count1;
	flight *count2;
	passenger *count3;
	reservation *count4;
	seat_assignment *count5;
    int length = 0;
	int airline_count = 0;
	int passenger_count = 0;
	int flight_count = 0;
	int reservation_count = 0;
	int seat_assignment_count = 0;
	fp = fopen("airline.txt","wb");

	//Determine number of airlines and write to file
	for( count1 = start1; count1 != NULL; count1 = count1->next) ++airline_count;
	fwrite(&airline_count,sizeof(int),1,fp);

	//Loop through and write airlines data to file
	for( count1 = start1; count1 != NULL; count1 = count1->next)
{
		//Determine length of airline name and write to file
		length = strlen(count1->airlinename);
		fwrite(&length,sizeof(int),1,fp);

		//Write airline name to file
		fwrite(count1->airlinename,length,1,fp);
//------------------------------------------------------------------------------
		//Determine number of flights for the airline and write to file
		for( count2 = count1->node1; count2 != NULL; count2 = count2->next) ++flight_count;
		fwrite(&flight_count,sizeof(int),1,fp);

		//Loop through and write flight data for the airline to file
		for( count2 = count1->node1; count2 != NULL; count2 = count2->next)
{
			//Determine length of flight number and write to file
			length = strlen(count2->flightnumber);
			fwrite(&length,sizeof(int),1,fp);

			//Write flight number to file
			fwrite(count2->flightnumber,length,1,fp);

            //Determine length of date of flight and write to file
            length = strlen(count2->date_of_flight);
            fwrite(&length,sizeof(int),1,fp);

            //Write data of flight to file
			fwrite(count2->date_of_flight,length,1,fp);

			//Determine length of departure location and write to file
			length = strlen(count2->departure_location);
			fwrite(&length,sizeof(int),1,fp);

			//Write departure location to file
			fwrite(count2->departure_location,length,1,fp);

			//Determine length of arrival location and write to file
			length = strlen(count2->arrival_location);
			fwrite(&length,sizeof(int),1,fp);

			//Write arrival location to file
			fwrite(count2->arrival_location,length,1,fp);

			//Determine length of take off time and write to file
			length = strlen(count2->take_off_time);
			fwrite(&length,sizeof(int),1,fp);

			//Write departure location to file
			fwrite(count2->take_off_time,length,1,fp);

            //Determine length of arrival time and write to file
            length = strlen(count2->arrival_time);
            fwrite(&length,sizeof(int),1,fp);

            //Write arrival location to file
			fwrite(count2->arrival_time,length,1,fp);

//------------------------------------------------------------------------------
			//Determine number of passengers for this flight and write to file
			for( count3 = count2->node2; count3 != NULL;
             count3 = count3->next) ++passenger_count;
			fwrite(&passenger_count,sizeof(int),1,fp);

			//Loop through and write passenger data for the flight to file
			for( count3 = count2->node2; count3 != NULL; count3 = count3->next)
{
				//Determine length of passenger name suffix and write to file
				length = strlen(count3->name_suffix);
				fwrite(&length,sizeof(int),1,fp);

				//Write passenger name suffix to file
				fwrite(count3->name_suffix,length,1,fp);

                //Determine length of passenger name and write to file
				length = strlen(count3->name);
				fwrite(&length,sizeof(int),1,fp);

				//Write passenger name to file
				fwrite(count3->name,length,1,fp);

            	//Determine length of passenger ID and write to file
				length = strlen(count3->passenger_id);
				fwrite(&length,sizeof(int),1,fp);

                //Write passenger ID to file
				fwrite(count3->passenger_id,length,1,fp);

                //Determine length of passenger address and write to file
                length = strlen(count3->address);
   	            fwrite(&length,sizeof(int),1,fp);

                //Write passenger address to file
				fwrite(count3->address,length,1,fp);

                //Determine length of passenger city and write to file
                length = strlen(count3->city);
				fwrite(&length,sizeof(int),1,fp);

				//Write passenger city to file
				fwrite(count3->city,length,1,fp);

				//Determine length of passenger gender and write to file
                length = strlen(count3->gender);
				fwrite(&length,sizeof(int),1,fp);

				//Write passenger gender to file
				fwrite(count3->gender,length,1,fp);

				//Determine length of passenger data of birth and write to file
                length = strlen(count3->data_of_birth);
				fwrite(&length,sizeof(int),1,fp);

				//Write passenger data of birth to file
				fwrite(count3->data_of_birth,length,1,fp);

				//Determine length of passenger weight and write to file
                length = strlen(count3->weight);
				fwrite(&length,sizeof(int),1,fp);

				//Write passenger weight to file
				fwrite(count3->weight,length,1,fp);
//------------------------------------------------------------------------------
		    //Determine number of reservation for this flight and write to file
			for( count4 = count2->node3; count4 != NULL;
             count4 = count4->next) ++reservation_count;
			fwrite(&reservation_count,sizeof(int),1,fp);

			//Loop through and write reservation data for the flight to file
			for( count4 = count2->node3; count4 != NULL; count4 = count4->next)
{
               //Determine length of reservation ID and write to file
               length = strlen(count4->reservation_id);
               fwrite(&length,sizeof(int),1,fp);

               //Write reservation id to file
               fwrite(count4->reservation_id,length,1,fp);

  	           //Determine length of passenger ID and write to file
			   length = strlen(count4->passenger_id);
		       fwrite(&length,sizeof(int),1,fp);

               //Write passenger ID to file
			   fwrite(count4->passenger_id,length,1,fp);

               //Determine length of flight_number and write to file
               length = strlen(count4->flight_number);
			   fwrite(&length,sizeof(int),1,fp);

               //Write flight number to file
			   fwrite(count4->flight_number,length,1,fp);

               //Determine length of cost and write to file
               length = strlen(count4->cost);
   	           fwrite(&length,sizeof(int),1,fp);

               //Write passenger cost to file
               fwrite(count4->cost,length,1,fp);

            //Write seat assignment to file

}
 }
  }
 }
	fclose(fp);
}

airline  * read_from_file()  //read from file airline.txt
{
	FILE *fp;
	airline   *start, *curr;
	int length = 0;
	int airline_count= 0;
	int flight_count = 0;
	int passenger_count = 0;
	int reservation_count = 0;
	int seat_assignment_count = 0;

	//Initialize pointers
	start = curr = NULL;

	//Open file for reading
	fp = fopen("airline.txt","rb");
	if(fp == NULL)
		return NULL;

	while(fread(&airline_count,sizeof(int),1,fp) == 1)
	{
		//Loop through "airline_count" airlines
		for( ; airline_count > 0; --airline_count )
		{
			//allocate room for a single airline structure
			airline *a = (airline *)malloc(sizeof(airline));
			a->next = NULL;
			a->node1 = NULL;

			//read airline name length, then the name itself
			fread(&length,sizeof(int),1,fp);
			a->airlinename = (char *)malloc(length+1);
			fread(a->airlinename,length,1,fp);
			a->airlinename[length] = 0;

			//append airline to the end of the airline list
			if(start == NULL)
				start = curr = a;
			else
			{
				curr->next = a;
				curr = curr->next;
			}

			//Read in number of flights stored for the airline
			fread(&flight_count,sizeof(int),1,fp);

			//Loop through "flight_count" flights
			flight *lastflight = NULL;
			for( ; flight_count > 0; --flight_count )
			{
				//allocate room for a single flight structure
				flight *f = (flight *)malloc(sizeof(flight));
				f->next = NULL;
				f->node2 = NULL;
				f->node3 = NULL;

				//read each string field of the flight, length-prefixed
				fread(&length,sizeof(int),1,fp);
				f->flightnumber = (char *)malloc(length+1);
				fread(f->flightnumber,length,1,fp);
				f->flightnumber[length] = 0;

				fread(&length,sizeof(int),1,fp);
				f->date_of_flight = (char *)malloc(length+1);
				fread(f->date_of_flight,length,1,fp);
				f->date_of_flight[length] = 0;

				fread(&length,sizeof(int),1,fp);
				f->departure_location = (char *)malloc(length+1);
				fread(f->departure_location,length,1,fp);
				f->departure_location[length] = 0;

				fread(&length,sizeof(int),1,fp);
				f->arrival_location = (char *)malloc(length+1);
				fread(f->arrival_location,length,1,fp);
				f->arrival_location[length] = 0;

				fread(&length,sizeof(int),1,fp);
				f->take_off_time = (char *)malloc(length+1);
				fread(f->take_off_time,length,1,fp);
				f->take_off_time[length] = 0;

				fread(&length,sizeof(int),1,fp);
				f->arrival_time = (char *)malloc(length+1);
				fread(f->arrival_time,length,1,fp);
				f->arrival_time[length] = 0;

				//append flight to the end of this airline's flight list
				if(a->node1 == NULL)
					a->node1 = f;
				else
					lastflight->next = f;
				lastflight = f;

				//Read in number of passengers stored for that flight
				fread(&passenger_count,sizeof(int),1,fp);

				//Loop through "passenger_count" passengers for this flight
				passenger *lastpass = NULL;
				for( ; passenger_count > 0; --passenger_count )
				{
					//allocate room for a single passenger structure
					passenger *p = (passenger *)malloc(sizeof(passenger));
					p->next = NULL;

					//read each string field of the passenger, length-prefixed
					fread(&length,sizeof(int),1,fp);
					p->name_suffix = (char *)malloc(length+1);
					fread(p->name_suffix,length,1,fp);
					p->name_suffix[length] = 0;

					fread(&length,sizeof(int),1,fp);
					p->name = (char *)malloc(length+1);
					fread(p->name,length,1,fp);
					p->name[length] = 0;

					fread(&length,sizeof(int),1,fp);
					p->passenger_id = (char *)malloc(length+1);
					fread(p->passenger_id,length,1,fp);
					p->passenger_id[length] = 0;

					fread(&length,sizeof(int),1,fp);
					p->address = (char *)malloc(length+1);
					fread(p->address,length,1,fp);
					p->address[length] = 0;

					fread(&length,sizeof(int),1,fp);
					p->city = (char *)malloc(length+1);
					fread(p->city,length,1,fp);
					p->city[length] = 0;

					fread(&length,sizeof(int),1,fp);
					p->gender = (char *)malloc(length+1);
					fread(p->gender,length,1,fp);
					p->gender[length] = 0;

					fread(&length,sizeof(int),1,fp);
					p->data_of_birth = (char *)malloc(length+1);
					fread(p->data_of_birth,length,1,fp);
					p->data_of_birth[length] = 0;

					fread(&length,sizeof(int),1,fp);
					p->weight = (char *)malloc(length+1);
					fread(p->weight,length,1,fp);
					p->weight[length] = 0;

					//append passenger to the end of this flight's passenger list
					if(f->node2 == NULL)
						f->node2 = p;
					else
						lastpass->next = p;
					lastpass = p;
				}

				//Read in number of reservations stored for that flight
				fread(&reservation_count,sizeof(int),1,fp);

				//Loop through "reservation_count" reservations for this flight
				reservation *lastres = NULL;
				for( ; reservation_count > 0; --reservation_count )
				{
					//allocate room for a single reservation structure
					reservation *r = (reservation *)malloc(sizeof(reservation));
					r->next = NULL;

					//read each string field of the reservation, length-prefixed
					fread(&length,sizeof(int),1,fp);
					r->reservation_id = (char *)malloc(length+1);
					fread(r->reservation_id,length,1,fp);
					r->reservation_id[length] = 0;

					fread(&length,sizeof(int),1,fp);
					r->passenger_id = (char *)malloc(length+1);
					fread(r->passenger_id,length,1,fp);
					r->passenger_id[length] = 0;

					fread(&length,sizeof(int),1,fp);
					r->flight_number = (char *)malloc(length+1);
					fread(r->flight_number,length,1,fp);
					r->flight_number[length] = 0;

					fread(&length,sizeof(int),1,fp);
					r->cost = (char *)malloc(length+1);
					fread(r->cost,length,1,fp);
					r->cost[length] = 0;

					//append reservation to the end of this flight's reservation list
					if(f->node3 == NULL)
						f->node3 = r;
					else
						lastres->next = r;
					lastres = r;
				}

				//Read in number of seat assignments stored for that flight
				fread(&seat_assignment_count,sizeof(int),1,fp);
			}
		}
	}
	fclose(fp);
	return start;
}
airline  * airline_menu(airline   *start)  //Menu Function which is handles the airlinelist
{
	int choice;
	printf("Welcome to the Unknow Name Airline System Main Menu\n");
	printf("Please enter your choice from the menu shown below\n");
	printf("1: Add a new airline to this airport\n");
	printf("2: Delete an airline from the airport\n");
	printf("3: Display the Airlines List at this Airport\n");
    printf("4: Enter Flight menu for an airline\n");
	printf("5: Exit the program\n");
	printf("To Save exit the program from system main menu\n");
	scanf ("%d", &choice);
	switch(choice)
	{
	case 1:
		{
			start1 = create_airline_node(start1);
		} break;
	case 2:
		{
			start1 = delete_airline_node(start1);
		} break;
	case 3:
		{
			print_airline_list(start1);
		} break;
	case 4:
		{
			start1 = enter_flight_menu(start1);
		} break;
	case 5:
		{
			write_to_file(start1);
			exit(1);
		} break;
	default:
		{
			start1 = airline_menu(start1);
		} break;
	}
	printf("\n");
	start1 = airline_menu(start1);
	return start1;
}
//--------------------------------------------------------------------------------
//Member Functions To Manipulate The Flight Linked List

flight* create_flight_node(flight *start2)  // Creates a sorted list of flights (default entry sort condition by flight no.)
{                                           // by entering the flight node at the sorted position,
    printf("\n");                           // it calls the function "enter_flight_info() to ask the
	if (start2 == NULL)                     // user for its information
	{
		start2 = (flight *) malloc(sizeof(flight));
		start2 = enter_flight_info(start2);
		start2->next = NULL;
}
	else
{
		flight *count_node1, *count_node2, *node;
		node = (flight *) malloc(sizeof(flight));
		node = enter_flight_info(node);
	for (count_node1 = start2;
    (count_node1 != NULL) && (strcmp(count_node1->flightnumber, node->flightnumber) <= 0);
     count_node2 = count_node1, count_node1 = count_node1->next);
	if(count_node1 == start2)
	{
		node->next = start2;
		start2 = node;
	}
	else if (count_node1 == NULL)
	{
			count_node2->next = node;
			node->next = NULL;
	}
	else
	{
		count_node2->next = node;
		node->next = count_node1;
	}
	}
	return start2;
}

flight* enter_flight_info(flight *node)  // Function to enter the information about the flight, this function is
{                                        // called from the function create_flight_node(flight *start)by itself.
	printf(" Welcome to the Flight List\n");
	printf("Please enter the Flight number\n"); //Flight Number (unique key)
	       fflush(stdin);
	       node->flightnumber = new char [80];
fgets(node->flightnumber,80,stdin);
	       node->flightnumber[strcspn(node->flightnumber,"\n")] = 0;
	printf("Please enter the Date of Flight\n");  //Date of Flight
           fflush(stdin);
	       node->date_of_flight = new char [80];
fgets(node->date_of_flight,80,stdin);
	       node->date_of_flight[strcspn(node->date_of_flight,"\n")] = 0;
	printf("Please enter the Departure Location\n");  //Departure From City
	       fflush(stdin);
	       node->departure_location = new char [80];
fgets(node->departure_location,80,stdin);
	       node->departure_location[strcspn(node->departure_location,"\n")] = 0;
	printf("Please enter the Arrival Location\n");  //Arrival At City
	       fflush(stdin);
	       node->arrival_location = new char [80];
fgets(node->arrival_location,80,stdin);
	       node->arrival_location[strcspn(node->arrival_location,"\n")] = 0;
	printf("Please enter the Take off time\n");  //Departuare time
	       fflush(stdin);
           node->take_off_time = new char [80];
fgets(node->take_off_time,80,stdin);
	       node->take_off_time[strcspn(node->take_off_time,"\n")] = 0;
    printf("Please enter the Arrival time\n");  //Arrival time
           fflush(stdin);
           node->arrival_time = new char [80];
fgets(node->arrival_time,80,stdin);
	       node->arrival_time[strcspn(node->arrival_time,"\n")] = 0;
	       node->node2 = NULL;

	return node;
}

flight* delete_flight_node(flight *start2)  // Function to delete the name of a flight, function
{                                           // searches for the name and deletes if it is found.
	printf("\n");

	if(start2 == NULL)
	{
		printf("Sorry, no available Flights today\n");
	}
	else
	{
		char flightnumber[80];
	printf("Please enter the flight number you want to delete\n");
		fflush(stdin);
		fgets(flightnumber,80,stdin);
	flightnumber[strcspn(flightnumber,"\n")] = 0;
		flight *count_node1, *count_node2;
		flight *temp;
		for(count_node1 = start2;
        (count_node1 != NULL) && (strcmp(count_node1->flightnumber, flightnumber)!= 0);
         count_node2 = count_node1, count_node1 = count_node1->next);
	if(count_node1!= NULL)
	{
	if (count_node1 == start2)
	{
			temp = start2;
			start2 = start2->next;
			free(temp);
		}
		else if(count_node1->next == NULL && count_node1 != start2)
		{
				temp = count_node1;
				count_node2->next = NULL;
				free (temp);
		}
		else
		{
				temp = count_node1;
				count_node2->next = count_node1->next;
				free (temp);
		}
	}
		else
		{
			printf("\n");
			printf("Sorry, this name was not found in this list\n");
		}
	}
	return start2;
}

void print_flight_list(flight *start2)
{
	printf("\n");
	if (start2 == NULL)
	{
		printf("Sorry, the Flight List is empty\n");
	}
	else
	{
		flight *count;
		for (count = start2; count != NULL; count = count->next)
		{
			printf("Flight Number : %s\n", count->flightnumber);
			printf("Data of Flight : %s\n", count->date_of_flight);
		    printf("Departure Location : %s\n", count->departure_location);
		    printf("Arrival Location : %s\n", count->arrival_location);
		    printf("Take off Time : %s\n", count->take_off_time);
		    printf("Arrival Time : %s\n", count->arrival_time);
			printf("\n");
		}
	}
}

flight* enter_passenger_menu(flight *start2)  // Function to search for the flight entered and enter its passenger list menu
{
	printf("\n");
	char flightnumber[80];
	printf("Welcome to the passenger list Menu\n");
	printf("Enter the Flight Number you wish to check\n");
	fflush(stdin);
	fgets(flightnumber,80,stdin);
	flightnumber[strcspn(flightnumber,"\n")] = 0;
	flight *count;
	for(count = start2; (count != NULL) && (strcmp(count->flightnumber, flightnumber) != 0);
     count = count->next);
	if(count == NULL)
	{
		printf("Sorry, this flight is not available\n");
		return start2;
	}
	else
	{
		count->node2 = passenger_menu(count->node2);
		return start2;
	}
}

flight* flight_menu(flight *start2)  // Menu Function which is handles the flightlist for an airline
{
	int choice;
	printf("Welcome to the Flight menu\n");
	printf("Please enter your choice from the menu shown below\n");
	printf("1: Add a new Flight to this Airline\n");
	printf("2: Delete a Flight from the Airline\n");
	printf("3: Display the Flight List for the Airline\n");
    printf("4: Enter passenger menu for a flight\n");
    printf("5: Enter reservation menu for a flight\n");
    printf("6: Enter Passenger seat assignment menu\n");
	printf("7: Return back to the Main Menu\n");
	scanf ("%d", &choice);
	switch(choice)
	{
	case 1:
	{
			start2 = create_flight_node(start2);
	     } break;
	case 2:
	{
			start2 = delete_flight_node(start2);
		} break;
	case 3:
	{
			print_flight_list(start2);
		} break;
	case 4:
	{
			start2 = enter_passenger_menu(start2);
		} break;
/*	case 5:
    {
            start2 = enter_reservation_menu(start2);
        } break;
    case 6:
    {
            start2 = enter_seat_assignment_menu(stat2);
        } break; */
	case 7:
	{
			return start2;
		} break;
	default:
	{
			start2 = flight_menu(start2);
		} break;
	}
	printf("\n");
	start2 = flight_menu(start2);
	return start2;
}

//------------------------------------------------------------------------------
//Member Functions To Manipulate The Passenger Linked List

passenger* create_passenger_node(passenger *start3)  //Creates a sorted list of passengers by entering the passenger node at the
{                                                    // sorted position, it calls the function "enter_passenger_info() to
    printf("\n");                                    // ask the user for its information
	if (start3 == NULL)
	{
		start3 = (passenger *) malloc(sizeof(passenger));
		start3 = enter_passenger_info(start3);
		start3->next = NULL;
	}
	else
	{
		passenger *count_node1, *count_node2, *node;
		node = (passenger *) malloc(sizeof(passenger));
		node = enter_passenger_info(node);
	for (count_node1 = start3; (count_node1 != NULL) && (strcmp(count_node1->name, node->name) <= 0); count_node2 = count_node1, count_node1 = count_node1->next);
		if(count_node1 == start3)
	{
			node->next = start3;
			start3 = node;
	}
	else if (count_node1 == NULL)
	{
		count_node2->next = node;
		node->next = NULL;
	}
	else
	{
		count_node2->next = node;
		node->next = count_node1;
	}
	}
	return start3;
}


passenger* enter_passenger_info(passenger *node)  // Function to enter the name of the passenger, this function is called
{                                                 // from the function create_passenger_node(passenger *start)by itself.
	printf(" Welcome to the Passenger List\n");
	printf("Please enter Passenger Name Suffix\n");
	fflush(stdin);
	node->name_suffix = new char [6];
	fgets(node->name_suffix,6,stdin);
	node->name_suffix[strcspn(node->name_suffix,"\n")] = 0;
    printf("Please enter Passenger Full Name\n");
	fflush(stdin);
	node->name = new char [80];
	fgets(node->name,80,stdin);
	node->name[strcspn(node->name,"\n")] = 0;
	printf("please enter Passenger ID\n");
	fflush(stdin);
	node->passenger_id = new char [10];
	fgets(node->passenger_id,10,stdin);
	node->passenger_id[strcspn(node->passenger_id,"\n")] = 0;
    printf("Please enter Passenger Address;\n");
    fflush(stdin);
    node->address = new char [80];
	fgets(node->address,80,stdin);
	node->address[strcspn(node->address,"\n")] = 0;
    printf("Please enter Passenger City\n");
    fflush(stdin);
    node->city = new char [30];
	fgets(node->city,30,stdin);
	node->city[strcspn(node->city,"\n")] = 0;
    printf("Please enter Gender\n");
    fflush(stdin);
    node->gender = new char [10];
    fgets(node->gender,10,stdin);
	node->gender[strcspn(node->gender,"\n")] = 0;
    printf("Please enter Data Of Birth\n");
    fflush(stdin);
    node->data_of_birth = new char [10];
    fgets(node->data_of_birth,10,stdin);
	node->data_of_birth[strcspn(node->data_of_birth,"\n")] = 0;
    printf("Please enter Weight\n");
    fflush(stdin);
    node->weight = new char [10];
    fgets(node->weight,10,stdin);
	node->weight[strcspn(node->weight,"\n")] = 0;
	return node;
}

passenger* delete_passenger_node(passenger *start3)  // Function to delete the name of a passenger in the flight, function
{                                                    // searches for the name and deletes if it is found.
	printf("\n");
	if(start3 == NULL)
	{
		printf("\n");
		printf("Sorry, the passenger list is empty\n");
	}
	else
	{
		char name[80];
		printf("Please enter the name of the passenger you want to delete\n");
		fflush(stdin);
		fgets(name,80,stdin);
	name[strcspn(name,"\n")] = 0;
		passenger *count_node1, *count_node2;
		passenger *temp;
	for(count_node1 = start3; (count_node1 != NULL) && (strcmp(count_node1->name, name) != 0);
    count_node2 = count_node1, count_node1 = count_node1->next);
		if(count_node1!= NULL)
	{
		if (count_node1 == start3)
	{
				temp = start3;
				start3 = start3->next;
				free(temp);
	}
		else if(count_node1->next == NULL && count_node1 != start3)
	{
			temp = count_node1;
			count_node2->next = NULL;
			free (temp);
	}
	else
	{
			temp = count_node1;
			count_node2->next = count_node1->next;
			free (temp);
		}
	}
	else
	{
		printf("\n");
		printf("Sorry, this name was not found in this list\n");
	}
}
	return start3;
}

passenger* passenger_menu(passenger *start3)  // Menu Function which is called from main and takes
{                                             // over the program list after that
	printf("\n");
	int choice;
	printf("Welcome to the passenger menu\n");
	printf("Please enter your choice from the menu shown below\n");
	printf("1: Add a passenger to this flight\n");
	printf("2: Delete a passenger from this flight\n");
	printf("3: Display the passenger list for this flight\n");
	printf("4: Return back to the Flight Menu\n");
	scanf ("%d", &choice);
	switch(choice)
	{
	case 1:
		{
			start3 = create_passenger_node(start3);
		} break;
	case 2:
		{
			start3 = delete_passenger_node(start3);
		} break;
	case 3:
		{
			print_passenger_list(start3);
		} break;
	case 4:
		{
			return start3;
		} break;
	default:
		{
			start3 = passenger_menu(start3);
		} break;
	}
	start3 = passenger_menu(start3);
	return start3;
}

void print_passenger_list(passenger *start3)
{
	printf("\n");
	if (start3 == NULL)
	{
		printf("Sorry, the passenger list is empty\n");
	}
	else
	{
		passenger *count;
		for (count = start3; count != NULL; count = count->next)
		printf("Passenger Name Suffix : %s\n", count->name_suffix);
		printf("Passenger Name : %s\n", count->name);
		printf("PassengerID : %s\n", count->passenger_id);
        printf("Passenger Address : %s\n", count->address);
        printf("Passenger City : %s\n", count->city);
        printf("Passenger Gender : %s\n", count->gender);
        printf("Passenger Data Of Birth : %s\n", count->data_of_birth);
        printf("Passenger Weight : %s\n", count->weight);
}

}
//------------------------------------------------------------------------------
//Member Functions To Manipulate The reservation Linked List

reservation* create_reservation_node(reservation *start4)  //Creates a sorted list of reservation by entering the reservation node at the
{                                                    // sorted position, it calls the function "enter_reservation_info() to
    printf("\n");                                   // ask the user for its information
	if (start4 == NULL)
	{
		start4 = (reservation *) malloc(sizeof(reservation));
		start4 = enter_reservation_info(start4);
		start4->next = NULL;
	}
	else
	{
		reservation *count_node1, *count_node2, *node;
		node = (reservation *) malloc(sizeof(reservation));
		node = enter_reservation_info(node);
	for (count_node1 = start4;
    (count_node1 != NULL) && (strcmp(count_node1->reservation_id, node->reservation_id) <= 0);
     count_node2 = count_node1, count_node1 = count_node1->next);
		if(count_node1 == start4)
	{
			node->next = start4;
			start4 = node;
	}
	else if (count_node1 == NULL)
	{
		count_node2->next = node;
		node->next = NULL;
	}
	else
	{
		count_node2->next = node;
		node->next = count_node1;
	}
	}
	return start4;
}

reservation* enter_reservation_info(reservation *node)  //Function to enter the name of the passenger, this function is called
{                                                 //from the function create_reservation_node(reservation *start)by itself.
	printf(" Welcome to the Reservation List\n");
	printf("Please enter your Reservation ID\n");
	fflush(stdin);
	node->reservation_id = new char [80];
	fgets(node->reservation_id,80,stdin);
	node->reservation_id[strcspn(node->reservation_id,"\n")] = 0;
	printf("please enter your Passenger ID\n");
	fflush(stdin);
	node->passenger_id = new char [10];
	fgets(node->passenger_id,10,stdin);
	node->passenger_id[strcspn(node->passenger_id,"\n")] = 0;
    printf("Please enter your Flight Number;\n");
    fflush(stdin);
    node->flight_number = new char [80];
	fgets(node->flight_number,80,stdin);
	node->flight_number[strcspn(node->flight_number,"\n")] = 0;
    printf("Please enter your Cost\n");
    fflush(stdin);
    node->cost = new char [30];
	fgets(node->cost,30,stdin);
	node->cost[strcspn(node->cost,"\n")] = 0;
	return node;
}

reservation* delete_reservation_node(reservation *start4)  //Function to delete the name of a passenger in the flight, function
{                                                    //searches for the name and deletes if it is found.
	printf("\n");
	if(start4 == NULL)
	{
		printf("\n");
		printf("Sorry, the reservation list is empty\n");
	}
	else
	{
		char reservation_id[80];
		printf("Please enter the reservation id you want to delete\n");
		fflush(stdin);
		fgets(reservation_id,80,stdin);
	reservation_id[strcspn(reservation_id,"\n")] = 0;
		reservation *count_node1, *count_node2;
		reservation *temp;
	for(count_node1 = start4;
    (count_node1 != NULL) && (strcmp(count_node1->reservation_id, reservation_id) != 0);
     count_node2 = count_node1, count_node1 = count_node1->next);
		if(count_node1!= NULL)
	{
		if (count_node1 == start4)
	{
			temp = start4;
			start4 = start4->next;
			free(temp);
	}
		else if(count_node1->next == NULL && count_node1 != start4)
	{
			temp = count_node1;
			count_node2->next = NULL;
			free (temp);
	}
	else
	{
			temp = count_node1;
			count_node2->next = count_node1->next;
			free (temp);
		}
	}
	else
	{
		printf("\n");
		printf("Sorry, this name was not found in this list\n");
	}
}
	return start4;
}

reservation* reservation_menu(reservation *start4)  //Menu Function which is called from main and takes
{                                                   //over the program list after that
	printf("\n");
	int choice;
	printf("Welcome to the Reservation menu\n");
	printf("Please enter your choice from the menu shown below\n");
	printf("1: Add a reservation to this flight\n");
	printf("2: Delete a reservation from this flight\n");
	printf("3: Display the reservation list for this flight\n");
	printf("4: Return back to the passenger Menu\n");
	scanf ("%d", &choice);
	switch(choice)
	{
	case 1:
		{
			start4 = create_reservation_node(start4);
		} break;
	case 2:
		{
			start4 = delete_reservation_node(start4);
		} break;
	case 3:
		{
			print_reservation_list(start4);
		} break;
	case 4:
		{
			return start4;
		} break;
	default:
		{
			start4 = reservation_menu(start4);
		} break;
	}
	start4 = reservation_menu(start4);
	return start4;
}

void print_reservation_list(reservation *start4)
{
	printf("\n");
	if (start4 == NULL)
	{
		printf("Sorry, the reservation list is empty\n");
	}
	else
	{
		reservation *count;
		for (count = start4; count != NULL; count = count->next)
		printf("Reservation ID : %s\n", count->reservation_id);
		printf("PassengerID : %s\n", count->passenger_id);
        printf("Flight Number : %s\n", count->flight_number);
        printf("Cost : %s\n", count->cost);
	}
}
//------------------------------------------------------------------------------
// Number Of Seats and Number Of Seats Booked
seat_assignment* create_seat_assignment_node(seat_assignment *start5)  //Creates a sorted list of reservation by entering the reservation node at the
{                                                    // sorted position, it calls the function "enter_reservation_info() to
    printf("\n");                                    // ask the user for its information
	if (start5 == NULL)
	{
		start5 = (seat_assignment *) malloc(sizeof(seat_assignment));
		start5 = enter_seat_assignment_info(start5);
		start5->next = NULL;
	}
	else
	{
		seat_assignment *count_node1, *count_node2, *node;
		node = (seat_assignment *) malloc(sizeof(seat_assignment));
		node = enter_seat_assignment_info(node);
	for (count_node1 = start5; (count_node1 != NULL) && (strcmp(count_node1->seat_assignment, node->seat_assignment) <= 0); count_node2 = count_node1, count_node1 = count_node1->next);
		if(count_node1 == start5)
	{
			node->next = start5;
			start5 = node;
	}
	else if (count_node1 == NULL)
	{
		count_node2->next = node;
		node->next = NULL;
	}
	else
	{
		count_node2->next = node;
		node->next = count_node1;
	}
	}
	return start5;
}

seat_assignment* enter_seat_assignment_info(seat_assignment *node)  // Function to enter the name of the passenger, this function is called
{                                                 // from the function create_seat_assignment_node(seat_assignment *start)by itself.
	printf(" Welcome to the Seat Assignment List\n");
	printf("Please enter your \n");
	fflush(stdin);
	fgets(node->seat_assignment,80,stdin);
	node->seat_assignment[strcspn(node->seat_assignment,"\n")] = 0;
	return node;
}

seat_assignment* cancelled_seat_assignment_node(seat_assignment *start5)
{                       // Function to delete the name of a seat_assignment in the flight, function
                       // searches for the name and deletes if it is found.
	printf("\n");
	if(start5 == NULL)
	{
		printf("\n");
		printf("Sorry, the seat_assignment list is empty\n");
	}
	else
	{
		char seat_name[80];
		printf("Please enter the seat_assignment you want to delete\n");
		fflush(stdin);
		fgets(seat_name,80,stdin);
		seat_name[strcspn(seat_name,"\n")] = 0;
		seat_assignment *count_node1, *count_node2;
		seat_assignment *temp;
	for(count_node1 = start5;
     (count_node1 != NULL) && (strcmp(count_node1->seat_assignment, seat_name) != 0);
      count_node2 = count_node1, count_node1 = count_node1->next);
		if(count_node1!= NULL)
	{
		if (count_node1 == start5)
	{
			temp = start5;
			start5 = start5->next;
			free(temp);
	}
		else if(count_node1->next == NULL && count_node1 != start5)
	{
			temp = count_node1;
			count_node2->next = NULL;
			free (temp);
	}
	else
	{
			temp = count_node1;
			count_node2->next = count_node1->next;
			free (temp);
		}
	}
	else
	{
		printf("\n");
		printf("Sorry, this name was not found in this list\n");
	}
}
	return start5;
}

seat_assignment* seat_assignment_menu(seat_assignment *start5)  // Menu Function which is called from main and takes
{                                                   // over the program list after that
	printf("\n");
	int choice;
	printf("Welcome to the Seat Assignment menu\n");
	printf("Please enter your choice from the menu shown below\n");
	printf("1: Add a seat to this flight\n");
	printf("2: Cancelled a seat from this flight\n");
	printf("3: Move passenger seat\n");
	printf("4: Display the passenger seat list for this flight\n");
	printf("5: Return back to the passenger Menu\n");
	scanf ("%d", &choice);
	switch(choice)
	{
	case 1:
		{
			start5 = create_seat_assignment_node(start5);
		} break;
	case 2:
		{
			start5 = cancelled_seat_assignment_node(start5);
		} break;
	case 3:
		{
			print_seat_assignment_list(start5);
		} break;
	case 4:
		{
			return start5;
		} break;
	default:
		{
			start5 = seat_assignment_menu(start5);
		} break;
	}
	start5 = seat_assignment_menu(start5);
	return start5;
}

void print_seat_assignment_list(seat_assignment *start5)
{
	printf("\n");
	if (start5 == NULL)
	{
		printf("Sorry, the seat assignment list is empty\n");
	}
	else
	{
		seat_assignment *count;
		for (count = start5; count != NULL; count = count->next)
		printf("Seat Assignment : %s\n", count->seat_assignment);
	}
}
//Main Function Calling The Menu Function

int main()
{
	start1 = read_from_file();
	start1 = airline_menu(start1);
	return 0;
}

//------------------------------------------------------------------------------


/*
The Unknow Name airline system has hired you to develop a database system
to keep track of airline reservations and flights.

Each flight requires the following information:
Flight Number (unique key), Departure and Arrival City, Date of Flight,
Departure and Arrival Time, Number of Seats, Number of Seats Booked
and an array of passengers on the flight stored by passenger ID.

Each reservation requires the following information:
Reservation ID (unique key), Passenger ID, Flight Number, Cost

Each passenger requires the following information:
Passenger ID (unique key), First Name, Last Name, Address, City

1)	Create structures for each of the above files and read the
information from three separate data files.

2)	The airline also wants the following set up:
a)	An input screen to add new flights (does not add passengers).
b)	An input screen to add new passengers (does not add flights).
c)	An input screen to add reservations (used to add passengers to flights).
d)	An output screen to show all current flights, sorted by departure time.
e)	An output screen to show all the passengers on a selected flight
 sorted by last name.
f)	Add a save option to store the file.

Some other notes:
- Passengers and flights must already be in the system in order
to be added to a reservation.

	- Use the unique ID's so you do not repeat data in the files.
*/


