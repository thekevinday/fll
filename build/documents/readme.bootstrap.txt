# fss-0002

Bootstrap Readme Documentation:
  The Featureless Linux Library provides a special bootstrap script in case the Featureless Make is not currently installed.

  The GNU bash scripts, called bootstrap.sh and install.sh, are provided to perform this bootstrap process.

  The syntax for bootstrap.sh is\:
    bootstrap.sh <operation> [options]
    - where operation is one of the following: 'build' or 'clean'.
    - No 'install' command is provided, all of the files to install may be found in the build/ directory after the build command is executed.
    - To install, either copy the files in the build directory to their appropriate destination or use the install.sh GNU bash script.
    - For all operations and options, get help from the bootstrap script by appending the "--help" to the script, such as: "./bootstrap.sh --help".
    - The monolithic build process is the simplest, which can be generated like the following: "./bootstrap.sh build -m monolithic".
    - When during development, consider using a work directory, such as: "./bootstrap.sh --work /tmp/work".

  The syntax for install.sh is\:
    install.sh [options]
    - This defaults to /usr/local/ paths commonly found in GNU Linux systems.
    - Accepts options for specifying specific install directory paths, such as a custom bin directory: "./install.sh --bindir /custom/program".
    - This is a simple installer and is not intended to be an all-solution.
    - For more powerful installation: manually install, use custom scripts, or use an appropriate build/install system.
    - When during development, consider using a work directory, such as: "./install.sh --work /tmp/work".
    - The --work parameter in install.sh is similar to the --prefix parameter, except that it is used for easier development scripting and also for communicating intent and has a different directory structure.
    - Note: The Featureless Make is a build system only and not an install system, this install.sh script may still be needed to install when using the Featureless Make.

  Build Example\:
    ./bootstrap.sh build

  Install Example\:
    ./install.sh

  Manual Install Example\:
    cp -vR build/includes/* /usr/include/
    cp -vR build/libaries/shared/* /usr/lib/
    cp -vR build/programs/shared/* /usr/bin/
    cp -vR build/settings/* /etc/

  Alternatively, a primitive install script is provided to help install\:
    ./install.sh

  If one of the build sub-directories, such as includes, libraries, programs, and settings, is empty or missing after a successful build, then there are no files of that type to install.

  Build Tree Structure Example (using the status_code-0.5.5 project)\:
    build/
    ├── documents
    ├── includes
    │   └── level_3
    │       └── status_code.h
    ├── libraries
    │   ├── script
    │   ├── shared
    │   │   ├── libstatus_code.so -> libstatus_code.so.0
    │   │   ├── libstatus_code.so.0 -> libstatus_code.so.0.5.5
    │   │   └── libstatus_code.so.0.5.5
    │   └── static
    │       └── libstatus_code.a
    ├── objects
    │   ├── private-status_code.o
    │   └── status_code.o
    ├── programs
    │   ├── script
    │   ├── shared
    │   │   └── status_code
    │   └── static
    │       └── status_code
    ├── settings
    └── stage
        ├── libraries_shared.built
        ├── libraries_static.built
        ├── objects_static.built
        ├── programs_shared.built
        ├── programs_static.built
        ├── skeleton.built
        ├── sources_headers.built
        ├── sources_script.built
        └── sources_settings.built


  Work Tree Structure Example at /tmp/work (using the status_code-0.5.5 project)\:
    /tmp/work/
    ├── includes
    │   └── level_3
    │       └── status_code.h
    ├── libraries
    │   ├── shared
    │   │   ├── libstatus_code.so -> libstatus_code.so.0
    │   │   ├── libstatus_code.so.0 -> libstatus_code.so.0.5.5
    │   │   └── libstatus_code.so.0.5.5
    │   └── static
    │       └── libstatus_code.a
    └── programs
        ├── shared
        │   └── status_code
        └── static
            └── status_code
