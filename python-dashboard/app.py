import streamlit as st
import pandas as pd
import time
from data_fetcher import fetch_data
from plotter import update_charts

# Initialize data frame to hold time and sensor data
data = {"Time": [], "averageDHT": [], "averageLDR": [], "averageSOIL": []}
df = pd.DataFrame(data)

# Set up Streamlit layout
st.title("PET Greenhouse Dashboard")
st.write("Vizualização em tempo real das variáveis ambientais")

# Initialize chart placeholders
st.write("Temperatura (°C):")
temp_chart = st.line_chart()
st.write("Luminosidade:")
light_chart = st.line_chart()
st.write("Umidade do solo (%):")
soil_chart = st.line_chart()

# Main loop for data fetching and chart updating
while True:
    new_data = fetch_data()  # Get new data point (simulated or from ESP32)
    print(new_data)
    if new_data:
        df = pd.concat([df, pd.DataFrame([new_data])], ignore_index=True)
        
        # Keep only the last 100 records to keep the dashboard responsive
        if len(df) > 100:
            df = df.iloc[-100:]

        # Update the charts with new data
        update_charts(df, temp_chart, light_chart, soil_chart)


    # Control update frequency (1 second)
    time.sleep(5)
