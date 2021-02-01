#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/adrii/talos_public_ws/src/pal_statistics/pal_statistics"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/adrii/talos_public_ws/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/adrii/talos_public_ws/install/lib/python2.7/dist-packages:/home/adrii/talos_public_ws/build/pal_statistics/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/adrii/talos_public_ws/build/pal_statistics" \
    "/usr/bin/python2" \
    "/home/adrii/talos_public_ws/src/pal_statistics/pal_statistics/setup.py" \
     \
    build --build-base "/home/adrii/talos_public_ws/build/pal_statistics" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/adrii/talos_public_ws/install" --install-scripts="/home/adrii/talos_public_ws/install/bin"
