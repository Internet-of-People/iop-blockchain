from distutils.core import setup
setup(name='IoPspendfrom',
      version='1.0',
      description='Command-line utility for IoP "coin control"',
      author='Gavin Andresen',
      author_email='gavin@IoPfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
