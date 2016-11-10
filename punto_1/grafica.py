import numpy as np
import matplotlib.pyplot as plt

U = np.loadtxt("potential.dat")
Ex = np.loadtxt("FieldEx.dat")
Ey = np.loadtxt("FieldEy.dat")

X, Y = np.meshgrid(np.linspace(0,5,250), 
                   np.linspace(0,5,250) )
plt.xlabel(r"$x$")
plt.ylabel(r"$y$")
plt.streamplot( X, Y, Ex, Ey, color="k" )
plt.imshow(U,extent=[0,5,0,5])
plt.colorbar()
plt.savefig("placas.pdf")
