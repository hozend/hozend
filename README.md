# $Id: README.md,v 0.1 2014/02/13 23:30:46 proff Exp $

Project Hozend


======

# Trying to recreate rubberhose for the 21st century. Original README.md is below (to Be updated)\

# Removed e-mails (iq.org + rubberhose.org) due to them being dead.

Original (circa 2000)

       RUBBERHOSE 0.8.3
                        ----------------

This is an alpha snap shot. Intended only for testing and
development. DO NOT TRUST THIS CODE. It wants to run away with your
prom date's underpants when you least expect it. 


Compile under linux. The NetBSD and FreeBSD kernel modules are out of
sync with the rest of the code. This will be rectified as soon
as the kernel interface has completely stabilised.

You may want to install OpenSSL.  Rubberhose will detect it on
configure and add the (usually faster) OpenSSL ciphers to its
collection)

Configure and compile:
$ ./configure
$ make

If you have docbook utilities installed you may like to
rebuild the Rubberhose documentation:

$ cd doc; make doc

Run the self-test suite. There are several hundred tests. While
this is an optional step, given stated aims of the code, it's
probably foolhardy not to.
$ make check

Become root.

Install binaries etc:
# make install
Install the maru and kue devices:
# hose_makedevs

Install the kue and maru kernel devices into the running kernel:
# hose_modload

Revert back to the user.

You can try 'hose list commands' for a list of client commands and 'hose
help [command]' for help on a specific command.

(Optionally) examine cipher speeds:
$ hose speeds

The default options to the following commands result in a small
(few Mb) test extent.

Create a new keymap. The keymap is is a list of keys, salts and
various other meta data used to describe an extent (file or
partition). It's a little like a pgp private key ring, except
that it's one to one bonded with a particular extent:
$ hose newkeymap

Create an extent. An extent is a file container used for block
storage. You can probably also use a disk partition, although
this hasn't been tested recently:
$ hose newextent

Create an aspect. An aspect is a `view' of some or all of blocks in an
extent. Under some of the remapping schemes, an extent may have multiple
aspects. Some of the remapping schemes are crypto-deniable. You may
need to move the mouse about or type on the keyboard to gather entropy
for key generation. Aspect 0 is created by default.
$ hose newaspect

You now test speed of the full crypto path with your chosen
algorithms:
$ hose speeds -e

Become root again and start up the hosed daemon:
# hosed

Tell hosed to attach itself to your newly created extent file:
# hose attachextent

Tell hosed to key aspect 0 (default). This "primes" the aspect.
# hose keyaspect

Tell hosed to bind aspect 0 (default) to a disk device
# hose bindaspect
# For crypto deniability reasons, the maru device assigned is
# random. In this example, we presume /dev/maru4

Aspect 0 should now appear as one of the /dev/maru* devices. We will
now create a file-system on it. It's important for efficiency to have
the file-system block size the same as the crypto block size (defaults
to 2048 bytes, see newkeymap -b), so we will tell mke2fs to use 2048
byte blocks.
# mke2fs -b 2048 /dev/maru4

Now, mount it!
# mount /dev/maru4 /mnt

Have a look inside:
# ls -la /mnt

Try copying in /bin/sh:
# cp /bin/sh /mnt

Unmount and unbind, dekey
# umount /mnt
# hose unbindaspect
# hose dekeyaspect
# hose detachextent

# hose_modunload

man pages (quite brief at the moment) and other documentation are
in doc.

Happy Rubberhos'in!

-Julian Assange 
 Ralf-P. Weinmann 