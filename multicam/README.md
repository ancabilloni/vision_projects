## Reading & display two usb webcam concurrently with Boost Thread (C++)

#### Tested on Ubuntu 18.04
The program detects up to 2 cameras in the system. Here I tested with a built-in laptop camera, and an external usb webcam.

#### Require:
- g++
- OpenCV
- Boost

#### To compile:
```
g++ multicam.cpp -o multicam -Lusr/lib/x86_64-linux-gnu -lboost_system -lboost_thread `pkg-config opencv --libs`
```

Replace `-Lusr/lib/x86_64-linux-gnu` with `-L<your/path/to/boost`

To locate path to Boost file: `locate boost | grep libboost_system` 

#### TO-DO:
- Create Makefile
