
import subprocess
from random import seed
from random import random
from random import randint
seed(1)

for _ in range(100):
	value = randint(0, 10)

	print str(value)

