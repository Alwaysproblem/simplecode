from subprocess import Popen, PIPE
import sys
import os

a = Popen(['powershell.exe', 'ls'], stdout=PIPE, encoding=sys.stdout.encoding)

b = a.stdout.readlines()
a.communicate()

print(''.join(b))
