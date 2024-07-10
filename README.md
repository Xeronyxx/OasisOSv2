# OasisOS [![Hits](https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2FXeronyxx%2FOasisOS&count_bg=%2300C2FD&title_bg=%23555555&icon=&icon_color=%23E7E7E7&title=hits&edge_flat=false)](https://hits.seeyoufarm.com)

![Maintainer](https://img.shields.io/badge/maintainer-funwithalbi-blue)
![Users](https://img.shields.io/badge/users-0-blue)

OasisOS is currently a terminal OS.
Only supports:
* USB Keyboards
* ATA disks
* VGA monitors

It might also support HDMI monitors but I'm not quite sure. OasisOS has been tested on real hardware and it works under those specifications. Albeit the memory amount display might not work.

# Building from source
Before proceeding, make sure to install [Docker](https://docker.com).
To build from source, `git clone` the repository, then run this command in the cloned folder:

`docker build buildenv -t oasisos-buildenv`

Wait for a while for Docker to build your image, then run the following command:

PowerShell: `docker run --rm -it -v "${pwd}:/root/env" oasisos-buildenv`

Windows CMD: `docker run --rm -it -v "%cd%":/root/env oasisos-buildenv`

UNIX-like (Linux or MacOS): `docker run --rm -it -v "$(pwd)":/root/env oasisos-buildenv`

Once you are in the Docker image, run the following command:

`make build-x86_64`

Once done, you should be able to see a build folder and dist folder inside of your cloned folder. The dist folder contains the `kernel.iso`.

Enjoy!

# Credits

This project couldn't have been made possible without GNU GRUB, which creates the bootable ISO.
