//초음파 센서의 핀번호를 설정한다.
int echoPin = 12, echoPin2 = 8;
int trigPin = 13, trigPin2 = 9;
float avg_dis1 = 0.0, avg_dis2 = 0.0;
int mcc = 100;
int cnt = 0;
float arr1[100], arr2[100];
int people_in = 0, people_out = 0, people_total = 0;
bool in_sw1 = false, in_sw2 = false;
bool out_sw1 = false, out_sw2 = false;
bool eq_sw = false;
bool in_start = false, out_start = false;
int in_times = 0, out_times = 0, total_times = 0;
float dis1_lowerbound = 0.0;
float dis1_upperbound = 0.0;
float dis2_lowerbound = 0.0;
float dis2_upperbound = 0.0;
float distance, distance2;
float prev_dis1 = 0.0, prev_dis2 = 0.0;

void setup() {
  Serial.begin(9600);
  // trig를 출력모드로 설정, echo를 입력모드로 설정
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}

void inCount(float dis1, float dis2) { //들어오는 경우 카운트 측정
  if (!out_start && !in_sw1 && (dis1 < dis1_lowerbound || dis1 > dis1_upperbound) && (dis2 > dis2_lowerbound && dis2 < dis2_upperbound)) {
    in_sw1 = true;
    in_start = true;
  }
  if (!in_sw2 && in_sw1 && (dis2 < dis2_lowerbound || dis2 > dis2_upperbound)) {
    in_sw2 = true;
  }
  if (!out_start && in_sw1 && in_sw2 && dis1 > dis1_lowerbound && dis1 < dis1_upperbound && dis2 < dis2_upperbound && dis2 > dis2_lowerbound) {
    in_times++;
  }
  else in_times = 0;
  if (in_times == 3) {
    people_in++;
    in_sw1 = false;
    in_sw2 = false;
    in_start = false;
    eq_sw=false;
  }
}
void outCount(float dis1, float dis2) {
  if (!in_start && !out_sw1 && (dis2 < dis2_lowerbound || dis2 > dis2_upperbound) && (dis1 > dis1_lowerbound && dis1 < dis1_upperbound)) {
    out_sw1 = true;
    out_start = true;
  }
  if (!out_sw2 && out_sw1 && (dis1 < dis1_lowerbound || dis1 > dis1_upperbound)) {
    out_sw2 = true;
  }
  if (!in_start && out_sw1 && out_sw2 && dis1 > dis1_lowerbound && dis1 < dis1_upperbound && dis2 < dis2_upperbound && dis2 > dis2_lowerbound) {
    out_times++;
  }
  else out_times = 0;
  if (out_times == 3) {
    people_out++;
    out_sw1 = false;
    out_sw2 = false;
    out_start = false;
    eq_sw = false;
  }
}
void equalCount(float dis1, float dis2, float p_dis1, float p_dis2) { //동시 잡아주기
  if (p_dis1 < dis1_upperbound && p_dis1 > dis1_lowerbound && p_dis2 < dis2_upperbound && p_dis2 > dis2_lowerbound &&
      (dis1 < dis1_lowerbound || dis1 > dis1_upperbound) && (dis2 < dis2_lowerbound || dis2 > dis2_upperbound)) {
    eq_sw = true;
  }
  if (eq_sw == true) { //동시에 떨어졌을 때
    if (dis1 > dis1_lowerbound && dis1 < dis1_upperbound && dis2 > dis2_lowerbound && dis2 < dis2_upperbound) { //동시에 올라오는 경우
      eq_sw = false;
    }
    else if (dis1 > dis1_lowerbound && dis1 < dis1_upperbound) {
      out_times++;
    }
    else if (dis2 > dis2_lowerbound && dis2 < dis2_upperbound) {
      in_times++;
    }
  }
}
void loop() {
  float duration, duration2;

  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.
  digitalWrite(trigPin2, HIGH);
  delay(10);
  digitalWrite(trigPin2, LOW);
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  duration2 = pulseIn(echoPin2, HIGH);

  
  // 초음파를 보낸다. 다 보내면 echo가 HIGH 상태로 대기하게 된다.
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
  duration = pulseIn(echoPin, HIGH);


  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.

  prev_dis1 = distance;
  prev_dis2 = distance2;
  distance = ((float)(340 * duration) / 10000) / 2;
  distance2 = ((float)(340 * duration2) / 10000) / 2;
  if (cnt < mcc && distance < 400 && distance2 < 400) { //바운드를 위해 튀는것 예외처리
    arr1[cnt] = distance;
    arr2[cnt] = distance2;
  }
  else if (cnt == mcc) { //바운드 값 설정
    float sum1 = 0.0, sum2 = 0.0;
    for (int i = 0; i < mcc; i++) {
      sum1 += arr1[i];
      sum2 += arr2[i];
    }
    avg_dis1 = sum1 / mcc;
    avg_dis2 = sum2 / mcc;
    sum1 = 0.0;
    sum2 = 0.0;
    for (int i = 0; i < mcc; i++) {
      sum1 += pow(arr1[i] - avg_dis1, 2);
      sum2 += pow(arr2[i] - avg_dis2, 2);
    }
    float sd1 = sqrt(sum1 / mcc) * 6;
    float sd2 = sqrt(sum2 / mcc) * 6;
    float sd;
    if (sd1 > sd2)
      sd = sd1;
    else
      sd = sd2;
    dis1_lowerbound = avg_dis1 - sd;
    dis1_upperbound = avg_dis1 + sd;
    dis2_lowerbound = avg_dis2 - sd;
    dis2_upperbound = avg_dis2 + sd;

  }
  else { //카운트 측정
    inCount(distance, distance2);
    outCount(distance, distance2);
    equalCount(distance, distance2, prev_dis1, prev_dis2);
    people_total = people_out - people_in;
  }
  if (distance < dis1_upperbound && distance > dis1_lowerbound && distance2 < dis2_upperbound && distance2 > dis2_lowerbound) //범위 안에 연속으로 있을 때
    total_times++;
  else
    total_times = 0;
  if (total_times == 3){
    total_times = 0;
    in_sw1 = false;
    out_sw1 = false;
    in_sw2 = false;
    out_sw2 = false;
    in_start = false;
    out_start = false;
  }
  cnt++;
  if(distance>400) distance = 0;
  if(distance2>400) distance2 = 0;
  Serial.print(distance);
  Serial.print(" ");
  Serial.print(distance2);
  Serial.print(" ");
  Serial.print(avg_dis1);
  Serial.print(" ");
  Serial.print(avg_dis2);
  Serial.print(" ");
  Serial.print(dis1_lowerbound);
  Serial.print(" ");
  Serial.print(dis1_upperbound);
  Serial.print(" ");
  Serial.print(dis2_lowerbound);
  Serial.print(" ");
  Serial.print(dis2_upperbound);
  Serial.print(" ");
  Serial.println((people_out - people_in) * 10);
}
