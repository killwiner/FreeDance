from termcolor import colored
import sys

for line in sys.stdin:
    if 'PASS' in line:
        print colored(line, 'green')
    elif 'FAIL' in line:
        print colored(line, 'red')
    else:
        print colored(line, 'white')
