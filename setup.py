#python setup.py build
#python setup.py install

from distutils.core import setup, Extension

sscmodule = Extension('ssc',
                depends = ['ScreenCapture.h'],
                extra_objects = ['/Users/sameriksson/store/xcode/PySamsScreenCapture/libSamScreenCapture.a'],
                      #extra_link_args=['-static'],
                      #include_dirs = ['/Users/sameriksson/store/xcode/PySamsScreenCapture'],
                      #libraries = ['libSamScreenCapture'],
                      #library_dirs = ['/Users/sameriksson/store/xcode/PySamsScreenCapture'],
                sources = ['samsscreencapture.c'])

setup (name = 'ssc',
       version = '1.0',
       description = 'Sams Screen Capture',
       ext_modules = [sscmodule])
