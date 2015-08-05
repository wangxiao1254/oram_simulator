#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt
import sys

def getaline(s):
   f = open(s)
   f.readline()

   x = list()
   y = list()
   for a in f.readlines():
      t = a.split()
      if(len(t) ==  3):
         if(float(t[0]) > 2 and float(t[2])< 26):
            x.append(float(t[0]))      
            y.append(float(t[2]))
   return x,y
mxx = -1
mxy = -1
mix = 1000
miy = 1000
style = ['-sb', '-pg', '-Hc', '-Dr', '-<k']
i = 0
for s in sys.argv[1:]:
   x,y = getaline(s)
   plt.plot(y, x, style[i], linewidth=2, label = s)
   mxx = max(mxx, max(x))
   mxy = max(mxy, max(y))
   mix = min(mix, min(x))
   miy = min(miy, min(y))
   i = i + 1
leg = plt.gca().legend(loc='upper left', fancybox=True, prop={'size':17},  ncol=1)
leg.draw_frame(False)
plt.xlabel('$\log_2(1/$failure probability$)$')
plt.ylabel('Stash Size')
plt.xlim([max(0, miy-1), mxy+1])
plt.ylim([max(0, mix-1), mxx+1])
plt.savefig(sys.argv[1], bbox_inches='tight', dpi=200)
