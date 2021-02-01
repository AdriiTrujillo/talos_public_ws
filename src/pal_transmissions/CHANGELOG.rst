^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Changelog for package pal_transmissions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

0.2.3 (2019-05-29)
------------------

0.2.2 (2016-11-09)
------------------
* Talos head transmission working
* Fixed equations for absolute encoder of half differential encoder
* Managed to make the head of talos work
* Fixing head differential
* Fixed typo half differential transmission loader
* Contributors: Hilario Tome

0.2.1 (2016-10-16)
------------------
* Fixed API compatibility
* Contributors: Hilario Tome

0.2.0 (2016-04-05)
------------------

0.1.1 (2015-10-08)
------------------
* Add missing return value
* Contributors: Adolfo Rodriguez Tsouroukdissian

0.1.0 (2015-08-06)
------------------
* Add custom REEM/REEM-C head transmission
  Transmission involving both head joints. Works like two independent reducers,
  except that the tilt joint's position limits depend on the pan joint's actual
  position.
  Implementation includes new transmission class, URDF loader plugin and test
  suite.
* Contributors: Adolfo Rodriguez Tsouroukdissian
