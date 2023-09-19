import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

KT = 50.2
KV = 0.3
KS = 0.5
MAX_ERROR_INICIAL = 1

DELTA_LIMITE_SUPERIOR = 1.2
DELTA_LIMITE_INFERIOR = 0.7

PPF_INICIO = 1
PPF_FIN = 0.17

T = 0.01
m = 3
n = 9
l = 21
c = 2.1
fin = 10
t = np.arange(0, fin, T)

qd1 = [-1, -1, -1]
qd2 = [1, -1, -1]
qd3 = [1, 1, -1]
qd4 = [-1, 1, -1]
qd5 = [-1, -1, 1]
qd6 = [1, -1, 1]
qd7 = [1, 1, 1]
qd8 = [-1, 1, 1]
qd9 = [0, 0, 0]

qd = np.vstack((qd1, qd2, qd3, qd4, qd5, qd6, qd7, qd8, qd9)).T

E1 = [0, 3]
E2 = [0, 4]
E3 = [0, 8]
E4 = [1, 2]
E5 = [1, 5]
E6 = [1, 8]
E7 = [2, 3]
E8 = [2, 6]
E9 = [2, 8]
E10 = [3, 4]
E11 = [3, 7]
E12 = [3, 8]
E13 = [4, 5]
E14 = [4, 7]
E15 = [4, 8]
E16 = [5, 6]
E17 = [5, 7]
E18 = [5, 8]
E19 = [6, 7]
E20 = [6, 8]
E21 = [7, 8]

E = np.vstack((E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12, E13, E14, E15, E16, E17, E18, E19, E20, E21))

q = np.array([[1.0579+1, 1.2313+1, 0.0123],
              [1.5815+1, 1.3371+1, 0.1681],
              [2.0201+1, 3.3460+1, 0.2113],
              [0.1792+1, 2.7710+1, 0.5225],
              [0.8085+1, 0.8848+1, 2.2038],
              [2.7998+1, 1.3196+1, 2.0627],
              [2.4380+1, 3.1536+1, 2.3853],
              [0.3991+1, 3.1141+1, 2.1780],
              [1.4800, 2.3256, 1.2323]])

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

for i in range(n):
    ax.scatter(q[i*m-2], q[i*m-1], q[i*m], marker='x', linewidth=2, s=15)

for i in range(l):
    d = np.linalg.norm(qd[:, E[i, 0]] - qd[:, E[i, 1]])
    qt = q[E[i, 0]*m:(E[i, 0]+1)*m] - q[E[i, 1]*m:(E[i, 1]+1)*m]
    e = np.linalg.norm(qt) - d
    varphi = e / ppf[i]
    Ez = 1/2 * np.log((DELTA_LIMITE_SUPERIOR*varphi + DELTA_LIMITE_INFERIOR*DELTA_LIMITE_SUPERIOR)/(DELTA_LIMITE_SUPERIOR*DELTA_LIMITE_INFERIOR-DELTA_LIMITE_INFERIOR*varphi))
    ax.plot([q[E[i, 0]*m-2], q[E[i, 1]*m-2]], [q[E[i, 0]*m-1], q[E[i, 1]*m-1]], [q[E[i, 0]*m], q[E[i, 1]*m]], 'k--', linewidth=0.5)
    
ppf = (PPF_INICIO-PPF_FIN)*np.exp(-c*t)+PPF_FIN
ppfp = -c*(PPF_INICIO-PPF_FIN)*np.exp(-c*t)

V = 3.2*np.random.rand(m*n, 1)

v0 = np.vstack((2*np.sin(t), 2*np.cos(t), np.ones(len(t)))).T
w0 = np.zeros((len(t), 3))

X = np.hstack((q, V))

for i in range(len(t)-1):
    qt = np.zeros((l, m))
    e = np.zeros(l)
    Z = np.zeros(l)
    varphi = np.zeros(l)
    Ez = np.zeros(l)
    rhop = np.zeros((l, l))
    temp = np.zeros((l, l))
    vd = np.zeros((m*n, 1))
    Vf = np.zeros((m*n, 1))
    Vfp = np.zeros((m*n, 1))
    Vfp2 = np.zeros((m*n, 1))
    S = np.zeros((m*n, 1))
    
    for k in range(l):
        qt[k] = q[E[k, 0]*m:(E[k, 0]+1)*m, i] - q[E[k, 1]*m:(E[k, 1]+1)*m, i]
        e[k] = np.linalg.norm(qt[k]) - d
        Z[k] = e[k]*(e[k]+2*d)
        varphi[k] = e[k]/ppf[i]
        Ez[k] = 1/2 * np.log((DELTA_LIMITE_SUPERIOR*varphi[k] + DELTA_LIMITE_INFERIOR*DELTA_LIMITE_SUPERIOR)/(DELTA_LIMITE_SUPERIOR*DELTA_LIMITE_INFERIOR-DELTA_LIMITE_INFERIOR*varphi[k]))
    
    qdin = qdinVector(E, qt, 9, l, m)
    
    for k in range(n):
        vd[k*m:(k+1)*m] = v0[i] + np.cross(w0[i], qdin[k*m:(k+1)*m])
    
    R = matrizRCubo9AgentWithLeader(q[:, i], m)
    
    rho = np.eye(l)*((1/(2*ppf[i]))*(1/(varphi+DELTA_LIMITE_INFERIOR) - 1/(varphi-DELTA_LIMITE_SUPERIOR)))
    
    if i == 0:
        rhop = rho/T
        temp = rho
    else:
        rhop = (rho - temp)/T
        temp = rho
    
    Vf[:, i] = -KV*R.T@rho@Ez + vd[:, 0]
    Zp = 2*R@V[:, i]
    Rp = matrizRCubo9AgentWithLeader(V[:, i], m)
    S = V[:, i] - Vf[:, i]
    tanH = -KT*np.tanh(S)
    Ezp = rho@(Zp-ppfp[i]*varphi)
    Vfp2[:, i] = -KV*(Rp.T@rho@Ez + R.T@rhop@Ez + R.T@rho@Ezp)
    
    if i == 0:
        Vfp[:, i] = Vf[:, i]/T
    else:
        Vfp[:, i] = (Vf[:, i] - Vf[:, i-1])/T
    
    u = -KS*S - R.T@rho@Ez + Vfp[:, i] + tanH
    X[i+1] = odeint(systemDoubleIntegratorWithDisturbance, X[i], [t[i], t[i+1]], args=(u[:, 0], m, n))[-1]
    q[i+1] = X[i+1, :m*n]
    V[i+1] = X[i+1, m*n:]
    
fig = plt.figure()
ax = fig.add_subplot(111)

for i in range(l):
    ax.plot(t[:-1], e[i], linewidth=2)
    
ax.plot(t[:-1], DELTA_LIMITE_SUPERIOR*ppf[:-1], 'r--', linewidth=2)
ax.plot(t[:-1], -DELTA_LIMITE_INFERIOR*ppf[:-1], 'r--', linewidth=2)
ax.grid(True)
ax.set_title('Errores de distancia entre agentes')
ax.set_xlabel('Segundos')
ax.set_ylabel('Distancia')

plt.show()