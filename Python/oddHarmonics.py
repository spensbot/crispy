import numpy as np
import matplotlib.pyplot as plt
import math

def squish(sample, squishFactor):
    #check for input errors
    if squishFactor < 0:
        raise EOFError
    
    #fix a clipping signal
    if sample > 1:
        return 1
    elif sample < -1:
        return -1

    #compress signal between -1 and 1
    exp = 1/squishFactor
    modified = 0
    if sample > 0:
        modified = -(1 - sample)**exp + 1
    else:
        modified = -(-(1 + sample)**exp + 1)
    return modified

#constants

xMax = math.pi
yMax = 2.0
dx = 0.01

#X values
xArray = np.arange(-xMax, xMax, dx)
signal = []
for x in xArray:
    signal.append(math.sin(x))

plt.plot(xArray, signal)


# squishFactors = [0.01, 0.1, .5, 2, 10, 100]
squishFactors = [1, 10, 100]

for sf in squishFactors:
    modifiedSignal = []
    for sample in signal:
        modifiedSignal.append(squish(sample, sf))
    plt.plot(xArray, modifiedSignal)

# for sf in squishFactors:
#     modifiedSignal = []
#     for sample in signal:
#         if sample < .5 :
#             sample = sample + sample*sf
#         else :
#             sample = sample + (1-sample)*sf

#         modifiedSignal.append(sample)
#     plt.plot(xArray, modifiedSignal)

# for sf in squishFactors:
#     modifiedSignal = []
#     for sample in signal:
#         compression = sample**1.25
#         newSample = sample*sf - compression*(sf-1)

#         modifiedSignal.append(newSample)
#     plt.plot(xArray, modifiedSignal)

plt.xlabel("x")
plt.ylabel("y")
plt.title("Spenser's Title")
plt.legend()
plt.axis([-xMax, xMax, -yMax, yMax])
plt.grid(color='g', linestyle='--', linewidth=1, axis='both', markevery=1)
plt.show()
