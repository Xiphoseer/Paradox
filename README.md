# Paradox
This software is inteded as a toolkit for the development of
a server emulator for the game LEGO Universe. It provides a set
of commands that can be used to read, analyse and possibly write
different file formats that the game used, as well as generating
documentation and source code snippets (mainly c++). These may be
used within server software wherever datastructures are commonly
known, and just very tedious to implement.

## Operating System
This software was written for use on a Linux distribution, and
as such may not work on other operating systems. The intention
is for it to be platform independent, but it may require some
changes to get it to work. I am open to contributions that allow
this software to be built on other systems, provided that it does
not break existing setups (too much).

## Building & Installation
Currently the repository is optimized to be built by the GNU
autotools. I'm happy to include other mechanisms like CMake,
if someone gets it working properly with all dependencies.

For building with the autotools, I recommend the following procedure:

```
# autoreconf --install
# mkdir build
# cd build
# ../configure
# make
# sudo make install
```

## Dependencies

This software requires (at least for building with gcc on linux) the
following libraries to be installed on your system:

* zlib (https://www.zlib.net/)
* Magick++ (http://www.imagemagick.org/Magick++/)
* JSON for Modern C++ (https://github.com/nlohmann/json)
* assembly (https://github.com/xiphoseer/assembly/)

At the moment, all three of the are required, altough I may add
some configure options later down the line to make some feature
that require these dependencies optional.

## License

Currently, I have not decided on a license for this project,
though as this is available publicly on github, I plan on choosing
a fairly standard open source one. This means that for the meantime
I tolerate other people using this software, but I still own the
IP rights to all the code I wrote.

## Notes

This codebase may contain some code snippets from stackoverflow
or similar sites. I try to mark all occurences appropriately within
the codebase. If you feel like I missed the attribution somewhere,
feel free to contact me and I will sort that out.

In case you found this, having never heard of any LU restoration
projects before, but are curious as to what has happend in the past years,
check out [Darkflame Universe](https://darkflameuniverse.org) or
[lcdr Universe](https://lcdruniverse.org).
