# Airport Control - Data File Formats

All files live in `data/` and use UTF-8 CSV with a header row on line 1.
Comma is the field separator; fields may be double-quoted.

## airlines.csv
| Column | Type | Notes |
|--------|------|-------|
| airlinename | string | unique airline name |

## flights.csv
| Column | Type | Notes |
|--------|------|-------|
| airlinename | string | references airlines.csv |
| flightnumber | string | **unique key** |
| date_of_flight | YYYY-MM-DD | |
| departure_location | string | city |
| arrival_location | string | city |
| take_off_time | HH:MM | local departure time |
| arrival_time | HH:MM | local arrival time |
| total_seats | int | capacity |
| seats_booked | int | must be <= total_seats |

## passengers.csv
| Column | Type | Notes |
|--------|------|-------|
| name_suffix | string | Mr., Mrs., Dr., ... |
| name | string | full name (First Last) |
| passenger_id | string | **unique key** (P0001...) |
| address | string | |
| city | string | |
| gender | M/F/O | |
| data_of_birth | YYYY-MM-DD | |
| weight | string | e.g. 78kg |

## reservations.csv
| Column | Type | Notes |
|--------|------|-------|
| reservation_id | string | **unique key** (R0001...) |
| passenger_id | string | must exist in passengers.csv |
| flight_number | string | must exist in flights.csv |
| cost | decimal | ticket price |

## seat_assignments.csv
| Column | Type | Notes |
|--------|------|-------|
| flight_number | string | must exist in flights.csv |
| seat_assignment | string | seat id, e.g. 12A |
| passenger_id | string | empty if the seat is free |
| available | 0/1 | 1 = seat free, 0 = seat taken |
| cost | decimal | price for the seat |

## Integrity rules
1. Reservation rows must reference an existing `passenger_id` and `flight_number`.
2. Unique keys (`flightnumber`, `passenger_id`, `reservation_id`) must not repeat.
3. `seats_booked` on a flight should equal the number of rows for that flight
   with `available = 0` in seat_assignments.csv.

## Loading order
1. `airlines.csv`
2. `flights.csv`
3. `passengers.csv`
4. `reservations.csv`
5. `seat_assignments.csv`

The loader in `src/csv_loader.h` follows this order automatically.
