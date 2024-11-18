import random
import time
import serial


#A porta COM deve ser mudada de acordo com a porta COM que o computador abre para a comunicação com a ESP via Bluetooth.
ser = serial.Serial('COM10', 11250, timeout=5)  # recolhe os dados da ESP32

def fetch_data():
    
    try:
        
        line = ser.readline().decode('utf-8').strip()
        values = line.split(',') if line else [0, 0, 0] #caso não consiga realizar a comunicação, os dados serão 0.
        
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
