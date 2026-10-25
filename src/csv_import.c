/*
 * csv_import.c
 * Standalone import tool: reads the CSV files in data/ and prints a
 * summary of what was loaded. Can be linked with the main program or
 * built on its own to verify the dataset:
 *
 *   clang++ src/csv_import.c src/csv_loader_test.c -o csv_import.exe
 */
#include <stdio.h>
#include "csv_loader.h"

int main(void)
{
    char **airlines = NULL;
    int na = csv_load_airlines(&airlines);
    printf("airlines.csv            : %d record(s)\n", na);

    struct csv_flight *flights = NULL;
    int nf = csv_load_flights(&flights);
    printf("flights.csv             : %d record(s)\n", nf);

    struct csv_passenger *passengers = NULL;
    int np = csv_load_passengers(&passengers);
    printf("passengers.csv          : %d record(s)\n", np);

    struct csv_reservation *res = NULL;
    int nr = csv_load_reservations(&res);
    printf("reservations.csv        : %d record(s)\n", nr);

    struct csv_seat *seats = NULL;
    int ns = csv_load_seats(&seats);
    printf("seat_assignments.csv    : %d record(s)\n", ns);

    printf("total records loaded    : %d\n", na + nf + np + nr + ns);
    return 0;
}
