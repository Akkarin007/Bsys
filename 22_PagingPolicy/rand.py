import subprocess
from random import seed
from random import random
seed(1)
s = "--addresses="
for _ in range(10):
	value = randint(0, 10)
	s = value + ","


subprocess.call(["python ./paging-policy.py", s, "--policy=OPT ","--cachesize=5", "-c"])
