## BTBCD -> Binary To BCD

Conversor de numeros binarios o decimales de 16 bits a formato BCD

### Pasos de ejecucion
- Compila el programa con `g++ -o btbcd btbcd.cpp bcd.cpp`
- Esto generara el ejecutable `btbcd`
- Al ejecutarlo veras lo siguiente
```
$ ./btbcd
=== [1] Convertir de decimal/binario a BCD (max 16 bits) ===
=== [2] Convertir de BCD en formato BCD a decimal/binario (max 16 bits) ===
[opcion 1 por defecto]:
```

#### Ejemplo
```
=== Conversor de decimal/binario a formato BCD (max 16 bits) ===
Ingrese el numero a convertir (decimal o binario [ej: b1011]): 142

============ Procedimiento =============
Desplazamiento: 0000 0000 0000 0000 0000
Desplazamiento: 0000 0000 0000 0000 0000

...

Desplazamiento: 0000 0000 0000 0000 0001
Desplazamiento: 0000 0000 0000 0000 0001
Desplazamiento: 0000 0000 0000 0000 0001
Desplazamiento: 0000 0000 0000 0000 0001
Desplazamiento: 0000 0000 0000 0000 0001
Desplazamiento: 0000 0000 0000 0000 0010
Desplazamiento: 0000 0000 0000 0000 0010
Desplazamiento: 0000 0000 0000 0000 0010
Desplazamiento: 0000 0000 0000 0000 0010
Desplazamiento: 0000 0000 0000 0000 0010
Desplazamiento: 0000 0000 0000 0000 0100
Desplazamiento: 0000 0000 0000 0000 0100
Desplazamiento: 0000 0000 0000 0000 0100
Desplazamiento: 0000 0000 0000 0000 0100
Desplazamiento: 0000 0000 0000 0000 0100
Desplazamiento: 0000 0000 0000 0000 1000
Se suma (0011): 1000 -> 1011
Desplazamiento: 0000 0000 0000 0000 1011
Desplazamiento: 0000 0000 0000 0000 1011
Desplazamiento: 0000 0000 0000 0000 1011
Desplazamiento: 0000 0000 0000 0000 1011
Desplazamiento: 0000 0000 0000 0000 0111
Se suma (0011): 0111 -> 1010
Desplazamiento: 0000 0000 0000 0001 1010
Desplazamiento: 0000 0000 0000 0001 1010
Desplazamiento: 0000 0000 0000 0001 1010
Desplazamiento: 0000 0000 0000 0001 1010
Desplazamiento: 0000 0000 0000 0001 0101
Se suma (0011): 0101 -> 1000
Desplazamiento: 0000 0000 0000 0011 1000
Desplazamiento: 0000 0000 0000 0011 1000
Desplazamiento: 0000 0000 0000 0011 1000
Desplazamiento: 0000 0000 0000 0011 1000
Desplazamiento: 0000 0000 0000 0011 0001
Desplazamiento: 0000 0000 0000 0111 0001
Se suma (0011): 0111 -> 1010
Desplazamiento: 0000 0000 0000 1010 0001
Desplazamiento: 0000 0000 0000 1010 0001
Desplazamiento: 0000 0000 0000 1010 0001
Desplazamiento: 0000 0000 0000 1010 0010
Desplazamiento: 0000 0000 0000 0100 0010
Desplazamiento: 0000 0000 0001 0100 0010
Desplazamiento: 0000 0000 0001 0100 0010
Desplazamiento: 0000 0000 0001 0100 0010

DECIMAL: 142
BINARY:  0000000010001110
BCD:     0000 0000 0001 0100 0010
```

## BOOTH

Algoritmo de multiplicacion de Booth para numeros binarios de 16 bits con o sin signo

### Pasos de ejecucion
- Compila el programa con `g++ -o booth booth.cpp`
- Esto generara el ejecutable `booth`
- Al ejecutarlo veras lo siguiente
```
$ ./booth
=== Multiplicación con Algoritmo de Booth (max 16 bits) ===
Ingrese el primer número (decimal o binario prefijado con b: ej: b1011):
```
>[!NOTE]
>
>Se antepone una 'b' para indicar que el numero es binario.
>
>Para numeros binarios negativos, ingresarlos con complemento a 2


#### Ejemplo
```
Ingrese el primer número (decimal o binario prefijado con b: ej: b1011): b10111
Ingrese el segundo número (decimal o binario prefijado con b: ej: b1100): b11

--- Valores ingresados ---
A (dec) = 23 | A (bin) = 0000000000010111
B (dec) = 3 | B (bin) = 0000000000000011

====================== Procedimiento ======================
| Cuenta | Q_0 | C_f | AL               | DL               |
| 16     | 1   | 0   | 0000000000000000 | 0000000000000011 |
| Cuenta | Q_0 | C_f | AL               | DL               |
| 15     | 1   | 0   | 0000000000001011 | 1000000000000001 |
| Cuenta | Q_0 | C_f | AL               | DL               |
| 14     | 0   | 0   | 0000000000010001 | 0100000000000000 |
| Cuenta | Q_0 | C_f | AL               | DL               |
| 13     | 0   | 0   | 0000000000001000 | 1010000000000000 |
| Cuenta | Q_0 | C_f | AL               | DL               |
| 12     | 0   | 0   | 0000000000000100 | 0101000000000000 |
| Cuenta | Q_0 | C_f | AL               | DL               |
| 11     | 0   | 0   | 0000000000000010 | 0010100000000000 |
| Cuenta | Q_0 | C_f | AL               | DL               |
| 10     | 0   | 0   | 0000000000000001 | 0001010000000000 |
| Cuenta | Q_0 | C_f | AL               | DL               |
| 9      | 0   | 0   | 0000000000000000 | 1000101000000000 |
| Cuenta | Q_0 | C_f | AL               | DL               |
| 8      | 0   | 0   | 0000000000000000 | 0100010100000000 |
| Cuenta | Q_0 | C_f | AL               | DL               |
| 7      | 0   | 0   | 0000000000000000 | 0010001010000000 |
| Cuenta | Q_0 | C_f | AL               | DL               |
| 6      | 0   | 0   | 0000000000000000 | 0001000101000000 |
| Cuenta | Q_0 | C_f | AL               | DL               |
| 5      | 0   | 0   | 0000000000000000 | 0000100010100000 |
| Cuenta | Q_0 | C_f | AL               | DL               |
| 4      | 0   | 0   | 0000000000000000 | 0000010001010000 |
| Cuenta | Q_0 | C_f | AL               | DL               |
| 3      | 0   | 0   | 0000000000000000 | 0000001000101000 |
| Cuenta | Q_0 | C_f | AL               | DL               |
| 2      | 0   | 0   | 0000000000000000 | 0000000100010100 |
| Cuenta | Q_0 | C_f | AL               | DL               |
| 1      | 0   | 0   | 0000000000000000 | 0000000010001010 |

=== Resultado ===
Binario (32 bits): 00000000000000000000000001000101
Decimal: 69
```
### Ejemplo numeros con signo
```
=== Multiplicación con Algoritmo de Booth (max 16 bits) ===
Ingrese el primer número (decimal o binario prefijado con b: ej: b1011): b1011
Ingrese el segundo número (decimal o binario prefijado con b: ej: b1100): -7

--- Valores ingresados ---
A (dec) = 11 | A (bin) = 0000000000001011
B (dec) = -7 | B (bin) = 1111111111111001

====================== Procedimiento ======================
| Cuenta | Q_0 | Q_+ | AL               | DL               |
| 16     | 1   | 0   | 0000000000000000 | 1111111111111001 |
| Cuenta | Q_0 | Q_+ | AL               | DL               |
| 15     | 0   | 1   | 1111111111111010 | 1111111111111100 |
| Cuenta | Q_0 | Q_+ | AL               | DL               |
| 14     | 0   | 0   | 0000000000000010 | 1111111111111110 |
| Cuenta | Q_0 | Q_+ | AL               | DL               |
| 13     | 1   | 0   | 0000000000000001 | 0111111111111111 |
| Cuenta | Q_0 | Q_+ | AL               | DL               |
| 12     | 1   | 1   | 1111111111111011 | 0011111111111111 |
| Cuenta | Q_0 | Q_+ | AL               | DL               |
| 11     | 1   | 1   | 1111111111111101 | 1001111111111111 |
| Cuenta | Q_0 | Q_+ | AL               | DL               |
| 10     | 1   | 1   | 1111111111111110 | 1100111111111111 |
| Cuenta | Q_0 | Q_+ | AL               | DL               |
| 9      | 1   | 1   | 1111111111111111 | 0110011111111111 |
| Cuenta | Q_0 | Q_+ | AL               | DL               |
| 8      | 1   | 1   | 1111111111111111 | 1011001111111111 |
| Cuenta | Q_0 | Q_+ | AL               | DL               |
| 7      | 1   | 1   | 1111111111111111 | 1101100111111111 |
| Cuenta | Q_0 | Q_+ | AL               | DL               |
| 6      | 1   | 1   | 1111111111111111 | 1110110011111111 |
| Cuenta | Q_0 | Q_+ | AL               | DL               |
| 5      | 1   | 1   | 1111111111111111 | 1111011001111111 |
| Cuenta | Q_0 | Q_+ | AL               | DL               |
| 4      | 1   | 1   | 1111111111111111 | 1111101100111111 |
| Cuenta | Q_0 | Q_+ | AL               | DL               |
| 3      | 1   | 1   | 1111111111111111 | 1111110110011111 |
| Cuenta | Q_0 | Q_+ | AL               | DL               |
| 2      | 1   | 1   | 1111111111111111 | 1111111011001111 |
| Cuenta | Q_0 | Q_+ | AL               | DL               |
| 1      | 1   | 1   | 1111111111111111 | 1111111101100111 |

=== Resultado ===
Binario (32 bits): 11111111111111111111111110110011
Decimal: -77
```
