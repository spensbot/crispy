import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider
import math

#Prepare plot figure
fig, (ax1, ax2) = plt.subplots(2)
plt.subplots_adjust(bottom=0.25)
fig.suptitle('Even Harmonics')
ax1.set(ylim=(-1.0, 1.0))

# Even harmonics saturation function
def even(sample, power, mix):
  dry = np.clip(sample, -1.0, 1.0)
  wet = dry ** power
  wet = abs(wet)
  wet -= 0.5
  wet *= 2.0
  return wet * mix + dry * (1-mix)
evenVect = np.vectorize(even)

# Data to graph
power0 = 2
mix0 = 0.5
xMax = np.pi * 2.0
xInput = np.arange(-1.2, 1.2, 0.01)
xAngle = np.arange(-xMax, xMax, 0.01)
sinInput = np.sin(xAngle)

#define sliders
axcolor = 'lightgoldenrodyellow'
axPower = plt.axes([0.25, 0.1, 0.65, 0.03], facecolor=axcolor)
axMix = plt.axes([0.25, 0.15, 0.65, 0.03], facecolor=axcolor)
slider_power = Slider(axPower, 'Power', -2, 10, valinit=power0, valstep=1)
slider_mix = Slider(axMix, 'Mix', 0, 1, valinit=mix0, valstep=0.01)

transferPlot, = ax1.plot(xInput, evenVect(xInput, power0, mix0), 'k')
ax1.grid(b=True, which='both', axis='both')
ax2.plot(xAngle, sinInput, 'g:')
responsePlot, = ax2.plot(xAngle, evenVect(sinInput, power0, mix0), 'k')
ax2.grid(b=True, which='both', axis='both')

#Update function upon slider change
def update(val):
  transferPlot.set_ydata(evenVect(xInput, slider_power.val, slider_mix.val))
  responsePlot.set_ydata(evenVect(sinInput, slider_power.val, slider_mix.val))
  fig.canvas.draw_idle()

slider_power.on_changed(update)
slider_mix.on_changed(update)

# Print key values of interest, then show plot.
# print(f"Sin RMS: {np.average(sinInput ** 2) ** 0.5}")
# print(f"Sin Average: {np.average(sinInput)}")
# print(f"Average: {np.average(response)}")
# print(f"RMS: {np.average(response ** 2) ** 0.5}")

plt.show()

