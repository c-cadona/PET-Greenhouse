import pandas as pd
import streamlit as st

def update_charts(df: pd.DataFrame, temp_chart, light_chart, soil_chart):
    # Atualiza os gráficos de linha do streamlit
    temp_chart.line_chart(df[['Time', 'averageDHT']].set_index('Time'))
    light_chart.line_chart(df[['Time', 'averageLDR']].set_index('Time'))
    soil_chart.line_chart(df[['Time', 'averageSOIL']].set_index('Time'))
