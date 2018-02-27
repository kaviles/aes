# aes
Implementations of AES

1. To run Python tests:
    
    * From root of "python3" directory...

    * python -m unittest test.test_[TESTNAME]

    * Or...

    * python -m unittest discover

    * Please Note: Monte Carlo tests will take multiple minutes each to complete.

2. To run CPP tests:

    * From root of "cpp/tests" directory...

    * Compile test_[TESTNAME].cpp file

    * g++ -std=c++11 -o [TESTNAME].exe tests_[TESTNAME].cpp ../aes/aes.cpp ../aes/utils.cpp

    * Run [TESTNAME].exe

    * ./[TESTNAME].exe

Currently both implementations:

  * Only support 128-bit keys.
  * Only encrypt in ECB, CBC, CFB128 modes.
  * Both python3 and cpp implementation do not require any non-standard external libraries.

TODO:

  * Write out to output tests files.