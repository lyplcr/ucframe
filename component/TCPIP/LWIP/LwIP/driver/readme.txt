This directory contains netif drivers for lwIP. These drivers are *not*
always updated when something changes in lwIP, meaning they might or
might not work with a version of lwIP different than they were written
for.

Therefore, the directory structure indicates the version of lwIP used
when the drivers were written. If there is any other versioning which
is of interest (e.g. for which OS or OS version), there should be an
extra readme file in the driver directory.


Usually, driver should continue to work without changes throughout
different minor releases in one major release (e.g. a driver written
for 1.3.0 should work with 1.3.1). Therefore, there are only directories
for major releases.