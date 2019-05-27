/*
    File:    mur128m_scaner_keyword_table.cpp
    Author:  Chikmarev Ilya
*/

#include "../include/mur128m_scaner_keyword_table.h"

namespace mur128m_scanner{
  const trans_table::Elem<Lexem_code> keywords_jump_table[] = {
    {const_cast<char32_t*>(U""),      Lexem_code::Id,            0}, // 0: b
    {const_cast<char32_t*>(U"p"),     Lexem_code::Id,            1}, // 1: bp

    {const_cast<char32_t*>(U"bdn"),   Lexem_code::Id,            2}, // 2: a...
    {const_cast<char32_t*>(U"s"),     Lexem_code::Id,            3}, // 3: ab...
    {const_cast<char32_t*>(U"d"),     Lexem_code::Id,            4}, // 4: ad...
    {const_cast<char32_t*>(U"d"),     Lexem_code::Id,            5}, // 5: an...
    {const_cast<char32_t*>(U"f"),     Lexem_code::Id,            6}, // 6: abs...
    {const_cast<char32_t*>(U"fi"),    Lexem_code::Id,            7}, // 7: add...
    {const_cast<char32_t*>(U"n"),     Lexem_code::Id,            8}, // 8: and
    {const_cast<char32_t*>(U""),      Lexem_code::Id,            0}, // 9: absf
    {const_cast<char32_t*>(U""),      Lexem_code::Id,            0}, // 10: addf
    {const_cast<char32_t*>(U""),      Lexem_code::Id,            0}, // 11: addi
    {const_cast<char32_t*>(U""),      Lexem_code::Id,            0}, // 12: andn

    {const_cast<char32_t*>(U"ahmo"),  Lexem_code::Id,           13}, // 13: c
    {const_cast<char32_t*>(U"l"),     Lexem_code::Id,                 14}, // 14: ca
    {const_cast<char32_t*>(U"as"),    Lexem_code::Id,                15}, // 15: ch
    {const_cast<char32_t*>(U"p"),     Lexem_code::Id,                 16}, // 16: cm
    {const_cast<char32_t*>(U"m"),     Lexem_code::Id,                 17}, // 17: co
    {const_cast<char32_t*>(U"l"),     Lexem_code::Id,                 18}, // 18: call
    {const_cast<char32_t*>(U"r"),     Lexem_code::Id,                 19}, // 19: ca
    {const_cast<char32_t*>(U"f"),     Lexem_code::Id,                 20}, // 20: ca
    {const_cast<char32_t*>(U"fi"),    Lexem_code::Id,                21}, // 21: ca
    {const_cast<char32_t*>(U"p"),     Lexem_code::Id,                 22}, // 22: ca
    {const_cast<char32_t*>(U"glprs"), Lexem_code::Id,             23}, // 23: ca
    {const_cast<char32_t*>(U""),   	  Lexem_code::Id,                   0}, // 24: ca
    {const_cast<char32_t*>(U""),      Lexem_code::Id,                   0}, // 25: ca
    {const_cast<char32_t*>(U""),      Lexem_code::Id,                   0}, // 26: ca
    {const_cast<char32_t*>(U"su"),    Lexem_code::Id,                27}, // 27: ca
    {const_cast<char32_t*>(U"l"),     Lexem_code::Id,                 28}, // 28: ca
    {const_cast<char32_t*>(U"r"),     Lexem_code::Id,                   29}, // 29: ca
    {const_cast<char32_t*>(U""),      Lexem_code::Id,                   0}, // 30: ca
    {const_cast<char32_t*>(U"r"),     Lexem_code::Id,                   31}, // 31: ca
    {const_cast<char32_t*>(U"e"),     Lexem_code::Id,                   32}, // 32: ca
    {const_cast<char32_t*>(U"z"),     Lexem_code::Id,                   33}, // 33: ca
    {const_cast<char32_t*>(U"e"),     Lexem_code::Id,                   34}, // 34: ca
    {const_cast<char32_t*>(U"r"),     Lexem_code::Id,                   42}, // 35: ca
    {const_cast<char32_t*>(U"r"),     Lexem_code::Id,                   43}, // 36: ca
    {const_cast<char32_t*>(U""),      Lexem_code::Id,                   0}, // 37: ca
    {const_cast<char32_t*>(U"x"),     Lexem_code::Id,                   45}, // 38: ca
    {const_cast<char32_t*>(U""),      Lexem_code::Id,                     0}, // 39: ca
    {const_cast<char32_t*>(U""),      Lexem_code::Id,                   0}, // 40: ca
    {const_cast<char32_t*>(U""),      Lexem_code::Id,                   0}, // 41: ca
    {const_cast<char32_t*>(U"x"),     Lexem_code::Id,                   48}, // 42: ca
    {const_cast<char32_t*>(U"1368"),  Lexem_code::Id,                49}, // 43: ca
    {const_cast<char32_t*>(U"4"),     Lexem_code::Id,                50}, // 44: ca
    {const_cast<char32_t*>(U"2"),     Lexem_code::Id,                51}, // 45: ca
    {const_cast<char32_t*>(U"0"),     Lexem_code::Id,                52}, // 46: ca
    {const_cast<char32_t*>(U"2"),     Lexem_code::Id,                53}, // 47: ca
    {const_cast<char32_t*>(U"8"),     Lexem_code::Id,                53}, // 48: ca
    {const_cast<char32_t*>(U""),      Lexem_code::Id,                0}, // 49: ca
    {const_cast<char32_t*>(U""),      Lexem_code::Id,                0}, // 50: ca
    {const_cast<char32_t*>(U""),      Lexem_code::Id,                0}, // 51: ca
    {const_cast<char32_t*>(U""),      Lexem_code::Id,                0}, // 52: ca

    {const_cast<char32_t*>(U"i"),     Lexem_code::Id,           59}, // 53: d
    {const_cast<char32_t*>(U"v"),     Lexem_code::Id,           60}, // 54: d
    {const_cast<char32_t*>(U"fim"),   Lexem_code::Id,           61}, // 55: d
    {const_cast<char32_t*>(U""),      Lexem_code::Id,            0}, // 56: d
    {const_cast<char32_t*>(U"su"),    Lexem_code::Id,           63}, // 57: d
    {const_cast<char32_t*>(U"o"),     Lexem_code::Id,           64}, // 58: d
    {const_cast<char32_t*>(U""),      Lexem_code::Id,           0}, // 59: d
    {const_cast<char32_t*>(U""),      Lexem_code::Id,           0}, // 60: d
    {const_cast<char32_t*>(U"d"),     Lexem_code::Id,           67}, // 61: d
    {const_cast<char32_t*>(U"i"),     Lexem_code::Id,           68}, // 62: d
    {const_cast<char32_t*>(U"su"),    Lexem_code::Id,           69}, // 63: d
    {const_cast<char32_t*>(U""),      Lexem_code::Id,           0}, // 64: d
    {const_cast<char32_t*>(U""),      Lexem_code::Id,           0}, // 65: d

    {const_cast<char32_t*>(U"lr"),    Lexem_code::Id,           72}, // 66: f
    {const_cast<char32_t*>(U"do"),    Lexem_code::Id,           73}, // 67: f
    {const_cast<char32_t*>(U"a"),     Lexem_code::Id,           74}, // 68: f
    {const_cast<char32_t*>(U"z1"),    Lexem_code::Id,           75}, // 69: f
    {const_cast<char32_t*>(U"a"),     Lexem_code::Id,           76}, // 70: f
    {const_cast<char32_t*>(U"c"),     Lexem_code::Id,           77}, // 71: f
    {const_cast<char32_t*>(U""),      Lexem_code::Id,           0}, // 72: f
    {const_cast<char32_t*>(U""),      Lexem_code::Id,           0}, // 73: f
    {const_cast<char32_t*>(U"t"),     Lexem_code::Id,           80}, // 74: f
    {const_cast<char32_t*>(U""),      Lexem_code::Id,           0}, // 75: f
    {const_cast<char32_t*>(U"1368"),  Lexem_code::Id,           82}, // 76: f
    {const_cast<char32_t*>(U"2"),     Lexem_code::Id,           83}, // 77: f
    {const_cast<char32_t*>(U"2"),     Lexem_code::Id,           84}, // 78: f
    {const_cast<char32_t*>(U"6"),     Lexem_code::Id,           85}, // 79: f
    {const_cast<char32_t*>(U"0"),     Lexem_code::Id,           86}, // 80: f
    {const_cast<char32_t*>(U"8"),     Lexem_code::Id,           87}, // 81: f
    {const_cast<char32_t*>(U""),      Lexem_code::Id,           0}, // 82: f
    {const_cast<char32_t*>(U""),      Lexem_code::Id,             0}, // 83: f
    {const_cast<char32_t*>(U""),      Lexem_code::Id,           0}, // 84: f
    {const_cast<char32_t*>(U""),      Lexem_code::Id,           0}, // 85: f

    {const_cast<char32_t*>(U"m"),   Lexem_code::Id,           92}, // 86: j
    {const_cast<char32_t*>(U"p"),   Lexem_code::Id,           93}, // 87: j
    {const_cast<char32_t*>(U"glnprsz"),   Lexem_code::Id,     94}, // 88: j
    {const_cast<char32_t*>(U"r"),   Lexem_code::Id,           95}, // 89: j
    {const_cast<char32_t*>(U"e"),   Lexem_code::Id,           96}, // 90: j
    {const_cast<char32_t*>(U"e"),   Lexem_code::Id,           97}, // 91: j
    {const_cast<char32_t*>(U""),   Lexem_code::Id,             0}, // 92: j
    {const_cast<char32_t*>(U"z"),   Lexem_code::Id,           99}, // 93: j
    {const_cast<char32_t*>(U"r"),   Lexem_code::Id,           100}, // 94: j
    {const_cast<char32_t*>(U"r"),   Lexem_code::Id,           101}, // 95: j
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 96: j
    {const_cast<char32_t*>(U"r"),   Lexem_code::Id,           103}, // 97: j
    {const_cast<char32_t*>(U"r"),   Lexem_code::Id,           104}, // 98: j
    {const_cast<char32_t*>(U"r"),   Lexem_code::Id,           105}, // 99: j
    {const_cast<char32_t*>(U""),   Lexem_code::Id,            0}, // 100: j
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 101: j
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 102: j
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 103: j
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 104: j
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 105: j

    {const_cast<char32_t*>(U"n"),   Lexem_code::Id,           111}, // 106: i
    {const_cast<char32_t*>(U"t"),   Lexem_code::Id,           112}, // 107: i
    {const_cast<char32_t*>(U"1368"),   Lexem_code::Id,        113}, // 108: i
    {const_cast<char32_t*>(U""),   Lexem_code::Id,              0}, // 109: i
    {const_cast<char32_t*>(U"26"),   Lexem_code::Id,           115}, // 110: i
    {const_cast<char32_t*>(U"2"),   Lexem_code::Id,            116}, // 111: i
    {const_cast<char32_t*>(U"4"),   Lexem_code::Id,            117}, // 112: i
    {const_cast<char32_t*>(U"2"),   Lexem_code::Id,           118}, // 113: i
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 114: i
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 115: i
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 116: i
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 117: i

    {const_cast<char32_t*>(U"i"),   Lexem_code::Id,           123}, // 118: u
    {const_cast<char32_t*>(U"n"),   Lexem_code::Id,           124}, // 119: u
    {const_cast<char32_t*>(U"t"),   Lexem_code::Id,           125}, // 120: u
    {const_cast<char32_t*>(U"1368"),   Lexem_code::Id,        126}, // 121: u
    {const_cast<char32_t*>(U""),   Lexem_code::Id,              0}, // 121: u
    {const_cast<char32_t*>(U"26"),   Lexem_code::Id,           128}, // 123: u
    {const_cast<char32_t*>(U"2"),   Lexem_code::Id,            129}, // 124: u
    {const_cast<char32_t*>(U"4"),   Lexem_code::Id,            130}, // 125: u
    {const_cast<char32_t*>(U"2"),   Lexem_code::Id,           131}, // 126: u
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 127: u
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 128: u
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 129: u
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 130: u

    {const_cast<char32_t*>(U"r"),   Lexem_code::Id,           136}, // 131: o
    {const_cast<char32_t*>(U"n"),   Lexem_code::Id,           137}, // 132: o
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 133: o

    {const_cast<char32_t*>(U"o"),   Lexem_code::Id,           139}, // 134: x
    {const_cast<char32_t*>(U"r"),   Lexem_code::Id,           140}, // 135: x
    {const_cast<char32_t*>(U"n"),   Lexem_code::Id,           141}, // 136: x
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 137: x

    {const_cast<char32_t*>(U"s"),   Lexem_code::Id,           143}, // 138: l
    {const_cast<char32_t*>(U"h"),   Lexem_code::Id,           144}, // 139: l
    {const_cast<char32_t*>(U"i"),   Lexem_code::Id,           145}, // 140: l
    {const_cast<char32_t*>(U"f"),   Lexem_code::Id,           146}, // 141: l
    {const_cast<char32_t*>(U"t"),   Lexem_code::Id,           147}, // 142: l
    {const_cast<char32_t*>(U"s"),   Lexem_code::Id,           148}, // 143: l
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 144: l

    {const_cast<char32_t*>(U"o"),   Lexem_code::Id,           150}, // 145: n
    {const_cast<char32_t*>(U"t"),   Lexem_code::Id,           151}, // 146: n
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 147: n

    {const_cast<char32_t*>(U"r"),   Lexem_code::Id,           153}, // 148: t
    {const_cast<char32_t*>(U"a"),   Lexem_code::Id,           154}, // 149: t
    {const_cast<char32_t*>(U"p"),   Lexem_code::Id,           155}, // 150: t
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 151: t

    {const_cast<char32_t*>(U"eos"),   Lexem_code::Id,           157}, // 152: r
    {const_cast<char32_t*>(U"u"),   Lexem_code::Id,           158}, // 153: r
    {const_cast<char32_t*>(U"t"),   Lexem_code::Id,           159}, // 154: r
    {const_cast<char32_t*>(U"h"),   Lexem_code::Id,           160}, // 155: r
    {const_cast<char32_t*>(U"n"),   Lexem_code::Id,           161}, // 156: r
    {const_cast<char32_t*>(U"agilnps"),   Lexem_code::Id,           162}, // 157: r
    {const_cast<char32_t*>(U"i"),   Lexem_code::Id,           163}, // 158: r
    {const_cast<char32_t*>(U"d"),   Lexem_code::Id,           164}, // 159: r
    {const_cast<char32_t*>(U"glnps"),   Lexem_code::Id,           164}, // 160: r
    {const_cast<char32_t*>(U"z"),   Lexem_code::Id,           165}, // 161: r
    {const_cast<char32_t*>(U"e"),   Lexem_code::Id,           166}, // 162: r
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 163: r
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 164: r
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 165: r
    {const_cast<char32_t*>(U"e"),   Lexem_code::Id,           171}, // 166: r
    {const_cast<char32_t*>(U"f"),   Lexem_code::Id,           172}, // 167: r
    {const_cast<char32_t*>(U"ghlt"),   Lexem_code::Id,           173}, // 168: r
    {const_cast<char32_t*>(U"f"),   Lexem_code::Id,           172}, // 169: r
    {const_cast<char32_t*>(U"e"),   Lexem_code::Id,           174}, // 170: r
    {const_cast<char32_t*>(U"e"),   Lexem_code::Id,           175}, // 171: r
    {const_cast<char32_t*>(U"z"),   Lexem_code::Id,           176}, // 172: r
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 173: r
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 174: r
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 175: r
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 176: r
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 177: r
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 178: r
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 179: r
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 180: r
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 181: r
    {const_cast<char32_t*>(U"s"),   Lexem_code::Id,           187}, // 182: r
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 183: r

    {const_cast<char32_t*>(U"t"),   Lexem_code::Id,           189}, // 184: s
    {const_cast<char32_t*>(U"r"),   Lexem_code::Id,           190}, // 185: s
    {const_cast<char32_t*>(U"i"),   Lexem_code::Id,           191}, // 186: s
    {const_cast<char32_t*>(U"n"),   Lexem_code::Id,           192}, // 187: s
    {const_cast<char32_t*>(U"g"),   Lexem_code::Id,           193}, // 188: s
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 189: s

    {const_cast<char32_t*>(U"ou"),   Lexem_code::Id,           195}, // 190: p
    {const_cast<char32_t*>(U"s"),   Lexem_code::Id,           196}, // 191: p
    {const_cast<char32_t*>(U"p"),   Lexem_code::Id,           197}, // 192: p
    {const_cast<char32_t*>(U"h"),   Lexem_code::Id,           198}, // 193: p
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 194: p
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 195: p

    {const_cast<char32_t*>(U"ou"),   Lexem_code::Id,           201}, // 196: m
    {const_cast<char32_t*>(U"v"),   Lexem_code::Id,           202}, // 197: m
    {const_cast<char32_t*>(U"l"),   Lexem_code::Id,           203}, // 198: m
    {const_cast<char32_t*>(U"1368us"),   Lexem_code::Id,           204}, // 199: m
    {const_cast<char32_t*>(U"2i"),   Lexem_code::Id,           205}, // 200: m
    {const_cast<char32_t*>(U"6"),   Lexem_code::Id,           206}, // 201: m
    {const_cast<char32_t*>(U"2"),   Lexem_code::Id,           207}, // 202: m
    {const_cast<char32_t*>(U"4"),   Lexem_code::Id,           208}, // 203: m
    {const_cast<char32_t*>(U"0us"),   Lexem_code::Id,           209}, // 204: m
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 205: m
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 206: m
    {const_cast<char32_t*>(U"f"),   Lexem_code::Id,           212}, // 207: m
    {const_cast<char32_t*>(U"us"),   Lexem_code::Id,           213}, // 208: m
    {const_cast<char32_t*>(U"us"),   Lexem_code::Id,           214}, // 209: m
    {const_cast<char32_t*>(U"fus"),   Lexem_code::Id,           215}, // 210: m
    {const_cast<char32_t*>(U"fus"),   Lexem_code::Id,           216}, // 211: m
    {const_cast<char32_t*>(U"f"),   Lexem_code::Id,           217}, // 212: m
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 213: m
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 214: m
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 215: m
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 216: m
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 217: m
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 218: m
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 219: m
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 220: m
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 221: m
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 222: m
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 223: m
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 224: m
    {const_cast<char32_t*>(U""),   Lexem_code::Id,           0}, // 225: m
    {const_cast<char32_t*>(U""),   Lexem_code::Id,            0}, // 226: m

  };
};
