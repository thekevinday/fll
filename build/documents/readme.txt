# fss-0002

Readme Documentation:
  The Featureless Linux Library, or FLL, is a set of projects designed to be used for Linux programming.

  The FLL is design around the following concepts\:
  - API designed around communicating to the programmer and maintaining unchanging consistency.
  - Hacker friendly, promote changing the project via its designed methodologies, implementations, standards, practices, and licenses.
  - Add freedom back to computing, via the LGPL license, because a library is a library.
  - A standard is not a true standard if it is not freely available and cannot be freely used or followed.
  - Avoid the "Feature" trap where projects keep adding things.
  - Provide an explicit versioning system that is more than a number, it communicates the status in a very simple manner.
  - Continue mantaining major versions, a project should be able to last 20, 30, or even 60 years without breaking changes.
  - Follow the KISS, Keep It Simple Stupid, principles.
  - Can be broken up into individual projects, and then further fine-tuned via custom define macros, so that only what is needed for specific situations need be used.

  The FLL versioning system has three parts: major.minor.micro.
  - The Major is the primary API specification, changes to this number represent massive breaking changes and for all intents and purposes is a different project.
  - The Minor represents potential breaking changes, Stable status and Development Status (whereas even numbers represent stable and odd numbers represent development).
  - The Micro represents bugfixes and security fixes, these should never introduce API breaking changes nor new functionality.

  Development releases (as specified by Minor version part) may introduce breaking changes and new functionality.
  Stable releases (as specified by the Minor version part) may not introduce breaking change, unless forced by some security or other difficult situation, and must not add new functionality.

  The FLL project is broken up into 3 different levels: level_0, level_1, and level_2.
  A third pseudo-level also exists for common programs built using this project, called level_3.

  With an exception of a few projects within level_0, each level should only depend on a project from a lower level.
  Therefore, a level_1 project can only depend on level_0 projects and a level_2 project can depend on only level_0 and level_1 projects.
  This does not technically apply to the pseudo-level, level_3, projects, but the pattern is generally followed.

  A few projects in level_0 are essentially required by everything and are depended on by virtually all projects, regardless of the level.
  These level_0 projects are\:
  - f_type: provides core typedef, #define, and similar structures for the entire set of FLL projects.
  - f_status: provides status codes and other status codes to be used by the entire set of FLL projects.
  - f_memory: provides common memory allocation/deallocation to be used by the entire set of FLL projects.
  - f_type_array: provides an extension on f_type that requires linking to f_memory to be used by the entire set of FLL projects.
  - f_string: provides common string management to be used by the entire set of the FLL projects.
  - f_utf: provides common UTF-8 related string management to be used by the entire set of the FLL projects.

  The above projects should be installed first, and in the provided order (f_type, then f_status, then f_memory, then f_type_array, then f_string, and finally f_utf).
  No other level_0 project should depend on another and can be installed in any order.

  To facilitate building of this project, two different build systems are provided\:
  - The bootstrap, via the bootstrap.sh script.
  - The Featureless Make, which is a level_3 project provided by FLL.

  An example bootstrap script is provided (build/scripts/bootstrap-example.sh) is provided for to show how to build the FLL directly from source.
  Use it as an example or explicitly call it (such as: "bash build/scripts/bootstrap-example.sh monolithic 0.5.5").

  See: dependencies for specific dependencies of this project.
  See: readme.bootstrap for bootstrap compiling (or just regular compiling) any part of the FLL and notes on installing.
  See: readme.build for Featureless Make compiling and notes on installing.
