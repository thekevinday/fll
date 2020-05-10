# fss-003
#
# This readme file is inteded to provide a basic introduction to the Featureless Linux Library (FLL).
#

Installation:
  The FLL provides two installation types\:
    - The bootstrap scripts.
    - The Featureless Make program.

  The bootstrap scripts provide a way to build and compile the entire FLL project, without the Fake program.
  This is done because the Fake program is actually part of the FLL project.
  This solves the problem that if you don't already have Fake installed, then you cannot install Fake.

  The bootstrap scripts also provide a way to convert the source code of the FLL into packages for compiling and/or releasing.
  The source code needs to be packaged before it can be compiled by either the bootstrap scripts or by the Fake program.

  The Fake program is not intended to be used as an installer, so the bootstrap scripts also provide an install script.
  This install script is intended to be used only by the FLL.
  Future versions of the FLL may include an install equivalent to the Fake program (and there may possibly be a package generation equivalent as well).

  The bootstrap scripts are as follows\:
    - bootstrap.sh
    - generate.sh
    - install.sh
    - package.sh

  The boostrap.sh script is intended to be a functional example of the command line arguments that should be used to generate, compile, and install the entire FLL.

  The generate.sh script is intended to take the FLL source code and compile it into appropriate binaries on the system, particularly when the Fake program is not installed.
  This is analogous to the GNU Make program and the FLL Fake progam.

  The install.sh script is intended to install the FLL onto the system. 
  This script very loosely follows a small amount of the logic of configure scripts.

  The package.sh script is intended to convert the FLL source code from the source code repository structure into a packaged structure.
  This should be used regadless of whether or not Fake or the generate.sh is used to build/compile the FLL (or any of its parts).
  Of particular note is that there are multiple ways to package the FLL, such as each package as its own program, each package by level, or each package as a monolithic library.

