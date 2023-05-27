import numpy as np  ##/*ctrl+p luego -> Python: Select Interpreter -> Python 3.10.6
import os

np.random.seed(1337)

dir_path = os.path.dirname(os.path.realpath(__file__))
final_path = os.path.join(dir_path, 'inputs')
if not os.path.exists(final_path):
   os.makedirs(final_path)


for pow in range (1,3): #[1,2)
  for x in range(2,11): #[2,10)
    n = x * (10**pow)
    f = open(final_path + "/input_" + str(n), "w")
    print(final_path + "/input_" + str(n)) ####debug####
    
    R = np.random.randint(1, 10001)
    W = np.random.randint(1, n)
    U = np.random.randint(1, 11)
    V = np.random.randint(U, 11)
    f.write(str(n) + ' ' + str(R) + ' ' + str(W) + ' ' + str(U) + ' ' + str(V) + "\n")

    oficinas = set()
    while len(oficinas) < n:
      #x = np.random.randint(-10000, 10000)   
      #y = np.random.randint(-10000, 10000)
      oficinas.add(tuple(np.random.randint(-10000, 10001, size=2))) #tupla (x,y) con -10.000 <= x, y <= 10.000
    
    for o in oficinas:
      x, y = o
      f.write(str(x) + ' ' + str(y) + '\n')
    f.close()