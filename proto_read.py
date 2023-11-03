import numpy as np

imax = 100
jmax = 100

mach = 0.0  
alpha = 0.0 
reyn = 0.0  
time = 0.0  

x = np.zeros((imax, jmax))
y = np.zeros((imax, jmax))
q = np.zeros((imax, jmax, 4))

with open('./anduct.B.x', 'rb') as file_x:
    ni, nj = np.fromfile(file_x, dtype=np.int32, count=2)
    x = np.fromfile(file_x, dtype=np.float32, count=ni*nj)
    y = np.fromfile(file_x, dtype=np.float32, count=ni*nj)

print(x, y, q)
