def polynomial_multiply(multiplier_a, multiplier_b):
    tmp = [0] * 64
    res = 0
    for i in range(64):
        tmp[i] = (multiplier_a << i) * ((multiplier_b >> i) & 1)
        res ^= tmp[i]
    return res


def find_highest_bit(value):
    i = 0
    while value != 0:
        i += 1
        value >>= 1
    return i


def polynomial_divide(numerator, denominator):
    quotient = 0
    tmp = numerator
    bit_count = find_highest_bit(tmp) - find_highest_bit(denominator)
    while bit_count >= 0:
        quotient |= (1 << bit_count)
        tmp ^= (denominator << bit_count)
        bit_count = find_highest_bit(tmp) - find_highest_bit(denominator)
    remainder = tmp
    return quotient, remainder


def reverse(x, bits):
    bin_x = bin(x)[2:].rjust(bits, '0')
    re_bin_x = bin_x[::-1]
    return int(re_bin_x, 2)


cipher = [0xBC8FF26D43536296, 0x520100780530EE16, 0x4DC0B5EA935F08EC, 0x342B90AFD853F450, 0x8B250EBCAA2C3681, 0x55759F81A2C68AE4]

res = b""
for a in cipher:
    d = 0xb0004b7679fa26b3  
    rr = reverse(a, 64)  
    rd = reverse((1 << 64) + d, 65)
    q, r = polynomial_divide(rr << 64, rd)
    r = reverse(r, 64)
    for i in range(8):
        res += bytes([r & 0xff])
        r >>= 8
print(res.decode())
