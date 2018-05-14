import numpy as np
import matplotlib.pyplot as plt

archivo = np.genfromtxt('potencial.txt')
archivo2 = np.genfromtxt('campoE_x.txt')
archivo3 = np.genfromtxt('campoE_y.txt')
x = np.linspace(0,511,512)
y = np.linspace(0,511,512)

plt.subplot(1,2,1)
plt.imshow(archivo)
plt.colorbar()
plt.subplot(1,2,2)
plt.streamplot(x,y,archivo2,archivo3)
plt.xlim(xmax=511)
plt.xlim(xmin=0)
plt.ylim(ymax=511)
plt.ylim(ymin=0)
plt.title('potencial y campo electrico')
plt.savefig('placas.pdf')


