<br>
<p align="center">
  <img src="projects/img/pi_logo.png"/><br><br>
A real-time people counting system using ultrasonic sensors<br>
 <a href="https://github.com/PEOPLE-INSIDE/people-inside"><strong>Visit PEOPLE INSIDE &raquo;</strong></a>
<br><br><br>
</p>

[![PLATFORM](https://camo.githubusercontent.com/fa324fd41901f19d1151ba104eb17ae57a1c4dd8/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f506c6174666f726d2d416e64726f69642d677265656e2e737667)](#)
[![BUILD STATUS](https://img.shields.io/travis/USER/REPO/BRANCH.svg)](#)
[![MIT LICENSE](https://img.shields.io/packagist/l/doctrine/orm.svg?maxAge=2592000)](#)

## Table of contents
- [About](#people-inside)
- [Purpose](#our-purpose)
- [Basic Principle](#basic-principle)
- [Quick Start](#quick-start)

## PEOPLE INSIDE
At the university meal time, too many people crowd into a restaurant. It's because there is a unified schedule. So sometimes we must go to another restaurant because there are no enough table. After all, it's a fool's errand. But, we don't have much time. o we have to wait in the restaurant. We want to check the number of indoor people in advance.
PEOPLE INSIDE is **a real-time people counting system using ultrasonic sensors**.
**Our system aims to measure indoor congestion metrics.**
You can check the number of people with application.

### Our Purpose
We are focusing on three main purposes.

![purpose](./projects/img/purpose.JPG)

### Quick Start

```
git clone https://github.com/PEOPLE-INSIDE/people-inside
```

`\projects\arduino` - Include two type of our Arduino source code (Classification / Random Forest)

`\projects\mobile_app` - Include our Android mobile application for display the number of people

`\projects\3d_modeling` - Include our 3d model chassis for Arduino and ultrasonic sensors.

`\projects\dataset` - Include our all signal dataset for training decision trees.


## Getting Started
### Installation Environment

Before you start, make sure the environment fits perfectly.
- **ultrasonic sensorㅡ** need 4 ultrasonic sensors which parallel aligned in pairs. You must prepare inexpensive one which like `HC-SR06` we used.
- **Wifi Shieldㅡ** necessary to send data to the application.
- **Serverㅡ**
- **Applicationㅡ** required to view the processed data directly.

![architecture](./projects/img/architecture.png)

### Basic Principle
If the **A** sensor detects a person first, it means *IN*. And the reverse, it means *OUT*.

![principle](./projects/img/principle.png) ![graph](./projects/img/graph.PNG)

## How To Use
You have to choose one method that you want to use.

- **Classification Algorithmㅡ** Classification algorithm that classifies Serial datas which one is *IN* and *OUT*.
- **Random Forestㅡ** Machine Learning with data sets what we collected.

## Classifiaction Algorithm
![graph](./projects/img/graph2.png)

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

## Hardware
* Arduino UNO X 1
* HC-SR06 Ultrasonic Sensor X 4
* PHPoC Arduino Shield X 1
* Jumper Cable (as much as you need)
* Arduino Chassis (3D printed)
* Battery X 1
* Android Mobile Phone

## Software
* Arduino 1.8.2 (Arduino IDE Sketch)
* Android Studio 2.3.2 (Android programming IDE)
* MATLAB R2017a<br>
  For signal processing
* Web Server<br>
  Hosting - [Hostinger](https://www.hostinger.kr/)
  PHP
  MySQL

## Open source
* [Arduino](https://www.arduino.cc)<br>
  Open-source electronic prototyping platform enabling users to create interactive electronic objects.

* [PHPoC](www.phpoc.com/)<br>
  PHPoC Shield for Arduino connects Arduino to Ethernet or Wi-Fi networks.

* [NewPing](http://playground.arduino.cc/Code/NewPing)<br>
  NewPing is Arduino IDE library for easy control ultrasonic sensors.

* [SPI](https://www.arduino.cc/en/reference/SPI)<br>
  Serial Peripheral Interface (SPI) is a synchronous serial data protocol used by microcontrollers for communicating with one or more peripheral devices quickly over short distances.

* [Sketchup](https://www.sketchup.com/ko)<br>
  SketchUp is 3D modeling software that's easy to learn and incredibly fun to use.

## Developers
We have a core project team composed of:

#### [Amber Cho](https://github.com/Seo-Hyung) - Founder/Lead &nbsp;  [![GITHUB](./projects/img/git.png)](https://github.com/Seo-Hyung) &nbsp; [![LINK](./projects/img/link.png)](https://seo-hyung.github.io)

<img align="left" width="40" height="40" src="https://avatars0.githubusercontent.com/u/18183191?v=3&s=460">

Amber is a Software Engineer and UI Designer. She always want to be a competent developer than now, so she is coding today as well. And that her effort are contributing to the team.

#### [Chris Yang](https://github.com/ysm0622) - Founder/Lead &nbsp;  [![GITHUB](./projects/img/git.png)](https://github.com/ysm0622) &nbsp; [![LINK](./projects/img/link.png)](https://ysm0622.github.io/cv)

<img align="left" width="40" height="40" src="https://avatars1.githubusercontent.com/u/18487241?v=3&s=460">

Chris is a Software Engineer, UI Designer, and author of many technical books & tutorials. He oversees the project direction, maintenance and organizes the planning and development efforts of the team.

#### [Martin Kim](https://github.com/skins346) - Founder/Lead &nbsp;  [![GITHUB](./projects/img/git.png)](https://github.com/skins346) &nbsp; [![LINK](./projects/img/link.png)](#)

<img align="left" width="40" height="40" src="https://avatars2.githubusercontent.com/u/18107262?v=3&s=460">

Martin is a Software Engineer, UI Designer, and author of many technical books & tutorials. He oversees the project direction, maintenance and organizes the planning and development efforts of the team.

## License
* This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.<br>
