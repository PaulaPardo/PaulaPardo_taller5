import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

fig = plt.figure()

archivo = np.genfromtxt("cuerda.txt")
x= archivo[:,0]
u1= archivo[:,1]
u2= archivo[:,2]
u3= archivo[:,3]
u4= archivo[:,4]
u5= archivo[:,5]
u6= archivo[:,6]
u7= archivo[:,7]
u8= archivo[:,8]
u9= archivo[:,9]
u10= archivo[:,10]


ims= []
for i in range(1,10):
    im = plt.plot(x,archivo[:,i], color= 'b')
    plt.xlabel('x')
    plt.ylabel('u(x,t)')
    ims.append(im)

ani = animation.ArtistAnimation(fig, ims, interval=50, blit=True,
                                repeat_delay=100)

ani.save('cuerda.gif')
