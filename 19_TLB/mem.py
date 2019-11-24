import subprocess

for x in xrange(0, 3000,50):

 	subprocess.call(["./tlb_mes", str(x), "100"])

