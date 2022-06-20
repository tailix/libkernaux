#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <kernaux/ntoa.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#define VALID_LONG_PREFIX "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
#define TOO_LONG_PREFIX   "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"

static const struct {
    const char *result;
    int base;
    uint64_t value;
} utoa_cases[] = {
    { "0", 2,   0 }, { "0", -2,  0 }, { "0", 'b', 0 }, { "0", 'B', 0 },
    { "0", 3,   0 }, { "0", -3,  0 },
    { "0", 4,   0 }, { "0", -4,  0 },
    { "0", 5,   0 }, { "0", -5,  0 },
    { "0", 6,   0 }, { "0", -6,  0 },
    { "0", 7,   0 }, { "0", -7,  0 },
    { "0", 8,   0 }, { "0", -8,  0 }, { "0", 'o', 0 }, { "0", 'O', 0 },
    { "0", 9,   0 }, { "0", -9,  0 },
    { "0", 10,  0 }, { "0", -10, 0 }, { "0", 'd', 0 }, { "0", 'D', 0 },
    { "0", 11,  0 }, { "0", -11, 0 },
    { "0", 12,  0 }, { "0", -12, 0 },
    { "0", 13,  0 }, { "0", -13, 0 },
    { "0", 14,  0 }, { "0", -14, 0 },
    { "0", 15,  0 }, { "0", -15, 0 },
    { "0", 16,  0 }, { "0", -16, 0 },
    { "0", 'h', 0 }, { "0", 'H', 0 }, { "0", 'x', 0 }, { "0", 'X', 0 },
    { "0", 17,  0 }, { "0", -17, 0 },
    { "0", 18,  0 }, { "0", -18, 0 },
    { "0", 19,  0 }, { "0", -19, 0 },
    { "0", 20,  0 }, { "0", -20, 0 },
    { "0", 21,  0 }, { "0", -21, 0 },
    { "0", 22,  0 }, { "0", -22, 0 },
    { "0", 23,  0 }, { "0", -23, 0 },
    { "0", 24,  0 }, { "0", -24, 0 },
    { "0", 25,  0 }, { "0", -25, 0 },
    { "0", 26,  0 }, { "0", -26, 0 },
    { "0", 27,  0 }, { "0", -27, 0 },
    { "0", 28,  0 }, { "0", -28, 0 },
    { "0", 29,  0 }, { "0", -29, 0 },
    { "0", 30,  0 }, { "0", -30, 0 },
    { "0", 31,  0 }, { "0", -31, 0 },
    { "0", 32,  0 }, { "0", -32, 0 },
    { "0", 33,  0 }, { "0", -33, 0 },
    { "0", 34,  0 }, { "0", -34, 0 },
    { "0", 35,  0 }, { "0", -35, 0 },
    { "0", 36,  0 }, { "0", -36, 0 },
    { "1111011", 2,   123 }, { "1111011", -2,  123 },
    { "1111011", 'b', 123 }, { "1111011", 'B', 123 },
    { "11120",   3,   123 }, { "11120",   -3,  123 },
    { "1323",    4,   123 }, { "1323",    -4,  123 },
    { "443",     5,   123 }, { "443",     -5,  123 },
    { "323",     6,   123 }, { "323",     -6,  123 },
    { "234",     7,   123 }, { "234",     -7,  123 },
    { "173",     8,   123 }, { "173",     -8,  123 },
    { "173",     'o', 123 }, { "173",     'O', 123 },
    { "146",     9,   123 }, { "146",     -9,  123 },
    { "123",     10,  123 }, { "123",     -10, 123 },
    { "123",     'd', 123 }, { "123",     'D', 123 },
    { "102",     11,  123 }, { "102",     -11, 123 },
    { "a3",      12,  123 }, { "A3",      -12, 123 },
    { "96",      13,  123 }, { "96",      -13, 123 },
    { "8b",      14,  123 }, { "8B",      -14, 123 },
    { "83",      15,  123 }, { "83",      -15, 123 },
    { "7b",      16,  123 }, { "7B",      -16, 123 },
    { "7b",      'h', 123 }, { "7B",      'H', 123 },
    { "7b",      'x', 123 }, { "7B",      'X', 123 },
    { "74",      17,  123 }, { "74",      -17, 123 },
    { "6f",      18,  123 }, { "6F",      -18, 123 },
    { "69",      19,  123 }, { "69",      -19, 123 },
    { "63",      20,  123 }, { "63",      -20, 123 },
    { "5i",      21,  123 }, { "5I",      -21, 123 },
    { "5d",      22,  123 }, { "5D",      -22, 123 },
    { "58",      23,  123 }, { "58",      -23, 123 },
    { "53",      24,  123 }, { "53",      -24, 123 },
    { "4n",      25,  123 }, { "4N",      -25, 123 },
    { "4j",      26,  123 }, { "4J",      -26, 123 },
    { "4f",      27,  123 }, { "4F",      -27, 123 },
    { "4b",      28,  123 }, { "4B",      -28, 123 },
    { "47",      29,  123 }, { "47",      -29, 123 },
    { "43",      30,  123 }, { "43",      -30, 123 },
    { "3u",      31,  123 }, { "3U",      -31, 123 },
    { "3r",      32,  123 }, { "3R",      -32, 123 },
    { "3o",      33,  123 }, { "3O",      -33, 123 },
    { "3l",      34,  123 }, { "3L",      -34, 123 },
    { "3i",      35,  123 }, { "3I",      -35, 123 },
    { "3f",      36,  123 }, { "3F",      -36, 123 },
    { "11000000111001", 2,  12345 }, { "11000000111001", -2,  12345 },
    { "121221020",      3,  12345 }, { "121221020",      -3,  12345 },
    { "3000321",        4,  12345 }, { "3000321",        -4,  12345 },
    { "343340",         5,  12345 }, { "343340",         -5,  12345 },
    { "133053",         6,  12345 }, { "133053",         -6,  12345 },
    { "50664",          7,  12345 }, { "50664",          -7,  12345 },
    { "30071",          8,  12345 }, { "30071",          -8,  12345 },
    { "17836",          9,  12345 }, { "17836",          -9,  12345 },
    { "12345",          10, 12345 }, { "12345",          -10, 12345 },
    { "9303",           11, 12345 }, { "9303",           -11, 12345 },
    { "7189",           12, 12345 }, { "7189",           -12, 12345 },
    { "5808",           13, 12345 }, { "5808",           -13, 12345 },
    { "46db",           14, 12345 }, { "46DB",           -14, 12345 },
    { "39d0",           15, 12345 }, { "39D0",           -15, 12345 },
    { "3039",           16, 12345 }, { "3039",           -16, 12345 },
    { "28c3",           17, 12345 }, { "28C3",           -17, 12345 },
    { "221f",           18, 12345 }, { "221F",           -18, 12345 },
    { "1f3e",           19, 12345 }, { "1F3E",           -19, 12345 },
    { "1ah5",           20, 12345 }, { "1AH5",           -20, 12345 },
    { "16ki",           21, 12345 }, { "16KI",           -21, 12345 },
    { "13b3",           22, 12345 }, { "13B3",           -22, 12345 },
    { "107h",           23, 12345 }, { "107H",           -23, 12345 },
    { "la9",            24, 12345 }, { "LA9",            -24, 12345 },
    { "jik",            25, 12345 }, { "JIK",            -25, 12345 },
    { "i6l",            26, 12345 }, { "I6L",            -26, 12345 },
    { "gp6",            27, 12345 }, { "GP6",            -27, 12345 },
    { "fkp",            28, 12345 }, { "FKP",            -28, 12345 },
    { "ejk",            29, 12345 }, { "EJK",            -29, 12345 },
    { "dlf",            30, 12345 }, { "DLF",            -30, 12345 },
    { "cq7",            31, 12345 }, { "CQ7",            -31, 12345 },
    { "c1p",            32, 12345 }, { "C1P",            -32, 12345 },
    { "bb3",            33, 12345 }, { "BB3",            -33, 12345 },
    { "an3",            34, 12345 }, { "AN3",            -34, 12345 },
    { "a2p",            35, 12345 }, { "A2P",            -35, 12345 },
    { "9ix",            36, 12345 }, { "9IX",            -36, 12345 },
};

static const struct {
    uint64_t value;
    const char *result;
} utoa2_cases[] = {
    { 0,                        "0"                                 },
    { 1,                        "1"                                 },
    { 2,                        "10"                                },
    { 3,                        "11"                                },
    { 4,                        "100"                               },
    { 5,                        "101"                               },
    { 6,                        "110"                               },
    { 7,                        "111"                               },
    { 8,                        "1000"                              },
    { UINT16_MAX,               "1111111111111111"                  },
    { UINT16_MAX + 1,           "10000000000000000"                 },
    { UINT32_MAX,               "11111111111111111111111111111111"  },
    { (uint64_t)UINT32_MAX + 1, "100000000000000000000000000000000" },
    { UINT64_MAX - 6,           "1111111111111111111111111111111111111111111111111111111111111001" },
    { UINT64_MAX - 5,           "1111111111111111111111111111111111111111111111111111111111111010" },
    { UINT64_MAX - 1,           "1111111111111111111111111111111111111111111111111111111111111110" },
    { UINT64_MAX,               "1111111111111111111111111111111111111111111111111111111111111111" },
};

static const struct {
    int64_t value;
    const char *result;
} itoa2_cases[] = {
    { 0,                       "0"                                 },
    { 1,                       "1"                                 },
    { -1,                      "-1"                                },
    { 2,                       "10"                                },
    { -2,                      "-10"                               },
    { 3,                       "11"                                },
    { -3,                      "-11"                               },
    { 4,                       "100"                               },
    { -4,                      "-100"                              },
    { 5,                       "101"                               },
    { -5,                      "-101"                              },
    { 6,                       "110"                               },
    { -6,                      "-110"                              },
    { 7,                       "111"                               },
    { -7,                      "-111"                              },
    { 8,                       "1000"                              },
    { -8,                      "-1000"                             },
    { UINT16_MAX,              "1111111111111111"                  },
    { UINT16_MAX + 1,          "10000000000000000"                 },
    { UINT32_MAX,              "11111111111111111111111111111111"  },
    { (int64_t)UINT32_MAX + 1, "100000000000000000000000000000000" },
    { INT64_MAX - 6,           "111111111111111111111111111111111111111111111111111111111111001"   },
    { INT64_MIN + 7,           "-111111111111111111111111111111111111111111111111111111111111001"  },
    { INT64_MAX - 5,           "111111111111111111111111111111111111111111111111111111111111010"   },
    { INT64_MIN + 6,           "-111111111111111111111111111111111111111111111111111111111111010"  },
    { INT64_MAX - 1,           "111111111111111111111111111111111111111111111111111111111111110"   },
    { INT64_MIN + 2,           "-111111111111111111111111111111111111111111111111111111111111110"  },
    { INT64_MAX,               "111111111111111111111111111111111111111111111111111111111111111"   },
    { INT64_MIN + 1,           "-111111111111111111111111111111111111111111111111111111111111111"  },
    { INT64_MIN,               "-1000000000000000000000000000000000000000000000000000000000000000" },
};

static const struct {
    uint64_t value;
    const char *result;
} utoa8_cases[] = {
    { 00,                       "0"                      },
    { 01,                       "1"                      },
    { 02,                       "2"                      },
    { 07,                       "7"                      },
    { 010,                      "10"                     },
    { 011,                      "11"                     },
    { 012,                      "12"                     },
    { 017,                      "17"                     },
    { 020,                      "20"                     },
    { 021,                      "21"                     },
    { 077,                      "77"                     },
    { 0100,                     "100"                    },
    { 0101,                     "101"                    },
    { 0177,                     "177"                    },
    { 0200,                     "200"                    },
    { 0201,                     "201"                    },
    { 0777,                     "777"                    },
    { 01000,                    "1000"                   },
    { 01001,                    "1001"                   },
    { 01777,                    "1777"                   },
    { 02000,                    "2000"                   },
    { 02001,                    "2001"                   },
    { 07777,                    "7777"                   },
    { 010000,                   "10000"                  },
    { 010001,                   "10001"                  },
    { UINT16_MAX,               "177777"                 },
    { UINT16_MAX + 1,           "200000"                 },
    { UINT32_MAX,               "37777777777"            },
    { (uint64_t)UINT32_MAX + 1, "40000000000"            },
    { UINT64_MAX - 6,           "1777777777777777777771" },
    { UINT64_MAX - 5,           "1777777777777777777772" },
    { UINT64_MAX - 1,           "1777777777777777777776" },
    { UINT64_MAX,               "1777777777777777777777" },
};

static const struct {
    int64_t value;
    const char *result;
} itoa8_cases[] = {
    { 00,                       "0"                       },
    { 01,                       "1"                       },
    { -01,                      "-1"                      },
    { 02,                       "2"                       },
    { -02,                      "-2"                      },
    { 07,                       "7"                       },
    { -07,                      "-7"                      },
    { 010,                      "10"                      },
    { -010,                     "-10"                     },
    { 011,                      "11"                      },
    { -011,                     "-11"                     },
    { 012,                      "12"                      },
    { 017,                      "17"                      },
    { 020,                      "20"                      },
    { 021,                      "21"                      },
    { 077,                      "77"                      },
    { 0100,                     "100"                     },
    { 0101,                     "101"                     },
    { 0177,                     "177"                     },
    { 0200,                     "200"                     },
    { 0201,                     "201"                     },
    { 0777,                     "777"                     },
    { 01000,                    "1000"                    },
    { 01001,                    "1001"                    },
    { 01777,                    "1777"                    },
    { 02000,                    "2000"                    },
    { 02001,                    "2001"                    },
    { 07777,                    "7777"                    },
    { 010000,                   "10000"                   },
    { 010001,                   "10001"                   },
    { UINT16_MAX,               "177777"                  },
    { UINT16_MAX + 1,           "200000"                  },
    { UINT32_MAX,               "37777777777"             },
    { (uint64_t)UINT32_MAX + 1, "40000000000"             },
    { INT64_MAX - 6,            "777777777777777777771"   },
    { INT64_MIN + 7,            "-777777777777777777771"  },
    { INT64_MAX - 5,            "777777777777777777772"   },
    { INT64_MIN + 6,            "-777777777777777777772"  },
    { INT64_MAX - 1,            "777777777777777777776"   },
    { INT64_MIN + 2,            "-777777777777777777776"  },
    { INT64_MAX,                "777777777777777777777"   },
    { INT64_MIN + 1,            "-777777777777777777777"  },
    { INT64_MIN,                "-1000000000000000000000" },
};

static const struct {
    uint64_t value;
    const char *result;
} utoa10_cases[] = {
    { 0,                        "0" },
    { 1,                        "1" },
    { 2,                        "2" },
    { 9,                        "9" },
    { 10,                       "10" },
    { 11,                       "11" },
    { 12,                       "12" },
    { 19,                       "19" },
    { 20,                       "20" },
    { 21,                       "21" },
    { 99,                       "99" },
    { 100,                      "100" },
    { 101,                      "101" },
    { 199,                      "199" },
    { 200,                      "200" },
    { 201,                      "201" },
    { 999,                      "999" },
    { 1000,                     "1000" },
    { 1001,                     "1001" },
    { 1999,                     "1999" },
    { 2000,                     "2000" },
    { 2001,                     "2001" },
    { 9999,                     "9999" },
    { 10000,                    "10000" },
    { 10001,                    "10001" },
    { UINT16_MAX,               "65535" },
    { UINT16_MAX + 1,           "65536" },
    { UINT32_MAX,               "4294967295" },
    { (uint64_t)UINT32_MAX + 1, "4294967296" },
    { UINT64_MAX - 6,           "18446744073709551609" },
    { UINT64_MAX - 5,           "18446744073709551610" },
    { UINT64_MAX - 1,           "18446744073709551614" },
    { UINT64_MAX,               "18446744073709551615" },
};

static const struct {
    int64_t value;
    const char *result;
} itoa10_cases[] = {
    { 0,                       "0" },
    { 1,                       "1" },
    { -1,                      "-1" },
    { 2,                       "2" },
    { -2,                      "-2" },
    { 9,                       "9" },
    { -9,                      "-9" },
    { 10,                      "10" },
    { -10,                     "-10" },
    { 11,                      "11" },
    { -11,                     "-11" },
    { 12,                      "12" },
    { 19,                      "19" },
    { 20,                      "20" },
    { 21,                      "21" },
    { 99,                      "99" },
    { 100,                     "100" },
    { 101,                     "101" },
    { 199,                     "199" },
    { 200,                     "200" },
    { 201,                     "201" },
    { 999,                     "999" },
    { 1000,                    "1000" },
    { 1001,                    "1001" },
    { 1999,                    "1999" },
    { 2000,                    "2000" },
    { 2001,                    "2001" },
    { 9999,                    "9999" },
    { 10000,                   "10000" },
    { 10001,                   "10001" },
    { UINT16_MAX,              "65535" },
    { UINT16_MAX + 1,          "65536" },
    { UINT32_MAX,              "4294967295" },
    { (int64_t)UINT32_MAX + 1, "4294967296" },
    { INT64_MAX - 8,           "9223372036854775799" },
    { INT64_MIN + 9,           "-9223372036854775799" },
    { INT64_MAX - 7,           "9223372036854775800" },
    { INT64_MIN + 8,           "-9223372036854775800" },
    { INT64_MAX - 1,           "9223372036854775806" },
    { INT64_MIN + 1,           "-9223372036854775807" },
    { INT64_MAX,               "9223372036854775807" },
    { INT64_MIN,               "-9223372036854775808" },
};

static const struct {
    uint64_t value;
    const char *result;
} utoa16_cases[] = {
    { 0x0,   "0"   }, { 0x1,   "1"   },
    { 0x2,   "2"   }, { 0x9,   "9"   },
    { 0xa,   "a"   }, { 0xb,   "b"   },
    { 0xc,   "c"   }, { 0xd,   "d"   },
    { 0xe,   "e"   }, { 0xf,   "f"   },
    { 0x10,  "10"  }, { 0x11,  "11"  },
    { 0x12,  "12"  }, { 0x19,  "19"  },
    { 0x1a,  "1a"  }, { 0x1b,  "1b"  },
    { 0x1c,  "1c"  }, { 0x1d,  "1d"  },
    { 0x1e,  "1e"  }, { 0x1f,  "1f"  },
    { 0x20,  "20"  }, { 0x21,  "21"  },
    { 0x22,  "22"  }, { 0x29,  "29"  },
    { 0x2a,  "2a"  }, { 0x2b,  "2b"  },
    { 0x2c,  "2c"  }, { 0x2d,  "2d"  },
    { 0x2e,  "2e"  }, { 0x2f,  "2f"  },
    { 0x90,  "90"  }, { 0x91,  "91"  },
    { 0x92,  "92"  }, { 0x99,  "99"  },
    { 0x9a,  "9a"  }, { 0x9b,  "9b"  },
    { 0x9c,  "9c"  }, { 0x9d,  "9d"  },
    { 0x9e,  "9e"  }, { 0x9f,  "9f"  },
    { 0xa0,  "a0"  }, { 0xa1,  "a1"  },
    { 0xa2,  "a2"  }, { 0xa9,  "a9"  },
    { 0xaa,  "aa"  }, { 0xab,  "ab"  },
    { 0xac,  "ac"  }, { 0xad,  "ad"  },
    { 0xae,  "ae"  }, { 0xaf,  "af"  },
    { 0xb0,  "b0"  }, { 0xb1,  "b1"  },
    { 0xb2,  "b2"  }, { 0xb9,  "b9"  },
    { 0xba,  "ba"  }, { 0xbb,  "bb"  },
    { 0xbc,  "bc"  }, { 0xbd,  "bd"  },
    { 0xbe,  "be"  }, { 0xbf,  "bf"  },
    { 0xc0,  "c0"  }, { 0xc1,  "c1"  },
    { 0xc2,  "c2"  }, { 0xc9,  "c9"  },
    { 0xca,  "ca"  }, { 0xcb,  "cb"  },
    { 0xcc,  "cc"  }, { 0xcd,  "cd"  },
    { 0xce,  "ce"  }, { 0xcf,  "cf"  },
    { 0xd0,  "d0"  }, { 0xd1,  "d1"  },
    { 0xd2,  "d2"  }, { 0xd9,  "d9"  },
    { 0xda,  "da"  }, { 0xdb,  "db"  },
    { 0xdc,  "dc"  }, { 0xdd,  "dd"  },
    { 0xde,  "de"  }, { 0xdf,  "df"  },
    { 0xe0,  "e0"  }, { 0xe1,  "e1"  },
    { 0xe2,  "e2"  }, { 0xe9,  "e9"  },
    { 0xea,  "ea"  }, { 0xeb,  "eb"  },
    { 0xec,  "ec"  }, { 0xed,  "ed"  },
    { 0xee,  "ee"  }, { 0xef,  "ef"  },
    { 0xf0,  "f0"  }, { 0xf1,  "f1"  },
    { 0xf2,  "f2"  }, { 0xf9,  "f9"  },
    { 0xfa,  "fa"  }, { 0xfb,  "fb"  },
    { 0xfc,  "fc"  }, { 0xfd,  "fd"  },
    { 0xfe,  "fe"  }, { 0xff,  "ff"  },
    { 0x100, "100" }, { 0x101, "101" },
    { 0x109, "109" }, { 0x10a, "10a" },
    { 0x10f, "10f" },
    { 0x110, "110" }, { 0x111, "111" },
    { 0x119, "119" }, { 0x11a, "11a" },
    { 0x11f, "11f" }, { 0x120, "120" },
    { 0x1ff, "1ff" }, { 0x200, "200" },
    { 0xfff, "fff" }, { 0x1000, "1000" },
    { UINT16_MAX,               "ffff" },
    { UINT16_MAX + 1,           "10000" },
    { UINT32_MAX,               "ffffffff" },
    { (uint64_t)UINT32_MAX + 1, "100000000" },
    { UINT64_MAX - 6,           "fffffffffffffff9" },
    { UINT64_MAX - 5,           "fffffffffffffffa" },
    { UINT64_MAX - 1,           "fffffffffffffffe" },
    { UINT64_MAX,               "ffffffffffffffff" },
};

static const struct {
    int64_t value;
    const char *result;
} itoa16_cases[] = {
    { 0x0,   "0"   }, { 0x1,   "1"   },
    { 0x2,   "2"   }, { 0x9,   "9"   },
    { 0xa,   "a"   }, { 0xb,   "b"   },
    { 0xc,   "c"   }, { 0xd,   "d"   },
    { 0xe,   "e"   }, { 0xf,   "f"   },
    { 0x10,  "10"  }, { 0x11,  "11"  },
    { 0x12,  "12"  }, { 0x19,  "19"  },
    { 0x1a,  "1a"  }, { 0x1b,  "1b"  },
    { 0x1c,  "1c"  }, { 0x1d,  "1d"  },
    { 0x1e,  "1e"  }, { 0x1f,  "1f"  },
    { 0x20,  "20"  }, { 0x21,  "21"  },
    { 0x22,  "22"  }, { 0x29,  "29"  },
    { 0x2a,  "2a"  }, { 0x2b,  "2b"  },
    { 0x2c,  "2c"  }, { 0x2d,  "2d"  },
    { 0x2e,  "2e"  }, { 0x2f,  "2f"  },
    { 0x90,  "90"  }, { 0x91,  "91"  },
    { 0x92,  "92"  }, { 0x99,  "99"  },
    { 0x9a,  "9a"  }, { 0x9b,  "9b"  },
    { 0x9c,  "9c"  }, { 0x9d,  "9d"  },
    { 0x9e,  "9e"  }, { 0x9f,  "9f"  },
    { 0xa0,  "a0"  }, { 0xa1,  "a1"  },
    { 0xa2,  "a2"  }, { 0xa9,  "a9"  },
    { 0xaa,  "aa"  }, { 0xab,  "ab"  },
    { 0xac,  "ac"  }, { 0xad,  "ad"  },
    { 0xae,  "ae"  }, { 0xaf,  "af"  },
    { 0xb0,  "b0"  }, { 0xb1,  "b1"  },
    { 0xb2,  "b2"  }, { 0xb9,  "b9"  },
    { 0xba,  "ba"  }, { 0xbb,  "bb"  },
    { 0xbc,  "bc"  }, { 0xbd,  "bd"  },
    { 0xbe,  "be"  }, { 0xbf,  "bf"  },
    { 0xc0,  "c0"  }, { 0xc1,  "c1"  },
    { 0xc2,  "c2"  }, { 0xc9,  "c9"  },
    { 0xca,  "ca"  }, { 0xcb,  "cb"  },
    { 0xcc,  "cc"  }, { 0xcd,  "cd"  },
    { 0xce,  "ce"  }, { 0xcf,  "cf"  },
    { 0xd0,  "d0"  }, { 0xd1,  "d1"  },
    { 0xd2,  "d2"  }, { 0xd9,  "d9"  },
    { 0xda,  "da"  }, { 0xdb,  "db"  },
    { 0xdc,  "dc"  }, { 0xdd,  "dd"  },
    { 0xde,  "de"  }, { 0xdf,  "df"  },
    { 0xe0,  "e0"  }, { 0xe1,  "e1"  },
    { 0xe2,  "e2"  }, { 0xe9,  "e9"  },
    { 0xea,  "ea"  }, { 0xeb,  "eb"  },
    { 0xec,  "ec"  }, { 0xed,  "ed"  },
    { 0xee,  "ee"  }, { 0xef,  "ef"  },
    { 0xf0,  "f0"  }, { 0xf1,  "f1"  },
    { 0xf2,  "f2"  }, { 0xf9,  "f9"  },
    { 0xfa,  "fa"  }, { 0xfb,  "fb"  },
    { 0xfc,  "fc"  }, { 0xfd,  "fd"  },
    { 0xfe,  "fe"  }, { 0xff,  "ff"  },
    { 0x100, "100" }, { 0x101, "101" },
    { 0x109, "109" }, { 0x10a, "10a" },
    { 0x10f, "10f" },
    { 0x110, "110" }, { 0x111, "111" },
    { 0x119, "119" }, { 0x11a, "11a" },
    { 0x11f, "11f" }, { 0x120, "120" },
    { 0x1ff, "1ff" }, { 0x200, "200" },
    { 0xfff, "fff" }, { 0x1000, "1000" },
    { UINT16_MAX,               "ffff" },
    { UINT16_MAX + 1,           "10000" },
    { UINT32_MAX,               "ffffffff" },
    { (uint64_t)UINT32_MAX + 1, "100000000" },
    { INT64_MIN + 7,            "-7ffffffffffffff9" },
    { INT64_MAX - 6,            "7ffffffffffffff9" },
    { INT64_MIN + 6,            "-7ffffffffffffffa" },
    { INT64_MAX - 5,            "7ffffffffffffffa" },
    { INT64_MIN + 2,            "-7ffffffffffffffe" },
    { INT64_MAX - 1,            "7ffffffffffffffe" },
    { INT64_MIN + 1,            "-7fffffffffffffff" },
    { INT64_MAX,                "7fffffffffffffff" },
    { INT64_MIN,                "-8000000000000000" },
};

static const char *str_end(const char *str)
{
    for (;; ++str) if (*str == '\0') return str;
}

void test_main()
{
    {
        char buffer[KERNAUX_UTOA_MIN_BUFFER_SIZE + 3];

        for (
            size_t index = 0;
            index < sizeof(utoa_cases) / sizeof(utoa_cases[0]);
            ++index
        ) {
            const char *const end1 = kernaux_utoa(
                utoa_cases[index].value,
                buffer,
                utoa_cases[index].base,
                NULL
            );
            assert(strcmp(buffer, utoa_cases[index].result) == 0);
            assert(end1 == str_end(buffer));

            const char *const end2 = kernaux_utoa(
                utoa_cases[index].value,
                buffer,
                utoa_cases[index].base,
                ""
            );
            assert(strcmp(buffer, utoa_cases[index].result) == 0);
            assert(end2 == str_end(buffer));

            const char *const end3 = kernaux_utoa(
                utoa_cases[index].value,
                buffer,
                utoa_cases[index].base,
                "foo"
            );
            assert(strncmp(buffer, "foo", 3) == 0);
            assert(strcmp(&buffer[3], utoa_cases[index].result) == 0);
            assert(end3 == str_end(buffer));
        }
    }

    {
        char buffer[KERNAUX_ITOA_MIN_BUFFER_SIZE + 3];

        for (
            size_t index = 0;
            index < sizeof(utoa_cases) / sizeof(utoa_cases[0]);
            ++index
        ) {
            if (utoa_cases[index].value > (uint64_t)INT64_MAX) continue;

            const int64_t value = utoa_cases[index].value;
            const int base = utoa_cases[index].base;

            const char *const end1 = kernaux_itoa(value, buffer, base, NULL);
            assert(strcmp(buffer, utoa_cases[index].result) == 0);
            assert(end1 == str_end(buffer));

            const char *const end2 = kernaux_itoa(value, buffer, base, "");
            assert(strcmp(buffer, utoa_cases[index].result) == 0);
            assert(end2 == str_end(buffer));

            const char *const end3 = kernaux_itoa(value, buffer, base, "foo");
            assert(strncmp(buffer, "foo", 3) == 0);
            assert(strcmp(&buffer[3], utoa_cases[index].result) == 0);
            assert(end3 == str_end(buffer));

            if (value <= 0 || base < 2 || base > 36) continue;

            const char *const end4 = kernaux_itoa(-value, buffer, base, NULL);
            assert(buffer[0] == '-');
            assert(strcmp(&buffer[1], utoa_cases[index].result) == 0);
            assert(end4 == str_end(buffer));

            const char *const end5 = kernaux_itoa(-value, buffer, base, "");
            assert(buffer[0] == '-');
            assert(strcmp(&buffer[1], utoa_cases[index].result) == 0);
            assert(end5 == str_end(buffer));

            const char *const end6 = kernaux_itoa(-value, buffer, base, "foo");
            assert(strncmp(buffer, "-foo", 4) == 0);
            assert(strcmp(&buffer[4], utoa_cases[index].result) == 0);
            assert(end6 == str_end(buffer));
        }
    }

    {
        char buffer[KERNAUX_UTOA2_BUFFER_SIZE];

        for (
            size_t index = 0;
            index < sizeof(utoa2_cases) / sizeof(utoa2_cases[0]);
            ++index
        ) {
            const char *const end1 =
                kernaux_utoa2(utoa2_cases[index].value, buffer);
            assert(strncmp(buffer, "0b", 2) == 0);
            assert(strcmp(&buffer[2], utoa2_cases[index].result) == 0);
            assert(end1 == str_end(buffer));
        }
    }

    {
        char buffer[KERNAUX_ITOA2_BUFFER_SIZE];

        for (
            size_t index = 0;
            index < sizeof(itoa2_cases) / sizeof(itoa2_cases[0]);
            ++index
        ) {
            const int64_t value = itoa2_cases[index].value;

            const char *const end1 = kernaux_itoa2(value, buffer);
            if (value >= 0) {
                assert(strncmp(buffer, "0b", 2) == 0);
                assert(strcmp(&buffer[2], itoa2_cases[index].result) == 0);
            } else {
                assert(strncmp(buffer, "-0b", 3) == 0);
                assert(strcmp(&buffer[3], &itoa2_cases[index].result[1]) == 0);
            }
            assert(end1 == str_end(buffer));

            if (value <= 0) continue;

            const char *const end2 = kernaux_itoa2(-value, buffer);
            assert(strncmp(buffer, "-0b", 3) == 0);
            assert(strcmp(&buffer[3], itoa2_cases[index].result) == 0);
            assert(end2 == str_end(buffer));
        }
    }

    {
        char buffer[KERNAUX_UTOA8_BUFFER_SIZE];

        for (
            size_t index = 0;
            index < sizeof(utoa8_cases) / sizeof(utoa8_cases[0]);
            ++index
        ) {
            const char *const end1 =
                kernaux_utoa8(utoa8_cases[index].value, buffer);
            assert(strncmp(buffer, "0o", 2) == 0);
            assert(strcmp(&buffer[2], utoa8_cases[index].result) == 0);
            assert(end1 == str_end(buffer));
        }
    }

    {
        char buffer[KERNAUX_ITOA8_BUFFER_SIZE];

        for (
            size_t index = 0;
            index < sizeof(itoa8_cases) / sizeof(itoa8_cases[0]);
            ++index
        ) {
            const int64_t value = itoa8_cases[index].value;

            const char *const end1 = kernaux_itoa8(value, buffer);
            if (value >= 0) {
                assert(strncmp(buffer, "0o", 2) == 0);
                assert(strcmp(&buffer[2], itoa8_cases[index].result) == 0);
            } else {
                assert(strncmp(buffer, "-0o", 3) == 0);
                assert(strcmp(&buffer[3], &itoa8_cases[index].result[1]) == 0);
            }
            assert(end1 == str_end(buffer));

            if (value <= 0) continue;

            const char *const end2 = kernaux_itoa8(-value, buffer);
            assert(strncmp(buffer, "-0o", 3) == 0);
            assert(strcmp(&buffer[3], itoa8_cases[index].result) == 0);
            assert(end2 == str_end(buffer));
        }
    }

    {
        char buffer[KERNAUX_UTOA10_BUFFER_SIZE];

        for (
            size_t index = 0;
            index < sizeof(utoa10_cases) / sizeof(utoa10_cases[0]);
            ++index
        ) {
            const char *const end1 =
                kernaux_utoa10(utoa10_cases[index].value, buffer);
            assert(strcmp(buffer, utoa10_cases[index].result) == 0);
            assert(end1 == str_end(buffer));
        }
    }

    {
        char buffer[KERNAUX_ITOA10_BUFFER_SIZE];

        for (
            size_t index = 0;
            index < sizeof(itoa10_cases) / sizeof(itoa10_cases[0]);
            ++index
        ) {
            const int64_t value = itoa10_cases[index].value;

            const char *const end1 = kernaux_itoa10(value, buffer);
            assert(strcmp(buffer, itoa10_cases[index].result) == 0);
            assert(end1 == str_end(buffer));

            if (value <= 0) continue;

            const char *const end2 = kernaux_itoa10(-value, buffer);
            assert(buffer[0] == '-');
            assert(strcmp(&buffer[1], itoa10_cases[index].result) == 0);
            assert(end2 == str_end(buffer));
        }
    }

    {
        char buffer[KERNAUX_UTOA16_BUFFER_SIZE];

        for (
            size_t index = 0;
            index < sizeof(utoa16_cases) / sizeof(utoa16_cases[0]);
            ++index
        ) {
            const char *const end1 =
                kernaux_utoa16(utoa16_cases[index].value, buffer);
            assert(strncmp(buffer, "0x", 2) == 0);
            assert(strcmp(&buffer[2], utoa16_cases[index].result) == 0);
            assert(end1 == str_end(buffer));
        }
    }

    {
        char buffer[KERNAUX_ITOA16_BUFFER_SIZE];

        for (
            size_t index = 0;
            index < sizeof(itoa16_cases) / sizeof(itoa16_cases[0]);
            ++index
        ) {
            const int64_t value = itoa16_cases[index].value;

            const char *const end1 = kernaux_itoa16(value, buffer);
            if (value >= 0) {
                assert(strncmp(buffer, "0x", 2) == 0);
                assert(strcmp(&buffer[2], itoa16_cases[index].result) == 0);
            } else {
                assert(strncmp(buffer, "-0x", 3) == 0);
                assert(strcmp(&buffer[3], &itoa16_cases[index].result[1]) == 0);
            }
            assert(end1 == str_end(buffer));

            if (value <= 0) continue;

            const char *const end2 = kernaux_itoa16(-value, buffer);
            assert(strncmp(buffer, "-0x", 3) == 0);
            assert(strcmp(&buffer[3], itoa16_cases[index].result) == 0);
            assert(end2 == str_end(buffer));
        }
    }
}
