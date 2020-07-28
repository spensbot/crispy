import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider
import math

# Prepare plot figure
fig, (ax1, ax2) = plt.subplots(2, sharex=True)
plt.subplots_adjust(bottom=0.25)
fig.suptitle('Even Harmonics')
ax1.set(ylim=(-1.0, 1.0))

# Even harmonics saturation function


def evenSaturate(sample, mix, withOffset=False):
    dry = np.clip(sample, -1.0, 1.0)
    wet = dry * dry
    wet = np.abs(wet)
    if (withOffset):
        wet -= 0.5
        wet *= 2.0
    return wet * mix + dry * (1-mix)


def oddSaturate(sample, power):
    modified = 0
    if sample > 0:
        modified = -(1 - sample)**power + 1
    else:
        modified = -(-(1 + sample)**power + 1)
    return modified

# Adding even saturation will change the range of the output


def evenRangeReduction(mix):
    return mix


def evenShift(mix):
    return evenRangeReduction(mix) / 2.0


def evenShrink(mix):
    return 2.0 / (2.0 - evenRangeReduction(mix))


def evenCenter(sample, mix):
    sample = sample - evenShift(mix)
    sample = sample * evenShrink(mix)
    return sample


def evenUncenter(sample, mix):
    sample = sample / evenShrink(mix)
    sample = sample + evenShift(mix)


def oddEven_S(sample, saturation, mix, withOffset=True, evenFirst=True):
    even = mix
    odd = 1.0-mix

    if (mix > 0.5):
        #odd = (1.0 - mix) * 2.0
        even = 1.0
    else:
        #odd = 1.0
        even = mix * 2.0

    odd *= saturation
    even *= saturation

    odd *= 2.0
    odd += 1.0
    odd = odd * odd * odd * odd

    if (evenFirst):
        sample = evenSaturate(sample, even, withOffset)
        #sample = evenCenter(sample, mix)
        sample = oddSaturate(sample, odd)
        #sample = evenUncenter(sample, mix)
    else:
        sample = oddSaturate(sample, odd)
        sample = evenSaturate(sample, even, withOffset)
    return sample


oddEven = np.vectorize(oddEven_S)

# Data to graph
saturation0 = 0.0
mix0 = 0.0
inputAmplitude0 = 1.0
xMax = np.pi * 1.0
xAngle = np.arange(-xMax, xMax, 0.1)
sinInput = np.sin(xAngle) * inputAmplitude0

# define sliders
axcolor = 'lightgoldenrodyellow'
axSaturation = plt.axes([0.25, 0.05, 0.65, 0.03], facecolor=axcolor)
axMix = plt.axes([0.25, 0.1, 0.65, 0.03], facecolor=axcolor)
axAmplitude = plt.axes([0.25, 0.15, 0.65, 0.03], facecolor=axcolor)
slider_saturation = Slider(axSaturation, 'Saturation',
                           0.0, 1.0, valinit=saturation0, valstep=0.01)
slider_mix = Slider(axMix, 'Odd/Even Mix', 0, 1, valinit=mix0, valstep=0.01)
slider_amplitude = Slider(axAmplitude, 'Input Amplitude',
                          0, 1, valinit=0.5, valstep=0.01)

oddEvenInput, = ax1.plot(xAngle, sinInput, 'g:')
oddEvenPlotOffset, = ax1.plot(xAngle, oddEven(
    sinInput, saturation0, mix0, True, False), 'b')
oddEvenPlot, = ax1.plot(xAngle, oddEven(
    sinInput, saturation0, mix0, False, False), 'k')
ax1.grid(b=True, which='both', axis='both')
ax1.set(ylabel='Odd -> Even')
ax1.legend(['Input', 'Offset', 'No Offset'])

evenOddInput, = ax2.plot(xAngle, sinInput, 'g:')
evenOddPlotOffset, = ax2.plot(xAngle, oddEven(
    sinInput, saturation0, mix0, True, True), 'b')
evenOddPlot, = ax2.plot(xAngle, oddEven(
    sinInput, saturation0, mix0, False, True), 'k')
ax2.grid(b=True, which='both', axis='both')
ax2.set(ylabel='Even -> Odd')
ax2.legend(['Input', 'Offset', 'No Offset'])

# Update function upon slider change


def update(val):
    sinInput = np.sin(xAngle) * slider_amplitude.val

    oddEvenInput.set_ydata(sinInput)
    evenOddInput.set_ydata(sinInput)

    oddEvenPlotOffset.set_ydata(
        oddEven(sinInput, slider_saturation.val, slider_mix.val, True, False))
    evenOddPlotOffset.set_ydata(
        oddEven(sinInput, slider_saturation.val, slider_mix.val, True, True))
    oddEvenPlot.set_ydata(
        oddEven(sinInput, slider_saturation.val, slider_mix.val, False, False))
    evenOddPlot.set_ydata(
        oddEven(sinInput, slider_saturation.val, slider_mix.val, False, True))
    fig.canvas.draw_idle()


slider_saturation.on_changed(update)
slider_mix.on_changed(update)
slider_amplitude.on_changed(update)

# Print key values of interest, then show plot.
# print(f"Sin RMS: {np.average(sinInput ** 2) ** 0.5}")
# print(f"Sin Average: {np.average(sinInput)}")
# print(f"Average: {np.average(response)}")
# print(f"RMS: {np.average(response ** 2) ** 0.5}")

plt.show()
