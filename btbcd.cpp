#include "bcd.h"
#include <bitset>
#include <iostream>
#include <string>
#include <sys/types.h>

const u_int BITS = 16;

Bcd *convert_bits_to_bcd(std::bitset<16> bits) {
std::cout << "\n============ Procedimiento =============\n";
  Bcd *bcd = new Bcd();

  if (bits.to_ulong() < 10) {
    bcd->unidad = bits.to_ulong();
    return bcd;
  }

  int i{15};

  while (i >= 0) {
    bcd->update(bits[i]);
    i--;
  }

  return bcd;
}

std::bitset<16> convert_bcd_to_bits(Bcd bcd) {
  uint decimal{};

  decimal += bcd.unidad.to_ulong();
  decimal += bcd.decena.to_ulong() * 10;
  decimal += bcd.centena.to_ulong() * 100;
  decimal += bcd.u_mil.to_ulong() * 1000;
  decimal += bcd.d_mil.to_ulong() * 10000;

  return std::bitset<16>(decimal);
}

u_long binToDec(const std::string &bin) {
    return std::bitset<BITS>(bin).to_ulong();
}

std::bitset<BITS> decToBin(int num) {
    return std::bitset<BITS> (num);
}

int main() {
  int decision{};

  std::cout << "=== [1] Convertir de decimal/binario a BCD (max 16 bits) ===\n";
  std::cout << "=== [2] Convertir de BCD en formato BCD a decimal/binario (max 16 bits) ===\n";

  std::cout << "[opcion 1 por defecto]: ";
  std::cin >> decision;

  if (decision != 2) {
    std::string input;
    std::cout << "=== Conversor de decimal/binario a formato BCD (max 16 "
                 "bits) ===\n";
    std::cout
        << "Ingrese el numero a convertir (decimal o binario [ej: b1011]): ";

    std::cin >> input;

    u_long number{};

    if (input[0] == 'b') {
        number = binToDec(input.substr(1));
    } else {
        number = std::stoi(input);
    }

    Bcd *bcd = convert_bits_to_bcd(decToBin(number));

    std::cout << "\nDECIMAL: " << number << '\n';
    std::cout << "BINARY:  " << decToBin(number) << '\n';
    std::cout << "BCD:     " << bcd->to_string() << '\n';

  } else {
    std::cout << "=== Conversor de formato BCD a decimal/binario (max 16 "
                 "bits) ===\n";

    std::cout << "Ingrese cada dígito BCD (4 bits)\n";

    std::string unidad_input, decena_input, centena_input, unidad_m_input, decena_m_input;

    std::cout << "Unidad: ";
    std::cin >> unidad_input;
    std::bitset<4> u(unidad_input);

    std::cout << "Decena: ";
    std::cin >> decena_input;
    std::bitset<4> d(decena_input);

    std::cout << "Centena: ";
    std::cin >> centena_input;
    std::bitset<4> c(centena_input);

    std::cout << "Unidad de mil: ";
    std::cin >> unidad_m_input;
    std::bitset<4> u_m(unidad_m_input);

    std::cout << "Decena de mil: ";
    std::cin >> decena_m_input;
    std::bitset<4> d_m(decena_m_input);

    Bcd bcd(u, d, c, u_m, d_m);

    std::cout << "\nBCD: " << bcd.to_string() << '\n';
    std::cout << "DECIMAL: " << convert_bcd_to_bits(bcd).to_ulong() << '\n';
    std::cout << "BINARY:  " << convert_bcd_to_bits(bcd).to_string() << '\n';
  }

  return 0;
}
