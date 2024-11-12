import pandas as pd
import streamlit as st

def update_charts(df: pd.DataFrame, temp_chart, light_chart, soil_chart):
    """
    Updates Streamlit line charts with the latest data.
    :param df: DataFrame containing the latest data
    :param temp_chart: Streamlit line chart for temperature
    :param light_chart: Streamlit line chart for light intensity
    :param soil_chart: Streamlit line chart for soil moisture
    """
    temp_chart.line_chart(df[['Time', 'averageDHT']].set_index('Time'))
    light_chart.line_chart(df[['Time', 'averageLDR']].set_index('Time'))
    soil_chart.line_chart(df[['Time', 'averageSOIL']].set_index('Time'))
