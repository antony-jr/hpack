# hpack

**hpack** can convert any data file into a C header file , storing the data in a C array. Thus one can use this array to reconstruct or use this data on runtime.
Useful if you want to store some data into your executable.

**Warning** : The resulting header file size will be your original file size multiplied by **4.4** KiB which can be quite huge. However no useless data is added to the array.
Therefore be mindful on what files you pack into your header.

# Installation

```
 $ git clone https://github.com/antony-jr/hpack
 $ cd hpack
 $ cmake .
 $ make -j$(nproc)
 $ ./hpack 
```

# Usage

```
Usage: ./hpack [INPUT FILEPATH] [OPTIONS]

OPTIONS: 
        -o,--output          set path to output file.
        -v,--variable-name   variable name to assign data.
        -g,--header-guard    name for header guard.
```

for example , you can encode the hpack binary as a c header like so,

```
 $ ./hpack hpack -v "hpack_binary_data" -g "HPACK_BINARY_DATA" -o hpack_binary.h
```

# License

The MIT License.

Antony Jr.
 
