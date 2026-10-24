from setuptools import find_packages
from setuptools import setup

setup(
    name='annin_ar4_driver',
    version='3.0.0',
    packages=find_packages(
        include=('annin_ar4_driver', 'annin_ar4_driver.*')),
)
