import serial
import matplotlib.pyplot as plt
import time
import numpy as np

ser = serial.Serial('COM5', 9600)
time.sleep(2)

temp_c = []
r_test = []
r_therm = []

print('Reading data... press Ctrl+C to stop and plot')

while True:
    try:
        line1 = ser.readline().decode('utf-8').strip()
        line2 = ser.readline().decode('utf-8').strip()
        line3 = ser.readline().decode('utf-8').strip()

        print(f"Raw: '{line1}' '{line2}' '{line3}'")

        temp_c.append(float(line1))
        r_test.append(float(line2))
        r_therm.append(float(line3))

        print(f"T: {float(line1):.1f} C | R_Test: {float(line2):2e} Ohm | T_Therm: {float(line3):.3f}")

    except KeyboardInterrupt:
        break

    except Exception as e:
        print(f"Error: {e}")
        print(f"Bad data was: '{line1}' '{line2}' '{line3}'")

print(f"Total readings collected: {len(temp_c)}")
print(temp_c)

coeffs = np.polyfit(temp_c, r_test, 1)
slope = coeffs[0]
fitted_line = np.polyval(coeffs, temp_c)
R0_measured = r_test[0]
TCR = (slope / R0_measured) * 1e6
print(f"TCR = {TCR:.1f} ppm/C")

plt.plot(temp_c, r_test, 'o', label='Measured')
plt.plot(temp_c, fitted_line, '-', label='Linear Fit')
plt.legend()
plt.title("Temperature Coefficient of Resistance")
plt.xlabel("Temp (C)")
plt.ylabel("Resistance (ohm)")
plt.show()
ser.close()
