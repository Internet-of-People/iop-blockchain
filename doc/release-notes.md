IoP Core version 0.13.x is now available from:

  <https://IoP.org/bin/IoP-core-0.13.x/>

This is a new major version release, including new features, various bugfixes
and performance improvements, as well as updated translations.

Please report bugs using the issue tracker at github:

  <https://github.com/internet-of-people/iop-blockchain/issues>


Compatibility
==============

We do not have time nor resources to provide support for an OS that is
end-of-life. From 0.13.0 on, Windows XP is no longer supported. Users are
suggested to upgrade to a newer verion of Windows, or install an alternative OS
that is supported.

No attempt is made to prevent installing or running the software on Windows XP,
you can still do so at your own risk, but do not expect it to work: do not
report issues about Windows XP to the issue tracker.

Notable changes
===============

Example item
--------------

Low-level RPC changes
---------------------

- `importprunedfunds` only accepts two required arguments. Some versions accept
  an optional third arg, which was always ignored. Make sure to never pass more
  than two arguments.


0.13.1 Change log
=================

Detailed release notes follow. This overview includes changes that affect
behavior, not code moves, refactors and string updates. For convenience in locating
the code changes and accompanying discussion, both the pull request and
git merge commit are mentioned.

    ... fill in here

Credits
=======

Thanks to everyone who directly contributed to this release:

    ... fill in here

As well as everyone that helped translating on [Transifex](https://www.transifex.com/projects/p/bitcoin/).
