//#include <SPI.h>
#include <QueueArray.h>
//#include <Phpoc.h>

#define DATA_SIZE 100
#define TREE_SIZE 50
//#define QN 6

// 핀번호 설정
int echo[4] = { 2, 8, 7, 5 };
int trig[4] = { 3, 9, 6, 4 };

// 거리
float distance[4];

// Bound, standard diviationl
float lowerbound[4], upperbound[4];
//PhpocClient client;
// global avg (벽과의 거리)
//float real_avg = 0;

// initial times
int times = 0;

int cnt = 0;
int data_cnt = 0;
bool isNewLine = false;

//QueueArray <float> Q[4];
//QueueArray <float> D;
float ar[16];
int index = 0;
//float Qsum[4] = {0,};
//float Qavg[4] = {0,};
bool first = false;
bool last = false;
bool sw = true;

int seq = 1;

int vote[TREE_SIZE];

void setup() {
  Serial.begin(250000);
  //  while (!Serial)
  //    ;
  //  Serial.println("Sending GET request to web server");
  //  Phpoc.begin(PF_LOG_SPI | PF_LOG_NET);
  for (int i = 0; i < 4; i++) {
    pinMode(trig[i], OUTPUT);
    pinMode(echo[i], INPUT);
  }
  //    lowerbound[0] = 88 - 4;
  //    lowerbound[1] = 88 - 4;
  //    lowerbound[2] = 88 - 4;
  //    lowerbound[3] = 88 - 4;
  //    upperbound[0] = 88 + 4;
  //    upperbound[1] = 88 + 4;
  //    upperbound[2] = 88 + 4;
  //    upperbound[3] = 88 + 4;
  lowerbound[0] = 83.08;
  lowerbound[1] = 83.35;
  lowerbound[2] = 82.82;
  lowerbound[3] = 83.34;
  upperbound[0] = 91.39;
  upperbound[1] = 91.66;
  upperbound[2] = 91.13;
  upperbound[3] = 91.65;
}

//void initialize(int init_time) {
//  if (times < init_time) {
//    for (int i = 0; i < 4; i++) {
//      arr[i][times] = distance[i];
//    }
//  }
//}

//void calculate_bound(int init_time) {
//  float sum[4] = {0,}, avg[4], stddv[4], sig = 0;
//
//  for (int i = 0; i < 4; i++) {
//    for (int j = 10; j < init_time; j++) {
//      sum[i] += arr[i][j];
//    }
//    avg[i] = sum[i] / (init_time - 10);
//    sum[i] = 0;
//  }
//
//  for (int i = 0; i < 4; i++) {
//    for (int j = 10; j < init_time; j++) {
//      sum[i] += pow(arr[i][j] - avg[i], 2);
//    }
//    stddv[i] = sqrt(sum[i] / (init_time - 10)) * 12;
//  }
//
//  for (int i = 0; i < 4; i++) {
//    if (stddv[i] > sig) sig = stddv[i];
//  }
//
//  for (int i = 0; i < 4; i++) {
//    lowerbound[i] = avg[i] - sig;
//    upperbound[i] = avg[i] + sig;
//  }
//
//  for (int i = 0; i < 4; i++) {
//    real_avg += avg[i];
//  }
//  real_avg /= 4;
//  lowerbound[0] = 83.08;
//  lowerbound[1] = 83.35;
//  lowerbound[2] = 82.82;
//  lowerbound[3] = 83.34;
//  upperbound[0] = 91.39;
//  upperbound[1] = 91.66;
//  upperbound[2] = 91.13;
//  upperbound[3] = 91.65;
//  //  for (int i = 0; i < 4; i++) {
//  //    lowerbound[i] = real_avg - sig;
//  //    upperbound[i] = real_avg + sig;
//  //  }
//}

bool isInBound(int i) {
  if (distance[i] > lowerbound[i] && distance[i] < upperbound[i]) return true;
  else return false;
}

void process(int i) {
  if (i==2 || i==5 || i==7 || i==8 || i==9 || i==10 || i==12 || i==17 || i==19 || i==26 || i==27 || i==29 || i==30 || i==41 || i==48){
    i=-1;
  }
  if (i == 0) { // 보선
    if (ar[3] < 62.25) {
      vote[i] = -1;
    } else {
      if (ar[1] < 81.12) {
        vote[i] = -1;
      } else {
        vote[i] = 1;
      }
    }
  }
  else if (i == 1) { // 채린
    if (ar[2] < 83.495) {
      vote[i] = 1;
    } else {
      if (ar[7] < 86.635) {
        vote[i] = -1;
      } else {
        vote[i] = 1;
      }
    }
  }
    else if (i == 2) { // 조서
      if (ar[6] < 79.23) {
        vote[i] = 1;
      } else {
        if (ar[0] < 87.26) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      }
    }
    else if (i == 3) { // 두상
      if (ar[11] < 48.25) {
        if (ar[4] < 43) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      } else {
        if (ar[2] < 87.105) {
          vote[i] = 1;
        } else {
          if (ar[3] < 55.455) {
            vote[i] = -1;
          } else {
            vote[i] = 1;
          }
        }
      }
    }
  else if (i == 4) { // 기욱
    if (ar[7] < 34) {
      vote[i] = -1;
    } else {
      if (ar[3] < 61.65) {
        vote[i] = -1;
      } else {
        if (ar[1] < 47.245) {
          vote[i] = -1;
        } else {
          vote[i] = 1;
        }
      }
    }
  }
    else if (i == 5) { // 형진
      if (ar[1] < 77.63) {
        if (ar[4] < 59.38) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      } else {
        if (ar[13] < 89.58) {
          if (ar[3] < 39.175) {
            vote[i] = -1;
          } else {
            vote[i] = 1;
          }
        } else {
          vote[i] = -1;
        }
      }
    }
  else if (i == 6) { // 종호
    if (ar[2] < 63.795) {
      vote[i] = 1;
    } else {
      if (ar[0] < 75.42) {
        vote[i] = 1;
      } else {
        if (ar[4] < 67.845) {
          vote[i] = 1;
        } else {
          if (ar[7] < 87.94) {
            vote[i] = -1;
          } else {
            vote[i] = 1;
          }
        }
      }
    }
  }
  else if (i == 7) { // 지식
    if (ar[1] < 81.185) {
      vote[i] = -1;
    } else {
      if (ar[3] < 55.27) {
        vote[i] = -1;
      } else {
        vote[i] = 1;
      }
    }
  }
    else if (i == 8) { // 지원
      if (ar[7] < 45.3) {
        if (ar[0] < 86.7) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      } else {
        vote[i] = 1;
      }
    }
    else if (i == 9) { // 광선
      if (ar[2] < 86.925) {
        vote[i] = 1;
      } else {
        if (ar[4] < 43.56) {
          vote[i] = 1;
        } else {
          if (ar[8] < 87.645) {
            vote[i] = -1;
          } else {
            vote[i] = 1;
          }
        }
      }
    }
    else if (i == 10) { // 남진
      if (ar[3] < 50.35) {
        vote[i] = -1;
      } else {
        if (ar[1] < 32.015) {
          vote[i] = -1;
        } else {
          if (ar[5] < 89.8) {
            vote[i] = 1;
          } else {
            vote[i] = -1;
          }
        }
      }
    }
  else if (i == 11) { // 소현
    if (ar[3] < 75.715) {
      vote[i] = -1;
    } else {
      if (ar[3] < 90.3) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    }
  }
  else if (i == 12) { // 성준
    if (ar[7] < 48.025) {
      vote[i] = -1;
    } else {
      if (ar[5] < 64.835) {
        vote[i] = -1;
      } else {
        vote[i] = 1;
      }
    }
  }
    else if (i == 13) { // 성민
      if (ar[7] < 49.08) {
        if (ar[0] < 47.06) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      } else {
        vote[i] = 1;
      }
    }
  else if (i == 14) { // 상우
    if (ar[1] < 81.21) {
      if (ar[0] < 76.17) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    } else {
      if (ar[3] < 81.225) {
        vote[i] = -1;
      } else {
        vote[i] = 1;
      }
    }
  }
  else if (i == 15) { // 영준
    if (ar[6] < 62.33) {
      if (ar[1] < 88.91) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    } else {
      if (ar[4] < 69.625) {
        vote[i] = 1;
      } else {
        if (ar[0] < 78.07) {
          vote[i] = 1;
        } else {
          if (ar[2] < 88.865) {
            vote[i] = -1;
          } else {
            vote[i] = 1;
          }
        }
      }
    }
  }
  else if (i == 16) { // 영송
    if (ar[3] < 75.25) {
      vote[i] = -1;
    } else {
      if (ar[1] < 61.875) {
        vote[i] = -1;
      } else {
        if (ar[1] < 89.465) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      }
    }
  }
    else if (i == 17) { // 유성
      if (ar[11] < 29.615) {
        if (ar[0] < 87.48) {
          vote[i] = -1;
        } else {
          vote[i] = 1;
        }
      } else {
        if (ar[1] < 78.645) {
          vote[i] = -1;
        } else {
          vote[i] = 1;
        }
      }
    }
  else if (i == 18) { // 승연
    if (ar[2] < 51.29) {
      if (ar[1] < 43.005) {
        vote[i] = -1;
      } else {
        vote[i] = 1;
      }
    } else {
      if (ar[2] < 88.565) {
        if (ar[0] < 68.315) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      } else {
        vote[i] = 1;
      }
    }
  }
    else if (i == 19) { // 용욱
      if (ar[7] < 40.145) {
        if (ar[6] < 42.94) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      } else {
        if (ar[15] < 33.16) {
          if (ar[5] < 86.505) {
            vote[i] = 1;
          } else {
            vote[i] = -1;
          }
        } else {
          vote[i] = 1;
        }
      }
    }
  else if (i == 20) { // 김현중
    if (ar[3] < 86.605) {
      if (ar[2] < 57.8) {
        vote[i] = 1;
      } else {
        if (ar[6] < 40.42) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      }
    } else {
      if (ar[1] < 59.46) {
        vote[i] = -1;
      } else {
        vote[i] = 1;
      }
    }
  }
  else if (i == 21) { // 장영준
    if (ar[7] < 81.99) {
      if (ar[14] < 43.185) {
        vote[i] = 1;
      } else {
        if (ar[0] < 81.265) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      }
    } else {
      if (ar[1] < 90.145) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    }
  }
  else if (i == 22) { // 주병
    if (ar[4] < 77.095) {
      if (ar[1] < 94.82) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    } else {
      if (ar[8] < 16.45) {
        vote[i] = 1;
      } else {
        if (ar[2] < 65.125) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      }
    }
  }
  else if (i == 23) { // 원균
    if (ar[7] < 60.91) {
      if (ar[0] < 51.18) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    } else {
      if (ar[14] < 86.355) {
        vote[i] = 1;
      } else {
        if (ar[5] < 86.23) {
          vote[i] = -1;
        } else {
          vote[i] = 1;
        }
      }
    }
  }
  else if (i == 24) { // 지영
    if (ar[6] < 62.33) {
      if (ar[1] < 88.91) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    } else {
      if (ar[4] < 69.625) {
        vote[i] = 1;
      } else {
        if (ar[0] < 78.07) {
          vote[i] = 1;
        } else {
          if (ar[2] < 88.865) {
            vote[i] = -1;
          } else {
            vote[i] = 1;
          }
        }
      }
    }
  }
  else if (i == 25) { // 규봉
    if (ar[6] < 52.785) {
      if (ar[13] < 26.455) {
        vote[i] = -1;
      } else {
        vote[i] = 1;
      }
    } else {
      if (ar[0] < 76.335) {
        vote[i] = 1;
      } else {
        if (ar[8] < 89.33) {
          vote[i] = -1;
        } else {
          vote[i] = 1;
        }
      }
    }
  }
    else if (i == 26) { // 진용
      if (ar[12] < 29.46) {
        if (ar[3] < 38.565) {
          vote[i] = -1;
        } else {
          vote[i] = 1;
        }
      } else {
        if (ar[4] < 37.44) {
          vote[i] = 1;
        } else {
          if (ar[8] < 29.02) {
            vote[i] = 1;
          } else {
            vote[i] = -1;
          }
        }
      }
    }
    else if (i == 27) { // 경나?
      if (ar[7] < 40.44) {
        vote[i] = -1;
      } else {
        if (ar[3] < 35.905) {
          vote[i] = -1;
        } else {
          vote[i] = 1;
        }
      }
    }
  else if (i == 28) {
    if (ar[3] < 81.64) {
      if (ar[0] < 50.085) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    } else {
      if (ar[1] < 80.765) {
        vote[i] = -1;
      } else {
        if (ar[1] < 89.66) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      }
    }
  }
  else if (i == 29) {
    if (ar[7] < 41.715) {
      vote[i] = -1;
    } else {
      if (ar[1] < 86.76) {
        vote[i] = -1;
      } else {
        if (ar[3] < 64.51) {
          vote[i] = -1;
        } else {
          vote[i] = 1;
        }
      }
    }
  }
  else if (i == 30) {
    if (ar[3] < 46.68) {
      vote[i] = -1;
    } else {
      if (ar[2] < 86.555) {
        vote[i] = 1;
      } else {
        if (ar[0] < 78.215) {
          vote[i] = 1;
        } else {
          if (ar[3] < 65.625) {
            vote[i] = 1;
          } else {
            vote[i] = -1;
          }
        }
      }
    }
  }
  else if (i == 31) {
    if (ar[4] < 80.99) {
      if (ar[3] < 45.485) {
        vote[i] = -1;
      } else {
        vote[i] = 1;
      }
    } else {
      if (ar[2] < 81.355) {
        vote[i] = 1;
      } else {
        if (ar[0] < 64.835) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      }
    }
  }
  else if (i == 32) {
    if (ar[7] < 69.09) {
      if (ar[2] < 74.935) {
        if (ar[1] < 59.635) {
          vote[i] = -1;
        } else {
          vote[i] = 1;
        }
      } else {
        vote[i] = -1;
      }
    } else {
      vote[i] = 1;
    }
  }
  else if (i == 33) {
    if (ar[6] < 79.955) {
      if (ar[1] < 90.88) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    } else {
      if (ar[4] < 56.625) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    }
  }
  else if (i == 34) {
    if (ar[3] < 79.925) {
      if (ar[4] < 75.775) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    } else {
      if (ar[1] < 75.685) {
        vote[i] = -1;
      } else {
        if (ar[2] < 87.795) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      }
    }
  }
  else if (i == 35) {
    if (ar[7] < 46.985) {
      vote[i] = -1;
    } else {
      if (ar[0] < 86.755) {
        vote[i] = 1;
      } else {
        if (ar[1] < 87.785) {
          vote[i] = -1;
        } else {
          vote[i] = 1;
        }
      }
    }
  }
  else if (i == 36) {
    if (ar[4] < 86.545) {
      vote[i] = 1;
    } else {
      if (ar[2] < 81.535) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    }
  }
  else if (i == 37) {
    if (ar[2] < 86.51) {
      if (ar[6] < 87.74) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    } else {
      if (ar[0] < 82) {
        vote[i] = 1;
      } else {
        if (ar[7] < 87.76) {
          vote[i] = -1;
        } else {
          vote[i] = 1;
        }
      }
    }
  }
  else if (i == 38) {
    if (ar[4] < 79.465) {
      if (ar[1] < 45.99) {
        vote[i] = -1;
      } else {
        vote[i] = 1;
      }
    } else {
      if (ar[6] < 75.765) {
        vote[i] = 1;
      } else {
        if (ar[0] < 84.38) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      }
    }
  }
  else if (i == 39) {
    if (ar[4] < 71.125) {
      if (ar[7] < 36.985) {
        vote[i] = -1;
      } else {
        vote[i] = 1;
      }
    } else {
      if (ar[0] < 75.86) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    }
  }
  else if (i == 40) {
    if (ar[0] < 86.595) {
      vote[i] = 1;
    } else {
      if (ar[2] < 75.555) {
        vote[i] = 1;
      } else {
        if (ar[2] < 87.485) {
          if (ar[6] < 55.33) {
            vote[i] = 1;
          } else {
            vote[i] = -1;
          }
        } else {
          vote[i] = 1;
        }
      }
    }
  }
  else if (i == 41) {
    if (ar[3] < 78.005) {
      if (ar[0] < 57.29) {
        vote[i] = 1;
      } else {
        if (ar[4] < 28.145) {
          vote[i] = 1;
        } else {
          vote[i] = 1;
        }
      }
    } else {
      if (ar[6] < 87.055) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    }
  }
  else if (i == 42) {
    if (ar[3] < 81.665) {
      if (ar[2] < 86.285) {
        vote[i] = 1;
      } else {
        if (ar[2] < 88.895) {
          vote[i] = -1;
        } else {
          vote[i] = 1;
        }
      }
    } else {
      if (ar[5] < 71.495) {
        vote[i] = -1;
      } else {
        vote[i] = 1;
      }
    }
  }
  else if (i == 43) {
    if (ar[4] < 86.72) {
      if (ar[5] < 54.95) {
        vote[i] = -1;
      } else {
        vote[i] = 1;
      }
    } else {
      if (ar[2] < 81.78) {
        vote[i] = 1;
      } else { 
        vote[i] = -1;
      }
    }
  }
  else if (i == 44) {
    if (ar[6] < 86.28) {
      if (ar[1] < 89.655) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    } else {
      if (ar[0] < 86.59) {
        vote[i] = 1;
      } else {
        if (ar[2] < 62.425) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      }
    }
  }
  else if (i == 45) {
    if (ar[6] < 86.295) {
      if (ar[1] < 53.585) {
        vote[i] = -1;
      } else {
        if (ar[1] < 89.69) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      }
    } else {
      if (ar[6] < 87.32) {
        vote[i] = -1;
      } else {
        vote[i] = 1;
      }
    }
  }
  else if (i == 46) {
    if (ar[6] < 79.27) {
      if (ar[3] < 35.905) {
        vote[i] = -1;
      } else {
        vote[i] = 1;
      }
    } else {
      if (ar[2] < 70.465) {
        vote[i] = 1;
      } else {
        if (ar[0] < 65.68) {
          vote[i] = 1;
        } else {
          vote[i] = -1;
        }
      }
    }
  }
  else if (i == 47) {
    if (ar[2] < 84.245) {
      vote[i] = 1;
    } else {
      if (ar[4] < 64.175) {
        vote[i] = 1;
      } else {
        if (ar[2] < 88.625) {
          vote[i] = -1;
        } else {
          vote[i] = 1;
        }
      }
    }
  }
  else if (i == 48) {
    if (ar[7] < 43.52) {
      if (ar[2] < 60.06) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    } else {
      if (ar[2] < 87.24) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    }
  }
  else if (i == 49) {
    if (ar[7] < 59.045) {
      if (ar[4] < 60.62) {
        vote[i] = 1;
      } else {
        vote[i] = -1;
      }
    } else {
      if (ar[5] < 65.57) {
        vote[i] = -1;
      } else {
        vote[i] = 1;
      }
    }
  }
}

void print_value() {
  //  Serial.print(times);
  //  Serial.print("\t");

  //  if (times > 30 && (!isInBound(0) || !isInBound(1) || !isInBound(2) || !isInBound(3))) {
  //    if (index < 40) {
  //      //      ar[index++] = Qavg[0];
  //      //      ar[index++] = Qavg[1];
  //      //      ar[index++] = Qavg[2];
  //      //      ar[index++] = Qavg[3];
  //    }
  //    isNewLine = false;
  //    data_cnt += 4;
  //  }

  //  for (int i = 0; i < 4; i++) {
  //    Q[i].push(distance[i]);
  //    Qsum[i] += distance[i];
  //  }
  //
  //  if (Q[0].count() == QN + 1) {
  //    for (int i = 0; i < 4; i++) {
  //      Qsum[i] -= Q[i].pop();
  //    }
  //  }
  //
  //  for (int i = 0; i < 4; i++)
  //    Qavg[i] = Qsum[i] / Q[i].count();

  if (isInBound(0) && isInBound(1) && isInBound(2) && isInBound(3) && !isNewLine) {
    cnt++;
  } else {
    cnt = 0;
  }

  if (cnt == 3) {
    cnt = 0;
    if (ar[12] != 0 || ar[13] != 0 || ar[14] != 0 || ar[15] != 0) {
      for (int i = 0; i < TREE_SIZE; i++) {
        process(i);
      }
      int sum = 0;
      int out = 0, in = 0;
      for (int i = 0; i < TREE_SIZE; i++) {
        Serial.print(vote[i]);
        Serial.print("\t");
        if (vote[i] == -1) out++;
        else if (vote[i] == 1) in++;
        sum += vote[i];
        vote[i] = 0;
      }
      Serial.println("\t");
      Serial.println("\t");
      Serial.print("IN  :  ");
      Serial.print(in);
      Serial.print("\t");
      Serial.print("OUT  :  ");
      Serial.print(out);
      Serial.print("\t");
      Serial.print("RESULT  :  ");
      Serial.print(sum);
      Serial.println("\t");
      Serial.println("\t");
      in = 0; out = 0; sum = 0;
    }
    for (int i = 0; i < 16; i++) {
      ar[i] = 0;
    }

    //    if (sw) {
    //      for (int i = 0; i < DATA_SIZE - data_cnt; i++) {
    //        Serial.print('0');
    //        Serial.print("\t");
    //      }
    //      Serial.println();
    //    }
    data_cnt = 0;
    isNewLine = true;
    index = 0;
  }

  //  if (!isInBound(0) || !isInBound(1) || !isInBound(2) || !isInBound(3)) {
  //    if (!first && D.count() < 12) {
  //      D.push(Qavg[0]);
  //      D.push(Qavg[1]);
  //      D.push(Qavg[2]);
  //      D.push(Qavg[3]);
  //    }
  //    if (!first && D.count() == 12) {
  //      for (int i = 0; i < 12; i++) ar[i] = D.pop();
  //      first = true;
  //      //      Serial.println("First On!");
  //    }
  //    if (first && !last) {
  //      D.push(Qavg[0]);
  //      D.push(Qavg[1]);
  //      D.push(Qavg[2]);
  //      D.push(Qavg[3]);
  //      if (D.count() > 12) for (int i = 0; i < 4; i++) D.pop();
  //    }
  //  }
  //
  //  if (first && !last && cnt == 2) {
  //    for (int i = 12; i < 24; i++) ar[i] = D.pop();
  //    last = true;
  //  }
  //  if (first && last) {
  //    process();
  //  }
  //  if (cnt == 2) {
  //    for (int i = 0; i < 24; i++) ar[i] = 0;
  //    isNewLine = true;
  //    cnt = 0;
  //    first = false;
  //    last = false;
  //  }

//  if (!isInBound(0) || !isInBound(1) || !isInBound(2) || !isInBound(3)) {
//    if (index < 14) {
//      for (int i = 0; i < 4; i++) {
//        if (distance[i] == 120.0) {
//          ar[index++] = 0;
//        } else {
//          ar[index++] = distance[i];
//        }
//      }
//    }
    for (int i = 0; i < 4; i++) {
      //    if (!isInBound(i)) {
            Serial.print(distance[i]);
            Serial.print("\t");
      //    }
    }
    data_cnt += 4;
    isNewLine = false;
    //    for (int i = 0; i < 4; i++) {
    //      //    if (!isInBound(i)) {
    //      Serial.print(lowerbound[i]);
    //      Serial.print("\t");
    //      //    }
    //    }
    //    for (int i = 0; i < 4; i++) {
    //      //    if (!isInBound(i)) {
    //      Serial.print(upperbound[i]);
    //      Serial.print("\t");
    //      //    }
    //    }
            Serial.println();
//  }
}

float getDistance(int i) {
  float result, du;
  digitalWrite(trig[i], HIGH);
  delay(5);
  digitalWrite(trig[i], LOW);
  du = pulseIn(echo[i], HIGH);
  //  result = ((float)(340 * du) / 10000) / 2;
  result = du / 58.2;
  if (result > 120) result = 120; // 튀는 값 120으로 보정
  return result;
}

//float getMedian(float a, float b, float c) {
//  float A = a, B = b, C = c;
//  if (b >= a && a >= c) return A;
//  if (c >= a && a >= b) return A;
//  if (a >= b && b >= c) return B;
//  if (c >= b && b >= a) return B;
//  if (a >= c && c >= b) return C;
//  if (b >= c && c >= a) return C;
//}

void loop() {
  int num = 1;

  for (int i = 0; i < 4; i++) distance[i] = getDistance(i);



  // 바운드 계산을 위한 초기값 (벽) 거리 측정
  //  initialize(30);

  // 바운드 계산
  //  if (times == 30) calculate_bound(30);


  // 출력
  print_value();

  if (Serial.available()) {
    Serial.read();
    sw = !sw;
  }

  times++;
}
