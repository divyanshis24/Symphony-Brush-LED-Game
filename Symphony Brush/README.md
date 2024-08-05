# Introduction
We created an innovative extension for any paintbrush that not only spreads colors across a canvas but also orchestrates a symphony of sound and generates mesmerizing visualizations in real-time.

## Audio Effects
This brush is capable of discerning colors, with each shade corresponding to a specific synthesizer sound. This turns painting into a symphonic endeavor. The speed at which you paint influences the pitch of the music, adding a dynamic layer of expression to your creative process.

## Visual
A captivating visual representation of sound waves dances across a screen, evolving in tandem with your brush strokes. This real-time feedback not only enhances your artistic journey but also deepens your connection to the immersive sensory world you're crafting.

# Construction

- MPU-6050: 3-Axis Accelerometer and Gyro Sensor Module: We used this motion processing technology to detect the speed of the brush in real-time.

- TCS3200: This color sensor was utilized to detect the colors being used.

- XIAO ESP32 S3: Chosen for its tiny size and Wi-Fi communication abilities, this microcontroller is mounted on the brush.

- ESP8266: This module feeds the real-time readings from the XIAO ESP32 S3 to our laptop, allowing integration with Ableton software.

This combination of hardware and software creates a unique, immersive experience, blending visual art with audio creation in a seamless, real-time process.

Refer The PPT for detail and demo videos
