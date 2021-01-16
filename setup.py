#!/usr/bin/env python3

"""
setup.py file for Fir1
"""

from setuptools import setup
from setuptools import Extension
import os
import numpy
from sys import platform

def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()

if platform == "linux" or platform == "linux2" or platform == "darwin":
	fir1_module = Extension('_fir1',
				sources=['fir1.i','Fir1.cpp'],
				extra_compile_args=['-std=c++11','-O3'],
                                swig_opts=['-c++','-py3'],
			        include_dirs=[numpy.get_include()],
				)
elif platform == "win32":
	fir1_module = Extension('_fir1',
			    sources=['fir1.i','Fir1.cpp'],
			    extra_compile_args=['/DWIN32_LEAN_AND_MEAN'],
                            swig_opts=['-c++','-py3'],
			    include_dirs=[numpy.get_include()],
	                       )

						   
setup (name = 'fir1',
       version = '1.5.0.0',
       author      = "Bernd Porr",
       author_email = "mail@berndporr.me.uk",
       url = "https://github.com/berndporr/fir1",
       description = 'Efficient FIR realtime filter',
       long_description=read('README_py'),
       ext_modules = [fir1_module],
       py_modules = ["fir1"],
       license='MIT',
       install_requires=[
          'numpy',
       ],
       classifiers=[
          'Intended Audience :: Developers',
          'Operating System :: POSIX',
	  'Operating System :: Microsoft :: Windows',
          'Programming Language :: Python :: 3',
          ]
      )
