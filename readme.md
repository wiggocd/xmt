## xmt

A fun piece of malware targeted at Windows XP / NT 5.1 based operating systems.

It goes without saying: don't run this on a computer or VM with, or connected to, any valuble data.

# Build Requirements

- g++ (mingw)

# Building

`make.bat`

# Testing

Run `bin/xmt.exe` in an isolated VM.

# Feature Roadmap

- Copy itself to the system directory and remove the original executable
- Attach to startup
- Disable task manager and regedit
- Overwrite boot sector at a certain date to display the wake up message from the matrix
