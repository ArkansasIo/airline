/*
 * csv_loader.h
 * CSV data import for the Airline Reservation System.
 *
 * Loads the files in the data/ directory:
 *   airlines.csv          -> list of airline names
 *   flights.csv           -> airline + flight records
 *   passengers.csv        -> passenger records
 *   reservations.csv      -> reservation records (unique keys)
 *   seat_assignments.csv  -> seat map per flight
 *
 * These mirror the same structures used by access navigation control.cpp
 * and the MySQL schema in database/schema.sql.
 */
#ifndef CSV_LOADER_H
#define CSV_LOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CSV_DIR "data/"
#define MAX_LINE 1024

/* ---------- small helpers ---------- */

/* Trim trailing CR/LF from a line read with fgets */
static void csv_chomp(char *s)
{
    size_t n = strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r'))
        s[--n] = 0;
}

/* Get the n-th comma separated field of a line (0 based).
 * Returns a malloc'd copy, or an empty string if the field is missing.
 * Fields may be quoted; simple unquoting is applied. */
static char *csv_field(const char *line, int n)
{
    const char *p = line;
    int field = 0;
    int in_quotes = 0;

    while (field < n && *p)
    {
        if (*p == '"')
            in_quotes = !in_quotes;
        else if (*p == ',' && !in_quotes)
            ++field;
        ++p;
    }

    /* collect until next unquoted comma or end of line */
    size_t cap = 256, len = 0;
    char *out = (char *)malloc(cap);
    if (!out)
        return NULL;
    out[0] = 0;

    while (*p && (in_quotes || *p != ','))
    {
        if (*p == '"')
        {
            in_quotes = !in_quotes;
            ++p;
            continue;
        }
        if (len + 2 > cap)
        {
            cap *= 2;
            char *tmp = (char *)realloc(out, cap);
            if (!tmp)
            {
                free(out);
                return NULL;
            }
            out = tmp;
        }
        out[len++] = *p++;
    }
    out[len] = 0;
    return out;
}

/* Open a data file, skipping the header line. Returns NULL if missing. */
static FILE *csv_open(const char *filename)
{
    char path[256];
    snprintf(path, sizeof(path), CSV_DIR "%s", filename);
    FILE *fp = fopen(path, "r");
    if (!fp)
        return NULL;
    char line[MAX_LINE];
    if (fgets(line, sizeof(line), fp) == NULL) /* discard header */
    {
        fclose(fp);
        return NULL;
    }
    return fp;
}

/* ---------- CSV record loaders ---------- */

/* Load airline names: "airlinename" */
static int csv_load_airlines(char ***names_out)
{
    FILE *fp = csv_open("airlines.csv");
    if (!fp)
        return 0;

    int count = 0, cap = 16;
    char **names = (char **)malloc(cap * sizeof(char *));
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp))
    {
        csv_chomp(line);
        if (!line[0])
            continue;
        if (count == cap)
        {
            cap *= 2;
            names = (char **)realloc(names, cap * sizeof(char *));
        }
        names[count++] = csv_field(line, 0);
    }
    fclose(fp);
    *names_out = names;
    return count;
}

/* One flight record */
struct csv_flight
{
    char *airline;
    char *flightnumber;
    char *date;
    char *departure;
    char *arrival;
    char *takeoff;
    char *arrivetime;
    int total_seats;
    int seats_booked;
};

/* Load flights: "airline,flightnumber,date,departure,arrival,takeoff,arrivetime,total,booked" */
static int csv_load_flights(struct csv_flight **out)
{
    FILE *fp = csv_open("flights.csv");
    if (!fp)
        return 0;

    int count = 0, cap = 16;
    struct csv_flight *rows = (struct csv_flight *)malloc(cap * sizeof(*rows));
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp))
    {
        csv_chomp(line);
        if (!line[0])
            continue;
        if (count == cap)
        {
            cap *= 2;
            rows = (struct csv_flight *)realloc(rows, cap * sizeof(*rows));
        }
        struct csv_flight *r = &rows[count];
        r->airline = csv_field(line, 0);
        r->flightnumber = csv_field(line, 1);
        r->date = csv_field(line, 2);
        r->departure = csv_field(line, 3);
        r->arrival = csv_field(line, 4);
        r->takeoff = csv_field(line, 5);
        r->arrivetime = csv_field(line, 6);
        char *ts = csv_field(line, 7);
        r->total_seats = atoi(ts);
        free(ts);
        char *sb = csv_field(line, 8);
        r->seats_booked = atoi(sb);
        free(sb);
        ++count;
    }
    fclose(fp);
    *out = rows;
    return count;
}

/* One passenger record */
struct csv_passenger
{
    char *suffix;
    char *name;
    char *id;
    char *address;
    char *city;
    char *gender;
    char *dob;
    char *weight;
};

/* Load passengers: "suffix,name,id,address,city,gender,dob,weight" */
static int csv_load_passengers(struct csv_passenger **out)
{
    FILE *fp = csv_open("passengers.csv");
    if (!fp)
        return 0;

    int count = 0, cap = 16;
    struct csv_passenger *rows = (struct csv_passenger *)malloc(cap * sizeof(*rows));
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp))
    {
        csv_chomp(line);
        if (!line[0])
            continue;
        if (count == cap)
        {
            cap *= 2;
            rows = (struct csv_passenger *)realloc(rows, cap * sizeof(*rows));
        }
        struct csv_passenger *r = &rows[count];
        r->suffix = csv_field(line, 0);
        r->name = csv_field(line, 1);
        r->id = csv_field(line, 2);
        r->address = csv_field(line, 3);
        r->city = csv_field(line, 4);
        r->gender = csv_field(line, 5);
        r->dob = csv_field(line, 6);
        r->weight = csv_field(line, 7);
        ++count;
    }
    fclose(fp);
    *out = rows;
    return count;
}

/* One reservation record */
struct csv_reservation
{
    char *id;
    char *passenger_id;
    char *flight_number;
    char *cost;
};

/* Load reservations: "id,passenger_id,flight_number,cost" */
static int csv_load_reservations(struct csv_reservation **out)
{
    FILE *fp = csv_open("reservations.csv");
    if (!fp)
        return 0;

    int count = 0, cap = 16;
    struct csv_reservation *rows = (struct csv_reservation *)malloc(cap * sizeof(*rows));
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp))
    {
        csv_chomp(line);
        if (!line[0])
            continue;
        if (count == cap)
        {
            cap *= 2;
            rows = (struct csv_reservation *)realloc(rows, cap * sizeof(*rows));
        }
        rows[count].id = csv_field(line, 0);
        rows[count].passenger_id = csv_field(line, 1);
        rows[count].flight_number = csv_field(line, 2);
        rows[count].cost = csv_field(line, 3);
        ++count;
    }
    fclose(fp);
    *out = rows;
    return count;
}

/* One seat assignment record */
struct csv_seat
{
    char *flight_number;
    char *seat;
    char *passenger_id;
    int available;
    char *cost;
};

/* Load seat assignments: "flight_number,seat,passenger_id,available,cost" */
static int csv_load_seats(struct csv_seat **out)
{
    FILE *fp = csv_open("seat_assignments.csv");
    if (!fp)
        return 0;

    int count = 0, cap = 16;
    struct csv_seat *rows = (struct csv_seat *)malloc(cap * sizeof(*rows));
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp))
    {
        csv_chomp(line);
        if (!line[0])
            continue;
        if (count == cap)
        {
            cap *= 2;
            rows = (struct csv_seat *)realloc(rows, cap * sizeof(*rows));
        }
        struct csv_seat *r = &rows[count];
        r->flight_number = csv_field(line, 0);
        r->seat = csv_field(line, 1);
        r->passenger_id = csv_field(line, 2);
        char *av = csv_field(line, 3);
        r->available = atoi(av);
        free(av);
        r->cost = csv_field(line, 4);
        ++count;
    }
    fclose(fp);
    *out = rows;
    return count;
}

#endif /* CSV_LOADER_H */
