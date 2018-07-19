import sys


types = ['int', 'long int', 'short int', 'short', 'long', 'float', 'double', 'int*', 'float*' ,'double*']

class interpreter(object):

    def __init__(self):
        pass


    def run(self):
        self.parse_statement()

    def parse_statement(self):
