[![Build Status](https://travis-ci.org/Granddave/Stretch-timer.svg?branch=master)](https://travis-ci.org/Granddave/Stretch-timer)

# Stretch Timer

Stretch Timer is an open source project that help people to stand up and stretch between their work sessions.

![Main window](https://github.com/Granddave/Stretch-timer/blob/master/preview-images/main-window.png)

![Popup message](https://github.com/Granddave/Stretch-timer/blob/master/preview-images/popup.png)

![Settings](https://github.com/Granddave/Stretch-timer/blob/master/preview-images/settings.png)

## Build dependencies

Ubuntu 20.04 dev packages: `qtbase5-dev qtmultimedia5-dev libxss-dev`

## Compilation

```sh
git clone https://github.com/Granddave/Stretch-timer.git
mkdir build && cd build
cmake .. && cmake --build .
```

## Install

### Windows

Go to [releases page](https://github.com/Granddave/Stretch-timer/releases) to download an installer for the latest stable version or download source and compile yourself.

### Linux

No complete precompiled binary or package exist for platforms other than Windows at the moment.
Compile and install the binary manually.
Tested on Manjaro KDE and Debian 9 and 10, but should work on most Linux platforms.

## License

Stretch Timer is licensed under GNU GPL3.
Developed by David Isaksson ([davidisaksson93@gmail.com](mailto:davidisaksson93@gmail.com))

### 3rd party licenses

The [darkstyle theme (cred to Jorgen-VikingGod)](https://github.com/Jorgen-VikingGod/Qt-Frameless-Window-DarkStyle) is licensed under the MIT license.
