/*
 * reports.c
 * Reporting functions required by the assignment:
 *   d) show all current flights, sorted by departure time
 *   e) show all passengers on a selected flight, sorted by last name
 *   f) summary statistics for the whole system
 *
 * These operate on the same linked lists used by
 * access navigation control.cpp (start1..start5 globals).
 */
#ifndef REPORTS_H
#define REPORTS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Extract the last word of a "First Last" style name */
static const char *last_name(const char *name)
{
    const char *last = strrchr(name, ' ');
    return last ? last + 1 : name;
}

/* Compare flights by take-off time (and then flight number as tie-break).
 * Works on the flight structure layout of the main program. */
struct flight_rep
{
    char *flightnumber;
    char *date_of_flight;
    char *departure_location;
    char *arrival_location;
    char *take_off_time;
    char *arrival_time;
};

static int compare_departure(const void *a, const void *b)
{
    const struct flight_rep *fa = (const struct flight_rep *)a;
    const struct flight_rep *fb = (const struct flight_rep *)b;
    int c = strcmp(fa->take_off_time, fb->take_off_time);
    if (c == 0)
        c = strcmp(fa->flightnumber, fb->flightnumber);
    return c;
}

/* Report (d): all flights sorted by departure time */
void report_flights_by_departure(struct flight_rep *flights, int count)
{
    int i;
    printf("\n==================================================\n");
    printf("  FLIGHT SCHEDULE (sorted by departure time)\n");
    printf("==================================================\n");
    if (count == 0)
    {
        printf("No flights in the system.\n");
        return;
    }
    qsort(flights, (size_t)count, sizeof(*flights), compare_departure);
    for (i = 0; i < count; ++i)
    {
        printf("%-8s %-12s %-16s -> %-16s %5s - %s\n",
               flights[i].flightnumber,
               flights[i].date_of_flight,
               flights[i].departure_location,
               flights[i].arrival_location,
               flights[i].take_off_time,
               flights[i].arrival_time);
    }
}

/* Compare passengers by last name */
struct passenger_rep
{
    char *passenger_id;
    char *name;
};

static int compare_last_name(const void *a, const void *b)
{
    const struct passenger_rep *pa = (const struct passenger_rep *)a;
    const struct passenger_rep *pb = (const struct passenger_rep *)b;
    return strcmp(last_name(pa->name), last_name(pb->name));
}

/* Report (e): passengers on a flight, sorted by last name */
void report_passengers_on_flight(struct passenger_rep *passengers, int count,
                                 const char *flightnumber)
{
    int i;
    printf("\n==================================================\n");
    printf("  PASSENGERS ON FLIGHT %s (sorted by last name)\n", flightnumber);
    printf("==================================================\n");
    if (count == 0)
    {
        printf("No passengers booked on this flight.\n");
        return;
    }
    qsort(passengers, (size_t)count, sizeof(*passengers), compare_last_name);
    for (i = 0; i < count; ++i)
        printf("%-10s %s\n", passengers[i].passenger_id, passengers[i].name);
}

/* Report (f): simple system statistics */
void report_statistics(int airlines, int flights, int passengers,
                       int reservations, int seats_taken, int total_seats)
{
    printf("\n==================================================\n");
    printf("  SYSTEM STATISTICS\n");
    printf("==================================================\n");
    printf("Airlines        : %d\n", airlines);
    printf("Flights         : %d\n", flights);
    printf("Passengers      : %d\n", passengers);
    printf("Reservations    : %d\n", reservations);
    printf("Seats booked    : %d of %d (%.1f%% load factor)\n",
           seats_taken, total_seats,
           total_seats ? (100.0 * seats_taken / total_seats) : 0.0);
}

#endif /* REPORTS_H */
