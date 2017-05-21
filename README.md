<br><br>
<p align="center">
  <img src="projects/img/pi_logo.png"/><br>
<b>A real-time people counting system using ultrasonic sensors</b><br><br>
<br><br>
</p>

[![PLATFORM](https://camo.githubusercontent.com/fa324fd41901f19d1151ba104eb17ae57a1c4dd8/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f506c6174666f726d2d416e64726f69642d677265656e2e737667)](#)
[![BUILD STATUS](https://img.shields.io/travis/USER/REPO/BRANCH.svg)](#)
[![MIT LICENSE](https://img.shields.io/packagist/l/doctrine/orm.svg?maxAge=2592000)](#)

## PEOPLE INSIDE
At meal time, there are too many people in a restaurant. So we have to wait in the restaurant. We want to check the number of indoor people in advance.
PEOPLE INSIDE is **a real-time people counting system using ultrasonic sensors**.
**Our system aims to measure indoor congestion metrics.**
You can check the number of people with application.

### Our Purpose
We are focusing on three main purposes.

![purpose](./projects/img/purpose.JPG)

### Quick Start <<
```
git clone https://github.com/PEOPLE-INSIDE/people-inside
```

## Getting Started
### Installation Environment

![architecture](./projects/img/architecture.png)

### Basic Principle
If the **A** sensor detects a person first, it means *IN*. And the reverse, it means *OUT*.

![principle](./projects/img/principle.png)

## How To Use
- **Classification Algorithmㅡ** we made classification algorithm that classifies Serial datas which one is *IN* and *OUT*.
- **Random Forestㅡ** we collect data sets we need, then 

## Classifiaction Algorithm

## Random Forest
<!--
두번째 Method는 Machine Learning 기법 중 하나인 Random Forest를 이용해 분류하는 것이다.
Random Forest 알고리즘은 Decision tree의 Ensemble 기법으로 높은 정확도를 보인다.
우리는 약 2800개의 Dataset(IN:1400, OUT:1400)을 제공하며, Example code에 이미 이 Dataset으로 학습된 Decision tree Model을 제공한다.
학습된 모델은 MATLAB의 Treebagger function을 이용하여 학습되었으며 트리의 갯수는 50개이다.

우리가 제공하는 모델은 우리의 환경에 최적화되어있기 때문에 당신의 testbed에서는 좋은 성능이 나오지 않을 수 있다.
그렇기 때문에 당신이 우리의 모델을 사용하고 싶지 않다면, 직접 Data를 모아 모델을 만들어 사용 할 수도 있다.
-->

## Performance
### Test video
[Click here](https://www.youtube.com/watch?v=0aNgP3FmK0k) to watch test video.

# Developers
