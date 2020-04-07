import numpy as np
import matplotlib.pyplot as plt
import math

x = np.arange(0, np.pi*2, 0.1)

y = np.sin(x)
yHalf = y/2

def rms(array):

  sumOfSquares = 0.0

  for val in array:
    sumOfSquares += val**2.0
  
  meanSquare = sumOfSquares / array.size

  return meanSquare ** 0.5

combinedRMS = ((rms(y)**2.0 + rms(yHalf)**2.0)/2.0)**0.5
combinedRMS2 = rms(np.concatenate((y, yHalf), axis=None))

print(f"\n RMS of y: {rms(y)}")
print(f"RMS of yHalf: {rms(yHalf)}")
print(f"Twice RMS of yHalf: {rms(yHalf) * 2.0}")
print(f"Combined RMS: {combinedRMS}")
print(f"Combined RMS2: {combinedRMS2} \n")

# plt.plot(x, y)
# plt.plot(x, yHalf)
# plt.show()

