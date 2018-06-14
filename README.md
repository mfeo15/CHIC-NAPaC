
<p align="center">
  <img src="http://oi63.tinypic.com/35ldrtz.jpg width="450" alt="Toygether logo" align="top" />
</p>


## Abstract

In team composed of a business school student, two designers and three engineers, the goal of CHIC (China Hardware Innovation Camp) is to develop a connected device in relation to the “Urban communities” theme, given to us at the beginning of an ideation process (September 2017). After developing multiple prototyping iterations during the semester, the manufacturing will be finalized during a fieldwork experience in Mainland China within local electronic factories.

Our product, named Toygether, is a connected plush toy that enables children to play with their parents, even when far away. The plush toy is screen-less and the electronics are hidden, allowing the parents to stay in contact with their kids, without having to rely on too present screens.

## Repo structure

The repo hosts the end result of the semester project of developping in such CHIC 2018 context. The different files are organized like the tree-structure illustrated below. The three main folders, `Project`, `Report` and `SHS` separate the different contents we worked on. In the `Project` directory, the Firmaware, PCB and Software development has been hosted. On the other hand, the documentation of the project is provided in a group report. Lastly, as part of the Minor STAS that provides the CHIC experience, the `SHS` directory (Social and Human Sciences) provides an anthropological research conduced on the distant-communication topic within the Chinese context and the left-behind children phenomenon.

```
.
├── Project
|   |
|   ├── Firmware
|   |   └── NAPaC_FW
|   |
|   ├── PCB
|   |
|   └── Software
|       |
|       ├── Android
|       |    ├── BasicClient
|       |    ├── SwissKnife
|       |    └── Toygether
|       |
|       └── Server
|
├── Report
|
└── SHS
    ├── Pre-processing
    └── Report
```

## Mainly develped with 

* [Altium Designer](https://www.altium.com/altium-designer/) - PCB design software
* [Android Studio](https://developer.android.com/studio/index.html) - IDE for Android app
* [Arduino IDE](https://www.arduino.cc/en/main/software) - IDE microcontroller ESP32

## Languages and libraries

* [C++ Arduino](https://www.arduino.cc/reference/en/) : ESP32 firmware
* [Kotlin](https://kotlinlang.org/) : Android App
* [Python](https://www.python.org/) : TCP Server
* [Java](https://www.java.com/en/) : Android App (in support to the main code in Kotlin)

## Authors
<img src="http://oi65.tinypic.com/2rw3go4.jpg" width="250" alt="NAPaC-Team" align="right" />

Collaborated on the different aspects of the project:

* **Marjane Amara** *(ECAL)* 
* **Chloe Dickson** *(EPFL)*
* **Estelle Geneux** *(UNIL-HEC)*
* **Matteo Yann Feo** *(EPFL)*
* **Simone Sanso** *(EPFL)*
* **Luca Sassoli de Bianchi** *(ECAL)* 

## External references

You can find out more about our team, our story and the whole CHIC program by checkoing out the following links:

* [Team landing-page](https://chi.camp/projects/napac/) : Everything you need to know about us and about our journey
* [CHIC](https://chi.camp/program/) : About the project and the program it offers
