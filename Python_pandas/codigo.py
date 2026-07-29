import pandas as pd
import time

def cargar_datos(archivo):
    try:
        df = pd.read_excel(archivo)
        if 'Fecha' in df.columns:
            df['Fecha'] = pd.to_datetime(df['Fecha']).dt.strftime('%Y-%m-%d')
        return df.to_dict('records')
    except Exception as e:
        print(f"Error al cargar Excel: {e}")
        return None

def burbuja(datos):
    arr = datos.copy()
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j]['Codigo Producto'] > arr[j+1]['Codigo Producto']:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr

def seleccion(datos):
    arr = datos.copy()
    n = len(arr)
    for i in range(n):
        min_idx = i
        for j in range(i+1, n):
            if arr[j]['Codigo Producto'] < arr[min_idx]['Codigo Producto']:
                min_idx = j
        arr[i], arr[min_idx] = arr[min_idx], arr[i]
    return arr

def insercion(datos):
    arr = datos.copy()
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and key['Codigo Producto'] < arr[j]['Codigo Producto']:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key
    return arr

def busqueda_binaria(arr, target):
    low = 0
    high = len(arr) - 1
    while low <= high:
        mid = (low + high) // 2
        if arr[mid]['Codigo Producto'] == target:
            return mid
        elif arr[mid]['Codigo Producto'] < target:
            low = mid + 1
        else:
            high = mid - 1
    return -1

def obtener_num_codigo(codigo):
    try:
        return int(codigo.upper().replace("P", ""))
    except:
        return -1

def busqueda_interpolacion(arr, target):
    t_num = obtener_num_codigo(target)
    if t_num == -1: return -1
    
    low = 0
    high = len(arr) - 1
    
    while low <= high and obtener_num_codigo(arr[low]['Codigo Producto']) <= t_num <= obtener_num_codigo(arr[high]['Codigo Producto']):
        l_num = obtener_num_codigo(arr[low]['Codigo Producto'])
        h_num = obtener_num_codigo(arr[high]['Codigo Producto'])
        
        if l_num == h_num:
            if l_num == t_num: return low
            else: return -1
            
        pos = low + int(((float(high - low) / (h_num - l_num)) * (t_num - l_num)))
        p_num = obtener_num_codigo(arr[pos]['Codigo Producto'])
        
        if p_num == t_num:
            return pos
        if p_num < t_num:
            low = pos + 1
        else:
            high = pos - 1
    return -1

def mostrar_estadisticas(datos_ordenados):
    df = pd.DataFrame(datos_ordenados)
    
    prod_stats = df.groupby(['Codigo Producto', 'Producto']).agg({
        'Cantidad': 'sum', 
        'Total Venta': 'sum'
    }).reset_index()
    
    mas_vendido = prod_stats.loc[prod_stats['Cantidad'].idxmax()]
    menos_vendido = prod_stats.loc[prod_stats['Cantidad'].idxmin()]
    
    sede_stats = df.groupby('Sede').agg({'Cantidad': 'sum', 'Total Venta': 'sum'}).reset_index()
    sede_mayor = sede_stats.loc[sede_stats['Total Venta'].idxmax()]
    sede_menor = sede_stats.loc[sede_stats['Total Venta'].idxmin()]
    
    df['Mes'] = pd.to_datetime(df['Fecha']).dt.strftime('%Y-%m')
    meses_sede = df.groupby(['Sede', 'Mes']).agg({'Cantidad': 'sum', 'Total Venta': 'sum'}).reset_index()
    meses_top3 = meses_sede.sort_values(['Sede', 'Total Venta'], ascending=[True, False]).groupby('Sede').head(3)

    print("\n--- DATOS RELEVANTES ---")
    print("\n[PRODUCTO MAS VENDIDO]")
    print(f"Codigo: {mas_vendido['Codigo Producto']} | Producto: {mas_vendido['Producto']}")
    print(f"Cantidad Total: {mas_vendido['Cantidad']} | Total Venta: S/{mas_vendido['Total Venta']:.2f}")
    
    print("\n[PRODUCTO MENOS VENDIDO]")
    print(f"Codigo: {menos_vendido['Codigo Producto']} | Producto: {menos_vendido['Producto']}")
    print(f"Cantidad Total: {menos_vendido['Cantidad']} | Total Venta: S/{menos_vendido['Total Venta']:.2f}")
    
    print("\n[SEDE CON MAYOR VENTA]")
    print(f"Sede: {sede_mayor['Sede']} | Cantidad Vendida: {sede_mayor['Cantidad']} | Total Venta: S/{sede_mayor['Total Venta']:.2f}")
    
    print("\n[SEDE CON MENOR VENTA]")
    print(f"Sede: {sede_menor['Sede']} | Cantidad Vendida: {sede_menor['Cantidad']} | Total Venta: S/{sede_menor['Total Venta']:.2f}")
    
    print("\n[TOP 3 MESES CON MAYOR VENTA POR SEDE]")
    sede_actual = ""
    for _, row in meses_top3.iterrows():
        if row['Sede'] != sede_actual:
            print(f"\nSede: {row['Sede']}")
            sede_actual = row['Sede']
        print(f"  Mes: {row['Mes']} | Cantidad: {row['Cantidad']} | Total Venta: S/{row['Total Venta']:.2f}")

def menu_ordenar(datos_originales):
    print("\n1. Metodo Burbuja")
    print("2. Metodo Seleccion")
    print("3. Metodo Insercion")
    while True:
        try:
            opc = int(input("Elija el metodo de ordenamiento: "))
            if opc in [1, 2, 3]: break
            print("Opcion invalida.")
        except ValueError:
            print("Ingrese un numero valido.")
    
    print("Ordenando las 10,000 filas. Por favor, espere...")
    if opc == 1:
        return burbuja(datos_originales)
    elif opc == 2:
        return seleccion(datos_originales)
    else:
        return insercion(datos_originales)

def main():
    archivo_excel = 'Ventas electronica SAC.xlsx'
    datos_originales = cargar_datos(archivo_excel)
    
    if not datos_originales:
        input("Presione Enter para salir...")
        return
        
    datos_ordenados = []
    esta_ordenado = False

    while True:
        print("\n--- MENU PRINCIPAL ---")
        print("1. Ordenar lista")
        print("2. Comparar algoritmos de ordenamiento")
        print("3. Buscar un producto")
        print("4. Obtener datos relevantes")
        print("5. Guardar un nuevo Excel Ordenado")
        print("6. Salir")
        
        try:
            opcion = int(input("\nSeleccione una opcion: "))
        except ValueError:
            print("Por favor, ingrese un numero valido.")
            time.sleep(1.5)
            continue

        if opcion == 1:
            datos_ordenados = menu_ordenar(datos_originales)
            esta_ordenado = True
            print("Lista ordenada y guardada en memoria exitosamente.")
            
        elif opcion == 2:
            print("\nIniciando comparacion con 10,000 registros (esto tomara unos segundos)...")
            
            inicio = time.perf_counter()
            burbuja(datos_originales)
            fin_burbuja = (time.perf_counter() - inicio) * 1000
            
            inicio = time.perf_counter()
            seleccion(datos_originales)
            fin_seleccion = (time.perf_counter() - inicio) * 1000
            
            inicio = time.perf_counter()
            datos_ordenados = insercion(datos_originales)
            fin_insercion = (time.perf_counter() - inicio) * 1000
            
            esta_ordenado = True
            print(f"\nTiempo Metodo Burbuja:   {fin_burbuja:.2f} ms")
            print(f"Tiempo Metodo Seleccion: {fin_seleccion:.2f} ms")
            print(f"Tiempo Metodo Insercion: {fin_insercion:.2f} ms")
            print("\nLa lista ha sido ordenada y se mantuvo en memoria para futuras operaciones.")
            
        elif opcion in [3, 4, 5]:
            if not esta_ordenado:
                print("\nERROR: Debe ordenar la lista primero (Opcion 1 o 2) antes de usar esta funcion.")
                continue
                
            if opcion == 3:
                codigo = input("\nIngrese el codigo del producto (ej. P005): ").strip().upper()
                print("1. Busqueda Binaria\n2. Busqueda por Interpolacion")
                while True:
                    try:
                        tipo_busqueda = int(input("Seleccione metodo de busqueda: "))
                        if tipo_busqueda in [1, 2]: break
                        print("Opcion invalida.")
                    except ValueError:
                        print("Ingrese un numero valido.")
                
                inicio = time.perf_counter()
                if tipo_busqueda == 1:
                    idx = busqueda_binaria(datos_ordenados, codigo)
                else:
                    idx = busqueda_interpolacion(datos_ordenados, codigo)
                tiempo = (time.perf_counter() - inicio) * 1000
                
                if idx != -1:
                    item = datos_ordenados[idx]
                    print(f"\n[PRODUCTO ENCONTRADO en {tiempo:.4f} ms]")
                    print(f"Codigo: {item['Codigo Producto']} | Producto: {item['Producto']} | Categoria: {item['Categoria']} | Precio Unitario: S/{item['Precio Unitario']}")
                else:
                    print(f"\nProducto '{codigo}' no fue encontrado. (Tiempo: {tiempo:.4f} ms)")
                
            elif opcion == 4:
                mostrar_estadisticas(datos_ordenados)
                
            elif opcion == 5:
                print("\nGenerando archivo Excel...")
                try:
                    df_guardar = pd.DataFrame(datos_ordenados)
                    df_guardar.to_excel("Ventas_Ordenadas_SAC.xlsx", index=False)
                    print("Archivo 'Ventas_Ordenadas_SAC.xlsx' guardado exitosamente en el directorio actual.")
                except Exception as e:
                    print(f"Error al guardar el archivo: {e}")
                
        elif opcion == 6:
            print("\nSaliendo del programa...")
            break
        else:
            print("Opcion no valida. Intente de nuevo.")

if __name__ == "__main__":
    main()