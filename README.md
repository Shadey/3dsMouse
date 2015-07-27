# 3dsMouse
3dsmouse uses an udp server/client setup to make the 3ds act as a mouse. Currently this only works for linux because I would imagine it would be simple to port over to  Windows/Mac

# Why UDP
I choosen to use UDP over TCP just because of the smaller packet sizes that UDP as. I would assume this would make the 3ds feel more responsive than TCP would. The con to this is there is no way to limit the amount of clients connected to the 3ds. (At least to my knowledge). So using this program in a public area would provide to be quite dangerous at its current stage. I might switch to TCP at later point, this project was more of a Proof of Concept then anything else.

#What else is there to do
- Make a makefile for the server.
- Use the circlepad instead of the DPAD
- Maybe also use touchpad for navigation as well.
- Port to Windows/Mac

#Build Client
Use ftbrony or ftpony for quick development. There a small python script that will send over the files over over the host

```
make
```
And thats it, the files should be on your 3ds

#Build server 
```
gcc -o server source/*.c -Iinclude -lX11 -lXst
```
