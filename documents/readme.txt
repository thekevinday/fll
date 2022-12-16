# fss-0002 iki-0000
#
# license: cc-by-sa-4.0
#
# This file (assumed to be named readme.txt) can be more easily read using the following iki_read commands:
#   iki_read readme.txt +Q -w -r FLL FLL -WW character "'" "'" code '"' '"'
#
# To read the "Installation" section of this file, use this command sequence:
#   fss_basic_list_read readme.txt +Q -cn "Installation" | iki_read +Q -w -r FLL FLL -WW character "'" "'" code '"' '"'
#
# This readme file is inteded to provide a basic introduction to the Featureless Linux Library (FLL).
#

Installation:
  The FLL:"Featureless Linux Library" provides two installation types\:
    - The management scripts.
    - The Featureless Make program.

  The management scripts provide a way to manage the source code, such as updating dependencies, constructing the souce code for release, and bootstrap compiling the system.

  The bootstrap compiling provides a way to build and compile the entire FLL:"Featureless Linux Library" project, without the file:"fake" program (bold:"Featureless Make").
  This bootstrap process solves the problem where if you don't already have bold:"Featureless Make" installed, then you cannot install bold:"Featureless Make".
  These bootstrap scripts are written in bold:"GNU Bash".

  The source code needs to be packaged before it can be compiled by either the bootstrap scripts or by the bold:"Featureless Make" program.

  The bold:"Featureless Make" program is neither intended nor designed to be used as an installer, so the bootstrap scripts also provide an install script written in bold:"GNU Bash".
  This install script is intended to be used only by the FLL:"Featureless Linux Library".
  Future versions of the FLL:"Featureless Linux Library" may include an install equivalent to the file:"fake" program (and there may possibly be a package generation equivalent as well).

  The management scripts are as follows\:
    - file:"bootstrap.sh".
    - file:"bootstrap-example.sh".
    - file:"install.sh".
    - file:"package.sh".

  The file:"bootstrap.sh" script is intended to take the FLL:"Featureless Linux Library" source code and compile it into appropriate binaries on the system, particularly when the file:"fake" program is not installed.
  This is analogous to the bold:"GNU Make" program and the FLL:"Featureless Linux Library" bold:"Featureless Make" program.

  The file:"bootstrap-example.sh" script is intended to be a functional example of the command line arguments that should be used to generate, compile, and install the entire FLL:"Featureless Linux Library".

  The file:"install.sh" script is intended to install the built and compiled FLL:"Featureless Linux Library" code onto the system.
  This script very loosely follows a small amount of the logic of the standard configure scripts.

  The file:"package.sh" script is intended to convert the FLL:"Featureless Linux Library" source code from the source code repository structure into a packaged or release.
  Of particular note is that there are multiple ways to package the FLL:"Featureless Linux Library", such as each package as its own individual project, each package by level, or each package as a monolithic library.
  This script also provides management functions for ensuring the dependencies and configuration settings are accurate.

Other Readmes:
  Repository providers like bold:"Github" and bold:"Gitlab" utilize file:"README.md", file:"LICENSE", and other special files at the root project level.
  This practice is not supported by the FLL:"Featureless Linux Library" project structure and is not normally used.

  Instead, these are provided only on special branches intended exclusively to be used for the appropriate repository provider.
  These readmes and related files are intended to document the project within the scope of the repository provider and usually a particular release version.
