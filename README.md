# Featureless Linux Library
[![Production - Run Tests](https://github.com/thekevinday/fll/actions/workflows/test-production.yml/badge.svg)](https://github.com/thekevinday/fll/actions/workflows/test-production.yml)

The Featureless Linux Library (FLL) is a library, along with a small set of programs, focused on a different design paradigm that found in GNU Linux systems (and now SystemdD Linux systems).

When computer power increases, programmers generally add more "features", thus making any performance gains in new hardware negligible.
This project is an attempt to develop a library above libc that breaks out of this terrible loop.

This github repository is a backup/alternative to the primary repo website on sourceforge.net where this project originated:
- https://sourceforge.net/projects/fll/

To keep releases simple, the default pre-packaged release tarballs are packages using the **monolithic** mode.
Be sure to compile using this mode `-m monolithic`.

The other build modes, **level**, **individual**, and **stand_alone**, may be accessed by downloading the repo with the appropriate version tag and using the bootstrap.sh build script.
- https://github.com/thekevinday/fll/releases

A good example on how build can be seen in the bootstrap-example.sh script found under the **build/scripts/** directory.
- https://github.com/thekevinday/fll/blob/github/build/scripts/bootstrap-example.sh

## Intended Features
- Wrapper to POSIX and possibly Linux libc functionality.
- Emphasis on making code human-readable and hacker-friendly.
- Security through Integrity design practices.
- UTF-8 Native support.
- Multiple Language support, to some extent.
- Keep It Simple (KIS) principles, without sacrificing *humanability*.
- A consistent API design paradigm.
- Long Term Survivability, software should be capable on staying the same for 20+ years and not be considered "outdated".
- Once a stable release is complete, its API should remain unchanged.
- Avoid the "Features", aka "bells and whistles" or "buzzword".

Note: *Hack*, *Hackable*, *Hacker*, etc.. are used here in the more traditional sense of the term and not in the context of *"..to break in"*.

## Licenses
There are several licenses in the project, each regarding different parts:
- cc-by-sa-4.0
- lgpl-2.1-or-later
- open-standard-license-1.0 (draft)

The cc-by-sa-4.0 is only used for non-code, non-standard, and non-specification files such as documentation.
The lgpl-2.1-or-later is used for all code in this project, including scripts.
The open-standard-license-1.0 is used for all standards and specifications.

Each individual file (or associated parent or header file) should document which license that file (or associated source files) fall under.

All files and code, unless otherwise noted, are Copyright © 2007-2023 Kevin Day.

## Project Design
The program is designed around providing a consistent API with a huge focus on hackability.
This is open-source, so everyone should be encouraged to take this and change it in any way they like.

To encourage hackability, many parts of this project are designed to communicate what is going on.
Even the version number with releases are set up to consistently communicate.

The FLL Project is broken up into 3 "levels" of projects, along with a "4th" level where programs are provided.
With the exception of a few core projects in *level 0*, each project in levels 0, 1, and 2 may only depend on a lower level.

The FLL Project may then be compiled into 3 different types of package modes:
- Individual, where each library project and program is packaged individually.
- Level, where each library, but not each program, is packaged on a per level basis.
- Monolithic, where all libraries, but not each program, are packaged into a single library.

These package modes determine how the libraries are linked to and are for a system administrators or a distributors to decide upon.
Take an `main.c` as an example where the `main.c` depends on something in the `f_string` (A level 0 project).:
- Individual Compile Example: `gcc -lc -lf_string`.
- Level Compile Example: `gcc -lc -lfll_0`.
- Monolithic Compile Example: `gcc -lc -lfll`.

While the project does not focus on installing to the system, a very simple install script (`install.sh`) is provided as helper as well as a functional example.

## Versioning
The version number is broken up to implicitly communicate in both a human-friendly and machine-friendly manner.
There are 3 parts of the version number:
1. Major
2. Minor
3. Micro

The **Major** number represents the primary API compatibility.
Different numbers here essentially communicate different projects.

The **Minor** number represents the stable vs developmental state.
An even number, including 0, is used to represent a stable release.
With even numbers, the API is guaranteed to not change in a breaking way, but new functionality may be added.
That said, exceptions do happen so any exceptions are to be strongly discouraged and used as a last resort.

An odd number represents development release.
The API may be broken between releases, but ideally even that will not change.

The **Micro** number represents individual release changes.
While this essentially means a change has been made, there are a common type of changes to be found within micro version number changes.
For stable releases, these are often security and bugfixes with new functionality being rare if at all.
For development releases, this is just about anything.

In general, to assure compatibility, new functionality will entail a new micro version for development followed a stable micro version.
The goal of this project is to not, if ever, have such things so ideally these will be uncommon once the projects main goals are released as a 1.0.0.

There is no ceiling to the numbers so a version of 1.70.10241 is completely valid.

## Programs
One of the original goals of this project was to make it available in multiple (programming) languages, which initially yielded: C, C++, and GNU Bash.
It was eventually decided that the best way to expose it to GNU Bash would be to expose the some parts of the library via programs for GNU Bash to call.

The FLL Project also needs examples, so there are some basic programs provided as examples on how to utilize the FLL API.
But why make *example* programs when *real* programs could be made and used as an example?

The programs themselves follow FLL design principles on making the interface human-friendly.
Software should be a tool for humans, and not a tool for machines.

### Program - Byte Dump
This tool is a nifty way to get a UTF-8 friendly hexdump alternative.
The output is intended to honor some of the feel of hexdump but do so in an FLL way.

### Program - Control
This project is not complete and development is planned for the FLL-0.7.x development releases.

The goal of this is to communicate with the "Controller" program, such as starting or stopping services.

### Program - Controller
This project is not complete and development is planned for the FLL-0.7.x development releases.

The goal of this is to provide task and service management similar to sysvinit, initng, and systemd.
This is designed to be used for booting the system as if it were /sbin/init.

This should be controllable from user-space via the "Control" program.

### Program - Featureless Make
The Featureless Make is the original program and goal of the Featureless Linux Library.
The GNU Make, Autoconf, and all those build processes are unnecessarily complex.

A major problem with these build systems is that they try to manage installation as well as compilation.
A build system should be just that a build system.
Trying to handle how the built package gets installed should be done by system administrators or distributors.
By avoiding this, the code becomes simpler, more "featureless", easier to maintain, and easier to hack.

The Featureless Make, called *Fake*, provides two primary ways to compile C, C++, and possibly other compiled languages:
1. Using the *"build"* command.
2. Using the *"make"* command.

The *build* command is as simple as it can be and follows a Featureless Settings Specification (FSS).
The *make* command (and its respective *fakefile*) provides a more advanced interface for handling complex build processes or compiling languages other than C/C++.

The build command (and subsequently the make command) currently provide some hardcoded program settings, such as the indexer "ar" runs `ar rcs`.
Eventually such things will be expanded into an FSS setting and made customizable.

Both the build and make commands support a small subset of make and autoconf functionality to make transitioning easier or make it easy to work alongside make and autoconf.

To help with understanding and using the Featureless Make program, fully functional example build settings and fakefiles are created for the program bzip (specifically version 1.0.8):
- https://github.com/thekevinday/fll/blob/github/level_3/fake/data/build/settings-example-bzip2
- https://github.com/thekevinday/fll/blob/github/level_3/fake/data/build/settings-example-bzip2
- https://github.com/thekevinday/fll/blob/github/level_3/fake/data/build/settings-example-bzip2recover
- http://sourceware.org/bzip2/

There is also a fakefile pre-configured to run GNU Make within itself to compile the Linux kernel fom source:
- https://github.com/thekevinday/fll/blob/github/level_3/fake/data/build/fakefile-example-linux_using_make

Bzip2 may be found here:
- http://sourceware.org/bzip2/

### Program - Firewall
This is one of the earliest proof of concept and functional example of the FLL library.
Now it is currently outdated, but it still remains operational as an iptables wrapper.
This program is actively used on the Turtle Kevux distribution at https://kevux.org/.
This requires *iptables* to be installed and executable.

### Program - FSS * Read and Write Programs
This is grouping together several different Featureless Settings Specification (FSS) programs that each read or write to their respective settings specification.

These are particularly useful for GNU Bash scripts to call and utilize for processing FSS files.

### Program - FSS Status Code and Status Code Programs
This is a group of programs used to translate status codes from a numeric representation to a more human-readable text representation.
The FSS Status Code program handles all of the standard FLL status codes as well as FSS specific status codes.
The Status Code program handles all of the standard FLL status codes.

These are particularly useful for GNU Bash programs to call and utilize for processing FSS files.

### Program - FSS Identify
This program is a compliment to the FSS * Read and FSS * Write functions that is designed to be used for identifying FSS files based on the FSS header comments.
A header comment might look like '# fss-0002 iki-0001'.

These are particularly useful for GNU Bash programs to call and utilize for processing FSS files.

### Program: IKI Read
Identical to the FSS Read Programs in design, this is a program for reading files in IKI format.

The IKI settings specification plays on how it is simpler than a Wiki syntax.
The IKI could be used for anything from e-mails and text-messages to word-processors.
The goal with IKI is to be very easily readably by a human, such as: `iki:"example"` or `url:"https://sourceforge.net/projects/fll/"`.

This program is a swiss army knife for reading files that contain IKI syntax.

### Program: IKI Write
Identical to the FSS Write Programs in design, this is a program for writing files in IKI format.

The IKI settings specification plays on how it is simpler than a Wiki syntax.
The IKI could be used for anything from e-mails and text-messages to word-processors.
The goal with IKI is to be very easily readably by a human, such as: `iki:"example"` or `url:"https://sourceforge.net/projects/fll/"`.

This program is a swiss army knife for writing files that contain IKI syntax.

### Program: UTF-8
A tool to convert one or more UTF-8 characters from the codepoint representation to a binary representation and back.

Can convert complete files into a binary file.
Can convert complete files into a text file of space separated codepoint values.

### Building and Documentation
At this time the documentation can only be found maintained within the FLL project itself within the *documents/* or *specifications/* directories.

While releases are pre-constructed, consider looking at the project in the git repo under the *build/* directory.
There are some scripts that provide examples on how to build and use the FLL project it all of its parts, such as:
- https://github.com/thekevinday/fll/blob/github/build/documents/readme.txt
- https://github.com/thekevinday/fll/blob/github/build/documents/readme.bootstrap.txt
- https://github.com/thekevinday/fll/blob/github/build/documents/readme.build.txt
- https://github.com/thekevinday/fll/blob/github/build/scripts/bootstrap-example.sh
- https://github.com/thekevinday/fll/blob/github/build/scripts/bootstrap.sh

### Downloading and Installing
The project can be installed using the latest release tag, such as 0.6.9:
- https://github.com/thekevinday/fll/releases

Using the raw git structure allows for the most flexibility but requires additional work to "package" a project.
The projects may be packaged using the package script and then each package can be individually built and installed:
- https://github.com/thekevinday/fll/blob/github/build/scripts/package.sh

The officially pre-packaged releases may be found at sourceforge.net:
- https://sourceforge.net/projects/fll/files/

The latest version, which at the time of this documentation write-up is a 0.6.x release that is the 0.6.9 stable release.
- https://sourceforge.net/projects/fll/files/FLL-0.6/0.6.9/

The main pre-packaged FLL release, which is pre-packaged for **monolithic** build mode, is called fll-0.6.9.tar.gz.
- https://sourceforge.net/projects/fll/files/FLL-0.6/0.6.9/monolithic/monolithic-fll-0.6.9.tar.gz/download

The other pre-packaged files in that directory are the individual pre-packaged programs.

Be sure to pass `-m monolithic` when bootstrapping or building the project using Featureless Make:
- `./boostrap.sh build -m monolithic`
- `fake build -m monolithic`

The files are built and stored into the `build/` project directory.
Either manually copy this over, use a package manager that supports the project (none exist at the time of this writing), or use the helper install script which by default follows the standard GNU Linux local install path paradigm (installs to `/usr/local/`).
- `su -c './install.sh'`
