import streamlit as st
import pandas as pd
import time
from data_fetcher import fetch_data
from plotter import update_charts

# Inicia o dataframe que conterá os dados de tempo e dos sensores
data = {"Time": [], "averageDHT": [], "averageLDR": [], "averageSOIL": []}
df = pd.DataFrame(data)

# Layout do streamlit:
st.title("PET Greenhouse Dashboard")
st.write("Vizualização em tempo real das variáveis ambientais")

# Inicia os placeholders dos gráficos
st.write("Temperatura (°C):")
temp_chart = st.line_chart()
st.write("Luminosidade:")
light_chart = st.line_chart()
st.write("Umidade do solo (%):")
soil_chart = st.line_chart()

while True:
    new_data = fetch_data()  # Pega os dados, da ESP. Em caso de erro de comunicação 
    print(new_data)
    if new_data:
        df = pd.concat([df, pd.DataFrame([new_data])], ignore_index=True)
        
        # Quando chegar em 100 leituras, apaga as mais antigas
        if len(df) > 100:
            df = df.iloc[-100:]

        # Atualiza os gráficos
        update_charts(df, temp_chart, light_chart, soil_chart)

    # Controla a frequência
    time.sleep(5)
