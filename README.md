# aes
Implementations of AES

1. To run Python tests:

    * python3 tests.py

2. To run CPP tests:

    * Compile tests.cpp file

    * g++ -std=c++11 -o tests.exe tests.cpp aes.cpp

    * Run tests.exe

    * ./tests

Currently both implementations:

  * Only support 128-bit keys.
  * Only encrypt in ECB mode.
  * Only encrypt one block at a time.

TODO:

  * Add support for CBC.
  * Add support for CBF.
  * Implement Monte Carlo Tests.
  * Read in from input tests files.
  * Write out to output tests files.
  * Test with cases in validation document.
