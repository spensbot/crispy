# Make It Crispy

![Screenshot of Crispy in action](https://raw.githubusercontent.com/spensbot/crispy/master/Graphic%20Design/BorderLess.png)

## A powerful saturation plugin for music production

### 64-bit versions available on Mac (vst3 and au) and Windows (vst3)
[Mac Downloads](https://github.com/spensbot/crispy/tree/master/Release%20Builds/Mac%20(64%20bit))

[Windows Downloads](https://github.com/spensbot/crispy/tree/master/Release%20Builds/Windows%20(64%20bit))

# Features

## Odd Saturation Knob
Adds odd harmonics to a signal. This is the biggest knob, and represents Crispy's primary function. The 'Saturation Visualizer' behind this knob demonstrates the effect the saturation algorithm has on a sin wave with a gain of 0 dB. Real-world audio, which is made up of many sin waves, will behave differently when saturated.

## Even Saturation Mix
Adds even harmonics to a signal. This slider is intended to change the color of saturation. It should be used in combination to the odd saturation knob.

## High/Low Pass Filters
These High and Low Pass knobs filter the signal before the saturator. This allows you to target and saturate a specific frequency range. In this way, Crispy can act like a harmonic exciter.

## Oversampling
Oversampling is important to reduce/remove aliasing when dealing with heavy saturation and/or high frequencies. However, this knob should be used with caution; High oversampling can add significant CPU load. Saturation adds harmonics to a signal. This can introduce frequencies too high for standard sample rates to capture. These uncapturable frequencies manifest as lower, aliased frequencies that create noise in a mix. 2x - 4x oversampling is often enough to remove audible artifacts, and is recommended in most cases. High oversampling rates should only be used when necessary. A 44.1kHz signal, oversampled 16x requires the algorithm to process over 705,000 samples per second!

## Dry/Wet Mix
A Standard Dry/Wet Mix. This allows you to mix the processed (wet) and unprocessed (dry) signal.

## Matched Bypass
Bypasses the plugin, while adding gain to match the RMS volume of the current dry/wet mix. Saturation adds volume to a signal, so most saturation plugins sound better when bypassed simply because the sound is louder. This feature is incredibly helpful. It allows you to hear how Crispy is changing your sound without volume bias.

## Auto-Gain
Adds gain to provide the saturation algorithm with an ideal signal level. When fed a quiet signal, crispy mostly just adds volume. Auto-Gain allows the full dynamic range of the mix to be saturated more evenly. Added gain is removed after saturation. The end result is similar to compression.

