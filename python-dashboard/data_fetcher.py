import random
import time
import serial

ser = serial.Serial('COM10', 11250, timeout=5)  # get data from esp32

def fetch_data():
    """
    Simulates or fetches data from ESP32.
    Returns a dictionary with time and sensor values.
    """
    try:
        
        line = ser.readline().decode('utf-8').strip()
        values = line.split(',') if line else [random.randint(15, 35), random.randint(100, 1000), random.randint(200, 800)]
        
        # For simulated data
        #values = [random.randint(15, 35), random.randint(100, 1000), random.#randint(200, 800)]
        
        # Map the simulated values to named fields
        new_data = {
            "Time": time.strftime('%H:%M:%S'),
            "averageDHT": values[0],
            "averageLDR": values[1],
            "averageSOIL": values[2]
        }
        
        return new_data
    except Exception as e:
        print(f"Data fetching error: {e}")
        return None
