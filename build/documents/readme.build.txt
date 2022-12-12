# fss-0002

Build Readme Documentation:
  The Featureless Make, or Fake, is a build system opposing the GNU Make build (and install) system.

  The GNU Make system is powerful, but introduces too much unecessary functionality.
  In opposition to parts of how GNU Make works but also in honor of the success of the GNU Make system, the Featureless Make system follows the following concepts\:
  - A build system is just that, a build system. Do not attempt to install, leave that to the distributor or individual installer.
  - A build system should not be trying to guess what is or is not on the system, instead, allow the distributor or individual installer to just specify what they want.
  - Provide a simple configuration design by using Featureless Settings Specification, or FSS.
  - Provide advanced functionality to provide flexibility with different system designs.
  - Userspace execution calling is expensive, attempt to avoid such overhead by providing built-in functionality where reasonably possible.
  - There should never need to be a "configure" script, like GNU Autoconf.

  The Fake is designed to specifically build the FLL and encourages the use of Fake to build FLL.

  The Fake provides two main build operations\:
  - build: a lean purely FSS based build process, designed around specific but simple project designs (explicitly used by FLL).
  - make: a more powerful build process design to be more akin to GNU Make.

  The Fake supports custom development environments using the "work" directory concept, such as "fake build -w /tmp/work".
  The "work" directory structure is identical to the build directory structure.

  Build Example, using "build"\:
    fake build

  Build Example, using "make"\:
    fake

  Build Example, explicitly using "make"\:
    fake make

  Build Tree Structure Example (using the FLL status_code-0.7.0 project)\:
    build/
    ├── documents
    ├── includes
    │   └── program
    │       └── status_code
    │           ├── fss
    │           │   ├── common.h
    │           │   └── status_code.h
    │           └── main
    │               ├── common.h
    │               ├── common-print.h
    │               ├── print.h
    │               └── status_code.h
    ├── libraries
    │   ├── script
    │   ├── shared
    │   │   ├── libstatus_code.so -> libstatus_code.so.0
    │   │   ├── libstatus_code.so.0 -> libstatus_code.so.0.7
    │   │   ├── libstatus_code.so.0.7 -> libstatus_code.so.0.7.0
    │   │   └── libstatus_code.so.0.7.0
    │   └── static
    │       └── libstatus_code.a
    ├── objects
    │   ├── config.o
    │   ├── fss
    │   │   ├── common.o
    │   │   └── status_code.o
    │   ├── main
    │   │   ├── common.o
    │   │   ├── common-print.o
    │   │   ├── print.o
    │   │   ├── private-status_code.o
    │   │   └── status_code.o
    │   ├── script
    │   ├── shared
    │   └── static
    ├── programs
    │   ├── script
    │   ├── shared
    │   │   ├── fss_status_code
    │   │   └── status_code
    │   └── static
    │       ├── fss_status_code
    │       └── status_code
    ├── settings
    └── stage
        ├── library_shared-settings.built
        ├── library_static-settings.built
        ├── objects_static-settings.built
        ├── program_shared-settings.fss.built
        ├── program_shared-settings.main.built
        ├── skeleton-settings.built
        ├── skeleton-settings.fss.built
        ├── skeleton-settings.main.built
        ├── sources_headers-settings.built
        ├── sources_script-settings.built
        ├── sources_script-settings.fss.built
        ├── sources_script-settings.main.built
        ├── sources_settings-settings.built
        ├── sources_settings-settings.fss.built
        └── sources_settings-settings.main.built

  See: FLL Fake project documents for further details on how to use the Fake system.
  See: FLL Fake project specifications for how to configure the build FSS files and make FSS files.
  See: readme.bootstrap.txt for notes on installing.
