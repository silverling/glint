#include "index.h"

const ImWchar32 fontawesome_solid_glyph_ranges[] = {
    0xE005,  0xE006,  0xE00D,  0xE00D,  0xE012,  0xE012,  0xE03F,  0xE041,  0xE059,  0xE076,  0xE085,  0xE086,  0xE097,
    0xE098,  0xE09A,  0xE09A,  0xE0A9,  0xE0A9,  0xE0AC,  0xE0AC,  0xE0B4,  0xE0B4,  0xE0B7,  0xE0B7,  0xE0BB,  0xE0BB,
    0xE0CF,  0xE0CF,  0xE0D8,  0xE0D8,  0xE0DF,  0xE0DF,  0xE0E3,  0xE0E4,  0xE131,  0xE131,  0xE139,  0xE13C,  0xE140,
    0xE140,  0xE152,  0xE152,  0xE163,  0xE163,  0xE169,  0xE169,  0xE16D,  0xE16D,  0xE17B,  0xE17B,  0xE184,  0xE185,
    0xE18F,  0xE18F,  0xE19A,  0xE19B,  0xE1A8,  0xE1A8,  0xE1B0,  0xE1B0,  0xE1BC,  0xE1BC,  0xE1C4,  0xE1C4,  0xE1C8,
    0xE1C8,  0xE1D3,  0xE1D3,  0xE1D5,  0xE1D5,  0xE1D7,  0xE1D7,  0xE1ED,  0xE1ED,  0xE1F3,  0xE1F3,  0xE1F6,  0xE1F6,
    0xE1FE,  0xE1FE,  0xE209,  0xE209,  0xE221,  0xE222,  0xE22D,  0xE22D,  0xE23D,  0xE23D,  0xE289,  0xE289,  0xE29C,
    0xE29C,  0xE2B7,  0xE2B7,  0xE2BB,  0xE2BB,  0xE2C5,  0xE2C5,  0xE2CA,  0xE2CA,  0xE2CD,  0xE2CE,  0xE2E6,  0xE2E6,
    0xE2EB,  0xE2EB,  0xE31E,  0xE31E,  0xE3AF,  0xE3AF,  0xE3B1,  0xE3B2,  0xE3F5,  0xE3F5,  0xE43C,  0xE43C,  0xE445,
    0xE445,  0xE447,  0xE448,  0xE46C,  0xE46C,  0xE473,  0xE473,  0xE476,  0xE477,  0xE47A,  0xE47B,  0xE490,  0xE490,
    0xE494,  0xE494,  0xE4A5,  0xE4A5,  0xE4A8,  0xE4AD,  0xE4AF,  0xE4B0,  0xE4B3,  0xE4B3,  0xE4B5,  0xE4CC,  0xE4CE,
    0xE4DE,  0xE4E0,  0xE4E6,  0xE4E8,  0xE4EB,  0xE4ED,  0xE503,  0xE507,  0xE525,  0xE527,  0xE52F,  0xE532,  0xE54F,
    0xE551,  0xE558,  0xE55A,  0xE56F,  0xE571,  0xE574,  0xE576,  0xE587,  0xE589,  0xE58F,  0xE591,  0xE59A,  0xE59C,
    0xE59D,  0xE5A0,  0xE5A1,  0xE5A9,  0xE5AA,  0xE5AF,  0xE5AF,  0xE5B4,  0xE5B4,  0xE678,  0xE678,  0xE67A,  0xE67A,
    0xE682,  0xE682,  0xE68F,  0xE68F,  0xE691,  0xE691,  0xE695,  0xE69B,  0xF000,  0xF00E,  0xF010,  0xF01E,  0xF021,
    0xF03E,  0xF040,  0xF04E,  0xF050,  0xF05E,  0xF060,  0xF06E,  0xF070,  0xF07E,  0xF080,  0xF080,  0xF083,  0xF08B,
    0xF08D,  0xF08E,  0xF090,  0xF091,  0xF093,  0xF098,  0xF09C,  0xF09E,  0xF0A0,  0xF0AE,  0xF0B0,  0xF0B2,  0xF0C0,
    0xF0CE,  0xF0D0,  0xF0D1,  0xF0D6,  0xF0DE,  0xF0E0,  0xF0E0,  0xF0E2,  0xF0EE,  0xF0F0,  0xF0FE,  0xF100,  0xF10E,
    0xF110,  0xF112,  0xF114,  0xF115,  0xF118,  0xF11E,  0xF120,  0xF12E,  0xF130,  0xF135,  0xF137,  0xF13A,  0xF13D,
    0xF13E,  0xF140,  0xF14E,  0xF150,  0xF159,  0xF15B,  0xF15E,  0xF160,  0xF165,  0xF175,  0xF178,  0xF182,  0xF183,
    0xF185,  0xF188,  0xF18E,  0xF18E,  0xF190,  0xF193,  0xF195,  0xF197,  0xF199,  0xF199,  0xF19C,  0xF19D,  0xF1AB,
    0xF1AE,  0xF1B0,  0xF1B3,  0xF1B8,  0xF1BB,  0xF1C0,  0xF1C9,  0xF1CD,  0xF1CE,  0xF1D8,  0xF1DE,  0xF1E0,  0xF1E6,
    0xF1EA,  0xF1EC,  0xF1F6,  0xF1FE,  0xF200,  0xF201,  0xF204,  0xF207,  0xF20A,  0xF20B,  0xF217,  0xF21E,  0xF221,
    0xF22D,  0xF233,  0xF236,  0xF238,  0xF239,  0xF240,  0xF24A,  0xF24D,  0xF24E,  0xF250,  0xF25D,  0xF26C,  0xF26C,
    0xF271,  0xF27B,  0xF283,  0xF283,  0xF28B,  0xF28E,  0xF290,  0xF292,  0xF295,  0xF295,  0xF29A,  0xF29A,  0xF29C,
    0xF29E,  0xF2A0,  0xF2A4,  0xF2A7,  0xF2A8,  0xF2B4,  0xF2B7,  0xF2B9,  0xF2BE,  0xF2C0,  0xF2C3,  0xF2C7,  0xF2CE,
    0xF2D0,  0xF2D4,  0xF2DB,  0xF2DC,  0xF2E5,  0xF2E5,  0xF2E7,  0xF2E7,  0xF2EA,  0xF2EA,  0xF2ED,  0xF2ED,  0xF2F1,
    0xF2F2,  0xF2F5,  0xF2F6,  0xF2F9,  0xF2F9,  0xF2FE,  0xF2FE,  0xF302,  0xF305,  0xF309,  0xF30C,  0xF31C,  0xF31C,
    0xF31E,  0xF31E,  0xF328,  0xF328,  0xF332,  0xF332,  0xF337,  0xF338,  0xF358,  0xF35B,  0xF35D,  0xF35D,  0xF360,
    0xF360,  0xF362,  0xF363,  0xF381,  0xF382,  0xF386,  0xF387,  0xF390,  0xF390,  0xF3A5,  0xF3A5,  0xF3BE,  0xF3BF,
    0xF3C1,  0xF3C1,  0xF3C5,  0xF3C5,  0xF3C9,  0xF3C9,  0xF3CD,  0xF3CF,  0xF3D1,  0xF3D1,  0xF3DD,  0xF3DD,  0xF3E0,
    0xF3E0,  0xF3E5,  0xF3E5,  0xF3ED,  0xF3ED,  0xF3FA,  0xF3FB,  0xF3FD,  0xF3FD,  0xF3FF,  0xF3FF,  0xF406,  0xF406,
    0xF410,  0xF410,  0xF422,  0xF422,  0xF424,  0xF425,  0xF432,  0xF434,  0xF436,  0xF436,  0xF439,  0xF43A,  0xF43C,
    0xF43C,  0xF43F,  0xF43F,  0xF441,  0xF441,  0xF443,  0xF443,  0xF445,  0xF445,  0xF447,  0xF447,  0xF44B,  0xF44B,
    0xF44E,  0xF44E,  0xF450,  0xF450,  0xF453,  0xF453,  0xF458,  0xF458,  0xF45C,  0xF45D,  0xF45F,  0xF45F,  0xF461,
    0xF462,  0xF466,  0xF466,  0xF468,  0xF46D,  0xF470,  0xF472,  0xF474,  0xF474,  0xF477,  0xF479,  0xF47D,  0xF47F,
    0xF481,  0xF482,  0xF484,  0xF487,  0xF48B,  0xF48B,  0xF48D,  0xF48E,  0xF490,  0xF494,  0xF496,  0xF497,  0xF49E,
    0xF49E,  0xF4A1,  0xF4A1,  0xF4AD,  0xF4AD,  0xF4B3,  0xF4B3,  0xF4B8,  0xF4BA,  0xF4BD,  0xF4BE,  0xF4C0,  0xF4C2,
    0xF4C4,  0xF4C4,  0xF4C6,  0xF4C6,  0xF4CD,  0xF4CE,  0xF4D3,  0xF4D3,  0xF4D6,  0xF4DB,  0xF4DE,  0xF4DF,  0xF4E2,
    0xF4E3,  0xF4E6,  0xF4E6,  0xF4FA,  0xF509,  0xF515,  0xF591,  0xF593,  0xF59D,  0xF59F,  0xF5A2,  0xF5A4,  0xF5A7,
    0xF5AA,  0xF5B1,  0xF5B3,  0xF5B4,  0xF5B6,  0xF5B8,  0xF5BA,  0xF5BD,  0xF5BF,  0xF5C5,  0xF5C7,  0xF5CB,  0xF5CD,
    0xF5CE,  0xF5D0,  0xF5D2,  0xF5D7,  0xF5D7,  0xF5DA,  0xF5DA,  0xF5DC,  0xF5DC,  0xF5DE,  0xF5DF,  0xF5E1,  0xF5E1,
    0xF5E4,  0xF5E4,  0xF5E7,  0xF5E7,  0xF5EB,  0xF5EB,  0xF5EE,  0xF5EE,  0xF5FC,  0xF5FD,  0xF601,  0xF601,  0xF604,
    0xF604,  0xF610,  0xF610,  0xF613,  0xF613,  0xF619,  0xF619,  0xF61F,  0xF61F,  0xF621,  0xF621,  0xF624,  0xF625,
    0xF629,  0xF62A,  0xF62E,  0xF630,  0xF637,  0xF637,  0xF63B,  0xF63C,  0xF641,  0xF641,  0xF644,  0xF644,  0xF647,
    0xF647,  0xF64A,  0xF64A,  0xF64F,  0xF64F,  0xF651,  0xF651,  0xF653,  0xF655,  0xF658,  0xF658,  0xF65D,  0xF65E,
    0xF662,  0xF662,  0xF664,  0xF666,  0xF669,  0xF66B,  0xF66D,  0xF66D,  0xF66F,  0xF66F,  0xF674,  0xF674,  0xF676,
    0xF676,  0xF678,  0xF679,  0xF67B,  0xF67C,  0xF67F,  0xF67F,  0xF681,  0xF684,  0xF687,  0xF689,  0xF696,  0xF696,
    0xF698,  0xF69B,  0xF6A0,  0xF6A1,  0xF6A7,  0xF6A7,  0xF6A9,  0xF6A9,  0xF6AD,  0xF6AD,  0xF6B6,  0xF6B7,  0xF6BB,
    0xF6BB,  0xF6BE,  0xF6BE,  0xF6C0,  0xF6C0,  0xF6C3,  0xF6C4,  0xF6C8,  0xF6C8,  0xF6CF,  0xF6CF,  0xF6D1,  0xF6D1,
    0xF6D3,  0xF6D3,  0xF6D5,  0xF6D5,  0xF6D7,  0xF6D7,  0xF6D9,  0xF6D9,  0xF6DD,  0xF6DE,  0xF6E2,  0xF6E3,  0xF6E6,
    0xF6E6,  0xF6E8,  0xF6E8,  0xF6EC,  0xF6ED,  0xF6F0,  0xF6F2,  0xF6FA,  0xF6FA,  0xF6FC,  0xF6FC,  0xF6FF,  0xF700,
    0xF70B,  0xF70C,  0xF70E,  0xF70E,  0xF714,  0xF715,  0xF717,  0xF717,  0xF71E,  0xF71E,  0xF722,  0xF722,  0xF728,
    0xF729,  0xF72B,  0xF72B,  0xF72E,  0xF72F,  0xF73B,  0xF73D,  0xF740,  0xF740,  0xF743,  0xF743,  0xF747,  0xF747,
    0xF74D,  0xF74D,  0xF751,  0xF753,  0xF756,  0xF756,  0xF75A,  0xF75B,  0xF75E,  0xF75F,  0xF769,  0xF769,  0xF76B,
    0xF76C,  0xF76F,  0xF770,  0xF772,  0xF773,  0xF77C,  0xF77D,  0xF780,  0xF781,  0xF783,  0xF784,  0xF786,  0xF788,
    0xF78C,  0xF78C,  0xF793,  0xF794,  0xF796,  0xF796,  0xF79C,  0xF79C,  0xF79F,  0xF7A0,  0xF7A2,  0xF7A2,  0xF7A4,
    0xF7A6,  0xF7A9,  0xF7AB,  0xF7AD,  0xF7AE,  0xF7B5,  0xF7B6,  0xF7B9,  0xF7BA,  0xF7BD,  0xF7BD,  0xF7BF,  0xF7C0,
    0xF7C2,  0xF7C2,  0xF7C4,  0xF7C5,  0xF7C9,  0xF7CA,  0xF7CC,  0xF7CE,  0xF7D0,  0xF7D0,  0xF7D2,  0xF7D2,  0xF7D7,
    0xF7DA,  0xF7E4,  0xF7E6,  0xF7EC,  0xF7EC,  0xF7EF,  0xF7EF,  0xF7F2,  0xF7F3,  0xF7F5,  0xF7F5,  0xF7F7,  0xF7F7,
    0xF7FA,  0xF7FB,  0xF802,  0xF802,  0xF805,  0xF807,  0xF80A,  0xF80D,  0xF80F,  0xF810,  0xF812,  0xF812,  0xF815,
    0xF816,  0xF818,  0xF818,  0xF81D,  0xF81D,  0xF827,  0xF82A,  0xF82F,  0xF82F,  0xF83E,  0xF83E,  0xF84A,  0xF84A,
    0xF84C,  0xF84C,  0xF850,  0xF850,  0xF853,  0xF853,  0xF85E,  0xF85E,  0xF863,  0xF863,  0xF86D,  0xF86D,  0xF879,
    0xF879,  0xF87B,  0xF87D,  0xF881,  0xF882,  0xF884,  0xF887,  0xF891,  0xF891,  0xF897,  0xF897,  0xF8C0,  0xF8C1,
    0xF8CC,  0xF8CC,  0xF8D7,  0xF8D7,  0xF8D9,  0xF8D9,  0xF8E5,  0xF8E5,  0xF8EF,  0xF8EF,  0xF8FF,  0xF8FF,  0x1F17F,
    0x1F17F, 0x1F308, 0x1F308, 0x1F30B, 0x1F30B, 0x1F30D, 0x1F310, 0x1F319, 0x1F319, 0x1F321, 0x1F321, 0x1F326, 0x1F327,
    0x1F329, 0x1F32A, 0x1F32D, 0x1F32D, 0x1F331, 0x1F332, 0x1F336, 0x1F336, 0x1F34B, 0x1F34B, 0x1F34E, 0x1F34F, 0x1F368,
    0x1F368, 0x1F36A, 0x1F36A, 0x1F374, 0x1F374, 0x1F377, 0x1F378, 0x1F381, 0x1F382, 0x1F393, 0x1F393, 0x1F397, 0x1F397,
    0x1F399, 0x1F399, 0x1F39E, 0x1F39F, 0x1F3A7, 0x1F3A8, 0x1F3AD, 0x1F3AD, 0x1F3B2, 0x1F3B2, 0x1F3B5, 0x1F3B5, 0x1F3C0,
    0x1F3C3, 0x1F3C5, 0x1F3C6, 0x1F3C8, 0x1F3C8, 0x1F3CA, 0x1F3CA, 0x1F3CD, 0x1F3CD, 0x1F3D0, 0x1F3D0, 0x1F3D3, 0x1F3D4,
    0x1F3D6, 0x1F3D6, 0x1F3D9, 0x1F3D9, 0x1F3DB, 0x1F3DB, 0x1F3E0, 0x1F3E0, 0x1F3E2, 0x1F3E2, 0x1F3E5, 0x1F3E5, 0x1F3E8,
    0x1F3E8, 0x1F3EB, 0x1F3EB, 0x1F3F4, 0x1F3F4, 0x1F3F7, 0x1F3F7, 0x1F404, 0x1F404, 0x1F408, 0x1F409, 0x1F40E, 0x1F40E,
    0x1F415, 0x1F415, 0x1F41F, 0x1F41F, 0x1F441, 0x1F441, 0x1F44D, 0x1F44E, 0x1F451, 0x1F451, 0x1F455, 0x1F455, 0x1F464,
    0x1F465, 0x1F47B, 0x1F47B, 0x1F480, 0x1F480, 0x1F489, 0x1F489, 0x1F48E, 0x1F48E, 0x1F494, 0x1F494, 0x1F499, 0x1F49C,
    0x1F4A1, 0x1F4A1, 0x1F4A3, 0x1F4A3, 0x1F4A7, 0x1F4A7, 0x1F4A9, 0x1F4A9, 0x1F4AC, 0x1F4AC, 0x1F4B0, 0x1F4B0, 0x1F4B2,
    0x1F4B3, 0x1F4BB, 0x1F4BC, 0x1F4BE, 0x1F4C2, 0x1F4C4, 0x1F4C6, 0x1F4CB, 0x1F4CF, 0x1F4D4, 0x1F4D4, 0x1F4D6, 0x1F4D6,
    0x1F4DC, 0x1F4E2, 0x1F4E6, 0x1F4E6, 0x1F4F0, 0x1F4F1, 0x1F4F6, 0x1F4F7, 0x1F4FB, 0x1F4FB, 0x1F500, 0x1F501, 0x1F504,
    0x1F504, 0x1F508, 0x1F508, 0x1F50A, 0x1F50D, 0x1F511, 0x1F518, 0x1F525, 0x1F525, 0x1F527, 0x1F528, 0x1F52C, 0x1F52C,
    0x1F534, 0x1F535, 0x1F547, 0x1F547, 0x1F549, 0x1F54E, 0x1F553, 0x1F553, 0x1F56B, 0x1F56B, 0x1F56E, 0x1F56E, 0x1F571,
    0x1F571, 0x1F575, 0x1F575, 0x1F577, 0x1F577, 0x1F57B, 0x1F57B, 0x1F57D, 0x1F57D, 0x1F582, 0x1F582, 0x1F588, 0x1F588,
    0x1F58A, 0x1F58C, 0x1F595, 0x1F596, 0x1F5A4, 0x1F5A5, 0x1F5A8, 0x1F5AA, 0x1F5B1, 0x1F5B1, 0x1F5B4, 0x1F5B4, 0x1F5B6,
    0x1F5B9, 0x1F5BB, 0x1F5BB, 0x1F5BF, 0x1F5BF, 0x1F5C1, 0x1F5C1, 0x1F5CB, 0x1F5CB, 0x1F5CE, 0x1F5CE, 0x1F5D5, 0x1F5D6,
    0x1F5D8, 0x1F5D9, 0x1F5E9, 0x1F5EA, 0x1F5FA, 0x1F5FA, 0x1F600, 0x1F606, 0x1F609, 0x1F60A, 0x1F60D, 0x1F60D, 0x1F610,
    0x1F610, 0x1F617, 0x1F619, 0x1F61B, 0x1F61D, 0x1F620, 0x1F620, 0x1F622, 0x1F622, 0x1F626, 0x1F626, 0x1F62B, 0x1F62E,
    0x1F633, 0x1F633, 0x1F636, 0x1F636, 0x1F642, 0x1F642, 0x1F644, 0x1F644, 0x1F681, 0x1F681, 0x1F686, 0x1F686, 0x1F68A,
    0x1F68A, 0x1F68D, 0x1F68D, 0x1F690, 0x1F691, 0x1F696, 0x1F698, 0x1F69A, 0x1F69A, 0x1F69C, 0x1F69C, 0x1F6A1, 0x1F6A2,
    0x1F6A6, 0x1F6A6, 0x1F6AA, 0x1F6AD, 0x1F6B0, 0x1F6B0, 0x1F6B2, 0x1F6B2, 0x1F6B4, 0x1F6B4, 0x1F6B6, 0x1F6B6, 0x1F6BD,
    0x1F6BD, 0x1F6BF, 0x1F6BF, 0x1F6C1, 0x1F6C1, 0x1F6CC, 0x1F6CC, 0x1F6CE, 0x1F6CE, 0x1F6D0, 0x1F6D0, 0x1F6D2, 0x1F6D2,
    0x1F6E1, 0x1F6E1, 0x1F6E3, 0x1F6E3, 0x1F6EB, 0x1F6EC, 0x1F6F0, 0x1F6F0, 0x1F6FB, 0x1F6FB, 0x1F7E0, 0x1F7EB, 0x1F90D,
    0x1F90E, 0x1F916, 0x1F916, 0x1F91A, 0x1F91A, 0x1F91D, 0x1F91D, 0x1F923, 0x1F923, 0x1F929, 0x1F929, 0x1F941, 0x1F944,
    0x1F94E, 0x1F94E, 0x1F953, 0x1F953, 0x1F955, 0x1F955, 0x1F95A, 0x1F95A, 0x1F977, 0x1F977, 0x1F990, 0x1F990, 0x1F99B,
    0x1F99B, 0x1F9A6, 0x1F9A6, 0x1F9B4, 0x1F9B4, 0x1F9B7, 0x1F9B7, 0x1F9CD, 0x1F9CD, 0x1F9E0, 0x1F9E1, 0x1F9E6, 0x1F9E6,
    0x1F9E9, 0x1F9EA, 0x1F9EC, 0x1F9ED, 0x1F9EF, 0x1F9F0, 0x1F9F2, 0x1F9F3, 0x1F9F9, 0x1F9F9, 0x1F9FB, 0x1F9FC, 0x1F9FE,
    0x1F9FE, 0x1FA79, 0x1FA7A, 0x1FA91, 0x1FA91, 0x1FA9B, 0x1FA9B, 0x1FAB6, 0x1FAB6, 0x1FAC1, 0x1FAC1, 0};
