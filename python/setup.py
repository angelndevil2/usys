from distutils.core import setup, Extension

module1 = Extension('usys',
                    sources=['kernel_conf_wrapper.cc'])

setup (name='usys',
       version='0.1',
       description='This is a demo package',
       ext_modules=[module1])

