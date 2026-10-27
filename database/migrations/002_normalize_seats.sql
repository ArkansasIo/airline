-- Migration 002: normalize flight seats and reservation seat assignments.
-- Safe to run after database/schema.sql.

USE airport_control;

CREATE TABLE IF NOT EXISTS seat (
  flightnumber  VARCHAR(80) NOT NULL,
  seat_id       VARCHAR(20) NOT NULL,
  available     TINYINT(1) NOT NULL DEFAULT 1,
  passenger_id  VARCHAR(20) NULL,
  cost          DECIMAL(10,2) NOT NULL DEFAULT 0.00,
  PRIMARY KEY (flightnumber, seat_id),
  CONSTRAINT fk_seat_flight
    FOREIGN KEY (flightnumber) REFERENCES flight(flightnumber)
    ON DELETE CASCADE,
  CONSTRAINT fk_seat_passenger
    FOREIGN KEY (passenger_id) REFERENCES passenger(passenger_id)
    ON DELETE SET NULL,
  INDEX idx_seat_availability (flightnumber, available)
) ENGINE=InnoDB;

CREATE TABLE IF NOT EXISTS reservation_seat (
  reservation_id VARCHAR(20) NOT NULL,
  flightnumber   VARCHAR(80) NOT NULL,
  seat_id        VARCHAR(20) NOT NULL,
  PRIMARY KEY (reservation_id, seat_id),
  UNIQUE KEY uq_reservation_seat (flightnumber, seat_id),
  CONSTRAINT fk_reservation_seat_reservation
    FOREIGN KEY (reservation_id) REFERENCES reservation(reservation_id)
    ON DELETE CASCADE,
  CONSTRAINT fk_reservation_seat_seat
    FOREIGN KEY (flightnumber, seat_id)
    REFERENCES seat(flightnumber, seat_id)
    ON DELETE CASCADE
) ENGINE=InnoDB;

-- Keep the denormalized flight counter consistent with the normalized seat map.
CREATE INDEX idx_reservation_flight ON reservation(flightnumber);
