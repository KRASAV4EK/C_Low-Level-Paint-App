# Semester Project APO
Our task was to create an app like "Paint" in Windows on the mzAPO desk.

## Video

A video of an older build can be found [here](video/video.mp4)

## Advice
You will need ARM cross compiler toolchain to compile the program. If you
use Ubuntu then you will need next line:
```
sudo apt install crossbuild-essential-armhf
```

## Connecting
There are two possible ways to connect to the desk: Online and Offline.
We were using only offline method.

There are some instructions for offline connect:

#### Login and Password
It will probably ask you to fill in the login and password so you can use the next one:
```
Login: root
Password: mzAPO35
```

#### SSH
It is necessary to add SSH mzAPO key. You can use next command:
```
ssh-add mzapo-root-key
```

#### IP
It is necessary to add IP of desk you are going to use. 
You will see an image at the display, all you need is to calculate from binary to decimal. 
Write that IP into Makefile 20. row:
```
Example:
firstline.secondline.thirdline.forthline
TARGET_IP ?= 192.168.223.216
```

## Running the programs
#### To run the program you must set IP and SSH key. After that just type next line in terminal.
```
make run
```

#### If you want to clean delete all .o files just type next line in terminal.
```
make clean
```

#### After compiling all files you can use next line just to run the program without compiling.
```
./main
```

## Built With
* [VS Code](https://code.visualstudio.com/) - The editor we were using.

## Authors
* **Timofeev Ilia** - *Initial work* - [CTU](https://gitlab.fel.cvut.cz/timofili)
* **Zharkov Arsenii** - *Initial Work* - [CTU](https://gitlab.fel.cvut.cz/zharkars)

## Information
You can find all needed information [here](https://cw.fel.cvut.cz/wiki/courses/b35apo).
