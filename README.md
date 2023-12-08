# AGV Data Parser

Simple program for parsing data captured by AGV robot and parsing it to CSV file.

### Running program

`cmake . && make && ./main`

### How to use
In `parseBinary.cpp` file we can specify which signals we want to include in output CSV file. To do this modify `required_fields` vector. Names of signals must exactly match names in XML file that describes binary data.

### Adding new converters
If any signal has a new datatype which is not handled in current version a new converter must be added. 

- Each converter must implement `getValue` method which specifies how raw bytes should be parsed in order to receive string that is later saved to output CSV file.

- Each converter must be added to a map in `config.h` that joins this converter with datatype's name it should be applied to.
