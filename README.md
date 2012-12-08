Act-Out! Game Library Project
==============

# Overview #

[![Build Status](https://secure.travis-ci.org/team-djikstra/Act-Out-gamelib.png?branch=master)](https://travis-ci.org/team-djikstra/Act-Out-gamelib)

Want to know the current status of the project? Click on the link above to 
visit our Travis-CI page to see the status of past builds and what versions
build and test cleanly.

Note: this project has gone through 2 renames, the first name was to more correctly 
give the intent of the project, the second was to correct a minor spelling error 
corrected a minor spelling error in the name. The links to the Travis builds under 
the old names are at the following locations:

https://travis-ci.org/team-djikstra/Nu-KleaAr-game
and
https://travis-ci.org/team-djikstra/Act-Out-gamelib

Want to see more detailed documentation?

1. See the [Wiki][] for high level design and discussion documentation.
2. You can [build the Api documentation](#building-the-api-documentation) 
   from the source code (currently not available online. Sorry).

## Project Goals ##

The goal of this project is to provide a generic framework for making simple
turn based strategy games. 

## Disclaimer ##

The focus is to provide support for the _logic_ of such games. As such, the 
library does not provide the kind of facilities that you might expect to find
in a game _engine_, such as graphics, sound, input control, tools for building
clients and servers. That is because this is not a game _engine_, but only a 
game _library_. This is the kind of thing that clients and services can be
implemented in terms of, but we consider this to be a separate concern. In the
future, we will probably create separate projects to provide more engine like
client-servery type stuff.

# Building from the Source #

Building the project should be straightforward, as we have no external
dependencies except for the STL, and this ships with most c++ compilers.
At minimum, you will need to have [gnumake][] v3.81 or higher and [g++][] 4.4.6 
or higher installed. Older versions may work, but are unsupported and untested.

To build, clone from the git repositiory on GitHub, or download a source archive.

```console
$ git clone git://github.com/team-djikstra/Act-Out-gamelib.git
$ cd Act-Out-gamelib
Act-Out-gamelib$ make
```

The resulting executables will be placed in the `bin` directory.

## Disclaimer ##

The source will probably build and run under other compilers than [g++][], 
since we are not using any non-standard libraries or extensions, but we have
not been tested the build on other compilers.

Likewise, the code should compile and run on other operating systems for the 
same reasons as outlinede above, but we have only actually tested on Linux
operating systems. (Specifically [centos][] and [Linux Mint][mint])

## Running The Validation Suites ##

Once the project has been built, you can run various validation suites against
the codebase, depending on what tools you have installed. If any of the
validation tools are missing, a warning will be issued and that suite will be
skipped.

To run the unit tests, simply type:

```console
$ make test
```

To run all available validation suites, type:

```console
$ make check
```

Currently, we are using the following validation tools:

1. [cppunit][]
2. [cppcheck][]
3. [valgrind][]
4. [cppncss][]

## Building the Api Documentation ##

All of the source code is documented with [doxygen][] comments, and the
documentation can be extracted by running the Doxygen tool. To build the 
pdf documentation, you will need to have a fairly complete LaTeX installation.
See the [doxygen][] homepage for details on what is required. Currently, 
there are three documentation sets that can be generated.

1. html - Separate html documentation sets will be built for the production
   source code, and the test code respectively.
2. latex - Separate pdf documents will be built for the production source code
   and the test code respectively. Note: this target depends on the html, and 
   will build the html documentation set if it hasn't been built already.
3. all-doc - Generates combined documentation sets for the production and test
   code in a single bundle. This target generates both html and pdf format.

To build any of the above documentation sets, simply type:

```console
$ make html
```
or
```console
$ make latex
```
or
```console
$ make all-doc
```

The resulting documentation sets will be placed under the 'doc' directory. Pdf
documentation will also be symlinked at the top level.

# Working with the Source Code #

If you build from a git clone of the source repository, please note a git
pre-commit hook will be installed the first time `make` is run. If you do not
change the source, this will not affect you at all. However, if you want to
make changes to the codebase, either as a primary project author, or on your
own personal fork, you should be aware that the precommit hook will check to
make sure that each changed file has the licence preamble installed (the 
project is licenced under LGPLv3), and that `make check` has been run. 

If either of these conditions is not met, the commit will be rejected. Since
the precommit hook is only installed on the local repo, this mechanism can
easily be circumvented, but we do not recommend that you do so.

The main purpose of this mechanism is not to enforce policy, but merely to
prevent accidental violations. If you want to violate policy, you will have
to do so on purpose by passing the `--no-verify` flag to `git commit`.

[gnumake]: http://www.gnu.org/software/make/
[g++]: http://gcc.gnu.org/
[centos]: http://www.centos.org/
[mint]: http://linuxmint.com/
[cppunit]: http://sourceforge.net/apps/mediawiki/cppunit/
[cppcheck]: http://cppcheck.sourceforge.net/
[valgrind]: http://valgrind.org/
[cppncss]: http://cppncss.sourceforge.net/
[doxygen]: http://www.stack.nl/~dimitri/doxygen/
[wiki]: /team-djikstra/Act-Out-gamelib/wiki
