# fss-003
#
# This readme file is inteded to provide a basic introduction to the Featureless Linux Library (FLL).
#

Installation:
  The FLL provides two installation types\:
    - The management scripts.
    - The Featureless Make program.

  The management scripts provide a way to manage the source code, such as updating dependencies, constructing the souce code for release, and bootstrap compiling the system.

  The bootstrap compiling provides a way to build and compile the entire FLL project, without the Featureless Make (Fake) program.
  This bootstrap process solves the problem where if you don't already have Fake installed, then you cannot install Fake.

  The source code needs to be packaged before it can be compiled by either the bootstrap scripts or by the Fake program.

  The Fake program is not intended to be used as an installer, so the bootstrap scripts also provide an install script.
  This install script is intended to be used only by the FLL.
  Future versions of the FLL may include an install equivalent to the Fake program (and there may possibly be a package generation equivalent as well).

  The management scripts are as follows\:
    - bootstrap.sh
    - bootstrap-example.sh
    - install.sh
    - package.sh

  The bootstrap.sh script is intended to take the FLL source code and compile it into appropriate binaries on the system, particularly when the Fake program is not installed.
  This is analogous to the GNU Make program and the FLL Fake program.

  The bootstrap-example.sh script is intended to be a functional example of the command line arguments that should be used to generate, compile, and install the entire FLL.

  The install.sh script is intended to install the built and compiled FLL code onto the system. 
  This script very loosely follows a small amount of the logic of configure scripts.

  The package.sh script is intended to convert the FLL source code from the source code repository structure into a packaged or release.
  Of particular note is that there are multiple ways to package the FLL, such as each package as its own individual project, each package by level, or each package as a monolithic library.
  This script also provides management functions for ensuring the dependencies and configuration settings are accurate.
