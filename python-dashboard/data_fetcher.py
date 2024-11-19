from serial.tools import list_ports
import serial
import time

def find_esp32_port(mac_address="08D1F9EE02CE", baud_rate=11250, timeout=5, fallback_port="COM7"):
    """
    Detecta automaticamente a porta COM usada pela ESP32 via Bluetooth com base no endereço MAC.
    Retorna a porta detectada ou usa uma porta configurada manualmente como fallback.
    """
    # Lista todas as portas COM disponíveis
    ports = list_ports.comports()
    for port in ports:
        try:
            # Verifica se o endereço MAC está contido no HWID
            if mac_address in port.hwid:
                print(f"Dispositivo encontrado: {port.device} (MAC: {mac_address})")
                # Testa a conexão para garantir que está funcional
                with serial.Serial(port.device, baud_rate, timeout=timeout) as ser:
                    return port.device
        except serial.SerialException as e:
            print(f"Erro ao tentar conectar à porta {port.device}: {e}")
    
    # Fallback manual
    print(f"Usando a porta fallback: {fallback_port}")
    return fallback_port

def fetch_data(mac_address="08D1F9EE02CE", fallback_port="COM7"):
    """
    Busca dados dos sensores conectados à ESP32 via porta serial.
    """
    port = find_esp32_port(mac_address, fallback_port=fallback_port)
    if not port:
        print("Dispositivo não encontrado. Verifique a conexão Bluetooth.")
        return None
    
    try:
        # Abre a conexão na porta detectada
        with serial.Serial(port, 11250, timeout=5) as ser:
            linha = ser.readline().decode('utf-8').strip()
            valores = linha.split(',') if linha else [0, 0, 0]
            return {
                "Time": time.strftime('%H:%M:%S'),
                "averageDHT": float(valores[0]),
                "averageLDR": float(valores[1]),
                "averageSOIL": float(valores[2])
            }
    except serial.SerialException as e:
        print(f"Erro de comunicação serial: {e}")
        return None
    except ValueError as e:
        print(f"Erro ao interpretar os dados: {e}")
        return None
