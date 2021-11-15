#!/usr/bin/env python
# coding: utf-8

# In[1]:


import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


# In[2]:


step = pd.read_csv("./step.txt", sep=' ', decimal=',', header=None, names=["Step", "Tseq", "Tpar", "Tpar_ff"])
step = step.apply(pd.to_numeric)
dimension = pd.read_csv("./dimension.txt", sep=' ', decimal=',', header=None, names=["Dimension", "Tseq", "Tpar", "Tpar_ff"])
dimension = dimension.apply(pd.to_numeric)
time = pd.read_csv("./time.txt", sep=' ', decimal=',', header=None, names=["Parallel_degree", "Tseq", "Tpar", "Tpar_ff"])
time = time.apply(pd.to_numeric)

# In[3]:


#step


# In[4]:


#dimension


# In[5]:


time["sp"] = time["Tseq"]/time["Tpar"]
time["sp_ff"] = time["Tseq"]/time["Tpar_ff"]
time["serial_fraction"] = (time["Parallel_degree"]/(time["Parallel_degree"]-1))*(1-(1/time["sp"]))
time["serial_fraction_ff"] = (time["Parallel_degree"]/(time["Parallel_degree"]-1))*(1-(1/time["sp_ff"]))
time.replace([np.inf, -np.inf], 1, inplace=True)
time["non_serial"] = 1-time["serial_fraction"]
time["non_serial_ff"] = 1-time["serial_fraction_ff"]


# In[6]:


#time


# In[7]:

plt.clf()
plt.title("Average time per step")
plt.grid()
plt.xticks(range(0,101,10))
plt.xlabel("Number of steps")
plt.ylabel("Time (ms)")
plt.plot(step["Step"], step["Tseq"]/1000, 'o-', color="seagreen", label="Tseq")
plt.plot(step["Step"], step["Tpar"]/1000, 'o-', color="royalblue", label="Tpar")
plt.plot(step["Step"], step["Tpar_ff"]/1000, 'o-', color="orange", label="Tpar_ff")
plt.legend()
plt.savefig('./plot/steps.png', bbox_inches = "tight")
#plt.show()


# In[8]:

plt.clf()
plt.title("Total time per square dimension")
plt.grid()
plt.xticks(range(0,3000,250))
plt.xlabel("Dimension")
plt.ylabel("Time (ms)")
plt.plot(dimension["Dimension"], dimension["Tseq"]/1000, 'o-', color="seagreen", label="Tseq")
plt.plot(dimension["Dimension"], dimension["Tpar"]/1000, 'o-', color="royalblue", label="Tpar")
plt.plot(dimension["Dimension"], dimension["Tpar_ff"]/1000, 'o-', color="orange", label="Tpar_ff")
plt.legend()
plt.savefig('plot/dimension.png', bbox_inches = "tight")
#plt.show()

# In[9]:

plt.clf()
plt.title("Completion time")
plt.grid()
plt.xticks(range(0,512,32))
plt.xlabel("Parallel degree")
plt.ylabel("Time (ms)")
plt.plot(time["Parallel_degree"], time["Tseq"]/1000, 'o-', color="seagreen", label="Tseq")
plt.plot(time["Parallel_degree"], time["Tpar"]/1000, 'o-', color="royalblue", label="Tpar")
plt.plot(time["Parallel_degree"], time["Tpar_ff"]/1000, 'o-', color="orange", label="Tpar_ff")
plt.legend()
plt.savefig('plot/completion_time.png', bbox_inches = "tight")
#plt.show()


# In[9]:

plt.clf()
plt.title("Speedup")
plt.grid()
plt.xticks(range(0,512,32))
plt.xlabel("Parallel degree")
plt.ylabel("Speedup")
plt.plot(time["Parallel_degree"], time["Tseq"]/time["Tpar"], 'o-', color="royalblue", label="Tpar")
plt.plot(time["Parallel_degree"], time["Tseq"]/time["Tpar_ff"], 'o-', color="orange", label="Tpar_ff")
plt.legend()
plt.savefig('plot/speedup.png', bbox_inches = "tight")
#plt.show()


# In[10]:

plt.clf()
plt.title("Scalability")
plt.grid()
plt.xticks(range(0,512,32))
plt.xlabel("Parallel degree")
plt.ylabel("Scalability")
plt.plot(time["Parallel_degree"], time["Tpar"][0]/time["Tpar"], 'o-', color="royalblue", label="Tpar")
plt.plot(time["Parallel_degree"], time["Tpar_ff"][0]/time["Tpar_ff"], 'o-', color="orange", label="Tpar_ff")
plt.legend()
plt.savefig('plot/scalability.png', bbox_inches = "tight")
#plt.show()


# In[11]:

plt.clf()
plt.title("Efficiency")
plt.grid()
plt.xticks(range(0,512,32))
plt.xlabel("Parallel degree")
plt.ylabel("Efficiency (%)")
plt.plot(time["Parallel_degree"], time["sp"]/time["Parallel_degree"]*100, 'o-', color="royalblue", label="Tpar")
plt.plot(time["Parallel_degree"], time["sp_ff"]/time["Parallel_degree"]*100, 'o-', color="orange", label="Tpar_ff")
plt.legend()
plt.savefig('plot/efficiency.png', bbox_inches = "tight")
#plt.show()


# In[12]:

plt.clf()
plt.title("Amdahl's Law stdlib implementation")
plt.grid(zorder=0)
plt.yticks(range(0,105,10))
plt.ylim(0,105)
plt.xlabel("Parallel degree")
plt.ylabel("Percentage(%)")
plt.bar(time["Parallel_degree"].apply(str), time["serial_fraction"]*100, label="Serial work", zorder=3)
plt.bar(time["Parallel_degree"].apply(str), time["non_serial"]*100, bottom=time["serial_fraction"]*100, label="Parallel work", zorder=3)
plt.legend()
plt.savefig('plot/serial.png', bbox_inches = "tight")
#plt.show()


# In[13]:

plt.clf()
plt.title("Amdahl's Law FastFlow implementation")
plt.grid(zorder=0)
plt.yticks(range(0,105,10))
plt.ylim(0,105)
plt.xlabel("Parallel degree")
plt.ylabel("Percentage(%)")
plt.bar(time["Parallel_degree"].apply(str), time["serial_fraction_ff"]*100, label="Serial work", zorder=3)
plt.bar(time["Parallel_degree"].apply(str), time["non_serial_ff"]*100, bottom=time["serial_fraction_ff"]*100, label="Parallel work", zorder=3)
plt.legend()
plt.savefig('plot/serial_ff.png', bbox_inches = "tight")
#plt.show()


# In[ ]:




