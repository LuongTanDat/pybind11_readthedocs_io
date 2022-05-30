import os
import sys

from distutils.core import setup, Extension
from distutils import sysconfig

cpp_args = ['-std=c++2a']

ext_modules = [
    Extension(
        'warp',
        ['op.cpp'],
        include_dirs=['pybind11/include'],
        language='c++',
        extra_compile_args=cpp_args,
    ),
]

setup(
    name='warp',
    version='0.0.1',
    author='Cliburn Chan',
    author_email='cliburn.chan@duke.edu',
    description='Example',
    ext_modules=ext_modules,
)
