import base64

def decodificar_base64(cadena_base64):
    try:
        # Decodificar la cadena Base64
        cadena_decodificada = base64.b64decode(cadena_base64).decode('utf-8')
        return cadena_decodificada
    except Exception as e:
        # Manejar posibles errores, como una cadena Base64 inválida
        print(f"Error al decodificar Base64: {e}")
        return None

# Ejemplo de uso:
cadena_base64 = "VkdobElHSnZjM01nY1hWcFpYSmxJR2R2SUhSdklIUm9aU0JrYjJ4c2MyaHZkWE5s"  # Ejemplo de "Hello world!" en Base64
cadena_base64 = "VGhlIGJvc3MgcXVpZXJlIGdvIHRvIHRoZSBkb2xsc2hvdXNl"  # Ejemplo de "Hello world!" en Base64
cadena_decodificada = decodificar_base64(cadena_base64)

if cadena_decodificada:
    print("Cadena decodificada:", cadena_decodificada)
else:
    print("No se pudo decodificar la cadena.")


# def decodificar_base64(cadena_base64):
#   """
#   Decodifica una cadena codificada en Base64 a bytes.

#   Parámetros:
#     cadena_base64 (str): La cadena codificada en Base64.

#   Devuelve:
#     bytes: Los bytes decodificados.
#   """

#   import base64

#   # Decodificamos la cadena
#   bytes_decodificados = base64.b64decode(cadena_base64)

#   return bytes_decodificados

# import base64

# def decode_base64(data):
#   """Decodes a Base64-encoded string.

#   Args:
#     data: The Base64-encoded string to decode.

#   Returns:
#     The decoded bytes.

#   Raises:
#     TypeError: If the input data is not a string.
#     ValueError: If the input data is not valid Base64.
#   """

#   if not isinstance(data, str):
#     raise TypeError("data must be a string")

#   try:
#      decoded_bytes = base64.b64decode(data)
#   except base64.binascii.Error:
#      raise ValueError("data is not valid Base64")

#   return decoded_bytes

# # Example usage:
# encoded_data = "VkdobElHSnZjM01nY1hWcFpYSmxJR2R2SUhSdklIUm9aU0JrYjJ4c2MyaHZkWE5s"
# encoded_data = "VGhlIGJvc3MgcXVpZXJlIGdvIHRvIHRoZSBkb2xsc2hvdXNl"
# decoded_data = decode_base64(encoded_data)
# print(decoded_data)  # Output: b'Hello, world!'


# # Ejemplo de uso
# cadena_base64 = "VkdobElHSnZjM01nY1hWcFpYSmxJR2R2SUhSdklIUm9aU0JrYjJ4c2MyaHZkWE5s"
# cadena_base64 = "VGhlIGJvc3MgcXVpZXJlIGdvIHRvIHRoZSBkb2xsc2hvdXNl"
# bytes_decodificados = decodificar_base64(cadena_base64)

# print(f"Cadena decodificada: {bytes_decodificados.decode('utf-8')}")
