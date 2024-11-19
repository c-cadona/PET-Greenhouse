import pandas as pd
import plotly.graph_objects as go
import streamlit as st

def update_charts(df: pd.DataFrame, temp_chart, light_chart, soil_chart):
    """
    Atualiza os gráficos usando Plotly para centralizar as linhas e adicionar limites.
    Inclui referências de mínima para luminosidade e umidade do solo.
    """
    if not df.empty:
        # Define o intervalo para centralizar os gráficos
        temp_min, temp_max = df["averageDHT"].min(), df["averageDHT"].max()
        light_min, light_max = df["averageLDR"].min(), df["averageLDR"].max()
        soil_min, soil_max = df["averageSOIL"].min(), df["averageSOIL"].max()

        # Adiciona margens para centralizar as linhas
        temp_range = [min(temp_min - 5, 18), max(temp_max + 5, 22)]
        light_range = [min(light_min - 50, 600), light_max + 50]
        soil_range = [min(soil_min - 10, 80), soil_max + 10]

        # Gráfico de temperatura com linhas de referência
        temp_fig = go.Figure()
        temp_fig.add_trace(go.Scatter(x=df["Time"], y=df["averageDHT"], mode="lines", name="Temperatura"))
        temp_fig.add_shape(
            type="line",
            x0=df["Time"].iloc[0], x1=df["Time"].iloc[-1],
            y0=22, y1=22,
            line=dict(color="red", width=2, dash="dash"),
            name="Máxima (22°C)"
        )
        temp_fig.add_shape(
            type="line",
            x0=df["Time"].iloc[0], x1=df["Time"].iloc[-1],
            y0=18, y1=18,
            line=dict(color="blue", width=2, dash="dash"),
            name="Mínima (18°C)"
        )
        temp_fig.update_layout(
            title="Temperatura (°C)",
            yaxis=dict(range=temp_range),
            legend=dict(
                orientation="h",
                yanchor="top",
                y=-0.3,
                xanchor="center",
                x=0.5
            ),
            showlegend=True
        )

        # Gráfico de luminosidade com linha de mínima
        light_fig = go.Figure()
        light_fig.add_trace(go.Scatter(x=df["Time"], y=df["averageLDR"], mode="lines", name="Luminosidade"))
        light_fig.add_shape(
            type="line",
            x0=df["Time"].iloc[0], x1=df["Time"].iloc[-1],
            y0=600, y1=600,
            line=dict(color="yellow", width=2, dash="dash"),
            name="Mínima (600)"
        )
        light_fig.update_layout(
            title="Luminosidade",
            yaxis=dict(range=light_range),
            legend=dict(
                orientation="h",
                yanchor="top",
                y=-0.3,
                xanchor="center",
                x=0.5
            ), 
            showlegend=True
        )

        # Gráfico de umidade do solo com linha de mínima
        soil_fig = go.Figure()
        soil_fig.add_trace(go.Scatter(x=df["Time"], y=df["averageSOIL"], mode="lines", name="Umidade do Solo"))
        soil_fig.add_shape(
            type="line",
            x0=df["Time"].iloc[0], x1=df["Time"].iloc[-1],
            y0=80, y1=80,
            line=dict(color="green", width=2, dash="dash"),
            name="Mínima (80%)"
        )
        soil_fig.update_layout(
            title="Umidade do Solo (%)",
            yaxis=dict(range=soil_range),
            legend=dict(
                orientation="h",
                yanchor="top",
                y=-0.3,
                xanchor="center",
                x=0.5
            ), 
            showlegend=True
        )

        # Atualiza os placeholders do Streamlit
        temp_chart.plotly_chart(temp_fig, use_container_width=True)
        light_chart.plotly_chart(light_fig, use_container_width=True)
        soil_chart.plotly_chart(soil_fig, use_container_width=True)
