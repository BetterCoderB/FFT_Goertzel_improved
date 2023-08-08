#include <Arduino.h>
#include <ADC.h>
#include <ADC_util.h>
ADC* adc = new ADC();

const int DATA_SIZE = 256;
const int frequency_k[] = {
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  10,
  11,
  12,
  13,
  14,
  15,
  16,
  17,
  18,
  19,
  20,
  21,
  22,
  23,
  24,
  25,
  26,
  27,
  28,
  29,
  30,
  31,
  32,
  33,
  34,
  35,
  36,
  37,
  38,
  39,
  40,
  41,
  42,
  43,
  44,
  45,
  46,
  47,
  48,
  49,
  50,
  51,
  52,
  53,
  54,
  55,
  56,
  57,
  58,
  59,
  60,
  61,
  62,
  63,
  64,
  65,
  66,
  67,
  68,
  69,
  70,
  71,
  72,
  73,
  74,
  75,
  76,
  77,
  78,
  79,
  80,
  81,
  82,
  83,
  84,
  85,
  86,
  87,
  88,
  89,
  90,
  91,
  92,
  93,
  94,
  95,
  96,
  97,
  98,
  99,
  100,
  101,
  102,
  103,
  104,
  105,
  106,
  107,
  108,
  109,
  110,
  111,
  112,
  113,
  114,
  115,
  116,
  117,
  118,
  119,
  120,
  121,
  122,
  123,
  124,
  125,
  126,
  127,
};

/* 
5120Hz / 256 * 30 = 600 Hz
            ...31 = 620 Hz
            ...32 = 640 Hz
*/
const int quantity_k = sizeof(frequency_k) / sizeof(int);
#include <FFT_Goertzel_improved.h>

Goertzel<DATA_SIZE, (int*)frequency_k, quantity_k> FFT_Goertzel;

//#include <signal.h>
float signal[] = {
  81.1658521,
72.5952757,
9.9882131,
-5.0399891,
42.6663793,
64.0135102,
3.6421458,
-75.9785298,
-85.3110274,
-31.8383388,
3.0139062,
-13.0735162,
-27.1808057,
7.1742881,
59.6290234,
72.8680873,
43.3106598,
12.3559569,
-0.7833688,
-13.9407265,
-36.0176782,
-48.7298902,
-42.1902218,
-32.2752422,
-26.3389094,
-4.2376451,
41.1328018,
72.3175783,
53.3177863,
10.2133982,
0.3946402,
23.9393440,
17.5310295,
-45.2343533,
-98.0787520,
-69.6264746,
7.7078816,
37.5575996,
-0.9564453,
-22.8465361,
31.8037934,
99.9388716,
82.6923241,
-8.0786804,
-63.3485166,
-32.4022403,
10.2832865,
-16.6794164,
-78.2191470,
-76.9828363,
1.1076429,
67.2479782,
57.9306168,
16.2284917,
14.5716068,
46.6904731,
47.6389986,
-2.8805606,
-54.0439793,
-61.4630299,
-41.2144587,
-28.6509579,
-23.2156242,
-4.4771421,
23.3653019,
38.9931139,
42.2273956,
48.1604696,
48.3852261,
17.7545595,
-34.0833987,
-58.6565878,
-36.5864030,
-13.0547030,
-30.9506195,
-57.1214819,
-26.0365079,
53.0047583,
92.9219642,
50.0000000,
-8.6683370,
-1.7128031,
44.1133142,
33.2471657,
-50.2589012,
-108.7590243,
-68.6113975,
12.9963237,
31.9972165,
-12.5851639,
-25.1042654,
37.4704278,
98.8143968,
75.3357197,
-4.0323939,
-44.8128471,
-21.8302963,
-1.4479999,
-31.1883794,
-70.6234492,
-58.6879023,
-3.4262473,
37.6613032,
41.2576674,
35.4284724,
40.9084608,
41.3273245,
21.1700585,
-5.1690789,
-21.6685892,
-37.3417495,
-58.9046495,
-62.2121696,
-25.9450373,
21.8795000,
33.2525561,
13.1483421,
16.4877498,
59.0916352,
79.8124066,
27.3412744,
-52.2212930,
-69.9749209,
-21.6272889,
5.0137158,
-37.0788241,
-78.3855801,
-34.8329184,
60.5823866,
97.0020786,
42.7197386,
-12.5475999,
7.1257517,
53.6353904,
32.3536739,
-52.2686338,
-100.6170907,
-60.8544653,
3.3588981,
12.9914790,
-15.8550110,
-10.4373382,
42.6858844,
80.7650609,
59.9897908,
11.7256486,
-13.8958248,
-16.5421001,
-26.3815207,
-45.9491556,
-50.7941023,
-34.8787964,
-16.2198038,
0.5424111,
29.0849626,
61.9636444,
64.5568531,
28.1001489,
-4.9553486,
0.0000000,
11.9022409,
-20.5772405,
-79.1528128,
-87.3524414,
-22.1910276,
41.3227428,
32.9829521,
-9.3061893,
3.2721531,
71.2420165,
97.2145575,
28.4604827,
-59.3447725,
-66.7255612,
-10.9430350,
6.1747181,
-46.3789355,
-83.1309862,
-31.9726984,
57.0304692,
83.5854035,
37.5678205,
1.3624366,
21.8644645,
48.2432662,
18.5791017,
-45.8542587,
-75.9085622,
-52.8446852,
-20.9903393,
-12.3081859,
-8.2329445,
14.4229294,
42.0003933,
50.8424193,
44.7238676,
37.2739491,
19.8581456,
-18.8772909,
-55.5687303,
-54.4286731,
-25.0341645,
-15.2160755,
-35.2530882,
-33.2623457,
24.4743740,
86.4030527,
78.1191993,
12.9348377,
-20.7844821,
11.3089226,
36.3629127,
-14.5508280,
-93.6274441,
-97.2392158,
-16.8580846,
45.4391020,
23.7207151,
-20.0540237,
4.7984411,
77.8245415,
96.0576992,
25.7029574,
-49.7875808,
-51.3993346,
-10.6783914,
-9.0730089,
-52.7324756,
-70.0258136,
-23.2050242,
39.2815933,
57.8160415,
39.5947597,
29.3034056,
35.5978182,
29.3062713,
-0.0641579,
-29.2399229,
-42.6080290,
-50.0000000,
-53.8988224,
-35.3212582,
7.7323261,
39.3498849,
33.4518867,
18.6667827,
36.0354869,
65.7795795,
46.6258237,
-26.5769952,
-78.1934699,
-53.9205718,
-2.7839032,
-6.6392572,
-54.4443272,
-54.2705098,
25.8569234,
99.0810486,
78.9388446,
3.7803478,
-20.5701515,
23.6600672,
44.3301763,
-17.4618891,
-94.9211740,
-90.8845008,
-16.3961257,
31.2417913,
10.6113248,
-14.6368309,
17.4779707,
73.4262672,
78.3458740,
25.1920305,
-23.7900642,
-30.6595153,
-22.9452260,
-34.3089611,
-51.3958896,
-44.1591675,
-15.7322691,
9.8800776,
28.6402463,
50.0585195,
62.3001642,
42.9068026,
3.7627127,
-14.7649212,
-5.6188917,
-11.3446049,
-54.0225571,
-85.3405177,
-49.6338181,
25.0111378,
54.7663872,
19.6423897,
-5.1311528,
36.2202896,
87.9617345,
78.3277159,
2.3417359,
-33.2052754,
20.7075222,
86.6360819,
78.4194910,
29.8233310,
41.6501991,
127.7062438,
190.3251427,
159.5411803,
87.4291334,
63.3217540,
84.2752478,
71.4002547,
-4.1914404,
-78.6784725,
-90.1842176,
-60.3643177,
-49.0795839,
-66.2415778,
-73.4463601,
-54.8825045,
-38.8241663,
-47.6955904,
-68.3684429,
-84.4481158,
-102.5482026,
-125.4030996,
-128.8659954,
-96.1023113,
-53.5104258,
-35.5431231,
-25.9664407,
20.9929067,
99.0897596,
139.9037535,
107.6621592,
59.7704149,
68.6965908,
113.1110971,
107.8935507,
37.7167884,
-8.1515845,
37.4911058,
116.5466157,
125.0669315,
62.1580301,
26.4525005,
64.6824433,
99.4850466,
44.5852621,
-65.6183311,
-124.1240214,
-101.8214022,
-77.5371976,
-112.0019857,
-159.9284373,
-144.9303438,
-74.7426019,
-26.1966979,
-34.8438800,
-57.6462365,
-50.0629943,
-28.1365379,
-29.3820077,
-49.9319549,
-56.3731723,
-38.6181326,
-13.2293041,
15.6838827,
59.6502324,
109.2021478,
133.1572736,
126.8670377,
125.1584068,
144.5054914,
145.5762596,
90.8013223,
16.2237723,
-5.3480955,
30.4613014,
47.6865727,
2.7441651,
-44.7117800,
-19.3891769,
48.2820362,
55.3595171,
-25.5236559,
-103.2302950,
-99.5882167,
-61.5794602,
-85.8272368,
-168.2469293,
-204.7848730,
-142.1303626,
-53.6667003,
-31.2122342,
-57.6513539,
-45.8319321,
24.5134340,
78.6117646,
59.9109963,
8.7541084,
-2.9991408,
28.7046001,
51.8460427,
45.5659561,
43.8325040,
73.1825669,
113.3945291,
134.9831957,
139.1828009,
137.3856260,
119.8934980,
76.4361024,
28.3723113,
3.9031728,
-9.2202442,
-45.7091637,
-96.7439723,
-107.8138893,
-61.1828685,
-17.3435427,
-35.8003723,
-85.3397197,
-87.6364174,
-39.2985181,
-25.2374932,
-91.5867832,
-166.1533569,
-154.5219292,
-75.6165812,
-32.8847391,
-60.3378987,
-73.3625717,
0.7892426,
108.2747696,
141.8198377,
92.2290326,
54.3814086,
84.8191415,
125.7023853,
101.1924546,
33.5258558,
7.9303083,
49.1472722,
95.0102703,
93.3406565,
68.0264677,
65.7872808,
81.0900535,
72.4604680,
29.0519791,
-20.9833993,
-59.4118546,
-94.4811240,
-126.3678392,
-135.2902145,
-118.2562138,
-103.6575195,
-106.2550126,
-97.0549595,
-51.2619114,
-3.7691257,
-10.6363256,
-61.3681573,
-82.2963747,
-41.9923412,
-1.7178429,
-23.0695045,
-65.8682609,
-38.7386414,
62.8406902,
139.4554975,
126.4117753,
84.8773159,
106.6102673,
172.8140008,
179.7917974,
94.5607325,
7.7645239,
5.4000878,
50.9745783,
49.2953935,
-10.2790944,
-44.6013918,
-6.2334484,
46.9085249,
38.4919236,
-21.4370597,
-64.6141252,
-67.8707366,
-73.4489455,
-111.3165887,
-153.4561105,
-161.3194705,
-138.7118253,
-111.2364210,
-82.2378801,
-42.1279026,
-3.0215446,
13.4728963,
15.9816528,
32.4482349,
57.4771820,
51.8399500,
10.0615968,
-12.3553690,
27.3212476,
89.0182613,
101.8265438,
71.7590019,
75.0538734,
140.2354143,
190.4642575,
149.0453268,
55.8485382,
15.3367121,
46.3775217,
57.7416598,
-10.9705041,
-93.4098149,
-91.1155767,
-18.3119232,
18.7792193,
-24.6687495,
-74.2958432,
-54.1895057,
1.2584751,
4.1792621,
-55.2911600,
-99.2306001,
-77.4692950,
-30.4736537,
-16.9466995,
-28.5875066,
-15.8420712,
31.3611518,
74.9443546,
90.5768388,
93.8881905,
100.6716245,
100.8599547,
87.8646214,
80.2109268,
89.3556404,
92.5500903,
69.6821833,
47.4524788,
65.6123710,
106.8093287,
108.6666820,
56.3121109,
13.7757383,
31.7037251,
64.8004103,
34.0282517,
-49.7822993,
-91.1291105,
-47.3738556,
4.9615790,
-18.8200247,
-84.8372854,
-90.0509756,
-17.2176683,
36.5320513,
1.5128430,
-63.6626664,
-60.8421889,
4.5843363,
37.8272194,
-2.0225434,
-45.7474279,
-21.0818254,
43.9807314,
70.1688136,
42.7053640,
20.8133380,
41.6104305,
71.3769364,
66.3339883,
36.0230523,
17.1697580,
15.6592964,
10.6188426,
-1.3897073,
-4.9763003,
-2.8257428,
-15.2390699,
-38.3758081,
-41.1982765,
-19.3430150,
-15.2386776,
-55.5025609,
-98.5927444,
-88.3648157,
-43.3551210,
-37.9178612,
-89.5104919,
-123.0078037,
-78.8863500,
-8.4157755,
-4.7420244,
-64.4195506,
-88.7394053,
-29.8506151,
35.3342905,
17.6080232,
-51.5907908,
-65.9882969,
-0.8987190,
52.7643816,
24.5308659,
-34.7143007,
-33.2325666,
26.3629191,
57.1633761,
18.4425561,
-31.5820054,
-29.0144991,
6.0736746,
11.2504603,
-23.2916485,
-50.5096200,
-43.4462252,
-27.1063275,
-28.5782418,
-38.1105402,
-37.8865074,
-35.6474404,
-43.2173516,
-46.6991762,
-30.5385814,
-14.4225885,
-27.7613434,
-54.1319642,
-45.1930925,
2.2914280,
29.1947943,
-0.2159505,
-35.6532457,
-9.5572666,
56.3250448,
74.0702876,
20.0386248,
-23.0086884,
14.7236824,
83.1448169,
82.9619618,
13.8304334,
-22.4811182,
27.8417558,
90.6523669,
73.7124516,
1.9796124,
-22.1801960,
29.4027178,
73.7225203,
42.9464885,
-19.0660100,
-28.0260581,
17.8604039,
44.8726993,
17.0422117,
-18.9910674,
-12.4955650,
20.0262230,
31.4982935,
16.3537395,
6.6056187,
14.7942192,
22.5810488,
21.7894246,
26.8942355,
39.8687300,
39.4943909,
22.1357786,
19.6057986,
49.3703513,
74.8787682,
54.4602010,
12.7596738,
13.8269949,
62.2195846,
85.5841516,
40.0788483,
-16.0826660,
-2.7215735,
59.8667706,
74.5911995,
11.2940048,
-43.9540458,
-14.1837191,
52.6701813,
53.0387303,
-18.9294638,
-62.8500684,
-20.7429137,
39.4162706,
27.0282351,
-38.7817681,
-62.6868083,
-14.9786792,
31.0457329,
12.4201345,
-35.7813334,
-41.7879089,
-2.8290074,
21.5782448,
3.1211123,
-22.4313449,
-19.2463704,
-1.0005006,
3.0807039,
-4.5180436,
-5.3313023,
-3.0649718,
-11.9222007,
-21.4838849,
-10.7773756,
7.4602795,
-2.7780318,
-39.1594079,
-51.8955682,
-18.4076565,
11.3425464,
-16.2380253,
-70.6805182,
-73.6244923,
-17.4410138,
14.6084285,
-30.5843621,
-91.3248019,
-77.8595876,
-7.5305047,
16.7373621,
-41.5447554,
-96.3450696,
-65.6055393,
7.3442336,
18.6244874,
-42.9888168,
-82.5681330,
-41.1389018,
20.8370111,
17.6037088,
-37.4768694,
-59.5396199,
-19.5646482,
21.0909494,
8.5368062,
-29.4833636,
-35.8135413,
-8.6042049,
8.1493498,
-3.2358865,
-17.0213139,
-14.6135931,
-9.5364788,
-13.1128898,
-12.3830316,
-0.6984016,
1.0666295,
-19.3089201,
-33.2147412,
-11.0129208,
22.0665088,
14.5623690,
-28.3949642,
-41.2287471,
4.8542206,
48.8721927,
25.1266598,
-33.3337195,
-36.2259053,
28.8590057,
71.5152977,
30.2960681,
-32.6833279,
-20.8269212,
53.0052786,
83.8567448,
29.6909148,
-26.9898100,
-2.1439231,
67.0216799,
80.4757745,
23.0071346,
-18.7052945,
12.7300972,
66.0025626,
64.2008894,
16.2468026,
-6.2145727,
22.1904336,
52.6513146,
43.3223686,
15.7495885,
10.2318505,
24.9693714,
31.6203926,
25.7395502,
24.7610309,
28.8196260,
21.9670878,
9.9479596,
17.9308069,
42.6560972,
45.4721848,
13.3736616,
-8.6084116,
19.1979798,
61.8727392,
53.1170017,
-1.5722677,
-23.0112651,
25.1478789,
74.4464388,
48.3299277,
-20.2889536,
-32.2031808,
30.7269689,
74.7635444,
31.6826846,
-38.7908156,
-36.4584697,
31.3014076,
61.6389996,
8.8093391,
-50.9819754,
-35.1276664,
25.9248429,
39.6901968,
-11.4650347,
-51.8942112,
-29.2673408,
14.4884114,
14.5498661,
-22.9127620,
-41.5482913,
-22.6302826,
-2.5091784,
-8.2894751,
-22.7658786,
-23.8016925,
-19.5898941,
-23.6484655,
-25.2697812,
-13.1774345,
-5.9937816,
-24.4443898,
-47.1487553,
-35.2835116,
0.7535588,
5.3084562,
-37.5750011,
-68.7023827,
-37.5467894,
14.4040742,
7.4134903,
-54.9870874,
-83.0954776,
-32.6286179,
24.0037767,
1.3477443,
-70.1966447,
-86.0601345,
-22.2191579,
27.9783454,
-8.3190438,
-76.2919300,
-76.0360760,
-9.5612493,
25.9985113,
-16.6246322,
-69.8580625,
-56.2516883,
0.3417935,
18.4027390,
-19.8418737,
-51.5925114,
-32.8903816,
3.3129997,
7.1243916,
-15.7931849,
-25.5363716,
-12.8773954,
-2.5523929,
-4.7976311,
-4.3724617,
2.4862896,
-1.1439889,
-15.3950179,
-13.0828735,
13.4565401,
27.5087565,
1.4746362,
-29.9208188,
-13.7260225,
35.2858959,
45.9342434,
-2.6417973,
-40.1200875,
-5.2136582,
57.1462196,
55.9663229,
-9.0825591,
-41.4089747,
10.7161478,
74.3009361,
57.5871541,
-13.4231314,
-32.7344325,
28.9111187,
82.0745044,
52.1301870,
-12.7061299,
-16.6736579,
42.9018529,
77.9979009,
42.6823643,
-5.5189174,
2.1241664,
47.5142603,
63.0009392,
33.3788127,
7.6826209,
18.4350748,
40.5600588,
41.2764667,
28.3077159,
24.8981443,
28.2562712,
23.6718241,
19.0290937,
30.0635922,
42.7643328,
29.4398968,
1.1267637,
1.8405818,
38.1813529,
56.8608163,
21.7954275,
-21.7935607,
-7.1992880,
49.1995317,
63.0351206,
7.1926590,
-40.3113131,
-8.3339853,
57.7672835,
58.7014658,
-10.9045637,
-51.3686928,
-4.6946866,
58.7399849,
44.1756013,
-27.8520248,
-53.8413595,
-0.6314510,
49.3589830,
23.0388307,
-38.9154611,
-48.6566319,
-0.2564641,
30.1196389,
0.9872903,
-40.8000898,
-38.5658988,
-6.2081049,
4.5927992,
-15.9898768,
-32.8014248,
-27.4861947,
-19.0546925,
-21.9296939,
-23.7789266,
-17.3956188,
-19.6262775,
-37.3265805,
-44.1477736,
-21.4237803,
0.5635794,
-18.0391265,
-57.6780644,
-58.0263905,
-11.1000346,
15.5984812,
-23.4151627,
-75.5954276,
-61.7045134,
2.8341938,
23.5364417,
-33.5816247,
-86.4203405,
-55.6901960,
15.4846078,
23.0146282,
-43.9936408,
-86.6420578,
-42.6518196,
22.8455691,
15.7069999,
-49.3721415,
-75.2237670,
-26.8524329,
22.7572277,
5.5252849,
-45.5955786,
-54.1578568,
-13.0499796,
15.3598773,
-2.8152016,
-31.2185297,
-28.0917772,
-5.2243012,
2.9109104,
-5.3618200,
-8.0128908,
-2.9324083,
-5.2816918,
-10.7579404,
0.0149059,
19.6961304,
};
const int quantity_sample = sizeof(signal) / sizeof(float);

void setup() {
  Serial.begin(115200);
  adc->adc0->setResolution(12);
  adc->adc0->setReference(ADC_REFERENCE::REF_3V3);

  float value;
  float max_level;
  int i;
  int j;
  for (j = 0; j < quantity_sample; j++) {
    
    value = signal[j];  //shift relative to zero
    FFT_Goertzel.write(value);          //write down the value
    max_level = FFT_Goertzel.getmax();  //get the maximum value in the given sample

    for (i = 0; i < quantity_k; i++) {
      value = (FFT_Goertzel.read(i) / max_level * 99);  //normalize received value
      Serial.print((int)value);
      Serial.print(' ');
    }
    Serial.println();
    delay(50);
  };
}
void loop() {
  
}