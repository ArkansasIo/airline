# Build the main console program and the CSV import tool on Windows (clang++).
# Usage:  powershell -File build.ps1
$ErrorActionPreference = "Stop"
$clang = "C:\Program Files\LLVM\bin\clang++.exe"

if (-not (Test-Path $clang)) {
    $clang = "clang++"
}

Write-Host "== Building airport.exe =="
& $clang "access navigation control.cpp" -o airport.exe
if ($LASTEXITCODE -ne 0) { throw "airport.exe build failed" }
Write-Host "OK: airport.exe"

Write-Host "== Building csv_import.exe =="
& $clang "src/csv_import.c" -o csv_import.exe
if ($LASTEXITCODE -ne 0) { throw "csv_import.exe build failed" }
Write-Host "OK: csv_import.exe"

Write-Host "== Build complete =="
