#include <cstdint>
#include <ios>
#include <iostream>
#include <bitset>
#include <string>
#include <cmath>
#include <sys/types.h>
#include <iomanip>
using namespace std;

const int BITS = 16;

template <size_t N>
long long bitsetToDecimal(const std::bitset<N>& bits) {
    // Si el MSB es 0 → es positivo
    if (bits[N - 1] == 0) {
        return static_cast<long long>(bits.to_ullong());
    }

    // Si es negativo (complemento a 2)
    std::bitset<N> temp = bits;

    // Invertir bits
    temp.flip();

    // Sumar 1
    unsigned long long magnitude = temp.to_ullong() + 1;

    // Convertir a negativo
    return -static_cast<long long>(magnitude);
}

int16_t toSigned(const std::bitset<16>& b) {
    return static_cast<int16_t>(b.to_ulong());
}

std::bitset<16> toBitset(int16_t x) {
    return std::bitset<16>(static_cast<uint16_t>(x));
}

std::bitset<16> subtract(const std::bitset<16>& a, const std::bitset<16>& b) {
    int16_t sa = toSigned(a);
    int16_t sb = toSigned(b);
    int16_t result = sa - sb;
    return toBitset(result);
}

bool fullAdder(bool b1, bool b2, bool &carry) {
  bool sum = (b1 ^ b2) ^ carry;
  carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
  return sum;
}

std::bitset<17> bitsetAdd(std::bitset<16> x, std::bitset<16> y) {
  bool carry{};
  std::bitset<17> ans;

  for (int i{}; i < 16; i++) {
    ans[i] = fullAdder(x[i], y[i], carry);
  }

  ans[16] = carry;

  return ans;
}

// Convierte binario string → entero con signo (2's complement)
int binToDec(const string &bin) {
    bitset<BITS> b(bin);
    // Si MSB = 1 → número negativo
    if (b[BITS - 1] == 1)
        return -((int)((~b).to_ulong() + 1));
    return (int)b.to_ulong();
}

// Convierte entero → binario string de 16 bits (2's complement)
std::bitset<BITS> decToBin(int num) {
    bitset<BITS> b;
    if (num < 0) {
        int pos = (abs(num) ^ ((1 << BITS) - 1)) + 1;
        b = bitset<BITS>(pos);
    } else {
        b = bitset<BITS>(num);
    }
    return b;
}

std::bitset<32> unsigned_booth_multiply(std::bitset<16> m, std::bitset<16> q) {
    uint count{16};
    bool cf{0};
    std::bitset<16> al{0};
    std::bitset<16> dl(q);

    std::cout << std::left << std::setw(60) << "====================== Procedimiento ======================\n";

    while (count > 0) {
        bool q_0 = q[16 - count];

        std::cout << std::left << "| " << std::setw(6) << "Cuenta"
        << " | " << std::setw(3) << "Q_0"
        << " | " << std::setw(3) << "C_f"
        << " | " << std::setw(16) << "AL"
        << " | " << std::setw(16) << "DL"
        << " |\n";

        std::cout << std::left << "| " << std::setw(6) << count
        << " | " << std::setw(3) << q_0
        << " | " << std::setw(3) << cf
        << " | " << std::setw(16) << al.to_string()
        << " | " << std::setw(16) << dl.to_string()
        << " |\n";

        if (q_0 == 1) {
            std::bitset<17> add(bitsetAdd(al, m));
            al = std::bitset<16>(add.to_ulong());
            cf = add[16];
        }
        dl = dl >> 1;
        dl[15] = al[0];

        al = al >> 1;
        al[15] = cf;

        cf = 0;

        --count;
    }

    uint32_t result =
    (static_cast<uint32_t>(al.to_ulong()) << 16) |
    static_cast<uint32_t>(dl.to_ulong());

    return std::bitset<32>(result);
}

std::bitset<32> signed_booth_multiply(std::bitset<16>m, std::bitset<16> q) {
    uint count{16};
    std::bitset<16> al{0};
    bool q_plus{0};
    std::bitset<16> dl(q);

    std::cout << std::left << std::setw(60) << "=================== Procedimiento ===================\n";

    while (count > 0) {
        bool q_0 = dl[0];

        std::cout << std::left << "| " << std::setw(6) << "Cuenta"
        << " | " << std::setw(3) << "Q_0"
        << " | " << std::setw(16) << "AL"
        << " | " << std::setw(16) << "DL"
        << " |\n";

        std::cout << std::left << "| " << std::setw(6) << count
        << " | " << std::setw(3) << q_0
        << " | " << std::setw(16) << al.to_string()
        << " | " << std::setw(16) << dl.to_string()
        << " |\n";

        if (q_0 > q_plus) {
            al = subtract(al, m);
        } else if (q_0 < q_plus) {
            std::bitset<17> add(bitsetAdd(al, m));
            al = std::bitset<16>(add.to_ulong());
        }

        q_plus = dl[0];
        dl = dl >> 1;
        dl[15] = al[0];

        al = al >> 1;
        al[15] = al[14];

        --count;
    }

    uint32_t result =
    (static_cast<uint32_t>(al.to_ulong()) << 16) |
    static_cast<uint32_t>(dl.to_ulong());

    return std::bitset<32>(result);
}
// Algoritmo de Booth
string boothMultiply(int multiplicand, int multiplier) {
    bitset<BITS> A(multiplicand);   // A
    bitset<BITS> S(-multiplicand); // -A
    bitset<BITS + BITS> P;         // [A | Q | Q-1]

    // Inicializar P
    for (int i = 0; i < BITS; i++)
        P[i + BITS] = (multiplier >> (BITS - 1 - i)) & 1;

    int Qm1 = 0;

    for (int i = 0; i < BITS; i++) {
        int Q0 = P[0];

        if (Q0 == 0 && Qm1 == 1) {
            // Suma A
            bitset<BITS + BITS> temp(A.to_ullong());
            temp <<= BITS;
            P = bitset<BITS + BITS>(P.to_ullong() + temp.to_ullong());
        }
        else if (Q0 == 1 && Qm1 == 0) {
            // Resta A → suma S
            bitset<BITS + BITS> temp(S.to_ullong());
            temp <<= BITS;
            P = bitset<BITS + BITS>(P.to_ullong() + temp.to_ullong());
        }

        // Guardar Q-1
        Qm1 = Q0;

        // Desplazamiento aritmético a la derecha
        bool msb = P[BITS + BITS - 1];
        P >>= 1;
        P[BITS + BITS - 1] = msb;
    }

    return P.to_string();
}

int main() {
    string inputA, inputB;
    int a, b;

    cout << "=== Multiplicación con Algoritmo de Booth (max 16 bits) ===" << endl;
    cout << "Ingrese el primer número (decimal o binario prefijado con b: ej: b1011): ";
    cin >> inputA;

    cout << "Ingrese el segundo número (decimal o binario prefijado con b: ej: b1100): ";
    cin >> inputB;

    // Procesar entradas
    if (inputA[0] == 'b') {
        a = binToDec(inputA.substr(1));
    }
    else
        a = stoi(inputA);
    if (inputB[0] == 'b')
        b = binToDec(inputB.substr(1));
    else
        b = stoi(inputB);

    // Mostrar en ambas representaciones
    cout << "\n--- Valores ingresados ---\n";
    cout << "A (dec) = " << a << " | A (bin) = " << decToBin(a).to_string() << '\n';
    cout << "B (dec) = " << b << " | B (bin) = " << decToBin(b).to_string() << "\n\n";

    std::bitset<32> result;
    if (a < 0 || b < 0) {
        result = signed_booth_multiply(decToBin(a), decToBin(b));
    } else {
        result = unsigned_booth_multiply(decToBin(a), decToBin(b));
    }

    std::cout << "Resultado parcial: " << result << '\n';

    // Ejecutar Booth
    string resultBin = boothMultiply(a, b);

    // Convertir resultado final a decimal (32 bits posibles)
    long resultDec = stoll(resultBin, nullptr, 2);
    if (resultBin[0] == '1') {
        // Es negativo (2's complement)
        resultDec = resultDec - (1LL << 32);
    }

    cout << "\n=== Resultado ===\n";
    cout << "Binario (32 bits): " << result.to_string() << '\n';
    cout << "Decimal: " << bitsetToDecimal(result) << '\n';

    return 0;
}
