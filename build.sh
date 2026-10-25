#!/usr/bin/env bash
# Build the main console program and the CSV import tool (Linux/macOS/MSYS).
set -e
echo "== Building airport.exe =="
clang++ "access navigation control.cpp" -o airport
echo "OK: airport"

echo "== Building csv_import =="
clang++ src/csv_import.c -o csv_import
echo "OK: csv_import"

echo "== Build complete =="
