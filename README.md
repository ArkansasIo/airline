# airport-control

C++ airline reservation database system (console based). Author: apocalypse coder0.

## Repository layout

```
access navigation control.cpp   main console program (menu-driven linked lists)
src/csv_loader.h                CSV import library for the data/ files
src/csv_import.c                standalone CSV import verification tool
src/reports.h                   reports: flights by departure time,
                                passengers by last name, statistics
data/airlines.csv               airline master data
data/flights.csv                flight schedule (unique flight number)
data/passengers.csv             passenger master data (unique passenger ID)
data/reservations.csv           reservations (unique reservation ID)
data/seat_assignments.csv       seat map per flight
database/schema.sql             MySQL schema (airline, flight, passenger,
                                reservation tree: node/branch/sub-branch/module,
                                app_setting)
database/dataset.sql            sample dataset for MySQL
config/config.json              JSON configuration (database, API, seats, logging)
config/settings.env             environment-variable settings overrides
config/api.md                   REST API specification (v1)
config/reservation_edit.h       C structs mirroring the reservation tree
```

## Build

```powershell
# main console program
clang++ "access navigation control.cpp" -o airport.exe

# CSV import verification tool
clang++ src/csv_import.c -o csv_import.exe
```

## Run

```
airport.exe        # loads airline.txt (if present) and shows the main menu
csv_import.exe     # verifies the CSV dataset in data/
```

Main menu: add/delete/list airlines, enter the flight menu per airline
(add/delete/list flights, passenger menu, reservation menu, seat assignment
menu), then option 5 saves everything back to `airline.txt`.

## Data model

- **Flight**: Flight Number (unique key), departure/arrival city, date,
  departure/arrival time, total seats, seats booked.
- **Reservation**: Reservation ID (unique key), Passenger ID, Flight Number, Cost.
- **Passenger**: Passenger ID (unique key), name, address, city.

Business rules:
- Passengers and flights must already exist before they can appear on a reservation.
- Unique IDs are never duplicated across the files.
- Report outputs: all flights sorted by departure time; all passengers on a
  selected flight sorted by last name; save option stores the data file.

## Database

Apply `database/schema.sql` then `database/dataset.sql` to a MySQL server:

```
mysql -u root -p < database/schema.sql
mysql -u root -p < database/dataset.sql
```

Settings live in the `app_setting` table and can be overridden by
`config/settings.env`.
