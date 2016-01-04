#include <simdmath/simdmath.h>
#include "common.h"
#include "catch.hpp"

#ifdef _MSC_VER
#  pragma warning(disable: 4244)
#endif

#ifdef SIMDMATH_VEC_FLOAT4

static const double input_x[360] = {
  0.0, 0.0174532925199, 0.0349065850399, 0.0523598775598,
  0.0698131700798, 0.0872664625997, 0.10471975512, 0.12217304764,
  0.13962634016, 0.157079632679, 0.174532925199, 0.191986217719,
  0.209439510239, 0.226892802759, 0.244346095279, 0.261799387799,
  0.279252680319, 0.296705972839, 0.314159265359, 0.331612557879,
  0.349065850399, 0.366519142919, 0.383972435439, 0.401425727959,
  0.418879020479, 0.436332312999, 0.453785605519, 0.471238898038,
  0.488692190558, 0.506145483078, 0.523598775598, 0.541052068118,
  0.558505360638, 0.575958653158, 0.593411945678, 0.610865238198,
  0.628318530718, 0.645771823238, 0.663225115758, 0.680678408278,
  0.698131700798, 0.715584993318, 0.733038285838, 0.750491578358,
  0.767944870878, 0.785398163397, 0.802851455917, 0.820304748437,
  0.837758040957, 0.855211333477, 0.872664625997, 0.890117918517,
  0.907571211037, 0.925024503557, 0.942477796077, 0.959931088597,
  0.977384381117, 0.994837673637, 1.01229096616, 1.02974425868,
  1.0471975512, 1.06465084372, 1.08210413624, 1.09955742876,
  1.11701072128, 1.1344640138, 1.15191730632, 1.16937059884,
  1.18682389136, 1.20427718388, 1.2217304764, 1.23918376892,
  1.25663706144, 1.27409035396, 1.29154364648, 1.308996939,
  1.32645023152, 1.34390352404, 1.36135681656, 1.37881010908,
  1.3962634016, 1.41371669412, 1.43116998664, 1.44862327916,
  1.46607657168, 1.4835298642, 1.50098315672, 1.51843644924,
  1.53588974176, 1.55334303427, 1.57079632679, 1.58824961931,
  1.60570291183, 1.62315620435, 1.64060949687, 1.65806278939,
  1.67551608191, 1.69296937443, 1.71042266695, 1.72787595947,
  1.74532925199, 1.76278254451, 1.78023583703, 1.79768912955,
  1.81514242207, 1.83259571459, 1.85004900711, 1.86750229963,
  1.88495559215, 1.90240888467, 1.91986217719, 1.93731546971,
  1.95476876223, 1.97222205475, 1.98967534727, 2.00712863979,
  2.02458193231, 2.04203522483, 2.05948851735, 2.07694180987,
  2.09439510239, 2.11184839491, 2.12930168743, 2.14675497995,
  2.16420827247, 2.18166156499, 2.19911485751, 2.21656815003,
  2.23402144255, 2.25147473507, 2.26892802759, 2.28638132011,
  2.30383461263, 2.32128790515, 2.33874119767, 2.35619449019,
  2.37364778271, 2.39110107523, 2.40855436775, 2.42600766027,
  2.44346095279, 2.46091424531, 2.47836753783, 2.49582083035,
  2.51327412287, 2.53072741539, 2.54818070791, 2.56563400043,
  2.58308729295, 2.60054058547, 2.61799387799, 2.63544717051,
  2.65290046303, 2.67035375555, 2.68780704807, 2.70526034059,
  2.72271363311, 2.74016692563, 2.75762021815, 2.77507351067,
  2.79252680319, 2.80998009571, 2.82743338823, 2.84488668075,
  2.86233997327, 2.87979326579, 2.89724655831, 2.91469985083,
  2.93215314335, 2.94960643587, 2.96705972839, 2.98451302091,
  3.00196631343, 3.01941960595, 3.03687289847, 3.05432619099,
  3.07177948351, 3.08923277603, 3.10668606855, 3.12413936107,
  3.14159265359, 3.15904594611, 3.17649923863, 3.19395253115,
  3.21140582367, 3.22885911619, 3.24631240871, 3.26376570123,
  3.28121899375, 3.29867228627, 3.31612557879, 3.33357887131,
  3.35103216383, 3.36848545635, 3.38593874887, 3.40339204139,
  3.42084533391, 3.43829862643, 3.45575191895, 3.47320521147,
  3.49065850399, 3.50811179651, 3.52556508903, 3.54301838155,
  3.56047167407, 3.57792496659, 3.59537825911, 3.61283155163,
  3.63028484415, 3.64773813667, 3.66519142919, 3.68264472171,
  3.70009801423, 3.71755130675, 3.73500459927, 3.75245789179,
  3.76991118431, 3.78736447683, 3.80481776935, 3.82227106187,
  3.83972435439, 3.85717764691, 3.87463093943, 3.89208423195,
  3.90953752447, 3.92699081699, 3.94444410951, 3.96189740203,
  3.97935069455, 3.99680398707, 4.01425727959, 4.03171057211,
  4.04916386463, 4.06661715715, 4.08407044967, 4.10152374219,
  4.11897703471, 4.13643032723, 4.15388361975, 4.17133691227,
  4.18879020479, 4.20624349731, 4.22369678983, 4.24115008235,
  4.25860337487, 4.27605666739, 4.29350995991, 4.31096325243,
  4.32841654495, 4.34586983747, 4.36332312999, 4.38077642251,
  4.39822971503, 4.41568300755, 4.43313630007, 4.45058959259,
  4.46804288511, 4.48549617763, 4.50294947015, 4.52040276267,
  4.53785605519, 4.55530934771, 4.57276264023, 4.59021593275,
  4.60766922527, 4.62512251778, 4.6425758103, 4.66002910282,
  4.67748239534, 4.69493568786, 4.71238898038, 4.7298422729,
  4.74729556542, 4.76474885794, 4.78220215046, 4.79965544298,
  4.8171087355, 4.83456202802, 4.85201532054, 4.86946861306,
  4.88692190558, 4.9043751981, 4.92182849062, 4.93928178314,
  4.95673507566, 4.97418836818, 4.9916416607, 5.00909495322,
  5.02654824574, 5.04400153826, 5.06145483078, 5.0789081233,
  5.09636141582, 5.11381470834, 5.13126800086, 5.14872129338,
  5.1661745859, 5.18362787842, 5.20108117094, 5.21853446346,
  5.23598775598, 5.2534410485, 5.27089434102, 5.28834763354,
  5.30580092606, 5.32325421858, 5.3407075111, 5.35816080362,
  5.37561409614, 5.39306738866, 5.41052068118, 5.4279739737,
  5.44542726622, 5.46288055874, 5.48033385126, 5.49778714378,
  5.5152404363, 5.53269372882, 5.55014702134, 5.56760031386,
  5.58505360638, 5.6025068989, 5.61996019142, 5.63741348394,
  5.65486677646, 5.67232006898, 5.6897733615, 5.70722665402,
  5.72467994654, 5.74213323906, 5.75958653158, 5.7770398241,
  5.79449311662, 5.81194640914, 5.82939970166, 5.84685299418,
  5.8643062867, 5.88175957922, 5.89921287174, 5.91666616426,
  5.93411945678, 5.9515727493, 5.96902604182, 5.98647933434,
  6.00393262686, 6.02138591938, 6.0388392119, 6.05629250442,
  6.07374579694, 6.09119908946, 6.10865238198, 6.1261056745,
  6.14355896702, 6.16101225954, 6.17846555206, 6.19591884458,
  6.2133721371, 6.23082542962, 6.24827872214, 6.26573201466
};

static const double expected_sinx[360] = {
  0.0, 0.0174524064373, 0.0348994967025, 0.0523359562429,
  0.0697564737441, 0.0871557427477, 0.104528463268, 0.121869343405,
  0.13917310096, 0.15643446504, 0.173648177667, 0.190808995377,
  0.207911690818, 0.224951054344, 0.2419218956, 0.258819045103,
  0.275637355817, 0.292371704723, 0.309016994375, 0.325568154457,
  0.342020143326, 0.358367949545, 0.374606593416, 0.390731128489,
  0.406736643076, 0.422618261741, 0.438371146789, 0.45399049974,
  0.469471562786, 0.484809620246, 0.5, 0.51503807491,
  0.529919264233, 0.544639035015, 0.559192903471, 0.573576436351,
  0.587785252292, 0.601815023152, 0.615661475326, 0.62932039105,
  0.642787609687, 0.656059028991, 0.669130606359, 0.681998360062,
  0.694658370459, 0.707106781187, 0.719339800339, 0.731353701619,
  0.743144825477, 0.754709580223, 0.766044443119, 0.777145961457,
  0.788010753607, 0.798635510047, 0.809016994375, 0.819152044289,
  0.829037572555, 0.838670567945, 0.848048096156, 0.857167300702,
  0.866025403784, 0.874619707139, 0.882947592859, 0.891006524188,
  0.898794046299, 0.906307787037, 0.913545457643, 0.920504853452,
  0.927183854567, 0.933580426497, 0.939692620786, 0.945518575599,
  0.951056516295, 0.956304755963, 0.961261695938, 0.965925826289,
  0.970295726276, 0.974370064785, 0.978147600734, 0.981627183448,
  0.984807753012, 0.987688340595, 0.990268068742, 0.992546151641,
  0.994521895368, 0.996194698092, 0.99756405026, 0.998629534755,
  0.999390827019, 0.999847695156, 1.0, 0.999847695156,
  0.999390827019, 0.998629534755, 0.99756405026, 0.996194698092,
  0.994521895368, 0.992546151641, 0.990268068742, 0.987688340595,
  0.984807753012, 0.981627183448, 0.978147600734, 0.974370064785,
  0.970295726276, 0.965925826289, 0.961261695938, 0.956304755963,
  0.951056516295, 0.945518575599, 0.939692620786, 0.933580426497,
  0.927183854567, 0.920504853452, 0.913545457643, 0.906307787037,
  0.898794046299, 0.891006524188, 0.882947592859, 0.874619707139,
  0.866025403784, 0.857167300702, 0.848048096156, 0.838670567945,
  0.829037572555, 0.819152044289, 0.809016994375, 0.798635510047,
  0.788010753607, 0.777145961457, 0.766044443119, 0.754709580223,
  0.743144825477, 0.731353701619, 0.719339800339, 0.707106781187,
  0.694658370459, 0.681998360062, 0.669130606359, 0.656059028991,
  0.642787609687, 0.62932039105, 0.615661475326, 0.601815023152,
  0.587785252292, 0.573576436351, 0.559192903471, 0.544639035015,
  0.529919264233, 0.51503807491, 0.5, 0.484809620246,
  0.469471562786, 0.45399049974, 0.438371146789, 0.422618261741,
  0.406736643076, 0.390731128489, 0.374606593416, 0.358367949545,
  0.342020143326, 0.325568154457, 0.309016994375, 0.292371704723,
  0.275637355817, 0.258819045103, 0.2419218956, 0.224951054344,
  0.207911690818, 0.190808995377, 0.173648177667, 0.15643446504,
  0.13917310096, 0.121869343405, 0.104528463268, 0.0871557427477,
  0.0697564737441, 0.0523359562429, 0.0348994967025, 0.0174524064373,
  6.12323399574e-17, -0.0174524064373, -0.0348994967025, -0.0523359562429,
  -0.0697564737441, -0.0871557427477, -0.104528463268, -0.121869343405,
  -0.13917310096, -0.15643446504, -0.173648177667, -0.190808995377,
  -0.207911690818, -0.224951054344, -0.2419218956, -0.258819045103,
  -0.275637355817, -0.292371704723, -0.309016994375, -0.325568154457,
  -0.342020143326, -0.358367949545, -0.374606593416, -0.390731128489,
  -0.406736643076, -0.422618261741, -0.438371146789, -0.45399049974,
  -0.469471562786, -0.484809620246, -0.5, -0.51503807491,
  -0.529919264233, -0.544639035015, -0.559192903471, -0.573576436351,
  -0.587785252292, -0.601815023152, -0.615661475326, -0.62932039105,
  -0.642787609687, -0.656059028991, -0.669130606359, -0.681998360062,
  -0.694658370459, -0.707106781187, -0.719339800339, -0.731353701619,
  -0.743144825477, -0.754709580223, -0.766044443119, -0.777145961457,
  -0.788010753607, -0.798635510047, -0.809016994375, -0.819152044289,
  -0.829037572555, -0.838670567945, -0.848048096156, -0.857167300702,
  -0.866025403784, -0.874619707139, -0.882947592859, -0.891006524188,
  -0.898794046299, -0.906307787037, -0.913545457643, -0.920504853452,
  -0.927183854567, -0.933580426497, -0.939692620786, -0.945518575599,
  -0.951056516295, -0.956304755963, -0.961261695938, -0.965925826289,
  -0.970295726276, -0.974370064785, -0.978147600734, -0.981627183448,
  -0.984807753012, -0.987688340595, -0.990268068742, -0.992546151641,
  -0.994521895368, -0.996194698092, -0.99756405026, -0.998629534755,
  -0.999390827019, -0.999847695156, -1.0, -0.999847695156,
  -0.999390827019, -0.998629534755, -0.99756405026, -0.996194698092,
  -0.994521895368, -0.992546151641, -0.990268068742, -0.987688340595,
  -0.984807753012, -0.981627183448, -0.978147600734, -0.974370064785,
  -0.970295726276, -0.965925826289, -0.961261695938, -0.956304755963,
  -0.951056516295, -0.945518575599, -0.939692620786, -0.933580426497,
  -0.927183854567, -0.920504853452, -0.913545457643, -0.906307787037,
  -0.898794046299, -0.891006524188, -0.882947592859, -0.874619707139,
  -0.866025403784, -0.857167300702, -0.848048096156, -0.838670567945,
  -0.829037572555, -0.819152044289, -0.809016994375, -0.798635510047,
  -0.788010753607, -0.777145961457, -0.766044443119, -0.754709580223,
  -0.743144825477, -0.731353701619, -0.719339800339, -0.707106781187,
  -0.694658370459, -0.681998360062, -0.669130606359, -0.656059028991,
  -0.642787609687, -0.62932039105, -0.615661475326, -0.601815023152,
  -0.587785252292, -0.573576436351, -0.559192903471, -0.544639035015,
  -0.529919264233, -0.51503807491, -0.5, -0.484809620246,
  -0.469471562786, -0.45399049974, -0.438371146789, -0.422618261741,
  -0.406736643076, -0.390731128489, -0.374606593416, -0.358367949545,
  -0.342020143326, -0.325568154457, -0.309016994375, -0.292371704723,
  -0.275637355817, -0.258819045103, -0.2419218956, -0.224951054344,
  -0.207911690818, -0.190808995377, -0.173648177667, -0.15643446504,
  -0.13917310096, -0.121869343405, -0.104528463268, -0.0871557427477,
  -0.0697564737441, -0.0523359562429, -0.0348994967025, -0.0174524064373
};
static const double expected_cosx[360] = {
  1.0, 0.999847695156, 0.999390827019, 0.998629534755,
  0.99756405026, 0.996194698092, 0.994521895368, 0.992546151641,
  0.990268068742, 0.987688340595, 0.984807753012, 0.981627183448,
  0.978147600734, 0.974370064785, 0.970295726276, 0.965925826289,
  0.961261695938, 0.956304755963, 0.951056516295, 0.945518575599,
  0.939692620786, 0.933580426497, 0.927183854567, 0.920504853452,
  0.913545457643, 0.906307787037, 0.898794046299, 0.891006524188,
  0.882947592859, 0.874619707139, 0.866025403784, 0.857167300702,
  0.848048096156, 0.838670567945, 0.829037572555, 0.819152044289,
  0.809016994375, 0.798635510047, 0.788010753607, 0.777145961457,
  0.766044443119, 0.754709580223, 0.743144825477, 0.731353701619,
  0.719339800339, 0.707106781187, 0.694658370459, 0.681998360062,
  0.669130606359, 0.656059028991, 0.642787609687, 0.62932039105,
  0.615661475326, 0.601815023152, 0.587785252292, 0.573576436351,
  0.559192903471, 0.544639035015, 0.529919264233, 0.51503807491,
  0.5, 0.484809620246, 0.469471562786, 0.45399049974,
  0.438371146789, 0.422618261741, 0.406736643076, 0.390731128489,
  0.374606593416, 0.358367949545, 0.342020143326, 0.325568154457,
  0.309016994375, 0.292371704723, 0.275637355817, 0.258819045103,
  0.2419218956, 0.224951054344, 0.207911690818, 0.190808995377,
  0.173648177667, 0.15643446504, 0.13917310096, 0.121869343405,
  0.104528463268, 0.0871557427477, 0.0697564737441, 0.0523359562429,
  0.0348994967025, 0.0174524064373, 6.12323399574e-17, -0.0174524064373,
  -0.0348994967025, -0.0523359562429, -0.0697564737441, -0.0871557427477,
  -0.104528463268, -0.121869343405, -0.13917310096, -0.15643446504,
  -0.173648177667, -0.190808995377, -0.207911690818, -0.224951054344,
  -0.2419218956, -0.258819045103, -0.275637355817, -0.292371704723,
  -0.309016994375, -0.325568154457, -0.342020143326, -0.358367949545,
  -0.374606593416, -0.390731128489, -0.406736643076, -0.422618261741,
  -0.438371146789, -0.45399049974, -0.469471562786, -0.484809620246,
  -0.5, -0.51503807491, -0.529919264233, -0.544639035015,
  -0.559192903471, -0.573576436351, -0.587785252292, -0.601815023152,
  -0.615661475326, -0.62932039105, -0.642787609687, -0.656059028991,
  -0.669130606359, -0.681998360062, -0.694658370459, -0.707106781187,
  -0.719339800339, -0.731353701619, -0.743144825477, -0.754709580223,
  -0.766044443119, -0.777145961457, -0.788010753607, -0.798635510047,
  -0.809016994375, -0.819152044289, -0.829037572555, -0.838670567945,
  -0.848048096156, -0.857167300702, -0.866025403784, -0.874619707139,
  -0.882947592859, -0.891006524188, -0.898794046299, -0.906307787037,
  -0.913545457643, -0.920504853452, -0.927183854567, -0.933580426497,
  -0.939692620786, -0.945518575599, -0.951056516295, -0.956304755963,
  -0.961261695938, -0.965925826289, -0.970295726276, -0.974370064785,
  -0.978147600734, -0.981627183448, -0.984807753012, -0.987688340595,
  -0.990268068742, -0.992546151641, -0.994521895368, -0.996194698092,
  -0.99756405026, -0.998629534755, -0.999390827019, -0.999847695156,
  -1.0, -0.999847695156, -0.999390827019, -0.998629534755,
  -0.99756405026, -0.996194698092, -0.994521895368, -0.992546151641,
  -0.990268068742, -0.987688340595, -0.984807753012, -0.981627183448,
  -0.978147600734, -0.974370064785, -0.970295726276, -0.965925826289,
  -0.961261695938, -0.956304755963, -0.951056516295, -0.945518575599,
  -0.939692620786, -0.933580426497, -0.927183854567, -0.920504853452,
  -0.913545457643, -0.906307787037, -0.898794046299, -0.891006524188,
  -0.882947592859, -0.874619707139, -0.866025403784, -0.857167300702,
  -0.848048096156, -0.838670567945, -0.829037572555, -0.819152044289,
  -0.809016994375, -0.798635510047, -0.788010753607, -0.777145961457,
  -0.766044443119, -0.754709580223, -0.743144825477, -0.731353701619,
  -0.719339800339, -0.707106781187, -0.694658370459, -0.681998360062,
  -0.669130606359, -0.656059028991, -0.642787609687, -0.62932039105,
  -0.615661475326, -0.601815023152, -0.587785252292, -0.573576436351,
  -0.559192903471, -0.544639035015, -0.529919264233, -0.51503807491,
  -0.5, -0.484809620246, -0.469471562786, -0.45399049974,
  -0.438371146789, -0.422618261741, -0.406736643076, -0.390731128489,
  -0.374606593416, -0.358367949545, -0.342020143326, -0.325568154457,
  -0.309016994375, -0.292371704723, -0.275637355817, -0.258819045103,
  -0.2419218956, -0.224951054344, -0.207911690818, -0.190808995377,
  -0.173648177667, -0.15643446504, -0.13917310096, -0.121869343405,
  -0.104528463268, -0.0871557427477, -0.0697564737441, -0.0523359562429,
  -0.0348994967025, -0.0174524064373, -1.83697019872e-16, 0.0174524064373,
  0.0348994967025, 0.0523359562429, 0.0697564737441, 0.0871557427477,
  0.104528463268, 0.121869343405, 0.13917310096, 0.15643446504,
  0.173648177667, 0.190808995377, 0.207911690818, 0.224951054344,
  0.2419218956, 0.258819045103, 0.275637355817, 0.292371704723,
  0.309016994375, 0.325568154457, 0.342020143326, 0.358367949545,
  0.374606593416, 0.390731128489, 0.406736643076, 0.422618261741,
  0.438371146789, 0.45399049974, 0.469471562786, 0.484809620246,
  0.5, 0.51503807491, 0.529919264233, 0.544639035015,
  0.559192903471, 0.573576436351, 0.587785252292, 0.601815023152,
  0.615661475326, 0.62932039105, 0.642787609687, 0.656059028991,
  0.669130606359, 0.681998360062, 0.694658370459, 0.707106781187,
  0.719339800339, 0.731353701619, 0.743144825477, 0.754709580223,
  0.766044443119, 0.777145961457, 0.788010753607, 0.798635510047,
  0.809016994375, 0.819152044289, 0.829037572555, 0.838670567945,
  0.848048096156, 0.857167300702, 0.866025403784, 0.874619707139,
  0.882947592859, 0.891006524188, 0.898794046299, 0.906307787037,
  0.913545457643, 0.920504853452, 0.927183854567, 0.933580426497,
  0.939692620786, 0.945518575599, 0.951056516295, 0.956304755963,
  0.961261695938, 0.965925826289, 0.970295726276, 0.974370064785,
  0.978147600734, 0.981627183448, 0.984807753012, 0.987688340595,
  0.990268068742, 0.992546151641, 0.994521895368, 0.996194698092,
  0.99756405026, 0.998629534755, 0.999390827019, 0.999847695156
};

TEST_CASE("vec_float4 sincos", "[sincosf4]") {
  for (int i = 0; i < 360; i += 4) {
    vec_float4 x = simdmath_setf4(input_x[i], input_x[i+1], input_x[i+2], input_x[i+3]);
    vec_float4 s, c;
    simdmath_sincosf4(x, &s, &c);
    REQUIRE(get_comp<0>(s) == Approx(expected_sinx[i+0]));
    REQUIRE(get_comp<1>(s) == Approx(expected_sinx[i+1]));
    REQUIRE(get_comp<2>(s) == Approx(expected_sinx[i+2]));
    REQUIRE(get_comp<3>(s) == Approx(expected_sinx[i+3]));
    REQUIRE(get_comp<0>(c) == Approx(expected_cosx[i+0]));
    REQUIRE(get_comp<1>(c) == Approx(expected_cosx[i+1]));
    REQUIRE(get_comp<2>(c) == Approx(expected_cosx[i+2]));
    REQUIRE(get_comp<3>(c) == Approx(expected_cosx[i+3]));
  }
  for (int i = 0; i < 360; i += 4) {
    vec_float4 x = simdmath_setf4(-input_x[i], -input_x[i+1], -input_x[i+2], -input_x[i+3]);
    vec_float4 s, c;
    simdmath_sincosf4(x, &s, &c);
    REQUIRE(get_comp<0>(s) == Approx(-expected_sinx[i+0]));
    REQUIRE(get_comp<1>(s) == Approx(-expected_sinx[i+1]));
    REQUIRE(get_comp<2>(s) == Approx(-expected_sinx[i+2]));
    REQUIRE(get_comp<3>(s) == Approx(-expected_sinx[i+3]));
    REQUIRE(get_comp<0>(c) == Approx(expected_cosx[i+0]));
    REQUIRE(get_comp<1>(c) == Approx(expected_cosx[i+1]));
    REQUIRE(get_comp<2>(c) == Approx(expected_cosx[i+2]));
    REQUIRE(get_comp<3>(c) == Approx(expected_cosx[i+3]));
  }
}

TEST_CASE("vec_float4 acos", "[acosf4]") {
  for (int i = 0; i < 180; i += 4) {
    vec_float4 x = simdmath_setf4(expected_cosx[i], expected_cosx[i+1], expected_cosx[i+2], expected_cosx[i+3]);
    vec_float4 y = simdmath_acosf4(x);
    REQUIRE(get_comp<0>(y) == Approx(input_x[i+0]));
    REQUIRE(get_comp<1>(y) == Approx(input_x[i+1]));
    REQUIRE(get_comp<2>(y) == Approx(input_x[i+2]));
    REQUIRE(get_comp<3>(y) == Approx(input_x[i+3]));
  }
  {
    vec_float4 x = simdmath_splatf4(expected_cosx[180]);
    vec_float4 y = simdmath_acosf4(x);
    REQUIRE(get_comp<0>(y) == Approx(input_x[180]));
    REQUIRE(get_comp<1>(y) == Approx(input_x[180]));
    REQUIRE(get_comp<2>(y) == Approx(input_x[180]));
    REQUIRE(get_comp<3>(y) == Approx(input_x[180]));
  }
}

TEST_CASE("vec_float4 tan", "[tanf4]") {
  for (int i = 0; i < 180; i += 4) {
    if (i == 88)
      continue;
    vec_float4 x = simdmath_setf4(input_x[i], input_x[i+1], input_x[i+2], input_x[i+3]);
    vec_float4 y = simdmath_tanf4(x);
    float y0 = expected_sinx[i] / expected_cosx[i];
    float y1 = expected_sinx[i+1] / expected_cosx[i+1];
    float y2 = expected_sinx[i+2] / expected_cosx[i+2];
    float y3 = expected_sinx[i+3] / expected_cosx[i+3];
    REQUIRE(get_comp<0>(y) == Approx(y0));
    REQUIRE(get_comp<1>(y) == Approx(y1));
    REQUIRE(get_comp<2>(y) == Approx(y2));
    REQUIRE(get_comp<3>(y) == Approx(y3));
  }
  {
    vec_float4 x = simdmath_setf4(input_x[88], input_x[89], input_x[91], 0.0f);
    vec_float4 y = simdmath_tanf4(x);
    float y0 = expected_sinx[88] / expected_cosx[88];
    float y1 = expected_sinx[89] / expected_cosx[89];
    float y2 = expected_sinx[91] / expected_cosx[91];
    float y3 = 0.0f;
    REQUIRE(get_comp<0>(y) == Approx(y0));
    REQUIRE(get_comp<1>(y) == Approx(y1));
    REQUIRE(get_comp<2>(y) == Approx(y2));
    REQUIRE(get_comp<3>(y) == Approx(y3));
  }
}

#endif
