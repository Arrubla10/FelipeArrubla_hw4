import numpy as np
import matplotlib.pyplot as plt
import subprocess

fig = plt.figure(figsize=(10,7))

for i in range(400):
    fj = np.loadtxt( "results{}.dat".format(i) )
    xj = fj[:,0]
    yj = fj[:,1]
    
    plt.ylim([-1,1])
    plt.xlabel(r"$x$")
    plt.ylabel(r"$u(x)$")
    plt.plot( xj, yj, 'k' )
    plt.savefig( "{}.png".format( i ) )
    plt.clf()

subprocess.call(['ffmpeg', '-i', '%d.png', 'output.avi'])
subprocess.call(['ffmpeg', '-i', 'output.avi', '-t', '100', 'cuerda.gif']) 
