import streamlit as st
import pandas as pd
import time
from data_fetcher import fetch_data
from plotter import update_charts

# Configuração inicial do Streamlit
st.set_page_config(page_title="Pet Greenhouse Dashboard", page_icon="🌱", layout="wide")

# Título e descrição do dashboard
st.title("Dashboard da PET Greenhouse")
st.write("Visualização em tempo real das variáveis ambientais")

# Inicializa o DataFrame para armazenar os dados dos sensores
if 'data' not in st.session_state:
    st.session_state.data = pd.DataFrame({"Time": [], "averageDHT": [], "averageLDR": [], "averageSOIL": []})

# Espaços reservados para os gráficos
st.write("Temperatura (°C):")
temp_chart = st.empty()
st.write("Luminosidade:")
light_chart = st.empty()
st.write("Umidade do Solo (%):")
soil_chart = st.empty()

# Configuração do intervalo de atualização
REFRESH_INTERVAL = 5  # Intervalo em segundos para atualizar os gráficos

# Loop contínuo para atualização dos gráficos
while True:
    # Busca novos dados dos sensores
    novos_dados = fetch_data()
    if novos_dados:
        # Atualiza os dados na sessão
        st.session_state.data = pd.concat(
            [st.session_state.data, pd.DataFrame([novos_dados])], ignore_index=True
        )
        # Mantém apenas as 100 leituras mais recentes
        if len(st.session_state.data) > 100:
            st.session_state.data = st.session_state.data.iloc[-100:]

    # Atualiza os gráficos
    update_charts(st.session_state.data, temp_chart, light_chart, soil_chart)

    # Pausa antes da próxima atualização
    time.sleep(REFRESH_INTERVAL)
