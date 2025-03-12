import streamlit as st
import pandas as pd
import time
from data_fetcher import fetch_data
from plotter import update_charts

# Configuração inicial do Streamlit
st.set_page_config(page_title="Pet Greenhouse", page_icon="⚡", layout="wide")

# Estilo do cabeçalho
st.markdown("""
    <style>
        .main-title {
            font-size: 40px;
            font-weight: bold;
            color: #2E8B57;
            text-align: center;
        }
        .sub-title {
            font-size: 18px;
            color: #6C757D;
            text-align: center;
            margin-top: -10px;
        }
        .metric-box {
            font-size: 16px;
            color: #FFFFFF;
            background-color: #4CAF50;
            padding: 10px;
            border-radius: 5px;
            text-align: center;
        }
        hr {
            border: 1px solid #DDD;
        }
    </style>
""", unsafe_allow_html=True)

# Título e subtítulo
st.markdown("<div class='main-title'>⚡Dashboard da Pet Greenhouse⚡</div>", unsafe_allow_html=True)
st.markdown("<div class='sub-title'>Monitoramento em tempo real das variáveis ambientais</div>", unsafe_allow_html=True)

# Inicializa o DataFrame para armazenar os dados dos sensores
if 'data' not in st.session_state:
    st.session_state.data = pd.DataFrame({"Time": [], "averageDHT": [], "averageLDR": [], "averageSOIL": []})

# Divisão em colunas para melhor organização
col1, col2, col3 = st.columns(3)

with col1:
    st.markdown("<div class='metric-box'>Temperatura (°C)</div>", unsafe_allow_html=True)
    temp_chart = st.empty()

with col2:
    st.markdown("<div class='metric-box'>Luminosidade</div>", unsafe_allow_html=True)
    light_chart = st.empty()

with col3:
    st.markdown("<div class='metric-box'>Umidade do Solo (%)</div>", unsafe_allow_html=True)
    soil_chart = st.empty()

# Configuração do intervalo de atualização
REFRESH_INTERVAL = 5  # Segundos

# Atualizações contínuas
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
