import numpy as np
import matplotlib.pyplot as plt

archivo = np.genfromtxt('Runge-Kutta.txt')
t = archivo[:,0]
q_1 = archivo[:,1]
p_1 = archivo[:,2]
q_2 = archivo[:,3]
p_2 = archivo[:,4]

plt.plot(p_2,q_2,color = 'b')
plt.xlabel('p_2')
plt.ylabel('q_2')
plt.title('Caos')
plt.savefig('caos.pdf')
