## Reading & display two usb webcam concurrently with Boost Thread (C++)

The program detects up to 2 webcams in the system and grab images synchronously. A good example on real application for multi-threading.

#### Tested on Ubuntu 18.04
. Here I tested with a built-in laptop camera, and an external usb webcam.

#### Require:
- g++
- OpenCV
- Boost

#### To compile:
- Using Makefile, compile with: 
`make`

- Manual
```
g++ multicam.cpp -o multicam -Lusr/lib/x86_64-linux-gnu -lboost_system -lboost_thread `pkg-config opencv --libs`
```
#### Change path to Boost library if neccessary
- To locate path to Boost file: `locate boost | grep libboost_system` 

- In Makefile, replace your Boost path at LIBPATH.
- In manual method, replace `-Lusr/lib/x86_64-linux-gnu` with `-L<your/path/to/boost`



#### Usage
Start program with `./multicam display`
Without `display` argument, the program still runs but it doesn't show any display.

#### Limitation
Due to crashing issue with imshow() feature when attempt to display video streaming windows synchronously, a mutex lock is applied when user wants to display streaming. Hence, the system will be serialized. See Issues for example codes that cause the crashes.

#### Credits:
I learned alot from: https://putuyuwono.wordpress.com/2015/05/29/multi-thread-multi-camera-capture-using-opencv/
